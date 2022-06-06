
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


void get_object_file() {

  log("creating object file");
  auto target_triple = llvm::sys::getDefaultTargetTriple();
  std::ofstream myfile;
  std::string ir_str;
  myfile.open ("program.ll");
  llvm::raw_string_ostream output(ir_str);
  module->print(output, nullptr);
  // log("program:");
  // log(ir_str);
  myfile << ir_str;
  myfile.close();
  return;
  llvm::InitializeAllTargetInfos();
  llvm::InitializeAllTargets();
  llvm::InitializeAllTargetMCs();
  llvm::InitializeAllAsmParsers();
  llvm::InitializeAllAsmPrinters();
  log("initialized info and target");
  std::string err;
  auto target = llvm::TargetRegistry::lookupTarget(target_triple, err);
  
  if (!target) {
    log(err);
    return;
  } 
  auto CPU = "generic";
  auto features = "";
  
  llvm::TargetOptions opt;
  auto RM = llvm::Optional<llvm::Reloc::Model>();
  auto TargetMachine = target->createTargetMachine(target_triple, CPU, features, opt, RM);

  log("created target machine");
  module->setDataLayout(TargetMachine->createDataLayout());
  module->setTargetTriple(target_triple);

  auto Filename = "output.o";
  std::error_code EC;
  llvm::raw_fd_ostream dest(Filename, EC, llvm::sys::fs::OF_None);
  log("opened file");
  if (EC) {
    log("Could not open file: " << EC.message());
    return ;
  }
  // llvm::PassBuilder<> pass;
  llvm::legacy::PassManager pass;
  auto FileType = llvm::CGFT_ObjectFile;
  
  if (TargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType)) {
    log("TheTargetMachine can't emit a file of this type");
    return ;
  }
  log("added pass");
  // pass.run(*module);
  log("ran pass");
  dest.flush();

  // llvm::outs() << "Wrote " << Filename << "\n";
  log("wrote object file");


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


  log("initialized");
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
llvm::Value *Operator::codegen() {
  log("codegen operator");
  llvm::Value *add_inst = llvm::BinaryOperator::CreateAdd(lhs.get()->codegen(), rhs.get()->codegen(), "temp");
  builder.get()->Insert(add_inst);
  log(*add_inst);
  return add_inst;
}

llvm::Value *Assignment::codegen() {
  printf("codegen assignment\n");
  if (def) {
    llvm::Value *AI = builder->CreateAlloca(llvm::Type::getInt32Ty(*context),nullptr, var_name);
    named_values[var_name] = AI;
  }
  builder->CreateStore(value->codegen(), named_values[var_name]);
  // builder->CreateStore(
}

llvm:: Value *VarUse::codegen() {
  log("codegen varuse");
  return named_values[var_name];
  value->print("x");
  llvm::Value *rhs = value->codegen();
  log(*rhs);
  // return builder->CreateStore(value->codegen(), named_values[var_name]);

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
  std::vector<llvm::Type *> Ints(parameters.size(),llvm::Type::getInt32Ty(*context));

  llvm::FunctionType *IT =
      llvm::FunctionType::get(llvm::Type::getInt32Ty(*context), Ints, false);

  llvm::Function *F =
      llvm::Function::Create(IT, llvm::Function::ExternalLinkage, fun_name, module.get());

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
  llvm::Value *if_cond_ir = cond.get()->codegen();
  llvm::BasicBlock *current_block = builder.get()->GetInsertBlock();
  llvm::StringRef prefix = current_block->getName();
  llvm::Function *current_function = builder.get()->GetInsertBlock()->getParent();
  llvm::BasicBlock *if_start_block = llvm::BasicBlock::Create(*context, prefix + ".if", current_function);
  llvm::BasicBlock *else_start_block = nullptr;
  if (else_body) {
    else_start_block = llvm::BasicBlock::Create(*context, prefix + ".else", current_function);
  }
  llvm::BasicBlock *if_end_block = llvm::BasicBlock::Create(*context, prefix + ".endif", current_function);
  
  if (else_start_block) {
    builder.get()->CreateCondBr(if_cond_ir, if_start_block, else_start_block);
  }
  else {
    builder.get()->CreateCondBr(if_cond_ir, if_start_block, if_end_block);
  }

  //populate the if body
  builder.get()->SetInsertPoint(if_start_block);

  body.get()->codegen(); 
  builder.get()->CreateBr(if_end_block);
  if (else_start_block) {
      builder.get()->SetInsertPoint(else_start_block);
      else_body.get()->codegen(); 
      builder.get()->CreateBr(if_end_block);
  }
  builder.get()->SetInsertPoint(if_end_block);
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