
#include "ir.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/PrintPasses.h"


#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

#include <fstream>
#include "llvm/IR/LegacyPassManager.h"

static std::unique_ptr<llvm::LLVMContext> context;
static std::unique_ptr<llvm::IRBuilder<>> builder;
static std::unique_ptr<llvm::Module> module;

std::map<std::string, llvm::Value *> named_values;
std::map<std::string, bool> named_val_is_array;

void get_object_file(std::string program_name) {

  log("creating object file");
  auto target_triple = llvm::sys::getDefaultTargetTriple();
  std::ofstream myfile;
  std::string ir_str;

  myfile.open (program_name + ".ll");
  llvm::raw_string_ostream output(ir_str);
  module->print(output, nullptr);
  // for(int i = 0; i < ir_str.size(); i++) {
  //   if (ir_str.at(i) == '\\' && ir_str.at(i) == '\\') {
  //     ir_str.erase(i, 1);
  //     break;
  //   }
  // }
  // log("program:");
  // log(ir_str);
  myfile << ir_str;
  myfile.close();
  return;
}


void init_module() {
  // Open a new context and module.
  context = std::make_unique<llvm::LLVMContext>();
  module = std::make_unique<llvm::Module>("comp", *context);

  // Create a new builder for the module.
  builder = std::make_unique<llvm::IRBuilder<>>(*context);


  std::vector<llvm::Type *> Ints(1,llvm::Type::getInt8PtrTy(*context));

  llvm::FunctionType *PT =
      llvm::FunctionType::get(llvm::Type::getInt32Ty(*context), Ints, true);

  llvm::Function *F =
      llvm::Function::Create(PT, llvm::Function::ExternalLinkage, "printf", module.get());

// std::vector<llvm::Type *> test(3, , llvm::PointerType::getInt32PtrTy(*context), llvm::Type::getInt32Ty(*context)); 
std::vector<llvm::Type *> memcpy_arg_type;
memcpy_arg_type.push_back(llvm::PointerType::getInt32PtrTy(*context));
memcpy_arg_type.push_back(llvm::PointerType::getInt32PtrTy(*context));
memcpy_arg_type.push_back(llvm::Type::getInt32Ty(*context));
 llvm::Type *memcpy_ret_type = llvm::Type::getInt64PtrTy(*context); 
  llvm::FunctionType *memcpy_type = 
    llvm::FunctionType::get(memcpy_ret_type, memcpy_arg_type,false);

      llvm::Function::Create(memcpy_type, llvm::Function::ExternalLinkage, "memcpy", module.get());

  log("module initialized");
}

llvm::Value *String::codegen() {
  log("codegen string");
  llvm::Type *byte_type = llvm::Type::getInt8Ty(*context);
  // string.find("\n"
  llvm::ArrayType *string_type = llvm::ArrayType::get(byte_type, (uint64_t)string.size() + 1);
  llvm::Constant *str_ir_value = llvm::ConstantDataArray::getString(*context, string, true);
  llvm::GlobalVariable *str_ir =
     new llvm::GlobalVariable(*module, string_type,
                        true, llvm::GlobalVariable::WeakAnyLinkage ,str_ir_value, "");
  str_ir->setUnnamedAddr(llvm::GlobalValue::UnnamedAddr::Global);
  // str_ir->
  // str_ir->setLinkage(llvm::GlobalValue::);
  // str_ir->setAlignment(llvm::MaybeAlign::;

  llvm::Value* zero = llvm::Constant::getNullValue(llvm::IntegerType::getInt32Ty(*context));
  llvm::Value* indices[] = {zero, zero};
  llvm::Value *GEP = llvm::GetElementPtrInst::Create(
    string_type,str_ir, indices,"",builder->GetInsertBlock());
  log(*GEP);
  log(*module);
  return GEP;
    
  // llvm::GetElementPtrInst::Create(
  //   llvm::Type::getInt8PtrTy(*context),str_ir_value,indices,"",builder->GetInsertBlock());
  // llvm::Constant* strVal = llvm::ConstantExpr::getGetElementPtr(llvm::Type::getInt8PtrTy(*context),str_ir,indices,true);
  // return builder->CreateGEP(llvm::Type::getInt8PtrTy(*context),str_ir, zero, "");
  // log(*strVal);
  // exit(0);
  // return strVal;

  
}


