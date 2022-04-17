#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include "unistd.h"
#include "string.h"
#include "vector"

#define MAX_MAPPING_LEN 64
enum Token {
    EOF_t,

    EXTERN_t, RETURN_t,
    IF_t, ELSE_t, WHILE_t, DO_t,
    FOR_t, BREAK_t, CONTINUE_t,
    

    ID_t, SEMICOL_t, TYPE_t,
    
    INTCONST_t, FLOATCONST_t,
    DOUBLECONST_t, BOOLCONST_t,
    CHARCONST_t,


    ASSIGN_t, EQ_t, NE_t,
    LT_t, GT_t, LE_t, GE_t,
    PLUS_t, MIN_t, DIV_t, 
    MUL_t, MOD_t, AND_t, OR_t,
    XOR_t, NOT_t,



    LPAREN_t, RPAREN_t,
    LBRACK_t, RBRACK_t,
    LBRACE_t, RBRACE_t,
    COMMA_t,

    UNKNOWN_t

};
enum Type {
  INT_t,
  FLOAT_t,
  DOUBLE_t,
  BOOL_t,
  CHAR_t
  
};
char reserved_words_mapping[MAX_MAPPING_LEN][MAX_MAPPING_LEN] = {
  ";"     , "="     , "==", "!="  ,
  "<"     , ">"     , "<=", ">="  ,
  "+"     , "-"     , "/" , "*"   , 
  "%"     , "&"     , "|" , "^"   , 
  "!"     , "("     , ")" , "["   , 
  "]"     , "{"     , "}" , ","    
};
Token tokens_mapping[MAX_MAPPING_LEN] = {
  SEMICOL_t , ASSIGN_t, EQ_t    , NE_t    ,
  LT_t      , GT_t    , LE_t    , GE_t    ,
  PLUS_t    , MIN_t   , DIV_t   , MUL_t   ,
  MOD_t     , AND_t   , OR_t    , XOR_t   ,
  NOT_t     , LPAREN_t, RPAREN_t, LBRACK_t,
  RBRACK_t  , LBRACE_t, RBRACE_t, COMMA_t
};

typedef struct token_s {
  Token type;
  union {
    double double_value;
    int32_t int_value;
    bool bool_value;
    uint32_t id;
    Type data_type;
    char * name;
  }data;
} token_st;


