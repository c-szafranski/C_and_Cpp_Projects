OBJ = silc.o Lexer.o Token.o Parser.o
OPTS = -g -c -Wall -Werror

silc: $(OBJ)
	g++ -o silc $(OBJ)
silc.o: silc.cc
	g++ $(OPTS) silc.cc
Lexer.o: Lexer.h Lexer.cc Token.h
	g++ $(OPTS) Lexer.cc
Token.o: Token.cc  Token.h Parser.h
	g++ $(OPTS) Token.cc
Parser.o: Parser.h Parser.cc Token.h Lexer.h
	g++ $(OPTS) Parser.cc

clean:
	rm -f *.o 
