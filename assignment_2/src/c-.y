%{
// C++ header stuff
#include <iostream>
#include <string>
#include <stdexcept>

#include "options/options.hpp"
#include "scanType.hpp" // must be included before tab.h
#include "c-.tab.h"

extern int yylex();
void yyerror(std::string msg) {std::cout << msg << std::endl;};
extern FILE* yyin;
extern int yydebug;

%}

%union {
    struct TokenData* tokenData;
}

    // define tokens
%token <tokenData> ID NUMCONST CHARCONST STRINGCONST BOOLCONST

%token <tokenData> BOOL CHAR INT IF THEN ELSE STATIC
%token <tokenData> WHILE DO FOR TO BY RETURN BREAK OR AND NOT 

%token <tokenData> SEMICOLON COMMA COLON LBRACK RBRACK LPAREN RPAREN
%token <tokenData> LCURL RCURL INC DEC ASS ADDASS SUBASS MULASS DIVASS PERCENT
%token <tokenData> LT LEQ GT GEQ EQ NEQ PLUS DASH SLASH ASTERISK QUESTION



%%
program         : declList
                ;

declList        : declList decl
                | decl
                ;

decl            : varDecl
                | funDecl
                ;

varDecl         : typeSpec varDeclList SEMICOLON
                ;

scopedVarDecl   : STATIC typeSpec varDeclList SEMICOLON
                | typeSpec varDeclList SEMICOLON
                ;

varDeclList     : varDeclList COMMA varDeclInit
                | varDeclInit
                ;

varDeclInit     : varDeclId
                | varDeclId COLON simpleExp
                ;

varDeclId       : ID
                | ID LBRACK NUMCONST RBRACK
                ;

typeSpec        : BOOL
                | CHAR
                | INT
                ;

funDecl         : typeSpec ID LPAREN parms RPAREN compoundStmt
                | ID LPAREN parms RPAREN compoundStmt
                ;

parms           : parmList
                |
                ;

parmList        : parmList SEMICOLON parmTypeList
                | parmTypeList
                ;

parmTypeList    : typeSpec parmIdList
                ;

parmIdList      : parmIdList COMMA parmId
                | parmId
                ;

parmId          : ID
                | ID LBRACK RBRACK
                ;

stmt            : openStmt
                | closedStmt
                ;

openStmt        : selectStmtOpen
                | iterStmtOpen
                ;

closedStmt      : selectStmtClosed
                | iterStmtClosed
                | expStmt
                | compoundStmt
                | returnStmt
                | breakStmt
                ;

expStmt         : exp SEMICOLON
                | SEMICOLON
                ;

compoundStmt    : LCURL localDecls stmtList RCURL
                ;

localDecls      : localDecls scopedVarDecl
                |
                ;

stmtList        : stmtList stmt
                |
                ;

selectStmtOpen  : IF simpleExp THEN stmt
                | IF simpleExp THEN closedStmt ELSE openStmt
                ;

selectStmtClosed: IF simpleExp THEN closedStmt ELSE closedStmt
                ;

iterStmtOpen    : WHILE simpleExp DO openStmt
                | FOR ID ASS iterRange DO openStmt
                ;

iterStmtClosed  : WHILE simpleExp DO closedStmt
                | FOR ID ASS iterRange DO closedStmt
                ;

iterRange       : simpleExp TO simpleExp
                | simpleExp TO simpleExp BY simpleExp
                ;

returnStmt      : RETURN SEMICOLON
                | RETURN exp SEMICOLON
                ;

breakStmt       : BREAK SEMICOLON
                ;

exp             : mutable assignop exp
                | mutable INC
                | mutable DEC
                | simpleExp
                ;

assignop        : ASS
                | ADDASS
                | SUBASS
                | MULASS
                | DIVASS
                ;

simpleExp       : simpleExp OR andExp
                | andExp
                ;

andExp          : andExp AND unaryRelExp
                | unaryRelExp
                ;

unaryRelExp     : NOT unaryRelExp
                | relExp
                ;

relExp          : sumExp relop sumExp
                | sumExp
                ;

relop           : LT
                | LEQ
                | GT
                | GEQ
                | EQ
                | NEQ
                ;

sumExp          : sumExp sumOp mulExp
                | mulExp
                ;

sumOp           : PLUS
                | DASH
                ;

mulExp          : mulExp mulOp unaryExp
                | unaryExp
                ;

mulOp           : ASTERISK
                | SLASH
                | PERCENT
                ;

unaryExp        : unaryOp unaryExp
                | factor
                ;

unaryOp         : DASH
                | ASTERISK
                | QUESTION
                ;

factor          : mutable
                | immutable
                ;

mutable         : ID
                | ID LBRACK exp RBRACK
                ;

immutable       : LPAREN exp RPAREN
                | call
                | constant

call            : ID LPAREN args RPAREN
                ;

args            : argList
                |
                ;

argList         : argList COMMA exp
                | exp
                ;

constant        : NUMCONST
                | BOOLCONST
                | CHARCONST
                | STRINGCONST
                ;
%%


int main(int argc, char** argv)
{
    Options options(argc, argv);
    yydebug = options.isdFlag();
    if (options.getFile())
    {
        yyin = options.getFile();
    }

    if (options.ispFlag())
    {
        // print tree
    }

    yyparse();
    return 0;
}
