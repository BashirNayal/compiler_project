#include "lexer.h"
#include "ast.h"
#include "ir.h"
#include "common.h"





std::map<char, int> BinopPrecedence;

extern token_st     global_token;
extern Type_en      global_type;


int main(int argc, char** argv) {
  setvbuf(stdout, NULL, _IONBF, 0);
  bool bound_check = false, bound_check_elimination = false;
  char* program_name = argv[1];
  if (argc > 2) {
    if (argc == 3) {
      bound_check = true;
    }
    else {
      bound_check = true;
      bound_check_elimination = true;
    }
  }


  stdin = fopen(program_name, "r");

  

  int i = 0;
  global_token = {};
  global_type = {};
  global_token.type = UNKNOWN_t;
  global_token = gettok();
  std::vector<std::unique_ptr<Expression>> expressions;
  while(true) {
    switch (global_token.type) {
      case EOF_t:
        goto codegen;
        break;
      case TYPE_t:
        global_type = global_token.data.data_type;
        expressions.push_back(parse_typed_expression());
      break;
      case EXTERN_t:
        handle_extern();
        break;
      default:
        getNextToken();
    }
  }
  codegen:
    
    init_module();
    // Turn AST to LLVM IR
    for (int i = 0; i < expressions.size(); i ++) {
      expressions.at(i)->codegen();
    }
    run_passes(bound_check, bound_check_elimination);
    std::string arg(program_name);
    arg.erase(arg.find('.'));
    get_object_file(arg);
    system(("./gen_exec.sh " + arg).c_str());

  return 0;
}