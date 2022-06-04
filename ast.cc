#include "ast.h"


extern token_st             global_token;
extern Type_en                 global_type;
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
    log(current_token.data.int_value);
    return std::make_unique<Const>(current_token.data.int_value);
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
  // std::string id_name = global_token.data.name;

  // getNextToken();  // eat identifier name.



  // if (global_token.type != LPAREN_t) {// Simple variable ref. 
  // //TODO: Add the variable type
  //   printf("parsed a variable name\n");
  //   // return std::make_unique<Variable>(id_name);
  // }

  // getNextToken();  // eat (
  // // Call.
  // if (global_token.type != TYPE_t) {
  //   printf("parsing a call\n");
  //   std::vector<std::unique_ptr<Expression>> args;
  //   if (global_token.type != RPAREN_t) {
  //     while (1) {
  //       if (auto Arg = ParseExpression())
  //         args.push_back(std::move(Arg));
  //       else
  //         return nullptr;

  //       if (global_token.type == RPAREN_t)
  //         break;

  //       if (global_token.type != COMMA_t) {
  //         fprintf(stderr, "Expected ')' or ',' in argument list");
  //         return nullptr;
  //       }
  //       getNextToken();
  //     }
  //   }

  //   // Eat the ')'.
  //   getNextToken();

  //   return std::make_unique<CallExpression>(id_name, std::move(args));
  // }
  // else {

  // }

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
    // LHS.get()->print();
  }
}

// void handle_top_level_exp() {
//   // Evaluate a top-level expression into an anonymous function.
//   if (ParseTopLevelExpr()) {
//     fprintf(stderr, "Parsed a top-level expr\n");
//   } else {
//     // Skip token for error recovery.
//     getNextToken();
//   }
// }

