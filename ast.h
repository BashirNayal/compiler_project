#pragma once

#include <string>
#include <memory>
#include <vector>
#include "lexer.h"

class Expression {
public:
  virtual ~Expression() {}
  virtual std::string stringify() {return nullptr;}
};

class Const : public Expression {
  double val;

public:
  Const(double val) : val(val) {}
  std::string stringify() {return std::to_string(val);}
};
class Variable : public Expression {
  std::string Name;

public:
  Variable(const std::string &Name) : Name(Name) {}
  std::string get_name() {return Name;}
  std::string stringify() {return Name.c_str();}
};

class Operator : public Expression {
  char Op;
  std::unique_ptr<Expression> lhs, rhs;

public:
  Operator(std::unique_ptr<Expression> lhs, char op,
                std::unique_ptr<Expression> rhs)
    : Op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}
};

class CallExpression : public Expression {
  std::string Callee;
  std::vector<std::unique_ptr<Expression>> Args;

public:
  CallExpression(const std::string &Callee,
              std::vector<std::unique_ptr<Expression>> Args)
    : Callee(Callee), Args(std::move(Args)) {}
};


class PrototypeAST {
  std::string Name;
  std::vector<std::string> Args;

public:
  PrototypeAST(const std::string &name, std::vector<std::string> Args)
    : Name(name), Args(std::move(Args)) {}

  const std::string &getName() const { return Name; }
};

class FunctionAST {
  std::unique_ptr<PrototypeAST> Proto;
  std::unique_ptr<Expression> Body;

public:
  FunctionAST(std::unique_ptr<PrototypeAST> Proto,
              std::unique_ptr<Expression> Body)
    : Proto(std::move(Proto)), Body(std::move(Body)) {}
};

std::unique_ptr<Expression> parse_token(token_st current_token);