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
  std::unique_ptr<Expression> expression;
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
        expression = parse_typed_expression();
        expression.get()->print("");

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
    init_module();
    printf("codegen\n");
    expression.get()->codegen();
    get_object_file();

  return 0;
}