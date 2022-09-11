all: scanner

scanner.tab.c scanner.tab.h:	scanner.y
	bison -t -v -d scanner.y

lex.yy.c: scanner.l scanner.tab.h
	flex scanner.l

scanner: lex.yy.c scanner.tab.c scanner.tab.h scanType.h helpers.h helpers.cpp
	g++ -o scanner scanner.tab.c lex.yy.c helpers.cpp

clean:
	rm scanner scanner.tab.c lex.yy.c scanner.tab.h scanner.output