static token_st gettok() {
  std::string read_string;
  token_st token = {};
  static int last_char = ' ';

  // skip whitespace.
  while (isspace(last_char)) {
    last_char = getchar();
  }
  // printf("current char: %c\n" , last_char);
  if (isalpha(last_char) || last_char == '_') {
    read_string = last_char;
    while (isalnum((last_char = getchar())) || last_char == '_')
      read_string += last_char;

    // std::cout << "read_string: " << read_string << "\n";

    if (read_string == "extern") {
      token.type = EXTERN_t;
    }
    else if (read_string == "int") {
      token.type = TYPE_t;
      token.data.data_type = INT_t;
    }
    else if (read_string == "return") {
      token.type = RETURN_t;
    }
    else if (read_string == "if") {
      token.type = IF_t;
    }
    else if (read_string == "else") {
      token.type = ELSE_t;
    }
    else if (read_string == "while") {
      token.type = WHILE_t;
    }
    else if (read_string == "for") {
      token.type = FOR_t;
    }
    else if (read_string == "do") {
      token.type == DO_t;
    }
    else if (read_string == "break") {
      token.type = BREAK_t;
    }
    else if (read_string == "continue") {
      token.type == CONTINUE_t;
    }
    else {
      token.data.name = (char*)malloc(read_string.length());
      strcpy(token.data.name, read_string.c_str());
      token.type = ID_t;
    }
    return token;
  }

  if (isdigit(last_char) || last_char == '.') {
    std::string NumStr;
    do {
      NumStr += last_char;
      last_char = getchar();
    } while (isdigit(last_char) || last_char == '.');

    token.type = INTCONST_t;
    token.data.int_value = strtod(NumStr.c_str(), nullptr);
    return token;
  }

  if (last_char == '#') {
    // Comment until end of line.
    do
      last_char = getchar();
    while (last_char != EOF && last_char != '\n' && last_char != '\r');

    if (last_char != EOF)
      return gettok();
  }

  // Check for end of file.  Don't eat the EOF.
  if (last_char == EOF) {
    token.type = EOF_t;
    return token;
  }
  char current_char = last_char;
  last_char = getchar();

  for (int i = 0; i < MAX_MAPPING_LEN; i++) {
    if (reserved_words_mapping[i][0] == current_char) {
        token.type = tokens_mapping[i];
        break;
    }
  }
  switch (current_char) {

    case '=':
      // token.type = ASSIGN_t;
      if (last_char == '=') {
        token.type = EQ_t;
        last_char = getchar();
      }
      break;
    case '!':
      // token.type = NOT_t;
      if (last_char == '=') {
        token.type = NE_t;
        last_char = getchar();
      }
      break;    

    case '<':
      // token.type = LT_t;
      if (last_char == '=') {
        token.type = LE_t;
        last_char = getchar();
      }
      break;
    case '>':
      // token.type = GT_t;
      if (last_char == '=') {
        token.type = GE_t;
        last_char = getchar();
      }
      break;
    case '/':
      // token.type = DIV_t;
      if (last_char == '/') {
        //skip comment
        do {
          last_char = getchar();
        } while (last_char != EOF && last_char != '\n');
        if (last_char != EOF)
          return gettok();
      }
      break;
  }
  return token;
}
void print_token(token_st token) {
  switch (token.type) {
    case LT_t:
      printf("(LT, '<')\n");
      break;
    case GT_t:
      printf("(GT, '>')\n");
      break;
    case LE_t:
      printf("(LE, '<=')\n");
      break;
    case GE_t:
      printf("(GE, '>=')\n");
      break;
    case EQ_t:
      printf("(EQ, '==')\n");
      break;
    case NOT_t:
      printf("(NOT, '!')\n");
      break;
    case NE_t:
      printf("(NE, '!=')\n");
      break;
    case AND_t:
      printf("(AND, '&')\n");
      break;
    case OR_t:
      printf("(OR, '|')\n");
      break;
    case XOR_t:
      printf("(XOR, '^')\n");
      break;
  
    
    case ID_t:
      printf("(ID, '%s')\n" , token.data.name);
      break;
    case ASSIGN_t:
      printf("(ASSIGN, '=')\n");
      break;
    case TYPE_t:
      printf("(TYPE, ");
      switch (token.data.data_type) {
        case INT_t:
          printf("'int')\n");
          break;
        case FLOAT_t:
          printf("'float')\n");
          break;
        case BOOL_t:
          printf("'bool')\n");
          break;
        case CHAR_t:
          printf("'char')\n");
          break;
        case DOUBLE_t:
          printf("'double')\n");
          break;
      }
      break;
    case INTCONST_t:
      printf("(INCONST, '%d')\n" , token.data.int_value);
      break;
    case SEMICOL_t:
      printf("(SEMICOLON, ';')\n");
      break;
    case RETURN_t:
      printf("(RETURN, 'return')\n");
      break;
    case IF_t:
      printf("(IF, 'if')\n");
      break;
    case ELSE_t:
      printf("(ELSE, 'else')\n");
      break;
    case LPAREN_t:
      printf("(LPAREN, '(')\n");
      break;
    case RPAREN_t:
      printf("(RPAREN, ')')\n");
      break;
    case LBRACE_t:
      printf("(LBRACE, '{')\n");
      break;
    case RBRACE_t:
      printf("(RBRACE, '}')\n");
      break;
    case LBRACK_t:
      printf("(LBRACK, '[')\n");
      break;
    case RBRACK_t:
      printf("(RBRACK, ']')\n");
      break;
    case COMMA_t:
      printf("(COMMA, ',')\n");
      break;
    case UNKNOWN_t:
      printf("(UNKNOWN)\n");
      break;
    case DIV_t:
      printf("(DIV, '/')\n");
      break;
    case MUL_t:
      printf("(MUL, '*')\n");
      break;
    case PLUS_t:
      printf("(PLUS, '+')\n");
      break;
    case MIN_t:
      printf("(MIN, '-')\n");
      break;
    case EOF_t:
      printf("(EOF)\n");
      break;
    default:
      printf("default case\n");
      break;
  }
}


int main() {


  // Prime the first token.
    int i = 0;
    token_st token = {};
    token.type = UNKNOWN_t;
    while(true) {
      token_st token = gettok();
      print_token(token);
      // free(token.data.name);
      if (token.type == EOF_t) break;
    }

  return 0;
}