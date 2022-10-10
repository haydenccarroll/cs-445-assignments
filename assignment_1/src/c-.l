%{
#include "scanType.h" // must be included before c-.tab.h

// C++ headers and stuff
#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>
#include <map>

#include "c-.tab.h"

extern char* yytext;

int passToken(int tokenClass);
std::string processStringConst(std::string str);
std::string processTokenConst(std::string str);
int processBoolConst(std::string str);
char processCharConst(std::string str);
std::string toUpper(std::string str);
static int lineNum = 1;

%}
%option noyywrap

%%
    // token specifications
\/\/[^\n]*           {}
\n                   { lineNum++;}
[ \t]                {}
true|false           { return passToken(BOOLCONST); }
while|for|if|int|bool|char|static|and|or|to|by|do|then|break|else|return|not         { return passToken(KEYWORD); }
[A-Za-z][A-Za-z0-9]* { return passToken(ID); }
[0-9]+               { return passToken(NUMCONST); }
\'((\\\')|([^\n\']))*\'       { return passToken(CHARCONST); }
\"([^\\"\n]|\\.)*\"    { return passToken(STRINGCONST); }
\=\=|\>\=|\<\=|\!\=|\+\+|\-\-|\+\=|\{|\}|\<|\>|\(|\)|\=|\;|\*|\%|\/|\-|\?|\+|\[|\]|\,|\:                { return passToken(TOKEN); }
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
        yylval.tokenData->charV = processCharConst(yytext); // placeholder
        break;
    case STRINGCONST:
        yylval.tokenData->inputStr = yytext;
        yylval.tokenData->str = processStringConst(yytext);
        break;
    case BOOLCONST:
        yylval.tokenData->inputStr = yytext;
        yylval.tokenData->num = processBoolConst(yytext);
        break;
    case KEYWORD:
        yylval.tokenData->inputStr = yytext;
        yylval.tokenData->str = toUpper(yylval.tokenData->inputStr);
        break;
    case TOKEN:
        yylval.tokenData->inputStr = yytext;
        yylval.tokenData->str = processTokenConst(yytext);
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

int processBoolConst(std::string str)
{
    return (str == "true");
}

std::string processStringConst(std::string str)
{
    std::string inputStr = str;
    std::string noQuotes = inputStr.substr(1, inputStr.size() - 2);
    std::string cumStr = "";
    for (int i=0; i < noQuotes.length(); i++)
    {
        if (noQuotes[i] == '\\')
        {
            if (i+1 == noQuotes.length())
            {
                throw std::runtime_error("runtime error: \\ escape character found at last char in string.\n");
            }
            switch(noQuotes[i+1])
            {
            case '0':
                cumStr += '\0';
                break;
            case 'n':
                cumStr += '\n';
                break;
            default:
                cumStr += noQuotes[i+1];
                break;
            }
            i++; // increment i an additional time
        } else {
            cumStr += noQuotes[i];
        }
    }

    return cumStr;
}

char processCharConst(std::string str)
{
    std::string inputStr = str;
    std::string processedStr = processStringConst(inputStr);

    if (processedStr.length() > 1)
    {
        std::cout << "WARNING(" << lineNum << "): character is " << processedStr.length() << " characters long and not a single character: '" << inputStr << "'.  The first char will be used." << std::endl;
    }

    else if (processedStr.length() == 0)
    {
        std::cout << "ERROR(" << lineNum << "): a character cannot be of size 0." << std::endl;
        throw std::runtime_error("runtime error: there shouldnt be a character of length 0.");
    }

    return processedStr[0];
}
std::string processTokenConst(std::string str)
{
    std::string original = str;
    std::map<std::string, std::string> tokenToTokenName;
    tokenToTokenName.insert({"==", "EQ"});
    tokenToTokenName.insert({">=", "GEQ"});
    tokenToTokenName.insert({"<=", "LEQ"});
    tokenToTokenName.insert({"!=", "NEQ"});
    tokenToTokenName.insert({"++", "INC"});
    tokenToTokenName.insert({"--", "DEC"});
    tokenToTokenName.insert({"+=", "ADDASS"});

    if (tokenToTokenName.count(original) == 1)
    {
        return tokenToTokenName.at(original);
    } else 
    {
        return original;
    }
}
