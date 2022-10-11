%{
// C++ header stuff
#include "options/options.hpp"
#include "types.hpp" // must be included before tab.h
#include "ast/const/const.hpp"

#include <iostream>
#include <string>
#include <stdexcept>
#include <stdlib.h>

#include "c-.tab.h"

extern int yylex();
void yyerror(std::string msg) {std::cout << msg << std::endl;};
extern FILE* yyin;
extern int yydebug;
extern int yylineno;

ASTNode* root = new ASTNode(0);

%}

%union {
    TokenData* tokenData;
    ASTNode* node;
    DataType* dataType;
}

%define parse.error verbose

    // define tokens
%token <tokenData> ID NUMCONST CHARCONST STRINGCONST BOOLCONST
%token <tokenData> BOOL CHAR INT IF THEN ELSE STATIC
%token <tokenData> WHILE DO FOR TO BY RETURN BREAK OR AND NOT 
%token <tokenData> SEMICOLON COMMA COLON LBRACK RBRACK LPAREN RPAREN
%token <tokenData> LCURL RCURL INC DEC ASS ADDASS SUBASS MULASS DIVASS PERCENT
%token <tokenData> LT LEQ GT GEQ EQ NEQ PLUS DASH SLASH ASTERISK QUESTION

%type <dataType> typeSpec

%type <node> program declList decl varDecl scopedVarDecl varDeclList
%type <node> varDeclInit varDeclId  funDecl parms parmList parmTypeList parmIdList
%type <node> parmId stmt openStmt closedStmt expStmt compoundStmt localDecls
%type <node> stmtList selectStmtOpen selectStmtClosed iterStmtOpen iterStmtClosed
%type <node> iterRange returnStmt breakStmt exp assignop simpleExp andExp
%type <node> unaryRelExp relExp relop sumExp sumOp mulExp mulOp unaryExp unaryOp
%type <node> factor mutable immutable call args argList constant



%%
program         : declList 
                    {
                        // $$ = $1;
                        // root = $$;
                    }
                ;

declList        : declList decl
                    {
                        // $$ = $1;
                        // $$.addSibling($2)
                    }
                | decl
                    {
                        $$ = $1;
                    }
                ;

decl            : varDecl
                    {
                        $$ = $1;
                    }
                | funDecl
                    {
                        $$ = $1;
                    }
                ;

varDecl         : typeSpec varDeclList SEMICOLON
                    {
                        // $$ = $2
                        // $$.addTypeSpec(typeSpec.type) for it and its siblings
                    }
                ;

scopedVarDecl   : STATIC typeSpec varDeclList SEMICOLON
                    {
                        // $$ = $2
                        // $$.addType(typeSpec.type) for all siblings
                        // $$.addStatic(true) for all siblings
                    }
                | typeSpec varDeclList SEMICOLON
                    {
                        // $$ = $2
                        // $$.addType(typeSpec.type) for all siblings
                    }
                ;

varDeclList     : varDeclList COMMA varDeclInit
                    {
                        // $$ = $1;
                        // $$.addSiblings($3)
                    }
                | varDeclInit
                    {
                        $$ = $1;
                    }
                ;

varDeclInit     : varDeclId
                    {
                        $$ = $1;
                    }
                | varDeclId COLON simpleExp
                    {
                        // $$ = $1;
                        // $$.addSibling(simpleExp)
                    }
                ;

varDeclId       : ID
                    {
                        // $$ = new var node ($1.str)
                    }
                | ID LBRACK NUMCONST RBRACK
                    {
                        // new var node($1.str, isArray, $3)
                    }
                ;

typeSpec        : BOOL
                    {
                        // $$ = enum::bool
                    }
                | CHAR
                    {
                        // $$ = enum::char
                    }
                | INT
                    {
                        // $$ = enum::int
                    }
                ;

funDecl         : typeSpec ID LPAREN parms RPAREN compoundStmt
                    {
                        // newFunDeclNode($1.value, $2.str)
                        // $$.addChildren(parms, compoundStmt)
                    }
                | ID LPAREN parms RPAREN compoundStmt
                    {
                        // newFunDeclNode(None (no primitive type), $1.str)
                        // $$.addChildren(parms, compoundStmt)
                    }
                ;

parms           : parmList
                    {
                        $$ = $1;
                    }
                |
                    {
                        $$ = nullptr;
                    }
                ;

parmList        : parmList SEMICOLON parmTypeList
                    {
                        // $$ = $1;
                        // $$.addSiblings(// parmTypeList and all its siblings)
                    }
                | parmTypeList
                    {
                        $$ = $1;
                    }
                ;