llvm::Value *Operator::codegen() {
  log("codegen operator");
  llvm::Value *lhs_ir = lhs->codegen();
  llvm::Value *rhs_ir = rhs->codegen();
  llvm::IntegerType *int_type = llvm::Type::getInt32Ty(*context);
  llvm::BasicBlock *current_bb = builder->GetInsertBlock();
  llvm::Value *inst;
  switch (op) {
    case PLUS_t:
      inst = llvm::BinaryOperator::CreateAdd(lhs_ir, rhs_ir, "");
      break;
    case MUL_t:
      inst = llvm::BinaryOperator::CreateMul(lhs_ir, rhs_ir, "");
      break;
    case DIV_t: 
      inst = llvm::BinaryOperator::CreateSDiv(lhs_ir, rhs_ir, "");
      break;
    case MIN_t: 
      inst = llvm::BinaryOperator::CreateSub(lhs_ir, rhs_ir, "");
      break;
    case AND_t: 
      inst = llvm::BinaryOperator::CreateAnd(lhs_ir, rhs_ir, "");
      break;
    case XOR_t: 
      inst = llvm::BinaryOperator::CreateXor(lhs_ir, rhs_ir, "");
      break;
    case MOD_t: 
      inst = llvm::BinaryOperator::CreateSRem(lhs_ir, rhs_ir, "");
      break;
    case GT_t:
      return llvm::CmpInst::Create(llvm::Instruction::OtherOps::ICmp, 
        llvm::CmpInst::Predicate::ICMP_SGT,
        lhs_ir, rhs_ir, "", current_bb);
    case LT_t:
      return llvm::CmpInst::Create(llvm::Instruction::OtherOps::ICmp, 
        llvm::CmpInst::Predicate::ICMP_SLT,
        lhs_ir, rhs_ir, "", current_bb);
    case EQ_t:
      return llvm::CmpInst::Create(llvm::Instruction::OtherOps::ICmp, 
        llvm::CmpInst::Predicate::ICMP_EQ,
        lhs_ir, rhs_ir, "", current_bb);
    case NE_t:
      return llvm::CmpInst::Create(llvm::Instruction::OtherOps::ICmp, 
        llvm::CmpInst::Predicate::ICMP_NE,
        lhs_ir, rhs_ir, "", current_bb);
    case GE_t:
      return llvm::CmpInst::Create(llvm::Instruction::OtherOps::ICmp, 
        llvm::CmpInst::Predicate::ICMP_SGE,
        lhs_ir, rhs_ir, "", current_bb);
    case LE_t:
      return llvm::CmpInst::Create(llvm::Instruction::OtherOps::ICmp, 
        llvm::CmpInst::Predicate::ICMP_SLE,
        lhs_ir, rhs_ir, "", current_bb);
    case OR_t: {
      llvm::Value *or_inst = llvm::BinaryOperator::CreateOr(lhs_ir, rhs_ir, "");
      builder->Insert(or_inst);
      return or_inst;
    }
    default:
      break;
  }
  builder->Insert(inst);
  return inst;
}

llvm::Value *Assignment::codegen() {
  printf("codegen assignment\n");
  if (def) {
    llvm::Value *AI = builder->CreateAlloca(llvm::Type::getInt32Ty(*context),nullptr, var_name);
    named_values[var_name] = AI;
    named_val_is_array[var_name] = false;
    log(*AI);
  }
  builder->CreateStore(value->codegen(), named_values[var_name]);
  
  return nullptr;
}

llvm:: Value *VarUse::codegen() {
  log("codegen varuse");
  // if (named_values[var_name]
  if (named_val_is_array[var_name] == true) {
    log("var use for arr ptr");
    log(*named_values[var_name]);
    return named_values[var_name];

  }
  return builder->CreateLoad(llvm::Type::getInt32Ty(*context),named_values[var_name]);
}

