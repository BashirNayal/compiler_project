
OBJS = main.o  ast.o lexer.o ir.o boundscheck.o
HEADERS = lexer.h ast.h llvm.h ir.h common.h
OUT = comp.bin
FLAGS = -g
# LIB_DIRS= /lib/llvm-14
LLVM_HDRS= `llvm-config-14 --cxxflags`

# CC = clang-14
CC= g++
LLVM_FLAGS=`llvm-config-14 --cxxflags --ldflags --system-libs --libs core`#mcjit native`



all: $(OBJS)
	$(CC) -o $(OUT) $(OBJS) $(LLVM_FLAGS)

# common.o: common.cc $(HEADERS)
# 	$(CC) -c $(FLAGS) common.cc $(LLVM_HDRS)

boundscheck.o: boundscheck.cc $(HEADERS)
	$(CC) -c $(FLAGS) boundscheck.cc $(LLVM_FLAGS) $(LLVM_HDRS)

ast.o: ast.cc $(HEADERS)
	$(CC) ast.h -c  $(FLAGS) ast.cc $(LLVM_FLAGS) $(LLVM_HDRS)
	
lexer.o: lexer.cc $(HEADERS)
	$(CC) -c $(FLAGS) lexer.cc $(LLVM_HDRS)

ir.o: ir.cc $(HEADERS)
	$(CC) -c $(FLAGS) ir.cc $(LLVM_HDRS)


main.o: main.cc $(HEADERS)
	$(CC) -c $(FLAGS) main.cc $(LLVM_HDRS)


clean:
	rm -f $(OBJS) $(OUT)







	# $(CC) -o $(OUT) $(LIB_DIRS)/lib/libLLVMCore.a $(LIB_DIRS)/lib/libLLVMSupport.a $(LIB_DIRS)/lib/libLLVMSystem.a $(OBJS)
	# $(CC) `llvm-config-14 --libs --cxxflags` -o $(OUT) $(OBJS)



	# $(CC) -c -I$(LIB_DIRS)/include $(FLAGS) main.cc
	# $(CC) -c $(LIB_HDRS) $(FLAGS) main.cc