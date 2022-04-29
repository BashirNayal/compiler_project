#include "lexer.h"
#include "ast.h"




int main() {


    int i = 0;
    token_st token = {};
    token.type = UNKNOWN_t;
    while(true) {
      token_st token = gettok();
      print_token(token);
      std::unique_ptr<Expression> temp = parse_token(token);
      printf("%s\n" , temp.get()->stringify().c_str());
      // free(token.data.name);
      if (token.type == EOF_t) break;
    }

  return 0;
}