static std::unique_ptr<PrototypeAST> ParsePrototype() {

  // //TODO: Store type here and eat it
  // if (global_token.type != ID_t) {
  //   fprintf(stderr, "Expected function name in prototype\n");
  //   return nullptr;
  // }

  // print_token(global_token);

  // std::string FnName = global_token.data.name;
  // getNextToken();

  // if (global_token.type != '(')
  //   fprintf(stderr, "Expected '(' in prototype");
  // print_token(global_token);

  // std::vector<std::string> ArgNames;
  // token_st temp_token = getNextToken();
  // while (temp_token.type == ID_t) {
  //   ArgNames.push_back(temp_token.data.name);
  //   temp_token = getNextToken();
  // }
  // if (global_token.type != ')') {
  //   fprintf(stderr, "Expected ')' in prototype");
  //   return nullptr;
  // }

  // // success.
  // getNextToken(); // eat ')'.

  // return std::make_unique<PrototypeAST>(FnName, std::move(ArgNames));
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


// static std::unique_ptr<FunctionAST> ParseDefinition() {
//   getNextToken();  // eat def.
//   auto Proto = ParsePrototype();
//   if (!Proto) return nullptr;

//   if (auto E = ParseExpression())
//     // return std::make_unique<FunctionAST>(std::move(Proto), std::move(E));
//   return nullptr;
// }

// static std::unique_ptr<FunctionAST> ParseTopLevelExpr() {
//   if (auto E = ParseExpression()) {
//     // Make an anonymous proto.
//     // auto Proto = std::make_unique<PrototypeAST>("", std::vector<std::string>());
//     // return std::make_unique<FunctionAST>(std::move(Proto), std::move(E));
//   }
//   return nullptr;
// }



std::unique_ptr<Expression> parse_expression() {
  std::unique_ptr<Expression> expr;
  char * id_name;
  // std::unique_ptr<Expression> lhs;
  switch (global_token.type) {
    case RETURN_t:
      log("found return");
      expr = parse_return();
      break;
    case INTCONST_t:
    log("found const " << global_token.data.int_value);
      expr = std::make_unique<Const>(global_token.data.int_value);
      getNextToken(); // eat const
      if (global_token.type == SEMICOL_t || global_token.type == RPAREN_t) {
        getNextToken(); // eat ';'
        // print_token(global_token);
        return expr;
      }
      break;
    case ID_t:
      printf("found id\n");
      //TODO: Handle function calls or indexing;
      id_name = global_token.data.name;
      getNextToken(); // eat the id name
      if (global_token.type == LPAREN_t) {
        printf("found function call inside of block\n");
        //TODO: parse arguments
      }
      else if (global_token.type == LBRACE_t) {
        printf("found array addressing\n");
      }
      else {
        //Found variable
        expr = std::make_unique<VarUse>(VarUse(id_name));
        //TODO 
        if (global_token.type == SEMICOL_t || global_token.type == RPAREN_t) {
          getNextToken(); // eat ';' or ')'
          return expr;
        }
      }
      break;
    default:
      printf("default case\n");
        
  }
  switch (global_token.type) {
    case PLUS_t:
      print_token(global_token);
      getNextToken(); // eat operator
      return std::make_unique<Operator>(std::move(expr), '+', std::move(parse_expression()));
    case MUL_t:
      getNextToken();
      return std::make_unique<Operator>(std::move(expr), '*', std::move(parse_expression()));
    case DIV_t:
      getNextToken();
      return std::make_unique<Operator>(std::move(expr), '/', std::move(parse_expression()));
    case MIN_t:
      getNextToken();
      return std::make_unique<Operator>(std::move(expr), '-', std::move(parse_expression()));
    case LPAREN_t:
      getNextToken();
      printf("IMPLEMENT ME!\n");
      exit(1);
    case GT_t:
      getNextToken();
      print_token(global_token);
      std::unique_ptr<Expression> rhs = parse_expression();
      rhs.get()->print("test");
      return std::make_unique<Operator>(std::move(expr), '>', std::move(rhs));
      
      
    
  }

}

std::unique_ptr<Expression> parse_fun_def(Type_en fun_type, std::string fun_name) {
  getNextToken(); // Eat '('
  printf("parsing a function def\n");
  if (global_token.type == RPAREN_t) {
    printf("parsing function with no parameters\n");
    //TODO return the function here
  }
  //TODO: add a case where there is no parameters
  //Get function parameters
  std::vector<std::unique_ptr<Param>> fun_params;
  while (true) {
    if (global_token.type == RPAREN_t) {
      getNextToken(); // eat ')'
      break;
    }
    Type_en param_type = global_token.data.data_type;
    getNextToken(); // eat type
    std::string param_name = global_token.data.name;
    getNextToken(); // eat name
    fun_params.push_back(std::make_unique<Param>(Param(param_name, param_type)));
    printf("first param\n");
    if (global_token.type == RPAREN_t) {
      getNextToken(); // eat ')'
      break;
    }
    else if (global_token.type != COMMA_t) {
      printf("ERROR: Expected ')' or ','\n");
      // return;
    }
    else {
      getNextToken(); // eat ','
    }
    std::cout << "found param " << param_name << std::endl;
  }
  printf("parsed params\n");
  std::unique_ptr<PrototypeAST> proto = 
    std::make_unique<PrototypeAST>(PrototypeAST(std::move(fun_params), fun_name));
  // proto.get()->print("");
  if (global_token.type == LBRACE_t) {
    printf("parsing function body\n");
    getNextToken(); //eat '{'
    std::unique_ptr<Block> block = parse_block();
    std::unique_ptr<FunctionAST> temp =
      std::make_unique<FunctionAST>(std::move(proto), std::move(block));
    return std::move(temp);
  }
  //TODO: parse the body
  // return proto;
  
}

std::unique_ptr<Expression> parse_typed_expression() {

  Type_en var_type = global_token.data.data_type;
  getNextToken(); // Eat the type
  std::string var_name = global_token.data.name;
  getNextToken(); // Eat the name
  printf("got var name '%s' of type '%d'\n" , var_name.c_str(), var_type);
  if (global_token.type == SEMICOL_t) {
    getNextToken(); // eat ';'
    return std::make_unique<VarDef>(VarDef(var_name, var_type));

  }
  else if (global_token.type == ASSIGN_t) {
    getNextToken(); //eat '='
    std::unique_ptr<Expression> rhs = parse_expression();
    // rhs.get()->print("x");
    return std::make_unique<Assignment>(var_name, std::move(rhs));
  }
  else if (global_token.type == LBRACK_t) {
    printf("parsing array\n");
    getNextToken(); // eat '['
    std::unique_ptr<Expression> index = parse_expression();
    if (global_token.type != RBRACK_t) {
      printf("ERROR: failed to parse array\n");
    }
    if (global_token.type == RBRACK_t) {
      getNextToken(); // eat ']'
    }
  }
  else if (global_token.type == LPAREN_t) { // function 
    printf("parsing fun_def\n");
    return parse_fun_def(var_type, var_name);
  }
  
  
}

std::unique_ptr<Block> parse_block() {
  std::vector<std::unique_ptr<Expression>> expressions;
  while (global_token.type != RBRACE_t) {
    // printf("inside the block\n");
    // getNextToken();
    switch (global_token.type) {
      case TYPE_t:
        expressions.push_back(std::move(parse_typed_expression()));
        break;
      case ID_t:
        expressions.push_back(std::move(parse_expression()));
        break;
      case RETURN_t:
        expressions.push_back(std::move(parse_return()));
        break;
      case IF_t:
        expressions.push_back(std::move(parse_if()));
        break;

      default:
        // print_token(global_token);
        getNextToken();
        break;
    }
    if (global_token.type == RBRACE_t) {
      printf("finished parsing block\n");
      getNextToken(); // eat '}'
      return std::make_unique<Block>(std::move(expressions));
    }
  }


}


std::unique_ptr<Expression> parse_id_or_fun() {
  Type_en id_or_fun_type = global_token.data.data_type;

  getNextToken(); // Eat the type
  std::string id_or_fun_name = global_token.data.name;
  getNextToken(); // Eat the name
  printf("got fun/var name '%s' of type '%d'\n" , id_or_fun_name.c_str(), id_or_fun_type);
  
  if (global_token.type == LBRACK_t) {} // Case of array indexing
  else if (global_token.type == LPAREN_t) { // Case of function definition
    getNextToken(); // Eat '('
    printf("parsing a function def\n");
    if (global_token.type == RPAREN_t) {
      printf("parsing function with no parameters\n");
      //TODO return the function here
    }
    //TODO: add a case where there is no parameters
    //Get function parameters
    std::vector<std::unique_ptr<Param>> fun_params;
    while (true) {
      Type_en param_type = global_token.data.data_type;
      getNextToken(); // eat type
      std::string param_name = global_token.data.name;
      getNextToken(); // eat name
      fun_params.push_back(std::make_unique<Param>(Param(param_name, param_type)));
      printf("first param\n");
      if (global_token.type == RPAREN_t) {
        getNextToken(); // eat ')'
        break;
      }
      else if (global_token.type != COMMA_t) {
        printf("ERROR: Expected ')' or ','\n");
        // return;
      }
      else {
        getNextToken(); // eat ','
      }
      std::cout << "found param " << param_name << std::endl;
    }
    printf("parsed params\n");
    std::unique_ptr<PrototypeAST> proto = 
      std::make_unique<PrototypeAST>(PrototypeAST(std::move(fun_params), id_or_fun_name));
    // proto.get()->print("");
    if (global_token.type == LBRACE_t) {
      printf("parsing function body\n");
      getNextToken(); //eat '{'
      std::unique_ptr<Block> block = parse_block();
      std::unique_ptr<FunctionAST> temp =
        std::make_unique<FunctionAST>(std::move(proto), std::move(block));
      return std::move(temp);
    }
    //TODO: parse the body
    // return proto;
  }
  else { // case of a variable

  }
}


// llvm::Value *FunctionAST::codegen() {
//   return nullptr;
// }


std::unique_ptr<Expression> parse_return() {
  log("parsing return");
  getNextToken(); // eat 'return'
  if (global_token.type == SEMICOL_t) {
    return std::make_unique<Return>(nullptr);
  }
  return std::make_unique<Return>(std::move(parse_expression()));
}

std::unique_ptr<Expression> parse_if() {
  log("parsing if");
  getNextToken(); // eat 'if'
  if (global_token.type != LPAREN_t) {
    log("ERROR: expected '(' after 'if'");
    return nullptr;
  }
  getNextToken(); // eat '('
  std::unique_ptr<Expression> cond = parse_expression();
  log("parsed if cond");
  if (global_token.type != LBRACE_t) {
    log("ERROR: expected '{' after if statement");
    return nullptr;
  }
  getNextToken(); // eat '{'
  std::unique_ptr<Block> body = parse_block();
  // cond.get()->print("ii");
  log("parsed if body");
  // body.get()->print("aa");
  return std::make_unique<If>(std::move(cond), std::move(body));
}