%{

// C++ headers and stuff
#include "types/include.hpp" // must be included before c-.tab.h
#include "ast/include.hpp"
#include "error/include.hpp"

#include <iostream>
#include <string>
#include <sstream>

#include "c-.tab.h"

extern char* yytext;

int passToken(int tokenClass);
std::string processStringConst(std::string str);
char processCharConst(std::string str);

static int lineNum = 1;

%}
%option noyywrap
%%

\/\/[^\n]*                        {} // ignore comments
[ \t]                             {} // ignore whitespace
"\n"                              { lineNum++; } // increment line number

"bool"   { return passToken(BOOL); }
"char"   { return passToken(CHAR); }
"int"    { return passToken(INT); }
"if"     { return passToken(IF); }
"then"   { return passToken(THEN); }
"else"   { return passToken(ELSE); }
"while"  { return passToken(WHILE); }
"do"     { return passToken(DO); }
"for"    { return passToken(FOR); }
"to"     { return passToken(TO); }
"by"     { return passToken(BY); }
"return" { return passToken(RETURN); }
"break"  { return passToken(BREAK); }
"or"     { return passToken(OR); }
"and"    { return passToken(AND); }
"not"    { return passToken(NOT); }
"static" { return passToken(STATIC); }

";"  { return passToken(SEMICOLON); }
","  { return passToken(COMMA); }
":"  { return passToken(COLON); }
"["  { return passToken(LBRACK); }
"]"  { return passToken(RBRACK); }
"("  { return passToken(LPAREN); }
")"  { return passToken(RPAREN); }
"{"  { return passToken(LCURL); }
"}"  { return passToken(RCURL); }
"++" { return passToken(INC); }
"--" { return passToken(DEC); }
"="  { return passToken(ASS); }
"+=" { return passToken(ADDASS); }
"-=" { return passToken(SUBASS); }
"*=" { return passToken(MULASS); }
"/=" { return passToken(DIVASS); }
"%"  { return passToken(PERCENT); }
"<"  { return passToken(LT); }
">"  { return passToken(GT); }
">=" { return passToken(GEQ); }
"<=" { return passToken(LEQ); }
"==" { return passToken(EQ); }
"!=" { return passToken(NEQ); }
"+"  { return passToken(PLUS); }
"-"  { return passToken(DASH); }
"/"  { return passToken(SLASH); }
"*"  { return passToken(ASTERISK); }
"?"  { return passToken(QUESTION); }

true|false                        { return passToken(BOOLCONST); }

[A-Za-z][A-Za-z0-9]*              { return passToken(ID); }

[0-9]+                            { return passToken(NUMCONST); }

\'((\\\')|([^\n\']))*\'           { return passToken(CHARCONST); }

\"([^\\"\n]|\\.)*\"               { return passToken(STRINGCONST); }

.                                 { std::cout << "ERROR(" << lineNum << "): Invalid or misplaced input character: '" << yytext << "'. Character Ignored.\n"; }
%%

///@brief given a token class (ID, NUMCONST, KEYWORD, etc...), pull the data from yytext and put it in yylval.tokenData.
///@param tokenClass enum type of token (ID, NUMCONST, KEYWORD, etc...)
int passToken(int tokenClass)
{
    yylval.tokenData = new TokenData;
    yylval.tokenData->lineNum = lineNum;
    switch (tokenClass)
    {
    case ID:
        yylval.tokenData->inputStr = yytext;
        yylval.tokenData->str = yylval.tokenData->inputStr;
        break;
    case NUMCONST:
        yylval.tokenData->inputStr = yytext;
        yylval.tokenData->num = atoi(yylval.tokenData->inputStr.c_str());
        break;
    case CHARCONST:
        yylval.tokenData->inputStr = yytext;
        yylval.tokenData->charV = processCharConst(yylval.tokenData->inputStr);
        break;
    case STRINGCONST:
        yylval.tokenData->inputStr = yytext;
        yylval.tokenData->str = processStringConst(yylval.tokenData->inputStr);
        break;
    case BOOLCONST:
        yylval.tokenData->inputStr = yytext;
        yylval.tokenData->boolV = (yylval.tokenData->inputStr == "true");
        break;
    }

    return tokenClass;
}

///@brief does all string processing such as removing quotes, and escaping characters
std::string processStringConst(std::string str)
{
    std::string noQuotes = str.substr(1, str.size() - 2);
    std::string cumStr = "";
    for (int i=0; i < noQuotes.length(); i++)
    {
        if (noQuotes[i] == '\\')
        {
            if (i+1 == noQuotes.length())
            {
                Error::error(lineNum, "escape character found at last char in string.");
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
            i++; // increment i an additional time since we looked ahead 1 char
        } else {
            cumStr += noQuotes[i];
        }
    }

    return cumStr;
}

///@brief similar to processStringConst but for chars.
char processCharConst(std::string str)
{
    std::string processedStr = processStringConst(str);

    if (processedStr.length() > 1)
    {
        std::stringstream ss;
        ss << "character is " << processedStr.length() 
           << " characters long and not a single character: '" 
           << str << "'.  The first char will be used.";
        Error::warning(lineNum, ss.str());
    }

    else if (processedStr.length() == 0)
    {
        std::stringstream ss;
        ss << "a character cannot be of size 0.";
        Error::error(lineNum, ss.str());
    }

    return processedStr[0];
}
