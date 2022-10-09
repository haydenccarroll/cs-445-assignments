%{
// C++ header stuff
#include <iostream>
#include <string>

#include "scanType.h" // must be included before tab.h
#include "c-.tab.h"

extern int yylex();
void yyerror(const char *errMsg)
{
    std::cout << "ERROR(" << "LINE NUMBER" << "): " << errMsg << std::endl;
}


%}

%union {
    struct TokenData* tokenData;
}

    // define tokens
%token HELLO SEMICOLON NUMBERS OTHER
%type <tokenData> HELLO SEMICOLON NUMBERS OTHER

%%
program : 
    stmts
;

stmts:
    | stmt SEMICOLON stmts
stmt: 
    HELLO {std::cout << "string";}
    | OTHER
    ;
%%


int main()
{
    yyparse();
    return 0;
}