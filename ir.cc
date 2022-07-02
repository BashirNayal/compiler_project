
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
#include <llvm/Support/SourceMgr.h>
#include <llvm/IRReader/IRReader.h>
#include <fstream>
#include "llvm/IR/LegacyPassManager.h"


#include "boundscheck.h"


static std::unique_ptr<llvm::LLVMContext> context;
static std::unique_ptr<llvm::IRBuilder<>> builder;
static std::unique_ptr<llvm::Module> module;

std::map<std::string, llvm::Value *> named_values;
std::map<std::string, bool> named_val_is_array;

static llvm::StructType *timeval_struct;

void run_passes(bool bc, bool bce) {
  if(bc) {
    do_bounds_check(*module);
  }

  get_object_file("temporary_ir");
  // -sccp 
  system("opt-14 -sccp -mem2reg -licm -sccp temporary_ir.ll -S -o temporary_ir.ll");
  
  llvm::SMDiagnostic err;
  module = llvm::parseIRFile("temporary_ir.ll", err, *context);
  system("unlink temporary_ir.ll");
  if (!module) {
    log("Encountered an error while reading temporary_ir.ll");
    exit(0);
  }


  if (bce) {

    do_bounds_check_elim(*module);
  }
}

void get_object_file(std::string program_name) {

  auto target_triple = llvm::sys::getDefaultTargetTriple();
  std::ofstream myfile;
  std::string ir_str;

  myfile.open (program_name + ".ll");
  llvm::raw_string_ostream output(ir_str);
  module->print(output, nullptr);
  myfile << ir_str;
  myfile.close();
  return;
}

void declare_printf() {
  std::vector<llvm::Type *> Ints(1,llvm::Type::getInt8PtrTy(*context));

  llvm::FunctionType *PT =
      llvm::FunctionType::get(llvm::Type::getInt32Ty(*context), Ints, true);

  llvm::Function *F =
      llvm::Function::Create(PT, llvm::Function::ExternalLinkage, "printf", module.get());
}
void declare_exit() {
  std::vector<llvm::Type *> Ints(1,llvm::Type::getInt32Ty(*context));

  llvm::FunctionType *PT =
      llvm::FunctionType::get(llvm::Type::getVoidTy(*context), Ints, false);

  llvm::Function *F =
      llvm::Function::Create(PT, llvm::Function::ExternalLinkage, "exit", module.get());

}
void declare_memcpy() {
  std::vector<llvm::Type *> memcpy_arg_type;
  memcpy_arg_type.push_back(llvm::PointerType::getInt32PtrTy(*context));
  memcpy_arg_type.push_back(llvm::PointerType::getInt32PtrTy(*context));
  memcpy_arg_type.push_back(llvm::Type::getInt32Ty(*context));
  llvm::Type *memcpy_ret_type = llvm::Type::getInt64PtrTy(*context); 
  llvm::FunctionType *memcpy_type = 
    llvm::FunctionType::get(memcpy_ret_type, memcpy_arg_type,false);

  llvm::Function::Create(memcpy_type, llvm::Function::ExternalLinkage, "memcpy", module.get());
}

void declare_gettimeofday() {
    std::vector<llvm::Type *> timeval_elm_types(2,llvm::Type::getInt64Ty(*context));
  
 timeval_struct = llvm::StructType::create(*context, timeval_elm_types, "struct.timeval");
  


  std::vector<llvm::Type*> gettimeofday_arg_type;
  gettimeofday_arg_type.push_back(llvm::PointerType::get(timeval_struct,0));
  gettimeofday_arg_type.push_back(llvm::Type::getInt8PtrTy(*context));

  llvm::FunctionType *gettimeofday_type = 
    llvm::FunctionType::get(llvm::Type::getInt32Ty(*context), gettimeofday_arg_type,false);

  llvm::Function::Create(gettimeofday_type, llvm::Function::ExternalLinkage, "gettimeofday", module.get());
}