parmTypeList    : typeSpec parmIdList
                    {
                        // this one is different. make a SIMPLE enum for typeSpec,
                        // $$ = $2
                        // $$.setType(typeSpec.type (enum)) for itself and all siblings.
                    }
                ;

parmIdList      : parmIdList COMMA parmId
                    {
                        // $$ = $1 if not null
                        // $$.addsibling($3)
                    }
                | parmId
                    {
                        $$ = $1;
                    }
                ;

parmId          : ID
                    {
                        // $$ = newParm(isArray = false, $$.str)
                    }
                | ID LBRACK RBRACK
                    {
                        // $$ = newParm(isArray = true, $$.str)
                    }
                ;

stmt            : openStmt
                    {
                        $$ = $1;
                    }
                | closedStmt
                    {
                        $$ = $1;
                    }
                ;

openStmt        : selectStmtOpen
                    {
                        $$ = $1;
                    }
                | iterStmtOpen
                    {
                        $$ = $1;
                    }
                ;

closedStmt      : selectStmtClosed
                    {
                        $$ = $1;
                    }
                | iterStmtClosed
                    {
                        $$ = $1;
                    }
                | expStmt
                    {
                        $$ = $1;
                    }
                | compoundStmt
                    {
                        $$ = $1;
                    }
                | returnStmt
                    {
                        $$ = $1;
                    }
                | breakStmt
                    {
                        $$ = $1;
                    }
                ;

expStmt         : exp SEMICOLON
                    {
                        $$ = $1;
                    }
                | SEMICOLON
                    {
                        $$ = nullptr;
                        // set to nullptr
                    }
                ;

compoundStmt    : LCURL localDecls stmtList RCURL
                    {
                        // $$ = newCompoundStmt()
                        // $$.addChildren(2, 3)
                    }
                ;

localDecls      : localDecls scopedVarDecl
                    {
                        // $$ = $1 if not nullptr
                        // $$.addSibling($2)
                    }
                |
                    {
                        $$ = nullptr;
                        // do nothing or set to nullptr
                    }
                ;

stmtList        : stmtList stmt
                    {
                        // $$ = $1 if not nullptr
                        // $$.addSibling($2)
                    }
                |
                    {
                        $$ = nullptr;
                        // either nothing or set to nullptr
                    }
                ;

selectStmtOpen  : IF simpleExp THEN stmt
                    {
                        // $$ = new if node (lineNum)
                        // $$.addChildren($2, 4)
                    }
                | IF simpleExp THEN closedStmt ELSE openStmt
                    {
                        // $$ = new if node (lineNum)
                        // $$.addChildren($2, 4,6)
                    }
                ;

selectStmtClosed: IF simpleExp THEN closedStmt ELSE closedStmt
                    {
                        // $$ = new if node (lineNum)
                        // $$.addChildren($2, 4, 6)
                    }
                ;

iterStmtOpen    : WHILE simpleExp DO openStmt
                    {
                        // $$ = NewWHILENode(lineNum)
                        // $$.addChildren($2, 4)
                    }
                | FOR ID ASS iterRange DO openStmt
                    {
                        // $$ = NewForNode(lineNum)
                        // $$.addChildren($2, 4, 6)
                    }
                ;

iterStmtClosed  : WHILE simpleExp DO closedStmt
                    {
                        // $$ = NewWHILENode(lineNum)
                        // $$.addChildren($2, 4)
                    }
                | FOR ID ASS iterRange DO closedStmt
                    {
                        // $$ = NewForNode(lineNum)
                        // $$.addChildren($2, 4, 6)
                    }
                ;

iterRange       : simpleExp TO simpleExp
                    {
                        // $$ = NewRangeNode(lineNum, $1, $3)
                    }
                | simpleExp TO simpleExp BY simpleExp
                    {
                        // $$ = NewRangeNode(lineNum, $1, $3, $5)
                    }
                ;

returnStmt      : RETURN SEMICOLON 
                    {
                        std::cout << "ADDED A CHILD\n"; root->addChild(new ASTNode(12));
                        // $$ = RETURNNODE
                    }
                | RETURN exp SEMICOLON
                    {
                        // $$ = RETURNNODE
                        // $$.addChildren($2)
                    }
                ;

breakStmt       : BREAK SEMICOLON
                    {
                        // $$ = BREAKNODE
                    }
                ;

exp             : mutable assignop exp
                    {
                        // $$ = $2
                        // $$.addChildren($1, $3)
                    }
                | mutable INC
                    {
                        // $$ = IncrementNode
                        // $$.addChildren($1)
                    }
                | mutable DEC
                    {
                        // $$ = DecrementNode
                        // $$.addChildren($1)
                    }
                | simpleExp
                    {
                        $$ = $1;
                    }
                ;

