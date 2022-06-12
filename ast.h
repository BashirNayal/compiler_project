#ifndef AST_H
#define AST_H

#include "lexer.h"
#include "common.h"

void handle_typed_expr();

class Expression {
public:
  virtual ~Expression() {}
  virtual llvm::Value *codegen() = 0;
  virtual std::string stringify() {return nullptr;}
  // virtual void print(/*char* str = ""*/) {return;}
  virtual void print(std::string str) {return;}
};

class Const : public Expression {
  int val;

public:
  Const(int val) : val(val) {}
  // void print() {printf("Const node: %s ", std::to_string(val).c_str());}
  void print(std::string str) {
    std::cout << str << val << std::endl;
  }
  virtual llvm::Value *codegen() override;
  int get_val() {return val;}
};

class Return : public Expression {
  std::unique_ptr<Expression> value;
  
  public:
    Return(std::unique_ptr<Expression> value)
      : value(std::move(value)) {}

  void print(std::string str) {
    std::cout << str << "return\n";
    value.get()->print(str + "--");
  }
  virtual llvm::Value *codegen() override;
};

class VarDef : public Expression {
  std::string Name;
  Type_en type;

public:
  VarDef(const std::string &Name, Type_en type) : Name(Name), type(type){}
  // std::string get_name() {return Name;}
  // std::string stringify() {return Name.c_str();}
  // void print() {printf("Variable node: %s " , Name.c_str());}
  void print(std::string str) {
    std::cout << str << "var def\n";
    std::cout << str << "--name: " << Name << std::endl;
  }
  virtual llvm::Value *codegen() {return nullptr;}
};

class Assignment : public Expression {
  std::string var_name;
  std::unique_ptr<Expression> value;
  std::unique_ptr<VarDef> def;
  
  public:
    Assignment(std::string var_name, std::unique_ptr<Expression> value)
      : var_name(var_name), value(std::move(value)) {}
    Assignment(std::string var_name, std::unique_ptr<Expression> value, std::unique_ptr<VarDef> def)
  : var_name(var_name), def(std::move(def)), value(std::move(value)) {}

  void print(std::string str) {
    if (def) def->print(str);
    std::cout << str << "assign\n";
    std::cout << str + "--name: " << var_name << std::endl;
    value.get()->print(str + "--");
  }
  virtual llvm::Value *codegen() override;
};

class VarUse : public Expression {
  std::string var_name;
  std::unique_ptr<Expression> value; //TODO remove this

public:
  VarUse(const std::string &var_name, std::unique_ptr<Expression> value) : var_name(var_name), value(std::move(value)){}
  VarUse(const std::string &var_name) : var_name(var_name){}
  // std::string get_name() {return Name;}
  // std::string stringify() {return Name.c_str();}
  void print(std::string str) {
    std::cout << str << "var use\n";
    std::cout << str << "--name: " << var_name << std::endl;
    // if (value) value.get()->print(str + "--");
  }
  virtual llvm::Value *codegen() override;
};

class Param : public Expression {
  std::string Name;
  Type_en type;

public:
  Param(const std::string &Name, const Type_en type) : Name(Name), type(type) {}
  std::string get_name() {return Name;}
  std::string stringify() {return Name.c_str();}
  void print(std::string str) {
    std::cout << str << "param: " << type << " " << Name << std::endl;
  }
  virtual llvm::Value *codegen() {return nullptr;}
};


class Operator : public Expression {
  Token op;
  std::unique_ptr<Expression> lhs, rhs;

public:
  Operator(std::unique_ptr<Expression> lhs, Token op,
                std::unique_ptr<Expression> rhs)
    : op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}

  void print(std::string str) {
    std::cout << str << "operator\n";
    lhs.get()->print(str + "--");
    std::cout << str << op << std::endl;
    rhs.get()->print(str + "--");
  }
  virtual llvm::Value *codegen() override;

};
class String : public Expression {
  std::string string;
public:
  String(const std::string &str) : string(str) {}
  void print(std::string str) {
    std::cout << str << "string\n";
    std::cout << str << "--\"" << string << "\"\n";
  }
  virtual llvm::Value *codegen() override;
};

class CallExpression : public Expression {
  std::string callee;
  std::vector<std::unique_ptr<Expression>> args;

public:
  CallExpression(const std::string &callee) :
    callee(callee) {}
  CallExpression(const std::string &callee,
              std::vector<std::unique_ptr<Expression>> args)
    : callee(callee), args(std::move(args)) {}
  void print(std::string str) {
    std::cout << str << "fun call: " << callee << std::endl;
    if (args.size() == 0) {
      return;
    }
    for (int i = 0; i < args.size(); i++) {
      args.at(i)->print(str + "--");
    }
  }
  virtual llvm::Value *codegen() override;
};


class PrototypeAST {
  std::vector<std::unique_ptr<Param>> parameters;
  std::string fun_name;
  public:
    PrototypeAST(std::vector<std::unique_ptr<Param>> parameters,
              std::string fun_name)
      : parameters(move(parameters)), fun_name(fun_name) {}
  void print(std::string str) {
    std::cout << str << "proto: " << fun_name << std::endl;
    for (int i = 0; i < parameters.size(); i++) {
      parameters.at(i).get()->print(str + "--");
    }
  }
  llvm::Function *codegen();
  std::string get_name() {return fun_name;}
};

class Array : public Expression {
  std::string name; 
  std::unique_ptr<Expression> size;
  std::vector<std::unique_ptr<Expression>> initial_values;
  public:
  Array(std::string name, std::unique_ptr<Expression> size) :
  size(std::move(size)), name(name) {}

