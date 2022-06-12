#include "ast.h"


extern token_st                   global_token;
extern Type_en                    global_type;
extern std::map<char, int>        BinopPrecedence;

/// GetTokPrecedence - Get the precedence of the pending binary operator token.
static int GetTokPrecedence() {
  // Make sure it's a declared binop.
  int TokPrec = BinopPrecedence[global_token.type];
  if (TokPrec <= 0) return -1;
  return TokPrec;
}


// std::unique_ptr<Expression>  prase_identifier(token_st current_token) {

//     return std::make_unique<Variable>(current_token.data.name);
// }
std::unique_ptr<Expression>  parse_const(token_st current_token) {
    getNextToken(); // Skip the parsed number
    log(current_token.data.int_value);
    return std::make_unique<Const>(current_token.data.int_value);
}

bool is_end_expression() {
return (global_token.type == SEMICOL_t || 
            global_token.type == RPAREN_t || 
            global_token.type == COMMA_t || 
            global_token.type == RBRACK_t || 
            global_token.type == RBRACE_t);
}

void handle_extern() {
  log("parsing extern");
}


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
      if (is_end_expression()) {
        getNextToken(); // eat ';' or ')' or ','
        return expr;
      }
      break;
    case STRING_t: {
      log("found str: " << global_token.data.str);
      char *temp = (char*)malloc(100);
      strncpy(temp, global_token.data.str, 10);
      std::string myString(global_token.data.str, std::strlen(global_token.data.str));
      expr = std::make_unique<String>(myString);
      getNextToken(); // eat 'str'
        print_token(global_token);

      if (is_end_expression()) {
        getNextToken(); // eat ';' or ')' or ','
        print_token(global_token);
        return expr;
      }

      break;
    }
    case ID_t:
      printf("found id\n");
      id_name = global_token.data.name;
      getNextToken(); // eat the id name
      if (global_token.type == LPAREN_t) {
        printf("found function call\n");
        getNextToken(); // eat '('
        if (global_token.type == RPAREN_t) {
          getNextToken(); // eat ')'
          if (global_token.type != SEMICOL_t) {
            log("ERROR: expected ';' after function call");
            exit(0);
          }
          getNextToken(); // eat ';'
          return std::make_unique<CallExpression>(id_name);
        }
        std::vector<std::unique_ptr<Expression>> args;
        while (global_token.type != SEMICOL_t) {
          args.push_back(std::move(parse_expression()));
          log("parsed one arg");
        }
        log("parsed args");
        return std::make_unique<CallExpression>(id_name, std::move(args));
      }
      else if (global_token.type == LBRACK_t) {
        printf("found array addressing\n");
        getNextToken(); // eat '['
        std::unique_ptr<Expression> index = parse_expression();
        if (global_token.type == ASSIGN_t) {
          getNextToken(); // eat '='
          std::unique_ptr<Expression> rhs = parse_expression();
          return std::make_unique<ArrayRef>(id_name, std::move(index), std::move(rhs));
        }
        expr = std::make_unique<ArrayRef>(id_name, std::move(index));
        if (is_end_expression() ) {
          getNextToken(); // eat ';' or ')' or ','
          return expr;
        }
      }
      else if (global_token.type == ASSIGN_t) {
        log("found var reassign");
        getNextToken(); // eat '='
          log("about to crash");
          std::unique_ptr<Expression> rhs = parse_expression();
          rhs->print("x");
          log("crashed");
          // rhs.get()->print("x");
          return std::make_unique<Assignment>(id_name, std::move(rhs));
        
      }
      else {
        //Found variable use
        log("found var use");
        expr = std::make_unique<VarUse>(VarUse(id_name));
        //TODO 
        if (is_end_expression() ) {
          getNextToken(); // eat ';' or ')' or ','
          return expr;
        }
      }
      break;
    case LPAREN_t:
        log("paren expression");
        getNextToken(); // eat '('
        expr = parse_expression();
        break;
    default:
      print_token(global_token);
      printf("default case\n");
      expr->print("f");
      exit(0);
        
  }
  switch (global_token.type) {
    case LPAREN_t:
      getNextToken(); // eat '('
      break;
    case NOT_t:
      log("implement me!");
      exit(0);
      break;
    case PLUS_t:
    case MUL_t:
    case DIV_t:
    case MIN_t:
    case GT_t:
    case LT_t:
    case EQ_t:
    case NE_t:
    case GE_t:
    case LE_t:
    case OR_t:
    case AND_t:
    case XOR_t:
    case MOD_t:
      print_token(global_token);
      Token op_token = global_token.type;
      getNextToken(); // eat operator
      return std::make_unique<Operator>(std::move(expr), op_token, std::move(parse_expression()));
      break;
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
    return std::make_unique<Assignment>(var_name, std::move(rhs),std::make_unique<VarDef>(VarDef(var_name, var_type)));
  }
  else if (global_token.type == LBRACK_t) {
    printf("parsing array\n");
    getNextToken(); // eat '['
    std::unique_ptr<Expression> size = parse_expression();
    // if (global_token.type != RBRACK_t) {
    //   printf("ERROR: failed to parse array\n");
    // }
    // getNextToken(); // eat ']'
    if (global_token.type == ASSIGN_t) {
      log("found array initialziation");
      getNextToken(); // eat '='
      if (global_token.type != LBRACE_t) {
        log("ERROR: expected '{' at the start of array initializer");
      }
      getNextToken(); // eat '{'
      std::vector<std::unique_ptr<Expression>> initial_values; 
      while (global_token.type != SEMICOL_t) {
        initial_values.push_back(std::move(parse_expression()));
      }
      getNextToken(); // eat ';'
      return std::make_unique<Array>(var_name, std::move(size), std::move(initial_values));
    }
    return std::make_unique<Array>(var_name, std::move(size));
  }
  else if (global_token.type == LPAREN_t) { // function 
    printf("parsing fun_def\n");
    return parse_fun_def(var_type, var_name);
  }
  
  
}