llvm::Value *Return::codegen() {
  if (value) {
    llvm::Value *ret_val = value->codegen();
    log((*ret_val));
    //TODO: this assumes int
    builder->CreateRet(ret_val);
  }
  else {

    builder->CreateRetVoid();
  }
  return nullptr;

}
llvm::Value *Const::codegen() {
  log("codegen const");
  llvm::IntegerType *int_type = llvm::Type::getInt32Ty(*context);
  llvm::Value *constant = llvm::ConstantInt::get(int_type, val);
  return constant;
}

llvm::Function *PrototypeAST::codegen() {
    // Make the function type:  double(double,double) etc.
  std::vector<llvm::Type *> Ints(parameters.size(),llvm::Type::getInt32Ty(*context));

  llvm::FunctionType *IT =
      llvm::FunctionType::get(llvm::Type::getInt32Ty(*context), Ints, false);

  llvm::Function *F =
      llvm::Function::Create(IT, llvm::Function::ExternalLinkage, fun_name, module.get());

  // Set names for all arguments.
  unsigned Idx = 0;
  for (auto &Arg : F->args())
    Arg.setName(parameters.at(Idx++)->get_name());

  return F;
}

llvm::Value *Block::codegen() {
  log("codegen block");
  for (int i = 0; i < expressions.size(); i++) {
    Expression *exp = expressions.at(i).get();
    exp->codegen();
  }
  return nullptr;
}
llvm::Value *If::codegen() {
  log("codegen if");
  llvm::Value *if_cond_ir = cond->codegen();
  llvm::BasicBlock *current_block = builder->GetInsertBlock();
  llvm::StringRef prefix = current_block->getName();
  llvm::Function *current_function = builder->GetInsertBlock()->getParent();
  llvm::BasicBlock *if_start_block = llvm::BasicBlock::Create(*context, prefix + ".if", current_function);
  llvm::BasicBlock *else_start_block = nullptr;
  if (else_body) {
    else_start_block = llvm::BasicBlock::Create(*context, prefix + ".else", current_function);
  }
  llvm::BasicBlock *if_end_block = llvm::BasicBlock::Create(*context, prefix + ".endif", current_function);
  
  if (else_start_block) {
    builder->CreateCondBr(if_cond_ir, if_start_block, else_start_block);
  }
  else {
    builder->CreateCondBr(if_cond_ir, if_start_block, if_end_block);
  }

  //populate the if body
  builder->SetInsertPoint(if_start_block);

  body->codegen(); 
  builder->CreateBr(if_end_block);
  if (else_start_block) {
      builder->SetInsertPoint(else_start_block);
      else_body->codegen(); 
      builder->CreateBr(if_end_block);
  }
  builder->SetInsertPoint(if_end_block);
  return nullptr;
}
llvm::Value * Elif::codegen() {
  log("codegen elif");
  return nullptr;
}

llvm::Value *While::codegen() {
  log("codegen while");
  llvm::BasicBlock *current_block = builder->GetInsertBlock();
  llvm::StringRef prefix = current_block->getName();
  llvm::Function *current_function = builder->GetInsertBlock()->getParent();
  llvm::BasicBlock *while_cond_block = llvm::BasicBlock::Create(*context, prefix + ".while.cond", current_function);
  llvm::BasicBlock *while_start_block = llvm::BasicBlock::Create(*context, prefix + ".while.start", current_function);
  llvm::BasicBlock *while_end_block = llvm::BasicBlock::Create(*context, prefix + ".while.end", current_function);
  
  builder->CreateBr(while_cond_block);
  builder->SetInsertPoint(while_cond_block);
  llvm::Value *while_cond_ir = cond->codegen();
  builder->CreateCondBr(while_cond_ir, while_start_block, while_end_block);
  builder->SetInsertPoint(while_start_block);
  body->codegen();
  builder->CreateBr(while_cond_block);
  builder->SetInsertPoint(while_end_block);


}

