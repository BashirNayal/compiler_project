#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <iostream>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <utility>

#include "llvm.h"

#define log(str) llvm::errs() << str << "\n"

#endif