  Array(std::string name, std::unique_ptr<Expression> size, std::vector<std::unique_ptr<Expression>> intial_values) :
  size(std::move(size)), name(name), initial_values(std::move(intial_values)) {}  

  void print(std::string str) {
    std::cout << str << "array: " << name << std::endl;
    std::cout << str << "size:" << std::endl;
    size->print(str);
    for (int i = 0; i < initial_values.size(); i++) {
      initial_values.at(i)->print(str + "--");
    }
  }
  virtual llvm::Value *codegen() override;
  
};

class ArrayRef : public Expression {
  std::string name;
  std::unique_ptr<Expression> index;
  std::unique_ptr<Expression> value;
  public:
  ArrayRef(std::string name, std::unique_ptr<Expression> index) :
  name(name), index(std::move(index)) {}
  ArrayRef(std::string name, std::unique_ptr<Expression> index, std::unique_ptr<Expression> value) :
  name(name), value(std::move(value)), index(std::move(index)) {}

  void print(std::string str) {
    log(str << "array ref: " << name);
    log(str << "index: ");
    index->print("--" + str);
    if (value) {
      log(str << "=");
      value->print("--" + str);
    }
  } 
  virtual llvm::Value * codegen() override;

};
class Block : public Expression{
  std::vector<std::unique_ptr<Expression>> expressions;

  public:
    Block(std::vector<std::unique_ptr<Expression>> expressions)
      : expressions(std::move(expressions)) {}

    void print(std::string str) {
      std::cout << str << "block: " << std::endl;
      for (int i = 0; i < expressions.size(); i++) {
        expressions.at(i).get()->print(str + "--");
      }
    }
    virtual llvm::Value *codegen() override;
};

class Elif : public Expression {
  std::unique_ptr<Expression> cond;
  std::unique_ptr<Block> body;
  public:
  Elif(std::unique_ptr<Expression> cond, 
    std::unique_ptr<Block> body) : 
    cond(std::move(cond)), body(std::move(body)) {}
  virtual llvm::Value *codegen() override;
};

class If : public Expression {
  std::unique_ptr<Expression> cond;
  std::unique_ptr<Block> else_body;
  std::unique_ptr<Block> body;
  std::vector<std::unique_ptr<Elif>> elif;
  public:
    If(std::unique_ptr<Expression> cond, 
      std::unique_ptr<Block> body, 
      std::unique_ptr<Block> else_body,
      std::vector<std::unique_ptr<Elif>> elif) :
      cond(std::move(cond)), 
      else_body(std::move(else_body)),  
      body(std::move(body)),
      elif(std::move(elif)) {}

    If(std::unique_ptr<Expression> cond, 
      std::unique_ptr<Block> body, 
      std::vector<std::unique_ptr<Elif>> elif) :
      cond(std::move(cond)), body(std::move(body)), elif(std::move(elif)) {}

    If(std::unique_ptr<Expression> cond, 
      std::unique_ptr<Block> body, 
      std::unique_ptr<Block> else_body) :
      cond(std::move(cond)), body(std::move(body)), else_body(std::move(else_body)) {}

    If(std::unique_ptr<Expression> cond, 
      std::unique_ptr<Block> body) :
      cond(std::move(cond)), body(std::move(body)) {}
    void print(std::string str) {
      std::cout << str << "if\n";
      cond.get()->print(str + "--");
      body.get()->print(str + "--");
      //TODO: print elif's
      if (else_body) {
        std::cout << str << "else\n";
        else_body.get()->print(str + "--");
      }

    }
    virtual llvm::Value *codegen() override;

};

class While : public Expression {
  std::unique_ptr<Expression> cond;
  std::unique_ptr<Block> body;
  public:
    While(std::unique_ptr<Expression> cond, 
      std::unique_ptr<Block> body) :
      cond(std::move(cond)), body(std::move(body)) {}
    void print(std::string str) {
      std::cout << str << "while\n";
      cond.get()->print(str + "--");
      body.get()->print(str + "--");
    }
    virtual llvm::Value *codegen() override;

};


class FunctionAST : public Expression{ //TODO: This might be bad/ add a node class
  std::unique_ptr<PrototypeAST> Proto;
  std::unique_ptr<Block> Body;

public:
  FunctionAST(std::unique_ptr<PrototypeAST> Proto,
              std::unique_ptr<Block> Body)
    : Proto(std::move(Proto)), Body(std::move(Body)) {}

  void print(std::string str) {
    std::cout << str << "fun def\n";
    Proto.get()->print(str + "--");
    Body.get()->print(str + "--");
  }
  llvm::Function *codegen();
};
std::unique_ptr<Expression> parse_identifier_exp();
std::unique_ptr<Expression> parse_token(token_st current_token);
static std::unique_ptr<Expression> ParsePrimary();
static std::unique_ptr<Expression> ParseBinOpRHS(int ExprPrec,
                                              std::unique_ptr<Expression> LHS);
static std::unique_ptr<FunctionAST> ParseTopLevelExpr();

void handle_extern();
void handle_top_level_exp();
std::unique_ptr<Expression> parse_return();
std::unique_ptr<Expression> parse_id_or_fun();
std::unique_ptr<Block> parse_block();
std::unique_ptr<Expression> parse_typed_expression();
std::unique_ptr<Expression> parse_expression();
std::unique_ptr<Expression> parse_if();


#endif