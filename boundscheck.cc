#define DEBUG_TYPE "BoundChecker"
#include "llvm.h"
#include "common.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/IRBuilder.h"

llvm::Function *checkBoundsFn;

std::pair<llvm::Value *, llvm::Value *>  getSizeAndAbsIndex(llvm::Value &V,
                                        llvm::Value &index,
                                        llvm::GetElementPtrInst *GEP);
bool instrumentAllocations(llvm::Function &F);
llvm::Type *Int32Ty;
llvm::SmallDenseMap<llvm::Function *, llvm::SmallDenseMap<int,int>> argMap;
llvm::SmallVector<llvm::Function*, 128> fnToDel;

bool shouldInstrument(llvm::Function *F) {
    if (F->isDeclaration()) {
        return false;
    }
    if (F->getName().startswith("__check") ||
        F->getName().startswith("get_time")) {
        return false;
    }
    return true;
}



// returns size and absolute index
std::pair<llvm::Value *, llvm::Value *>  getSizeAndAbsIndex(llvm::Value &V, 
                                                   llvm::Value &index,
                                                   llvm::GetElementPtrInst *GEP) {
    // if the array comes from an allocation
    if (llvm::AllocaInst *AI = llvm::dyn_cast<llvm::AllocaInst>(&V)) {
        return std::pair<llvm::Value*, llvm::Value*>(AI->getArraySize(), &index);
    }
    // if the array comes from an argument
    else if (llvm::Argument *ARG = llvm::dyn_cast<llvm::Argument>(&V)) {
        // get the function of the current arugment
        llvm::Function *fn = llvm::dyn_cast<llvm::Function>(ARG->getParent());
        if (!fn) {
            llvm::BasicBlock *BB = llvm::dyn_cast<llvm::BasicBlock>(ARG->getParent());
            if (BB) {
                fn = llvm::dyn_cast<llvm::Function>(BB->getParent());
            }
        } 
        if (!fn) {
            log("Error: Instruction not in a function?");
            return std::pair<llvm::Value*, llvm::Value*>(nullptr,nullptr);
        }
        // a special case for main since argc is the size of argv
        if (fn->getName() == "main") {
            return std::pair<llvm::Value*, llvm::Value*>(fn->getArg(0),&index);
        }
        // consult the argMap to get the size of the array in
        // the argument list
        llvm::ConstantInt *argIndex = llvm::dyn_cast<llvm::ConstantInt>(&index); 
        if (argIndex) {
            if (argMap.count(fn) != 0) {
                int i = 0;
                for (auto &arg : fn->args()) {
                    if (&arg == ARG) {
                        break;
                    }
                    i++;
                }
                int sizeIndex = argMap.lookup(fn).lookup(i);
                int j = 0;
                for (auto &arg : fn->args()) {
                    if (j == sizeIndex) { 
                        return std::pair<llvm::Value*, llvm::Value*>(&arg,&index);
                    }
                    j++;
                }
            }
        }
    }
    // if the array comes from a phi node
    else if (llvm::PHINode *phi = llvm::dyn_cast<llvm::PHINode>(&V)) {
        // create a phi node to store the size of the array
        llvm::PHINode *newPI =
            llvm::PHINode::Create(Int32Ty, phi->getNumOperands(), 
                            phi->getName() + ".size", 
                            phi);
        // add the possible size of each phi operand
        for (int i = 0; i < (int)phi->getNumOperands(); i++) {
            // a special case when phi refrences itself
            if (llvm::dyn_cast<llvm::PHINode>(phi->getOperand(i)) && 
                                  phi == phi->getOperand(i)) {
                newPI->addIncoming(newPI, phi->getIncomingBlock(i));
            }
            else {
                newPI->addIncoming(getSizeAndAbsIndex(*phi->getOperand(i), index, GEP).first, 
                                   phi->getIncomingBlock(i));                      
            }
        }
        return std::pair<llvm::Value*,llvm::Value*>(newPI, &index);
    }
    // if the array comes from another GEP instruction
    else if (llvm::GetElementPtrInst *prev_GEP = llvm::dyn_cast<llvm::GetElementPtrInst>(&V)) {
        // if the GEP references a constant
        if (prev_GEP->getNumOperands() > 2) { 
            if (llvm::Constant *constantVal = llvm::dyn_cast<llvm::Constant>(prev_GEP->getOperand(0))) {
                if (llvm::ConstantDataArray *constantArray = 
                    llvm::dyn_cast<llvm::ConstantDataArray>(constantVal->getOperand(0))) {
                    return std::pair<llvm::Value*, llvm::Value*> (llvm::ConstantInt::get(Int32Ty, 
                                                     constantArray->getNumElements()),
                                                     &index);
                }  
            }
        }
        else {
            std::pair<llvm::Value*, llvm::Value*>res;
            res = getSizeAndAbsIndex(*prev_GEP->getOperand(0), 
                                     *prev_GEP->getOperand(1), 
                                     GEP);
            // the offset of the current GEP
            llvm::ConstantInt *lhs = llvm::dyn_cast<llvm::ConstantInt>(&index);
            // the offset of the previous GEP
            llvm::ConstantInt *rhs = llvm::dyn_cast<llvm::ConstantInt>(res.second);
            llvm::Value *computedIndex;
            // compute the offset as a constant if both lhs and rhs are constants
            if (lhs && rhs) {
                computedIndex = 
                    llvm::ConstantInt::get(Int32Ty, 
                                     lhs->getSExtValue() + rhs->getSExtValue());
            }
            // compute the offset if at least lhs or rhs is not a constant
            else {
                computedIndex = llvm::BinaryOperator::CreateAdd(&index, res.second, "off.", GEP);
            }
            return std::pair<llvm::Value*, llvm::Value*>(res.first,computedIndex);
        }
    }
    // if the array comes from a load instruction
    else if (llvm::LoadInst *LI = llvm::dyn_cast<llvm::LoadInst>(&V)) {
        return getSizeAndAbsIndex(*LI->getOperand(0), index, GEP);
    }
    // return null if something goes wrong
    return std::pair<llvm::Value*,llvm::Value*>(nullptr,nullptr);
}

