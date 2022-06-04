
#include "ir.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/PrintPasses.h"




static std::unique_ptr<llvm::LLVMContext> context;
static std::unique_ptr<llvm::IRBuilder<>> builder;
static std::unique_ptr<llvm::Module> module;

std::map<std::string, llvm::Value *> named_values;

void init_module() {
  // Open a new context and module.
  context = std::make_unique<llvm::LLVMContext>();
  module = std::make_unique<llvm::Module>("comp", *context);

  // Create a new builder for the module.
  builder = std::make_unique<llvm::IRBuilder<>>(*context);
  log("initialized");
  log(*module);
}

llvm::Value *log_errorV(const char *str) {
  std::cout << "ERROR: " << str << std::endl;
  return nullptr;
}

void get_ir(std::unique_ptr<Expression> expr = nullptr) {
  printf("get_ir\n");
    if (expr) expr.get()->codegen();
    else {
      printf("generating IR\n");
      // llvm::ConstantFP *fp =  llvm::ConstantFP::get(context, llvm::APFloat(5.4));
      // module->print(llvm::errs(), nullptr);
    }
}

llvm::Value *Assignment::codegen() {
  printf("generating code for Assignment\n");
  // llvm::BasicBlock *block = llvm::BasicBlock::Create(*context,"entry");
  // builder->SetInsertPoint(block);
  // for (auto &I : *block) {
  //   log(I);
  //   log("loop");
  // }
  // log(*int_type);
  
  // llvm::IntegerType *int_type = llvm::Type::getInt32Ty(*context);
  // llvm::Value *zero = llvm::ConstantInt::get(int_type, 0);
  // builder.get()->CreateRet(zero);
  // // builder.get()->CreateRetVoid();
  // log(*zero);
  // builder.get()->CreateAlloca(int_type, zero, "test");
  // llvm::AllocaInst(int_type, 0, "test" , block);
  // llvm::ReturnInst(*context,*zero,*block);
  // llvm::AllocaInst(int_type,);
  log("before log");

  // log(*block);
  
  // builder.CreateAlloca(
  // module.get()->print();
  // llvm::PrintModulePass::PrintModulePass();
  // llvm::errs() << "test\n";
  // llvm::errs() << module.get() << "\n";
  log(*module);
  log("test");
  // llvm::errs() << llvm::BasicBlock::Create(context,"entry")->getName() << "\n";
  llvm::forcePrintModuleIR();
}

llvm::Value *Return::codegen() {
  if (value) {
    llvm::IntegerType *int_type = llvm::Type::getInt32Ty(*context);
    llvm::Value *ret_val = value.get()->codegen();
    log((*ret_val));
    //TODO: this assumes int
    builder.get()->CreateRet(ret_val);
  }
  else {

    builder.get()->CreateRetVoid();
  }

}
llvm::Value *Const::codegen() {
  log("codegen const");
  llvm::IntegerType *int_type = llvm::Type::getInt32Ty(*context);
  llvm::Value *constant = llvm::ConstantInt::get(int_type, val);
  return constant;
}

llvm::Function *PrototypeAST::codegen() {
    // Make the function type:  double(double,double) etc.
  std::vector<llvm::Type *> Doubles(parameters.size(), llvm::Type::getDoubleTy(*context));
  std::vector<llvm::Type *> Ints(parameters.size(),llvm::Type::getInt32Ty(*context));
  llvm::FunctionType *FT =
      llvm::FunctionType::get(llvm::Type::getDoubleTy(*context), Doubles, false);

  llvm::FunctionType *IT =
      llvm::FunctionType::get(llvm::Type::getInt32Ty(*context), Ints, false);

  llvm::Function *F =
      llvm::Function::Create(FT, llvm::Function::ExternalLinkage, fun_name, module.get());

  // Set names for all arguments.
  unsigned Idx = 0;
  for (auto &Arg : F->args())
    Arg.setName(parameters.at(Idx++).get()->get_name());

  return F;


  return nullptr;
}


llvm::Value *Block::codegen() {
  log("codegen block");
  for (int i = 0; i < expressions.size(); i++) {
    Expression *exp = expressions.at(i).get();
    exp->codegen();
  }
}
llvm::Value *If::codegen() {
  log("codegen if");
}
llvm::Value * Elif::codegen() {
  log("codegen elif");
}


llvm::Function *FunctionAST::codegen() {
    log("codegen fun");
    llvm::Function *fun = module->getFunction(Proto->get_name());

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
    named_values[std::string(Arg.getName())] = &Arg;
  }
  Body->codegen();
  if (verifyFunction(*fun)) {
    log(*module);
    return fun;
  }
  else {
    log("ERROR: failed to generate function IR for " <<  Proto->get_name());
    fun->eraseFromParent();
    return nullptr;
  }
    
}