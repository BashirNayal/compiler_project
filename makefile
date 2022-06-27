
OBJS = main.o  ast.o lexer.o ir.o boundscheck.o
HEADERS = lexer.h ast.h llvm.h ir.h common.h
OUT = comp.bin
FLAGS = -g
LLVM_HDRS= `llvm-config-14 --cxxflags`

# CC = clang-14
CC= g++
LLVM_FLAGS=`llvm-config-14 --cxxflags --ldflags --system-libs --libs core`



all: $(OBJS)
	$(CC) -o $(OUT) $(OBJS) $(LLVM_FLAGS)

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
	