#pragma once
#include "common.h"
#include "ast.h"
llvm::Value *log_errorV(const char *str);
void get_ir(std::unique_ptr<Expression> expr);
void init_module();
void get_object_file();
