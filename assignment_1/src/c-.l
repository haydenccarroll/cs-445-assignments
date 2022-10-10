%{
#include "scanType.h" // must be included before c-.tab.h

// C++ headers and stuff
#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>

#include "c-.tab.h"

extern char* yytext;

int passToken(int tokenClass);
void processStringConst();
std::string toUpper(std::string str);
static int lineNum = 1;

%}
%option noyywrap

%%
    // token specifications
\n                   { lineNum++;}
[ \t]                {}
true|false           { return passToken(BOOLCONST); }
while|for|if|int|return         { return passToken(KEYWORD); }
[A-Za-z][A-Za-z0-9]* { return passToken(ID); }
[0-9]+               { return passToken(NUMCONST); }
'[^\\']'|'\\.'       { return passToken(CHARCONST); }
\"([^\\"]|\\.)*\"    { return passToken(STRINGCONST); }
\=\=|\>\=|\<\=|\!\=|\{|\}|\<|\>|\(|\)|\=|;                { return passToken(TOKEN); }
.       { std::cout << "ERROR(" << lineNum << "): Invalid or misplaced input character: '" << yytext << "'. Character Ignored.\n"; }
%%
// C++ functions

int passToken(int tokenClass)
{
    yylval.tokenData = new TokenData;
    yylval.tokenData->lineNum = lineNum;
    switch (tokenClass)
    {
    case ID:
        yylval.tokenData->inputStr = yytext;
        break;
    case NUMCONST:
        yylval.tokenData->inputStr = yytext;
        yylval.tokenData->num = atoi(yytext);
        break;
    case CHARCONST:
        yylval.tokenData->inputStr = yytext;
        yylval.tokenData->charV = 'c'; // placeholder
        break;
    case STRINGCONST:
        processStringConst();
        break;
    case BOOLCONST:
        yylval.tokenData->inputStr = yytext;
        yylval.tokenData->num = (yytext == "true") ? 1 : 0;
        break;
    case KEYWORD:
        yylval.tokenData->inputStr = yytext;
        yylval.tokenData->str = toUpper(yylval.tokenData->inputStr);
        break;
    case TOKEN:
        yylval.tokenData->inputStr = yytext;
        break;
    }

    return tokenClass;
}

std::string toUpper(std::string str)
{
    std::string cpy = str;
    for (auto & c: cpy) c = toupper(c);
    return cpy;

}

void processStringConst()
{
    std::string inputStr = yytext;
    std::string newStr = "";
    yylval.tokenData->inputStr = inputStr;
    for (int i=0; i < inputStr.length(); i++)
    {
        if (inputStr[i] == '\\')
        {
            if (i+1 == inputStr.length())
            {
                throw std::runtime_error("runtime error: \\ escape character found at last char in string.\n");
            }
            switch(inputStr[i+1])
            {
            case '0':
                newStr += '\0';
                break;
            case 'n':
                newStr += '\n';
                break;
            default:
                newStr += inputStr[i+1];
                break;
            }
            i++; // increment i an additional time
        }
    }

    yylval.tokenData->str = newStr;
}