std::unique_ptr<While> parse_while() {
  log("parsing while");
  getNextToken(); // eat 'while'
  if (global_token.type != LPAREN_t) {
    log("ERROR: expected '(' after 'while'");
    return nullptr;
  }
  getNextToken(); // eat '('
  std::unique_ptr<Expression> cond = parse_expression();
  if (global_token.type != LBRACE_t) {
    log("ERROR: expected '{' after while condition");
    return nullptr;
  }
  getNextToken(); // eat '{'
  std::unique_ptr<Block> body = parse_block();
  return std::make_unique<While>(std::move(cond), std::move(body));
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
      case WHILE_t:
        expressions.push_back(std::move(parse_while()));
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
  return nullptr;
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


std::unique_ptr<Expression> parse_return() {
  log("parsing return");
  getNextToken(); // eat 'return'
  if (global_token.type == SEMICOL_t) {
    return std::make_unique<Return>(nullptr);
  }
  return std::make_unique<Return>(std::move(parse_expression()));
}


std::unique_ptr<Expression> parse_elif() {
}

std::unique_ptr<Block> parse_else() {
  if (global_token.type != LBRACE_t) {
    log("ERROR: expected '{' after else");
    return nullptr;
  }
  getNextToken(); // eat '{'
  std::unique_ptr<Block> else_body = parse_block();
  log("parsed else body");
  return else_body;
}


std::unique_ptr<Expression> parse_if() {
  log("parsing if");
  getNextToken(); // eat 'if'
  if (global_token.type != LPAREN_t) {
    log("ERROR: expected '(' after 'if'");
    return nullptr;
  }
  getNextToken(); // eat '('
  std::unique_ptr<Expression> if_cond = parse_expression();
  log("parsed if cond");
  print_token(global_token);

  if (global_token.type != LBRACE_t) {
    log("ERROR: expected '{' after if statement");
    return nullptr;
  }

  getNextToken(); // eat '{'
  std::unique_ptr<Block> if_body = parse_block();
  log("parsed if body");
  if (global_token.type != ELSE_t) {
    return std::make_unique<If>(std::move(if_cond), std::move(if_body));
  }
  log("found else");
  getNextToken(); // eat 'else'
  if (global_token.type == IF_t){ // else if branch
    parse_elif();
  }
  else { // else branch
    if (global_token.type != LBRACE_t) {
      log("ERROR: expected '{' at the start of else block");
      return nullptr;
    }
      std::unique_ptr<Block> else_body = parse_else();
      log("parsed if-else");
      return std::make_unique<If>(
        std::move(if_cond), 
        std::move(if_body), 
        std::move(else_body));
  }
}