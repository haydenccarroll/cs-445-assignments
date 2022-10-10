%{
#include "scanType.h" // must be included before c-.tab.h

// C++ headers and stuff
#include <iostream>
#include <string>

#include "c-.tab.h"
extern void yyerror(const char *errMsg); // defined in c-.y
int passToken(int tokenClass);

%}
%option noyywrap

%%
    // token specifications
true|false           { return passToken(BOOLCONST); }
while|for|if         { return passToken(KEYWORD); }
[A-Za-z][A-Za-z0-9]+ { return passToken(ID); }
[0-9]+               { return passToken(NUMCONST); }
'[^\\']'|'\\.'       { return passToken(CHARCONST); }
\"([^\\"]|\\.)*\"    { return passToken(STRINGCONST); }
\{|\}                { return passToken(TOKEN); }
.       { yyerror("Invalid or misplaced input character: CHARACTER. Character Ignored."); }
%%
// C++ functions

int passToken(int tokenClass)
{
    yylval.tokenData = new TokenData;
    switch (tokenClass)
    {
    case ID:
        yylval.tokenData->str = yytext;
        break;
    case NUMCONST:
        yylval.tokenData->str = yytext;
        yylval.tokenData->num = atoi(yytext);
        break;
    case CHARCONST:
        yylval.tokenData->str = yytext;
        yylval.tokenData->charV = 'c'; // placeholder
        break;
    case STRINGCONST:
        yylval.tokenData->str = yytext; // placeholder
        break;
    case BOOLCONST:
        yylval.tokenData->str = yytext;
        yylval.tokenData->num = (yytext == "true") ? 1 : 0;
        break;
    case KEYWORD:
        yylval.tokenData->str = yytext;
        break;
    case TOKEN:
        yylval.tokenData->str = yytext;
        break;
    }

    return tokenClass;
}