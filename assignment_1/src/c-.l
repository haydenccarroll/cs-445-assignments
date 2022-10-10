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
    switch (tokenClass)
    {
    case ID:
        break;
    case NUMCONST:
        break;
    case CHARCONST:
        break;
    case STRINGCONST:
        break;
    case BOOLCONST:
        break;
    case KEYWORD:
        break;
    case TOKEN:
        break;

    }

    return tokenClass;
}