llvm::Value *CallExpression::codegen() {
  log("codegen call");
  std::vector<llvm::Value*> args_ir;
  for (int i = 0; i < args.size(); i++) {
    args_ir.push_back(args.at(i)->codegen());
  }
  log("before the crash");
  return builder->CreateCall(module->getFunction(callee), args_ir, "");
}
llvm::Value *Array::codegen() {
  log("codegen array");
  llvm::Value *ir_size = size->codegen();
  if (initial_values.size() == 0) {
    llvm::Value * AI = builder->CreateAlloca(llvm::Type::getInt32Ty(*context), ir_size, name);
    named_values[name] = AI;
    named_val_is_array[name] = true;
    return AI; 
  }
  std::vector<llvm::Constant *> ir_init_values;
  for (int i = 0; i < initial_values.size(); i++) {
    llvm::IntegerType *int_type = llvm::Type::getInt32Ty(*context);
    llvm::Constant *constant = 
      llvm::ConstantInt::get(int_type,dynamic_cast<Const*>(initial_values.at(i).get())->get_val());
    ir_init_values.push_back(constant);
  }
  llvm::Constant *init = llvm::ConstantArray::get(llvm::ArrayType::get(llvm::Type::getInt32Ty(*context),ir_init_values.size()), ir_init_values);
  log(*init);
  
  // exit(0);
}
llvm::Value *ArrayRef::codegen() {
  log("codegen arrayref");

  llvm::Value *ir_index = index->codegen();
  llvm::Value* zero = llvm::Constant::getNullValue(llvm::IntegerType::getInt32Ty(*context));
  llvm::Value* indices[] = {ir_index, zero};
  llvm::Value *GEP =
   builder->CreateGEP(named_values[name]->getType()->getPointerElementType(), named_values[name], ir_index, "");
  if (!value) {
    return builder->CreateLoad(llvm::IntegerType::getInt32Ty(*context), GEP);
  }
  else {
    llvm::Value *ir_value = value->codegen();
    return builder->CreateStore(ir_value, GEP);
  }
}

llvm::Function *FunctionAST::codegen() {
  log("codegen fun");

  llvm::Function *fun = module->getFunction(Proto->get_name());

  if (Proto->get_name() == "main") {
    log("codegen for main");


        // Make the function type:  double(double,double) etc.
    std::vector<llvm::Type *> main_args_type;
    main_args_type.push_back(llvm::Type::getInt32Ty(*context));
    llvm::Type *byte_ptr_type = llvm::Type::getInt8PtrTy(*context);
    main_args_type.push_back(llvm::PointerType::get(byte_ptr_type ,0));
    llvm::FunctionType *IT =
        llvm::FunctionType::get(llvm::Type::getInt32Ty(*context), main_args_type, false);

    llvm::Function *F =
        llvm::Function::Create(IT, llvm::Function::ExternalLinkage, Proto->get_name(), module.get());
    F->getArg(0)->setName("argc");
    F->getArg(1)->setName("argv");
    fun = F;
  }



  if (!fun)
    fun = Proto->codegen();

  if (!fun)
    return nullptr;
  // Create a new basic block to start insertion into.
  llvm::BasicBlock *BB = llvm::BasicBlock::Create(*context, "entry", fun);
  builder->SetInsertPoint(BB);


  // Record the function arguments in the NamedValues map.
  named_values.clear();
  for (auto &Arg : fun->args()) {
    if (fun->getName() == "main") break;
    //TODO: here
    llvm::Value *AI = builder->CreateAlloca(llvm::Type::getInt32Ty(*context),nullptr, Arg.getName() + ".");
    llvm::Value *SI = builder->CreateStore(&Arg, AI);
    named_values[std::string(Arg.getName())] = AI;
  }
  Body->codegen();
  if (verifyFunction(*fun) || true) {
    // log(*module);
    return fun;
  }
  else {
    // log(*module);
    log("ERROR: failed to generate function IR for " <<  Proto->get_name());
    fun->eraseFromParent();
    return nullptr;
  }
  return nullptr;
    
}