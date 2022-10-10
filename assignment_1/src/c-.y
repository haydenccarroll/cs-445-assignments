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
stmt: ID          {std::cout << "Line " << "1" << " Token: ID Value: " << yylval.tokenData->str << std::endl;}
    | NUMCONST    {std::cout << "Line " << "1" << " Token: NUMCONST Value: " << yylval.tokenData->num << " Input: " << yylval.tokenData->str << std::endl;}
    | CHARCONST   {std::cout << "Line " << "1" << " Token: CHARCONST Value: '" << yylval.tokenData->charV << "' Input: " << yylval.tokenData->str << std::endl;}
    | STRINGCONST {std::cout << "Line " << "1" << " Token: STRINGCONST Value: \"" << yylval.tokenData->str << "\" Len: " << "9" << " Input: " << yylval.tokenData->str << std::endl;}
    | BOOLCONST   {std::cout << "Line " << "1" << " Token: BOOLCONST Value: " << yylval.tokenData->num << " Input: " << yylval.tokenData->str << std::endl;}
    | KEYWORD     {std::cout << "Line " << "1" << " Token: " << yylval.tokenData->str << std::endl;}
    | TOKEN       {std::cout << "Line " << "1" << " Token: " << yylval.tokenData->str << std::endl;}
;
%%


int main()
{
    yyparse();
    return 0;
}