#include "ast.h"
#include "lexer.h"

extern token_st             global_token;
extern Type                 global_type;
extern std::map<char, int>  BinopPrecedence;

/// GetTokPrecedence - Get the precedence of the pending binary operator token.
static int GetTokPrecedence() {
  // Make sure it's a declared binop.
  int TokPrec = BinopPrecedence[global_token.type];
  if (TokPrec <= 0) return -1;
  return TokPrec;
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


std::unique_ptr<Expression> parse_identifier_exp() {
  //TODO: Check where var name is stored
  // std::string id_name = global_token.data.id;
  std::string id_name = global_token.data.name;

  getNextToken();  // eat identifier name.



  if (global_token.type != LPAREN_t) {// Simple variable ref. 
  //TODO: Add the variable type
    printf("parsed a variable name\n");
    return std::make_unique<Variable>(id_name);
  }

  getNextToken();  // eat (
  // Call.
  if (global_token.type != TYPE_t) {
    printf("parsing a call\n");
    std::vector<std::unique_ptr<Expression>> args;
    if (global_token.type != RPAREN_t) {
      while (1) {
        if (auto Arg = ParseExpression())
          args.push_back(std::move(Arg));
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

    return std::make_unique<CallExpression>(id_name, std::move(args));
  }
  else {

  }

}



static std::unique_ptr<Expression> ParsePrimary() {



  switch (global_token.type) {
  default:
    fprintf(stderr, "unknown token when expecting an expression\n");
    return nullptr;  
  case ID_t:
    return parse_identifier_exp();
  case INTCONST_t:
    return parse_const(global_token);
  case LPAREN_t:
    return parse_paren_expr();
  }
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

    // Okay, we know this is a binop.
    //TODO: Fix the hardcoding here
    int BinOp = '+';

    getNextToken(); // eat binop

    // Parse the primary expression after the binary operator.
    auto RHS = ParsePrimary();
    if (!RHS)
      return nullptr;

    // If BinOp binds less tightly with RHS than the operator after RHS, let
    // the pending operator take RHS as its LHS.
    int NextPrec = GetTokPrecedence();
    if (TokPrec < NextPrec) {
      RHS = ParseBinOpRHS(TokPrec + 1, std::move(RHS));
      if (!RHS)
        return nullptr;
    }

    // Merge LHS/RHS.
    LHS =
        std::make_unique<Operator>(std::move(LHS), (char)BinOp, std::move(RHS));
    LHS.get()->print();
  }
}

void handle_top_level_exp() {
  // Evaluate a top-level expression into an anonymous function.
  if (ParseTopLevelExpr()) {
    fprintf(stderr, "Parsed a top-level expr\n");
  } else {
    // Skip token for error recovery.
    getNextToken();
  }
}

static std::unique_ptr<PrototypeAST> ParsePrototype() {

  //TODO: Store type here and eat it
  if (global_token.type != ID_t) {
    fprintf(stderr, "Expected function name in prototype\n");
    return nullptr;
  }

  print_token(global_token);

  std::string FnName = global_token.data.name;
  getNextToken();

  if (global_token.type != '(')
    fprintf(stderr, "Expected '(' in prototype");
  print_token(global_token);

  std::vector<std::string> ArgNames;
  token_st temp_token = getNextToken();
  while (temp_token.type == ID_t) {
    ArgNames.push_back(temp_token.data.name);
    temp_token = getNextToken();
  }
  if (global_token.type != ')') {
    fprintf(stderr, "Expected ')' in prototype");
    return nullptr;
  }

  // success.
  getNextToken(); // eat ')'.

  return std::make_unique<PrototypeAST>(FnName, std::move(ArgNames));
}


static std::unique_ptr<PrototypeAST> ParseExtern() {
  getNextToken();  // eat extern.
  return ParsePrototype();
}

void handle_extern() {
  if (ParseExtern()) {
    fprintf(stderr, "Parsed an extern\n");
  } else {
    // Skip token for error recovery.
    getNextToken();
  }
}


static std::unique_ptr<FunctionAST> ParseDefinition() {
  getNextToken();  // eat def.
  auto Proto = ParsePrototype();
  if (!Proto) return nullptr;

  if (auto E = ParseExpression())
    return std::make_unique<FunctionAST>(std::move(Proto), std::move(E));
  return nullptr;
}

static std::unique_ptr<FunctionAST> ParseTopLevelExpr() {
  if (auto E = ParseExpression()) {
    // Make an anonymous proto.
    auto Proto = std::make_unique<PrototypeAST>("", std::vector<std::string>());
    return std::make_unique<FunctionAST>(std::move(Proto), std::move(E));
  }
  return nullptr;
}
