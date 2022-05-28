#include "lexer.h"
#include "ast.h"

extern token_st global_token;




int main() {


    int i = 0;
    global_token = {};
    global_token.type = UNKNOWN_t;
    global_token = gettok();
    while(true) {
      switch (global_token.type) {
        case EOF_t:
          printf("reached EOF token\n");
          return 0;
        // case ID_t:
        //   ();

        default:
          getNextToken();
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