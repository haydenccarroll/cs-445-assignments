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
%token ID NUMCONST CHARCONST STRINGCONST BOOLCONST KEYWORD TOKEN
%type <tokenData> ID NUMCONST CHARCONST STRINGCONST BOOLCONST KEYWORD TOKEN

%%
program : 
    stmts
;

stmts: stmt stmts
     | stmt
;
stmt: ID        {std::cout << "idconst";}
    | NUMCONST  {std::cout << "numconst";}
    | CHARCONST {std::cout << "charconst";}
    | STRINGCONST {std::cout << "stringconst";}
    | BOOLCONST {std::cout << "boolconst";}
    | KEYWORD {std::cout << "keyword";}
    | TOKEN {std::cout << "token";}
;
%%


int main()
{
    yyparse();
    return 0;
}