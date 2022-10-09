%{
#include "scanType.h" // must be included before c-.tab.h

// C++ headers and stuff
#include <iostream>
#include <string>

#include "c-.tab.h"
%}
%option noyywrap

    // regular expressions
numbers     ([0-9])+

%%
    // token specifications
"hello" { std::cout << "found a hello"; yylval.tokenData = new TokenData; yylval.tokenData->str = yytext; return (HELLO);}
numbers { return (NUMBERS);}
";"     { return (SEMICOLON);}
.       { return }
%%
// C++ functions
