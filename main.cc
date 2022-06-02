#include "lexer.h"
#include "ast.h"

extern token_st global_token;
extern Type     global_type;

std::map<char, int> BinopPrecedence;

int main() {
  setvbuf(stdout, NULL, _IONBF, 0);
  BinopPrecedence[GT_t] = 10;
  BinopPrecedence[PLUS_t] = 20;
  BinopPrecedence[MIN_t] = 20;
  BinopPrecedence[MUL_t] = 40;  // highest.

  int i = 0;
  global_token = {};
  global_type = {};
  global_token.type = UNKNOWN_t;
  global_token = gettok();
  while(true) {
    switch (global_token.type) {
      case EOF_t:
        printf("reached EOF token\n");
        return 0;
      case ID_t:
        parse_identifier_exp();
        break;
      case TYPE_t:
        printf("found a type\n");
        global_type = global_token.data.data_type;
        parse_id_or_fun().get()->print("");
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

    // while(true) {
    //   global_token = gettok();
    //   print_token(global_token);


    //   // std::unique_ptr<Expression> temp = parse_token();
    //   // printf("%s\n" , temp.get()->stringify().c_str());
    //   // free(token.data.name);
    //   if (global_token.type == EOF_t) break;
    // }


  return 0;
}