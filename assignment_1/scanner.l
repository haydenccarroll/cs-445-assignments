%{
// this *order* of these includes is mandatory
#include <algorithm>
#include <string>
#include <cstring>

#include "scanType.hpp"  // TokenData Type
#include "scanner.tab.h"  // token definitions from the bison
#include "strutil.hpp"

int line = 1;
int numErrors;    // ERR err count

static int setValue(int linenum, int tokenClass, char *svalue)
{
    int i = 0;
    // create the pass-back data space
    yylval.tokenData = new TokenData;

    // fill it up
    yylval.tokenData->linenum = linenum;
    yylval.tokenData->tokenstr = std::string(svalue);
  
    switch (tokenClass) {
        case ID:
            break;
        case NUMCONST:
            yylval.tokenData->numConst = std::atoi(svalue);
            break;
        case CHARCONST:
            yylval.tokenData->charConst = strutil::get_first_char(strutil::remove_quotes(svalue));
            break;
        case BOOLCONST:
            yylval.tokenData->boolConst = yylval.tokenData->tokenstr == "true";
            break;
        case STRINGCONST:
            yylval.tokenData->stringConst = strutil::make_str(strutil::remove_quotes(svalue));
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