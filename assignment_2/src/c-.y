%{
// C++ header stuff
#include <iostream>
#include <string>
#include <stdexcept>

#include "scanType.hpp" // must be included before tab.h
#include "c-.tab.h"

extern int yylex();
void yyerror(std::string msg) {std::cout << msg << std::endl;};
extern FILE* yyin;

%}

%union {
    struct TokenData* tokenData;
}

    // define tokens
%token <tokenData> ID NUMCONST CHARCONST STRINGCONST BOOLCONST KEYWORD TOKEN

%%
program : 
    stmts
;

stmts: stmt stmts
     | stmt
;
stmt: ID          {std::cout << "Line " << yylval.tokenData->lineNum << " Token: ID Value: " << yylval.tokenData->inputStr << std::endl;}
    | NUMCONST    {std::cout << "Line " << yylval.tokenData->lineNum << " Token: NUMCONST Value: " << yylval.tokenData->num << "  Input: " << yylval.tokenData->inputStr << std::endl;}
    | CHARCONST   {std::cout << "Line " << yylval.tokenData->lineNum << " Token: CHARCONST Value: '" << yylval.tokenData->charV << "'  Input: " << yylval.tokenData->inputStr << std::endl;}
    | STRINGCONST {std::cout << "Line " << yylval.tokenData->lineNum << " Token: STRINGCONST Value: \"" << yylval.tokenData->str << "\"  Len: " << yylval.tokenData->str.length() << "  Input: " << yylval.tokenData->inputStr << std::endl;}
    | BOOLCONST   {std::cout << "Line " << yylval.tokenData->lineNum << " Token: BOOLCONST Value: " << yylval.tokenData->num << "  Input: " << yylval.tokenData->inputStr << std::endl;}
    | KEYWORD     {std::cout << "Line " << yylval.tokenData->lineNum << " Token: " << yylval.tokenData->str << std::endl;}
    | TOKEN       {std::cout << "Line " << yylval.tokenData->lineNum << " Token: " << yylval.tokenData->str << std::endl;}
;
%%


int main(int argc, char** argv)
{
    if (argc > 1)
    {
        yyin = fopen(argv[1], "r");
        if (!yyin)
        {
            throw std::runtime_error("runtime error: could not open input file.");
        }
    }

    yyparse();
    return 0;
}
