OBJS = ast.o lexer.o main.o 
HEADERS = lexer.h ast.h
OUT = comp.bin
FLAGS = -DDEBUG

all: $(OBJS)
	g++ -o $(OUT) $(OBJS)


ast.o: ast.cc ast.h
	g++ -c $(FLAGS) ast.cc
	
lexer.o: lexer.cc lexer.h
	g++ -c $(FLAGS) lexer.cc

main.o: main.cc lexer.h ast.h
	g++ -c $(FLAGS) main.cc

clean:
	rm -f $(OBJS) $(OUT)