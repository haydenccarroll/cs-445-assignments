%{
#include "scanType.h" // must be included before c-.tab.h

// C++ headers and stuff
#include <iostream>
#include <string>

#include "c-.tab.h"
extern void yyerror(const char *errMsg); // defined in c-.y

%}
%option noyywrap

%%
    // token specifications
"hello" { yylval.tokenData = new TokenData; yylval.tokenData->str = yytext; return (HELLO);}
([0-9])+ { yylval.tokenData = new TokenData; yylval.tokenData->str = yytext; return (NUMBERS);}
";"     { return (SEMICOLON);}
.       { yyerror("Invalid or misplaced input character: CHARACTER. Character Ignored."); }
%%
// C++ functions
