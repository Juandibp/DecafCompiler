all:
	$(MAKE) bison
	$(MAKE)	flex
	g++ -c  compiler/objetos.cpp parser.tab.c lex.yy.c 
	ar rvs lexgram.a  parser.tab.o lex.yy.o objetos.o
	g++ -std=c++11 -Wall -Wextra compiler/main.cpp lexgram.a -o proyecto



bison:
	bison -d compiler/parser.y	
	
	
flex:
	flex compiler/scanner.l
	
test:
	
	