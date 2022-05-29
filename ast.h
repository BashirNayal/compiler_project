#pragma once

#include <string>
#include <memory>
#include <vector>
#include "lexer.h"

void handle_typed_expr();

class Expression {
public:
  virtual ~Expression() {}
  virtual std::string stringify() {return nullptr;}
  // virtual void print(/*char* str = ""*/) {return;}
  virtual void print(std::string str) {return;}
};

class Const : public Expression {
  double val;

public:
  Const(double val) : val(val) {}
  std::string stringify() {return std::to_string(val);}
  // void print() {printf("Const node: %s ", std::to_string(val).c_str());}
  void print(std::string str) {
    std::cout << str << val << std::endl;
  }
};

class Assignment : public Expression {
  std::string var_name;
  std::unique_ptr<Expression> value;
  
  public:
    Assignment(std::string var_name, std::unique_ptr<Expression> value)
      : var_name(var_name), value(std::move(value)) {}

  void print(std::string str) {
    std::cout << str << "ASSIGNMENT\n";
    std::cout << str + "--VARNAME: " << var_name << std::endl;
    value.get()->print(str + "--");
  }
};

class VarDef : public Expression {
  std::string Name;
  Type type;

public:
  VarDef(const std::string &Name, Type type) : Name(Name), type(type){}
  // std::string get_name() {return Name;}
  // std::string stringify() {return Name.c_str();}
  // void print() {printf("Variable node: %s " , Name.c_str());}
};
class Param : public Expression {
  std::string Name;
  Type type;

public:
  Param(const std::string &Name, const Type type) : Name(Name), type(type) {}
  std::string get_name() {return Name;}
  std::string stringify() {return Name.c_str();}
    void print(std::string str) {
      std::cout << str << "PARAM: " << type << " " << Name << std::endl;
    }
};


class Operator : public Expression {
  char Op;
  std::unique_ptr<Expression> lhs, rhs;

public:
  Operator(std::unique_ptr<Expression> lhs, char op,
                std::unique_ptr<Expression> rhs)
    : Op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}

  // void print() {
  //   printf("Operator node: (");
  //   lhs.get()->print();
  //   printf(" %c ", Op);
  //   rhs.get()->print();
  //   printf(") ");
  // }



};

class CallExpression : public Expression {
  std::string Callee;
  std::vector<std::unique_ptr<Expression>> args;

public:
  CallExpression(const std::string &Callee,
              std::vector<std::unique_ptr<Expression>> args)
    : Callee(Callee), args(std::move(args)) {}
};


class PrototypeAST {
  std::vector<std::unique_ptr<Param>> parameters;
  std::string fun_name;
  public:
    PrototypeAST(std::vector<std::unique_ptr<Param>> parameters,
              std::string fun_name)
      : parameters(move(parameters)), fun_name(fun_name) {}
  void print(std::string str) {
    std::cout << str << "PROTO: " << fun_name << std::endl;
    for (int i = 0; i < parameters.size(); i++) {
      parameters.at(i).get()->print(str + "--");
    }
  }
};

class Block {
  std::vector<std::unique_ptr<Expression>> expressions;

  public:
    Block(std::vector<std::unique_ptr<Expression>> expressions)
      : expressions(std::move(expressions)) {}

    void print(std::string str) {
      std::cout << str << "BLOCK: " << std::endl;
      for (int i = 0; i < expressions.size(); i++) {
        expressions.at(i).get()->print(str + "--");
      }
    }
};

class FunctionAST : public Expression{ //TODO: This might be bad/ add a node class
  std::unique_ptr<PrototypeAST> Proto;
  std::unique_ptr<Block> Body;

public:
  FunctionAST(std::unique_ptr<PrototypeAST> Proto,
              std::unique_ptr<Block> Body)
    : Proto(std::move(Proto)), Body(std::move(Body)) {}

  void print(std::string str) {
    std::cout << str << "FUN DEF\n";
    Proto.get()->print(str + "--");
    Body.get()->print(str + "--");
  }
};
std::unique_ptr<Expression> parse_identifier_exp();
std::unique_ptr<Expression> parse_token(token_st current_token);
static std::unique_ptr<Expression> ParsePrimary();
static std::unique_ptr<Expression> ParseBinOpRHS(int ExprPrec,
                                              std::unique_ptr<Expression> LHS);
static std::unique_ptr<FunctionAST> ParseTopLevelExpr();

void handle_extern();
void handle_top_level_exp();
std::unique_ptr<Expression> parse_id_or_fun();
std::unique_ptr<Block> parse_block();


