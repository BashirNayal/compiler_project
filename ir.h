#ifndef IR_H
#define IR_H

#include "common.h"
#include "ast.h"
llvm::Value *log_errorV(const char *str);
void init_module();
void get_object_file();

#endif
