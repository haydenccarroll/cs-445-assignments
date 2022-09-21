%{
#include <algorithm>
#include <string>
#include <cstring>

#include "scanType.h"  // TokenData Type
#include "c-.tab.h"  // token definitions from the bison
#include "helpers.h"

int line = 1;
int numErrors;    // ERR err count

static int setValue(int linenum, int tokenClass, char* strVal)
{
    int i = 0;
    // create the pass-back data space
    yylval.tokenData = new TokenData;

    // fill it up
    yylval.tokenData->linenum = linenum;
    yylval.tokenData->tokenstr = std::string(strVal);
  
    switch (tokenClass) {
        case ID:
            // do nothing for ID
            break;
        case STRINGCONST:
            yylval.tokenData->stringConst = helpers::toString(helpers::removeQuotes(strVal));
            break;
        case NUMCONST:
            yylval.tokenData->numConst = std::atoi(strVal);
            break;
        case CHARCONST:
            // want to populate stringConst too because we want to warn if a char is too long
            yylval.tokenData->stringConst = helpers::toString(helpers::removeQuotes(strVal));
            yylval.tokenData->charConst = helpers::toChar(helpers::removeQuotes(strVal));
            break;
        case BOOLCONST:
            yylval.tokenData->boolConst = (yylval.tokenData->tokenstr == "true");
            break;
        case KEYWORD:
            std::transform(yylval.tokenData->tokenstr.begin(), yylval.tokenData->tokenstr.end(), yylval.tokenData->tokenstr.begin(), toupper);
            break;
        default:
            break;

    }

    // return the tokenclass
    return tokenClass;
}

%}

%option noyywrap

%%
\/\/.*\n                    { line++; }
\"((\\\")|([^\n\"]))*\"     { return setValue(line, STRINGCONST, yytext); }
\'((\\\')|([^\n\']))*\'     { return setValue(line, CHARCONST, yytext); }
(true)|(false)              { return setValue(line, BOOLCONST, yytext); }
while|if|for|to|return|break|not|and|or|by|do|then|else|begin|end|int|static|bool|char   { return setValue(line, KEYWORD, yytext); }
[a-zA-Z][a-zA-Z0-9]*        { return setValue(line, ID, yytext); }
[0-9]+                      { return setValue(line, NUMCONST, yytext); }
\(|\)|\?|\*|\/|\%|\-|\[|\]|\+|\<\-|\+\=|\=\=|\-\=|\*\=|\/\=|\;|\<|\<\=|\>|\>\=|\=|\!\=|\+\+|\-\-|\:|\,|\{|\} { return setValue(line, TOKEN, yytext); }
[ \t]                       ;
\n                          { line++; return setValue(line, yytext[0], yytext ); }
.                           { printf("ERROR(%d): Invalid or misplaced input character: \'%c\'. Character Ignored.\n", line, yytext[0]); numErrors++; }
%%
