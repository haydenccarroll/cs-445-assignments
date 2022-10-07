%{
// this *order* of these includes is mandatory
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <memory>

#include "scanType.hpp"  // TokenData Type
#include "c-.tab.h"  // token definitions from the bison

int line = 1;
int numErrors;    // ERR err count
std::vector<std::unique_ptr<TokenData>> token_vec;

static int setValue(int lineNum, int tokenClass, char *svalue)
{
    token_vec.push_back(std::make_unique<TokenData>());
    yylval.tokenData = token_vec.back().get();
    yylval.tokenData->lineNum = lineNum;
    yylval.tokenData->tokenStr = std::string(svalue);

    return tokenClass;
}

%}

%option noyywrap

%%
\/\/.*\n                    { line++; }
\n                          { line++; }

"int"                       { return INT; }
"bool"                      { return BOOL; }
"char"                      { return CHAR; }

"return"                    { return setValue(line, RETURN, yytext); }
"break"                     { return setValue(line, BREAK, yytext); }
"not"                       { return setValue(line, NOT, yytext); }
"else"                      { return setValue(line, ELSE, yytext); }
"or"                        { return setValue(line, OR, yytext); }
"by"                        { return setValue(line, BY, yytext); }
"do"                        { return setValue(line, DO, yytext); }
"while"                     { return setValue(line, WHILE, yytext); }
"if"                        { return setValue(line, IF, yytext); }
"for"                       { return setValue(line, FOR, yytext); }
"and"                       { return setValue(line, AND, yytext); }
"to"                        { return setValue(line, TO, yytext); }
"then"                      { return setValue(line, THEN, yytext); }
"{"                         { return setValue(line, LCURL, yytext); }
"}"                         { return setValue(line, RCURL, yytext); }
"static"                    { return setValue(line, STATIC, yytext); }
"?"                         { return setValue(line, RAND, yytext); }
"*"                         { return setValue(line, ASTERISK, yytext); }
"/"                         { return setValue(line, DIV, yytext); }
"%"                         { return setValue(line, MOD, yytext); }
"+"                         { return setValue(line, ADD, yytext); }
"("                         { return setValue(line, LPAREN, yytext); }
")"                         { return setValue(line, RPAREN, yytext); }
"["                         { return setValue(line, LBRACK, yytext); }
"]"                         { return setValue(line, RBRACK, yytext); }
"-"                         { return setValue(line, DASH, yytext); }
"="                         { return setValue(line, ASGN, yytext); }
"+="                        { return setValue(line, ADDASGN, yytext); }
"-="                        { return setValue(line, SUBASGN, yytext); }
"*="                        { return setValue(line, MULASGN, yytext); }
"/="                        { return setValue(line, DIVASGN, yytext); }
";"                         { return setValue(line, SEMI, yytext); }
"<"                         { return setValue(line, LT, yytext); }
"<="                        { return setValue(line, LEQ, yytext); }
">"                         { return setValue(line, GT, yytext); }
">="                        { return setValue(line, GEQ, yytext); }
"=="                        { return setValue(line, EQ, yytext); }
"!="                        { return setValue(line, NEQ, yytext); }
"++"                        { return setValue(line, INC, yytext); }
"--"                        { return setValue(line, DEC, yytext); }
":"                         { return setValue(line, COL, yytext); }
","                         { return setValue(line, COM, yytext); }

\"((\\\")|([^\n\"]))*\"     { return setValue(line, STRINGCONST, yytext); }
\'((\\\')|([^\n\']))*\'     { return setValue(line, CHARCONST, yytext); }
"true"|"false"              { return setValue(line, BOOLCONST, yytext); }
[0-9]+                      { return setValue(line, NUMCONST, yytext); }
[a-zA-Z][a-zA-Z0-9]*        { return setValue(line, ID, yytext); }

[\t ]                       ;
.                           { printf("ERROR(%d): Invalid or misplaced input character: \'%c\'. Character Ignored.\n", line, yytext[0]); numErrors++; }
%%