assignop        : ASS
                    {
                        // assignop(ASS)
                    }
                | ADDASS
                    {
                        // assignop(ASS)
                    }
                | SUBASS
                    {
                        // assignop(ASS)
                    }
                | MULASS
                    {
                       // assignop(ASS)
                    }
                | DIVASS
                    {
                        // assignop(ASS)
                    }
                ;

simpleExp       : simpleExp OR andExp
                    {
                        // $$ = newsimpleOrExp
                        // $$.addChlidren(1, 3)
                    }
                | andExp
                    {
                        $$ = $1;
                    }
                ;

andExp          : andExp AND unaryRelExp
                    {
                        // $$ = newNode
                        // $1, $3 = newNode.children()
                    }
                | unaryRelExp
                    {
                        $$ = $1;
                    }
                ;

unaryRelExp     : NOT unaryRelExp
                    {
                        // $$ = $2.negate(true)
                    }
                | relExp
                    {
                        $$ = $1;
                    }
                ;

relExp          : sumExp relop sumExp
                    {
                        // $$ = $2.addchlidren($1, $3)
                    }
                | sumExp
                    {
                        $$ = $1;
                    }
                ;

relop           : LT
                    {
                        // $$ = newRelopNode(LT)
                    }
                | LEQ
                    {
                        // $$ = newRelopNode(LEQ)
                    }
                | GT
                    {
                        // $$ = newRelopNode(GT)
                    }
                | GEQ
                    {
                        // $$ = newRelopNode(GEQ)
                    }
                | EQ
                    {
                        // $$ = newRelopNode(EQ)
                    }
                | NEQ
                    {
                        // $$ = newRelopNode(NEQ)
                    }
                ;

sumExp          : sumExp sumOp mulExp
                    {
                        // $$ = $2.addchildren($1, $3)
                    }
                | mulExp
                    {
                        $$ = $1;
                    }
                ;

sumOp           : PLUS
                    {
                        // $$ = newBoolOpNode(plus)
                    }
                | DASH
                    {
                        // $$ = newBoolOpNode(minus)
                    }
                ;

mulExp          : mulExp mulOp unaryExp
                    {
                        // $2.addChild($1, $3)
                        // $$ = $2;
                    }
                | unaryExp
                    {
                        $$ = $1;
                    }
                ;

mulOp           : ASTERISK
                    {
                        // $$ = newBinaryOpNode()
                    }
                | SLASH
                    {
                        // $$ = newBinaryOpNode()
                    }
                | PERCENT
                    {
                        // $$ = newBinaryOpNode()
                    }
                ;

unaryExp        : unaryOp unaryExp
                    {
                        // $1.addSibling($2)
                        // $$ = $1;
                    }
                | factor
                    {
                        $$ = $1;
                    }
                ;

unaryOp         : DASH 
                    {
                        // $1 = new unary node(-)
                    }
                | ASTERISK
                    {
                        // $1 = new unary node(-)
                    }
                | QUESTION
                    {
                        // $1 = new unary node(-)
                    }
                ;

factor          : mutable 
                    { 
                        $$ = $1; 
                    }
                | immutable 
                    {
                        $$ = $1;
                    }
                ;

mutable         : ID
                    {
                        // $$ = new ID node(linenum, idname)
                    }
                | ID LBRACK exp RBRACK
                    {
                        // $$ = new ID node(linenum, idname, isArray=true)
                    }
                ;

immutable       : LPAREN exp RPAREN
                    {
                        $$ = $2;
                    }
                | call
                    {
                        $$ = $1;
                    }
                | constant
                    {
                        $$ = $1;
                    }
                ;

call            : ID LPAREN args RPAREN
                    {
                        // a bit more complex i think, not sure
                    }
                ;

args            : argList
                    {
                        $$ = $1;
                    }
                |
                    {
                        $$ = nullptr;
                    }
                ;

argList         : argList COMMA exp
                    {
                        $$ = $1;
                        $$->addSibling($3);
                    }
                | exp
                    {
                        $$ = $1;
                    }
                ;

constant        : NUMCONST
                    {
                        $$ = new ConstNode(yylineno, ConstType::Int, $1->num);
                    }
                | BOOLCONST
                    {
                        $$ = new ConstNode(yylineno, ConstType::Bool, ($1->num == 1));
                    }
                | CHARCONST
                    {
                        $$ = new ConstNode(yylineno, ConstType::Char, $1->charV);
                    }
                
                | STRINGCONST
                    {
                        $$ = new ConstNode(yylineno, ConstType::String, $1->str);
                    }
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

    yyparse();

    if (options.ispFlag())
    {
        root->printRoot();
    }

    return EXIT_SUCCESS;
}
