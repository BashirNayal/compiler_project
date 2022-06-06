#ifndef LEXER_H
#define LEXER_H


#include "unistd.h"
#include "string.h"
#include "common.h"

#define MAX_MAPPING_LEN 64


enum Token {
    EOF_t,

    EXTERN_t, RETURN_t,
    IF_t, ELSE_t, WHILE_t, DO_t,
    FOR_t, BREAK_t, CONTINUE_t,
    

    ID_t, SEMICOL_t, TYPE_t,
    
    INTCONST_t, FLOATCONST_t,
    DOUBLECONST_t, BOOLCONST_t,
    CHARCONST_t, STRING_t,


    ASSIGN_t, EQ_t, NE_t,
    LT_t, GT_t, LE_t, GE_t,
    PLUS_t, MIN_t, DIV_t, 
    MUL_t, MOD_t, AND_t, OR_t,
    XOR_t, NOT_t,



    LPAREN_t, RPAREN_t,
    LBRACK_t, RBRACK_t,
    LBRACE_t, RBRACE_t,
    COMMA_t,  QUOTE_t,

    UNKNOWN_t

};
enum Type_en {
  INT_t,
  STRING_T,
  FLOAT_t,
  DOUBLE_t,
  BOOL_t,
  CHAR_t
  
};
static char reserved_words_mapping[MAX_MAPPING_LEN][MAX_MAPPING_LEN] = {
  ";"     , "="     , "==", "!="  ,
  "<"     , ">"     , "<=", ">="  ,
  "+"     , "-"     , "/" , "*"   , 
  "%"     , "&"     , "|" , "^"   , 
  "!"     , "("     , ")" , "["   , 
  "]"     , "{"     , "}" , ","   ,
  "\""
};
static Token tokens_mapping[MAX_MAPPING_LEN] = {
  SEMICOL_t , ASSIGN_t, EQ_t    , NE_t    ,
  LT_t      , GT_t    , LE_t    , GE_t    ,
  PLUS_t    , MIN_t   , DIV_t   , MUL_t   ,
  MOD_t     , AND_t   , OR_t    , XOR_t   ,
  NOT_t     , LPAREN_t, RPAREN_t, LBRACK_t,
  RBRACK_t  , LBRACE_t, RBRACE_t, COMMA_t ,
  QUOTE_t
};

typedef struct token_s {
  Token type;
  union {
    double double_value;
    int32_t int_value;
    bool bool_value;
    uint32_t id;
    Type_en data_type;
    char * name;
    char * str;
  }data;
} token_st;


void print_token(token_st token);
token_st gettok(void);
token_st getNextToken();


#endif