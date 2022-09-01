%{
// // // // // // // // // // // // // // // // // // // // // // // 
// CS445 - Calculator Example Program written in the style of the C-
// compiler for the class.
//
// Robert Heckendorn
// Jan 21, 2021    

#include "scanType.h"  // TokenData Type
#include <stdio.h>

double vars[26];    

extern int yylex();
extern FILE *yyin;
extern int line;         // ERR line number from the scanner!!
extern int numErrors;    // ERR err count

#define YYERROR_VERBOSE
void yyerror(const char *msg)
{
    printf("ERROR(%d): %s\n", line, msg);
    numErrors++;
}

%}

// this is included in the tab.h file
// so scanType.h must be included before the tab.h file!!!!
%union {
    TokenData *tokenData;
    double value;
}

    /* not entirely sure what union, token, and type do. */
%token <tokenData> QUIT NUMBER ID
%type  <value> funDecl

%%
program : declList
        ;

declList : decList decl
         | decl
         ;

decl     : varDecl
         | funcDecl

varDecl  : typeSpec varDeclList ';'
         ;

scopedVarDecl : static typeSpec varDeclList ';'
              | typeSpec varDeclList ';'

varDeclList   : varDeclList, varDeclInit
              | simpleExp
              ;

varDeclInit   : varDeclId
              | varDeclId ':' simpleExp
              ;

varDeclId     : ID
              | ID '[' NUMCONST ']'
              ;

typeSpec      : bool
              | char
              | int
              ;

funDecl       : typeSpec ID '(' parms ')' compoundStmt
              | ID '(' parms ')' compoundStmt
              ;

parms         : parmList
              | 'ε'
              ;

parmList      : parmList ';' parmTypeList
              | parmTypeList
              ;

parmTypeList  : typeSpec parmIdList
              ;

parmIdList    : parmIdList ',' parmId
              | parmId
              ;

parmId        : ID
              | ID '['']'
              ;

stmt          : expStmt | compoundStmt | selectStmt
              | iterStmt | returnStmt | breakStmt
              ;

expStmt       : exp ';'
              | ';'
              ;

compoundStmt  : '{' localDecls stmtList '}'
              ;

localDecls    : localDecls scopedVarDecl
              | 'ε'
              ;

stmtList      : stmtList stmt
              | 'ε'
              ;

selectStmt    : 'if' simpleExp 'then' stmt
              | 'if' simpleExp 'then' stmt 'else' stmt
              ;

iterStmt      : 'while' simpleExp 'do' stmt
              | 'for' ID '=' iterRange 'do' stmt
              ;

iterRange     : simpleExp 'to' simpleExp
              | simpleExp 'to' simpleExp 'by' simpleExp
              ;

returnStmt    : 'return' ';'
              | 'return' exp ';'
              ;

breakStmt     : 'break' ';'
              ;

exp           : mutable assignop exp
              | mutable '++' | mutable '--'
              | simpleExp
              ;

assignop      : '=' | '+=' | '-=' | '*=' | '/='
              ;

simpleExp     : simpleExp 'or' andExp
              | andExp

andExp        : andExp 'and' unaryRelExp
              | unaryRelExp
              ;

unaryRelExp   : 'not' unaryRelExp | relExp
              ;

relExp        : sumExp relop sumExp
              | sumExp
              ;

relop         : '<' | '<=' | '>' | '>=' | '==' | '!='
              ;

sumExp        : sumExp sumop mulExp
              | mulExp
              ;

sumop         : '+' | '-'
              ;

mulExp        : mulExp mulop unaryExp 
              | unaryExp
              ;

mulop         : '*' | '/' | '%'
              ;

unaryExp      : unaryop unaryExp
              | factor
              ;

unaryop       : '-' | '*' | '?'
              ;

factor        : mutable | immutable
              ;

mutable       : ID | ID '[' exp ']'
              ;

immutable     : '(' exp ')'
              | call
              | constant
              ;

call          : ID '(' args ')'
              ;

args          : argList
              | 'ε'
              ;

argList       : argList ',' exp
              | exp
              ;

constant      : NUMCONST | CHARCONST | STRINGCONST | 'true' | 'false'

%%
extern int yydebug;
int main(int argc, char *argv[])
{
    if (argc > 1) {
        if ((yyin = fopen(argv[1], "r"))) {
            // file open successful
        }
        else {
            // failed to open file
            printf("ERROR: failed to open \'%s\'\n", argv[1]);
            exit(1);
        }
    }

    // init variables a through z
    for (int i=0; i<26; i++) vars[i] = 0.0;

    // do the parsing
    numErrors = 0;
    yyparse();

    printf("Number of errors: %d\n", numErrors);   // ERR

    return 0;
}