void define_get_time() {
  std::vector<llvm::Type *> Ints(1,llvm::Type::getInt8PtrTy(*context));

  llvm::FunctionType *PT =
      llvm::FunctionType::get(llvm::Type::getInt32Ty(*context), false);

  llvm::Function *F =
      llvm::Function::Create(PT, llvm::Function::ExternalLinkage, "get_time", module.get());
  



  llvm::BasicBlock *BB = llvm::BasicBlock::Create(*context, "entry", F);
  builder->SetInsertPoint(BB);
  llvm::Value *timeval_ir = builder->CreateAlloca(timeval_struct,nullptr,"");
  std::vector<llvm::Value*> call_args;
  call_args.push_back(timeval_ir);
  call_args.push_back(llvm::Constant::getNullValue(llvm::PointerType::getInt8PtrTy(*context)));
  llvm::Value *gettimeofday_ret_val = builder->CreateCall(module->getFunction("gettimeofday"), call_args);

  llvm::Value *zero = llvm::Constant::getNullValue(llvm::IntegerType::getInt32Ty(*context));
  llvm::Value *one = llvm::ConstantInt::get(llvm::IntegerType::getInt32Ty(*context), 1);
  llvm::Value *zero_zero[] = {zero, zero};
  llvm::Value *zero_one[] = {zero, one};


  llvm::Value *first_member = builder->CreateGEP(timeval_struct,timeval_ir,zero_zero, "strct.first");
  llvm::Value *second_member = builder->CreateGEP(timeval_struct,timeval_ir,zero_one, "strct.second");
  llvm::Value *second_member_value = 
    builder->CreateLoad(llvm::IntegerType::getInt64Ty(*context),second_member);
  llvm::Value *casted_second_member_val = builder->CreateCast(
    llvm::Instruction::CastOps::Trunc, second_member_value, llvm::IntegerType::getInt32Ty(*context));
 
  builder->CreateRet(casted_second_member_val); 


  
}

void define_check_bounds() {
    std::vector<llvm::Type *> param_types;
    param_types.push_back(llvm::Type::getInt32Ty(*context));
    param_types.push_back(llvm::Type::getInt32Ty(*context));

  llvm::FunctionType *PT =
      llvm::FunctionType::get(llvm::Type::getVoidTy(*context), param_types, false);

  llvm::Function *F =
      llvm::Function::Create(PT, llvm::Function::ExternalLinkage, "__check_bounds__", module.get());
  



  llvm::BasicBlock *entry_block = llvm::BasicBlock::Create(*context, "entry", F);
  llvm::BasicBlock *true_block = llvm::BasicBlock::Create(*context, "memory_err", F);
  llvm::BasicBlock *false_block = llvm::BasicBlock::Create(*context, "memory_ok", F);
  
  builder->SetInsertPoint(entry_block);

  llvm::Value *cmp_inst = 
   builder->CreateCmp(llvm::CmpInst::Predicate::ICMP_SGE, F->getArg(0), F->getArg(1));
  builder->CreateCondBr(cmp_inst, true_block, false_block);
  builder->SetInsertPoint(true_block);

  llvm::Type *byte_type = llvm::Type::getInt8Ty(*context);
  std::string string = "error: memory violation\n";
  llvm::ArrayType *string_type = llvm::ArrayType::get(byte_type, (uint64_t)string.size() + 1);
  llvm::Constant *str_ir_value = llvm::ConstantDataArray::getString(*context, string, true);
  llvm::GlobalVariable *str_ir =
     new llvm::GlobalVariable(*module, string_type,
                        true, llvm::GlobalVariable::WeakAnyLinkage ,str_ir_value, "");
  str_ir->setUnnamedAddr(llvm::GlobalValue::UnnamedAddr::Global);
    

  llvm::Value* zero = llvm::Constant::getNullValue(llvm::IntegerType::getInt32Ty(*context));
  llvm::Value* indices[] = {zero, zero};
  llvm::Value *GEP = llvm::GetElementPtrInst::Create(
    string_type,str_ir, indices,"",builder->GetInsertBlock());

  builder->CreateCall(module->getFunction("printf"), GEP);
  
  builder->CreateCall(
    module->getFunction("exit"), llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 1));
  builder->CreateRetVoid();

  builder->SetInsertPoint(false_block);
  builder->CreateRetVoid();

 

}

void init_module() {
  context = std::make_unique<llvm::LLVMContext>();
  module = std::make_unique<llvm::Module>("comp", *context);
  builder = std::make_unique<llvm::IRBuilder<>>(*context);

  declare_printf();
  declare_exit();
  declare_memcpy();
  declare_gettimeofday();
  define_get_time();
  define_check_bounds();

}

