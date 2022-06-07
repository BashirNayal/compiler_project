#include "lexer.h"
#include "ast.h"
#include "ir.h"
#include "common.h"





std::map<char, int> BinopPrecedence;

extern token_st     global_token;
extern Type_en      global_type;


int main() {
  setvbuf(stdout, NULL, _IONBF, 0);
  BinopPrecedence[GT_t] = 10;
  BinopPrecedence[PLUS_t] = 20;
  BinopPrecedence[MIN_t] = 20;
  BinopPrecedence[MUL_t] = 40;  // highest.
  
  // llvm::LLVMContext context;
  // llvm::LLVMContext context;


  int i = 0;
  global_token = {};
  global_type = {};
  global_token.type = UNKNOWN_t;
  global_token = gettok();
  std::vector<std::unique_ptr<Expression>> expressions;
  while(true) {
    switch (global_token.type) {
      case EOF_t:
        printf("reached EOF token\n");
        goto codegen;
      case ID_t:
        // parse_identifier_exp();
        break;
      case TYPE_t:
        printf("found a type\n");
        global_type = global_token.data.data_type;
        // expression = parse_id_or_fun();
        expressions.push_back(parse_typed_expression());

        // getNextToken();
        // parse_identifier_exp();
      break;

      case EXTERN_t:
        printf("found extern\n");
        handle_extern();
        break;
      default:
        getNextToken();
        // handle_top_level_exp();
    }
  }
  codegen:
    for (int i = 0; i < expressions.size(); i ++) {
      expressions.at(i)->print("");
    }
    
    init_module();
    for (int i = 0; i < expressions.size(); i ++) {
      expressions.at(i)->codegen();
    }
    get_object_file();

  return 0;
}