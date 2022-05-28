#include "ast.h"
#include "lexer.h"

extern token_st global_token;



static std::map<char, int> BinopPrecedence;

/// GetTokPrecedence - Get the precedence of the pending binary operator token.
static int GetTokPrecedence() {
  // Make sure it's a declared binop.
  int TokPrec = BinopPrecedence[global_token.type];
  if (TokPrec <= 0) return -1;
  return TokPrec;
}

static std::unique_ptr<Expression> ParseBinOpRHS(int ExprPrec,
                                              std::unique_ptr<Expression> LHS) {
  // If this is a binop, find its precedence.
  while (true) {
    int TokPrec = GetTokPrecedence();

    // If this is a binop that binds at least as tightly as the current binop,
    // consume it, otherwise we are done.
    if (TokPrec < ExprPrec)
      return LHS;
  }
}



static std::unique_ptr<Expression> ParseExpression() {
  auto LHS = ParsePrimary();
  if (!LHS)
    return nullptr;

  return ParseBinOpRHS(0, std::move(LHS));
}



// std::unique_ptr<Expression>  prase_identifier(token_st current_token) {

//     return std::make_unique<Variable>(current_token.data.name);
// }
std::unique_ptr<Expression>  parse_const(token_st current_token) {
    getNextToken(); // Skip the parsed number
    return std::make_unique<Const>((double)current_token.data.int_value);
}


static std::unique_ptr<Expression> parse_paren_expr() {
  getNextToken(); // eat (
  auto V = ParseExpression();
  if (!V)
    return nullptr;

  if (global_token.type != RPAREN_t) {
    fprintf(stderr, "ERROR: expected ')'");
    return nullptr;
  }
  getNextToken(); // eat ).
  return V;
}


static std::unique_ptr<Expression> ParseIdentifierExpr() {
  //TODO: Check where var name is stored
  // std::string IdName = global_token.data.id;
  std::string IdName = "";

  getNextToken();  // eat identifier.

  if (global_token.type != LPAREN_t) // Simple variable ref.
    return std::make_unique<Variable>(IdName);

  // Call.
  getNextToken();  // eat (
  std::vector<std::unique_ptr<Expression>> Args;
  if (global_token.type != RPAREN_t) {
    while (1) {
      if (auto Arg = ParseExpression())
        Args.push_back(std::move(Arg));
      else
        return nullptr;

      if (global_token.type == RPAREN_t)
        break;

      if (global_token.type != COMMA_t) {
        fprintf(stderr, "Expected ')' or ',' in argument list");
        return nullptr;
      }
      getNextToken();
    }
  }

  // Eat the ')'.
  getNextToken();

  return std::make_unique<CallExpression>(IdName, std::move(Args));
}



// std::unique_ptr<Expression> parse_token(token_st current_token) {
//   switch (current_token.type) {
//   default:
//     // return printf("unknown token when expecting an expression");
//     return nullptr;
//   case ID_t:
//     return prase_identifier(current_token);
//   case INTCONST_t:
//     return parse_const(current_token);
// //   case '(':
// //     return ParseParenExpr();
//   }
// }


static std::unique_ptr<Expression> ParsePrimary() {


  BinopPrecedence[GT_t] = 10;
  BinopPrecedence[PLUS_t] = 20;
  BinopPrecedence[MIN_t] = 20;
  BinopPrecedence[MUL_t] = 40;  // highest.


  switch (global_token.type) {
  default:
    fprintf(stderr, "unknown token when expecting an expression");
    return nullptr;  
  case ID_t:
    return ParseIdentifierExpr();
  case INTCONST_t:
    return parse_const(global_token);
  case LPAREN_t:
    return parse_paren_expr();
  }
}


void handle_typed_expr() {
  printf("typed expr\n");
  Type fun_type = global_token.data.data_type;
  getNextToken();
  // switch (global_token) 

}



// int NextPrec = GetTokPrecedence();
// if (TokPrec < NextPrec) {
//     // Merge LHS/RHS.
//   LHS = std::make_unique<BinaryExprAST>(BinOp, std::move(LHS),
//                                           std::move(RHS));
// }  // loop around to the top of the while loop.