llvm::Value *String::codegen() {
  llvm::Type *byte_type = llvm::Type::getInt8Ty(*context);
  // string.find("\n"
  llvm::ArrayType *string_type = llvm::ArrayType::get(byte_type, (uint64_t)string.size() + 1);
  llvm::Constant *str_ir_value = llvm::ConstantDataArray::getString(*context, string, true);
  llvm::GlobalVariable *str_ir =
     new llvm::GlobalVariable(*module, string_type,
                        true, llvm::GlobalVariable::WeakAnyLinkage ,str_ir_value, "");
  str_ir->setUnnamedAddr(llvm::GlobalValue::UnnamedAddr::Global);

  llvm::Value* zero = llvm::Constant::getNullValue(llvm::IntegerType::getInt32Ty(*context));
  llvm::Value* indices[] = {zero, zero};
  llvm::Value *GEP = llvm::GetElementPtrInst::Create(
    string_type,str_ir, indices,"",builder->GetInsertBlock());

  return GEP;
}


llvm::Value *Operator::codegen() {
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
      log(*inst);
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
  if (def) {
    llvm::Value *AI = builder->CreateAlloca(llvm::Type::getInt32Ty(*context),nullptr, var_name);
    named_values[var_name] = AI;
    named_val_is_array[var_name] = false;
  }
  builder->CreateStore(value->codegen(), named_values[var_name]);
  
  return nullptr;
}

llvm:: Value *VarUse::codegen() {
  if (named_val_is_array[var_name] == true) {
    return named_values[var_name];

  }
  return builder->CreateLoad(llvm::Type::getInt32Ty(*context),named_values[var_name]);
}

llvm::Value *Return::codegen() {
  if (value) {
    llvm::Value *ret_val = value->codegen();
    builder->CreateRet(ret_val);
  }
  else {
    builder->CreateRetVoid();
  }
  return nullptr;

}
llvm::Value *Const::codegen() {
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
  for (int i = 0; i < expressions.size(); i++) {
    Expression *exp = expressions.at(i).get();
    exp->codegen();
  }
  return nullptr;
}
llvm::Value *If::codegen() {
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
  log("ERROR: 'else if' is not supported");
  return nullptr;
}

llvm::Value *While::codegen() {
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
  return nullptr;
}

llvm::Value *CallExpression::codegen() {
  std::vector<llvm::Value*> args_ir;
  for (int i = 0; i < args.size(); i++) {
    args_ir.push_back(args.at(i)->codegen());
  }
  return builder->CreateCall(module->getFunction(callee), args_ir, "");
}
llvm::Value *Array::codegen() {
  llvm::Value *ir_size = size->codegen();
  llvm::Value * AI = builder->CreateAlloca(llvm::Type::getInt32Ty(*context), ir_size, name);
  named_values[name] = AI;
  named_val_is_array[name] = true;

  if (initial_values.size() == 0) {
    return AI; 
  }

  std::vector<llvm::Constant *> ir_init_values;
  for (int i = 0; i < initial_values.size(); i++) {
    llvm::IntegerType *int_type = llvm::Type::getInt32Ty(*context);
    llvm::Constant *constant = 
      llvm::ConstantInt::get(int_type,dynamic_cast<Const*>(initial_values.at(i).get())->get_val());
    ir_init_values.push_back(constant);
  }

  for(int i = 0; i < ir_init_values.size(); i++) {

    llvm::Value *ir_index = llvm::ConstantInt::get(llvm::IntegerType::getInt32Ty(*context), i);
    llvm::Value* zero = llvm::Constant::getNullValue(llvm::IntegerType::getInt32Ty(*context));
    llvm::Value* indices[] = {ir_index, zero};
    llvm::Value *GEP =
      builder->CreateGEP(named_values[name]->getType()->getPointerElementType(), named_values[name], ir_index, "");

    llvm::Value *ir_value = ir_init_values.at(i);
    builder->CreateStore(ir_value, GEP);
  }

  return AI;
}
llvm::Value *ArrayRef::codegen() {

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

  llvm::Function *fun = module->getFunction(Proto->get_name());

  if (Proto->get_name() == "main") {


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
    llvm::Value *AI = builder->CreateAlloca(llvm::Type::getInt32Ty(*context),nullptr, Arg.getName() + ".");
    llvm::Value *SI = builder->CreateStore(&Arg, AI);
    named_values[std::string(Arg.getName())] = AI;
  }
  Body->codegen();
  if (verifyFunction(*fun) || true) {
    return fun;
  }
  else {
    log("ERROR: failed to generate function IR for " <<  Proto->get_name());
    fun->eraseFromParent();
    return nullptr;
  }
  return nullptr;
    
}