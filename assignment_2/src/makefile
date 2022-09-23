all: c-

c-.tab.c c-.tab.h:	c-.y
	bison -t -v -d c-.y

lex.yy.c: c-.l c-.tab.h
	flex c-.l

c-: lex.yy.c c-.tab.c c-.tab.h scanType.h helpers.h helpers.cpp
	g++ -o c- c-.tab.c lex.yy.c helpers.cpp

clean:
	rm c- c-.tab.c lex.yy.c c-.tab.h c-.output