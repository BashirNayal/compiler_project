
#include "ir.h"

extern llvm::LLVMContext TheContext;
extern llvm::IRBuilder<> Builder(TheContext);
extern std::unique_ptr<llvm::Module> TheModule;

extern std::map<std::string, llvm::Value *> NamedValues;


llvm::Value *log_errorV(const char *str) {
  std::cout << "ERROR: " << str << std::endl;
  return nullptr;
}

void get_ir(std::unique_ptr<Expression> expr) {
    expr.get()->codegen();
}


llvm::Value *FunctionAST::codegen() {
    llvm::Function *TheFunction = TheModule->getFunction(Proto.get()->get_name());

  if (!TheFunction)
    TheFunction = Proto->codegen();

  if (!TheFunction)
    return nullptr;

  // Create a new basic block to start insertion into.
  BasicBlock *BB = BasicBlock::Create(*TheContext, "entry", TheFunction);
  Builder->SetInsertPoint(BB);

  // Record the function arguments in the NamedValues map.
  NamedValues.clear();
  for (auto &Arg : TheFunction->args())
    NamedValues[std::string(Arg.getName())] = &Arg;

  if (Value *RetVal = Body->codegen()) {
    // Finish off the function.
    Builder->CreateRet(RetVal);

    // Validate the generated code, checking for consistency.
    verifyFunction(*TheFunction);

    return TheFunction;
  }

  // Error reading body, remove function.
  TheFunction->eraseFromParent();
  return nullptr;
    
}