#include "ast.h"
#include "lexer.h"

std::unique_ptr<Expression>  prase_identifier(token_st current_token) {

    return std::make_unique<Variable>(current_token.data.name);
}
std::unique_ptr<Expression>  parse_const(token_st current_token) {
    return std::make_unique<Const>((double)current_token.data.int_value);
}


std::unique_ptr<Expression> parse_token(token_st current_token) {
  switch (current_token.type) {
  default:
    // return printf("unknown token when expecting an expression");
    return nullptr;
  case ID_t:
    return prase_identifier(current_token);
  case INTCONST_t:
    return parse_const(current_token);
//   case '(':
//     return ParseParenExpr();
  }
}