//Finds all allocations in a function and inserts a call that prints its size.
bool instrumentAllocations(llvm::Function &F) {
    bool Changed = false;
    llvm::SmallDenseMap<llvm::CallInst*, llvm::CallInst*> replaceCI;
    std::pair<llvm::Value *, llvm::Value *> sizeAndOffset;
    llvm::IRBuilder<> B(&F.getEntryBlock());
    
    llvm::Value *size;
    // // Iterate over all instructions in this function.
    for (llvm::inst_iterator II = inst_begin(F), E = inst_end(F); II != E; ++II) {
    //     // if the current instruction is a GEP instruction
        llvm::Instruction *I = &*II;
        if (llvm::GetElementPtrInst *GEP = llvm::dyn_cast<llvm::GetElementPtrInst>(I)) {
            B.SetInsertPoint(GEP);
            // GEPs with more than 2 arguments will be skipped
            if (GEP->getNumOperands() > 2) 
                continue;
            // extract the ptr and index from the GEP instruction
            llvm::Value *index = GEP->getOperand(1);
            llvm::Value *V = GEP->getOperand(0);
            // calculate the size and the absolute index of the array
            sizeAndOffset = getSizeAndAbsIndex(*V, *index, GEP);
            size = sizeAndOffset.first;
            index = sizeAndOffset.second;
            if (!size || !index) {
                log("Error: Couldn't get size or index");
                continue;
            }
            // add the bound check call
            B.CreateCall(checkBoundsFn, { index, size });
            Changed = true;
        }
        // if the current instruction is a call instruction
        else if (llvm::CallInst *CI = llvm::dyn_cast<llvm::CallInst>(I)) {
            llvm::Function *fn = llvm::dyn_cast<llvm::Function>(CI->getOperand(CI->getNumOperands() - 1));
            // check if this function has been instrumented
            if (argMap.count(fn) != 0) {
                llvm::SmallDenseMap<int,int>indexMap = argMap.lookup(fn);
                llvm::SmallVector<llvm::Value *, 0> operands;
                // add all the old operands to the vector operands
                for (int i = 0; i < (int)CI->getNumOperands() - 1; i++) {
                    operands.push_back(CI->getOperand(i));
                }
                // calculate the size and add them on top of the old operands
                for (auto indexPair : indexMap) {
                    llvm::Value *index = llvm::ConstantInt::get(Int32Ty,indexPair.first);
                    llvm::Value *sizeVal = 
                        getSizeAndAbsIndex(*operands[indexPair.first], 
                                           *index, 
                                           nullptr).first;
                    if (sizeVal) {
                        operands.push_back(sizeVal);
                    }
                }
                // replace the old call with the new one that has all the new operands
                llvm::CallInst *newCI = llvm::CallInst::Create(fn, operands);
                replaceCI.insert(std::pair<llvm::CallInst*,llvm::CallInst*>(CI,newCI));
                Changed = true;
            }
        }
        // log(*I);
    }
    for (auto CI : replaceCI) {
        // llvm::ReplaceInstWithInst(CI.first, CI.second);
    }
    return Changed;
}

bool do_bounds_check(llvm::Module &M) {
    llvm::LLVMContext &C = M.getContext();
    llvm::Type *VoidTy = llvm::Type::getVoidTy(C);
    Int32Ty = llvm::Type::getInt32Ty(C);
    auto FnCallee = M.getOrInsertFunction("__check_bounds__",
                                          VoidTy, Int32Ty, Int32Ty);
    checkBoundsFn = llvm::dyn_cast<llvm::Function>(FnCallee.getCallee());

    bool Changed = false;
    for (llvm::Function &F : M) {
        if (!shouldInstrument(&F)) {
            continue;
        }

        log("Visiting function for Bounds Checking: " << F.getName());
        Changed |= instrumentAllocations(F);
    }

    return Changed;
}









bool remove_redundant_bc(llvm::Function &F) {
    log("remove red check");
    for (llvm::inst_iterator II = inst_begin(F), E = inst_end(F); II != E; ++II) {
    llvm::Instruction *I = &*II;
        if (llvm::CallInst *CI = llvm::dyn_cast<llvm::CallInst>(I)) {
            if (CI->getCalledFunction()->getName() == "__check_bounds__") {
                auto CII = CI->arg_begin();
                llvm::Value *index = CII->get();
                CII++;
                llvm::Value *size = CII->get();
                log("index " << *index);
                log("size " << *size);
            }
            
        }
    }

}



bool do_bounds_check_elim(llvm::Module &M) {
    bool Changed = false;
    for (llvm::Function &F : M) {
        if (!shouldInstrument(&F)) {
            continue;
        }
        log("Visiting function for elimination of bounds-check: " << F.getName());
        Changed |= remove_redundant_bc(F); 
    }

    return Changed;
}
