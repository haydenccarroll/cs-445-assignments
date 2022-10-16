%{
// C++ header stuff
#include "options/options.hpp"
#include "error/error.hpp"
#include "symTable/symTable.hpp"
#include "semantics/semantics.hpp"
#include "types/types.hpp" // must be included before tab.h
#include "ast/ast.hpp" // must be included before tab.h

#include <iostream>
#include <string>
#include <stdexcept>
#include <stdlib.h>

#include "c-.tab.h"

extern int yylex();
void yyerror(std::string msg) { std::cout << msg << std::endl; };
extern FILE* yyin;
extern int yydebug;

ASTNode* root = nullptr;

%}

%union {
    TokenData* tokenData;
    ASTNode* node;
    DataTypeEnum dataTypeEnum;
}

%define parse.error verbose

    // define tokens
%token <tokenData> ID NUMCONST CHARCONST STRINGCONST BOOLCONST
%token <tokenData> BOOL CHAR INT IF THEN ELSE STATIC
%token <tokenData> WHILE DO FOR TO BY RETURN BREAK OR AND NOT 
%token <tokenData> SEMICOLON COMMA COLON LBRACK RBRACK LPAREN RPAREN
%token <tokenData> LCURL RCURL INC DEC ASS ADDASS SUBASS MULASS DIVASS PERCENT
%token <tokenData> LT LEQ GT GEQ EQ NEQ PLUS DASH SLASH ASTERISK QUESTION

%type <dataTypeEnum> typeSpec

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
                        $$ = $1;
                        root = $$;
                    }
                ;

declList        : declList decl
                    {
                        $$ = $1;
                        $$->addSibling($2);
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
                        $$ = $2;
                        VarDeclNode* declNode = dynamic_cast<VarDeclNode*>($$);
                        if (declNode == nullptr)
                        {
                            Error::error($2->getLineNum(), "dynamic_cast<VarDeclNode*> failed. node is of the wrong type.");
                        }
                        declNode->setTypeSpec($1);
                    }
                ;

scopedVarDecl   : STATIC typeSpec varDeclList SEMICOLON
                    {
                        $$ = $3;
                        VarDeclNode* declNode = dynamic_cast<VarDeclNode*>($$);
                        if (declNode == nullptr)
                        {
                            Error::error($3->getLineNum(), "dynamic_cast<VarDeclNode*> failed. Node is wrong type.");
                        }
                        declNode->setStatic(true);
                        declNode->setTypeSpec($2); 
                    }
                | typeSpec varDeclList SEMICOLON
                    {
                        $$ = $2;
                        VarDeclNode* declNode = dynamic_cast<VarDeclNode*>($2);
                        if (declNode == nullptr)
                        {
                            Error::error($2->getLineNum(), "dynamic_cast<VarDeclNode*> failed. node is wrong type.");
                        }
                        declNode->setTypeSpec($1);
                    }
                ;

varDeclList     : varDeclList COMMA varDeclInit
                    {
                        $$ = $1;
                        $$->addSibling($3);
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
                        $$ = $1;
                        $$->addChild($3);
                    }
                ;

varDeclId       : ID
                    {
                        DataType dataType = DataType(DataTypeEnum::Void);

                        $$ = new VarDeclNode($1->lineNum, $1->str, dataType);
                    }
                | ID LBRACK NUMCONST RBRACK
                    {
                        DataType dataType = DataType(DataTypeEnum::Void, true);
                        $$ = new VarDeclNode($1->lineNum, $1->str, dataType);
                    }
                ;

typeSpec        : BOOL
                    {
                        $$ = DataTypeEnum::Bool;
                    }
                | CHAR
                    {
                        $$ = DataTypeEnum::Char;
                    }
                | INT
                    {
                        $$ = DataTypeEnum::Int;
                    }
                ;

funDecl         : typeSpec ID LPAREN parms RPAREN compoundStmt
                    {
                        DataType dataType = DataType($1);
                        $$ = new FunDeclNode($2->lineNum, $2->str, dataType);
                        $$->addChild($4);

                        auto compStmt = dynamic_cast<CompoundStmtNode*>($6);
                        if (compStmt == nullptr)
                        {
                            Error::critical($6->getLineNum(), "Failed converting node to compstmt");
                        }
                        compStmt->setIsFromFunction(true);
                        $$->addChild($6);
                    }
                | ID LPAREN parms RPAREN compoundStmt
                    {
                        DataType dataType = DataType(DataTypeEnum::Void);
                        $$ = new FunDeclNode($1->lineNum, $1->str, dataType);
                        $$->addChild($3);
                        $$->addChild($5);
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
                        $$ = $1;
                        $$->addSibling($3);
                    }
                | parmTypeList
                    {
                        $$ = $1;
                    }
                ;

parmTypeList    : typeSpec parmIdList
                    {
                        $$ = $2;
                        ParamNode* param = dynamic_cast<ParamNode*>($$);
                        if (param == nullptr)
                        {
                            Error::error($2->getLineNum(), "dynamic_cast<ParamNode*> failed. Node is wrong type.");
                        }
                        param->setTypeSpec($1);
                    }
                ;

parmIdList      : parmIdList COMMA parmId
                    {
                        if ($1 == nullptr)
                        {
                            $$ = $3;
                        }
                        else {
                            $$ = $1;
                            $$->addSibling($3);
                        }
                    }
                | parmId
                    {
                        $$ = $1;
                    }
                ;

parmId          : ID
                    {
                        DataType dataType = DataType(DataTypeEnum::Void);
                        $$ = new ParamNode($1->lineNum, $1->str, dataType);
                    }
                | ID LBRACK RBRACK
                    {
                        DataType dataType = DataType(DataTypeEnum::Void, true);
                        $$ = new ParamNode($1->lineNum, $1->str, dataType);
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
                    }
                ;

compoundStmt    : LCURL localDecls stmtList RCURL
                    {
                        $$ = new CompoundStmtNode($1->lineNum);
                        $$->addChild($2);
                        $$->addChild($3);
                    }
                ;

localDecls      : localDecls scopedVarDecl
                    {
                        if ($1 == nullptr)
                        {
                            $$ = $2;
                        }
                        else {
                            $$ = $1;
                            $$->addSibling($2);
                        }
                    }
                |
                    {
                        $$ = nullptr;
                    }
                ;

stmtList        : stmtList stmt
                    {
                        if ($1 == nullptr)
                        {
                            $$ = $2;
                        }
                        else {
                            $$ = $1;
                            $$->addSibling($2);
                        }
                    }
                |
                    {
                        $$ = nullptr;
                    }
                ;

selectStmtOpen  : IF simpleExp THEN stmt
                    {
                        $$ = new IfNode($1->lineNum);
                        $$->addChild($2);
                        $$->addChild($4);
                    }
                | IF simpleExp THEN closedStmt ELSE openStmt
                    {
                        $$ = new IfNode($1->lineNum);
                        $$->addChild($2);
                        $$->addChild($4);
                        $$->addChild($6);
                    }
                ;

selectStmtClosed: IF simpleExp THEN closedStmt ELSE closedStmt
                    {
                        $$ = new IfNode($1->lineNum);
                        $$->addChild($2);
                        $$->addChild($4);
                        $$->addChild($6);
                    }
                ;

iterStmtOpen    : WHILE simpleExp DO openStmt
                    {
                        $$ = new WhileNode($1->lineNum);
                        $$->addChild($2);
                        $$->addChild($4);
                    }
                | FOR ID ASS iterRange DO openStmt
                    {
                        $$ = new ForNode($1->lineNum);
                        DataType dataType = DataType(DataTypeEnum::Int);
                        ASTNode* id = new VarDeclNode($2->lineNum, $2->str, dataType);
                        $$->addChild(id);
                        $$->addChild($4);
                        $$->addChild($6);
                    }
                ;

iterStmtClosed  : WHILE simpleExp DO closedStmt
                    {
                        $$ = new WhileNode($1->lineNum);
                        $$->addChild($2);
                        $$->addChild($4);
                    }
                | FOR ID ASS iterRange DO closedStmt
                    {
                        $$ = new ForNode($1->lineNum);
                        DataType dataType = DataType(DataTypeEnum::Int);
                        ASTNode* id = new VarDeclNode($2->lineNum, $2->str, dataType);
                        $$->addChild(id);
                        $$->addChild($4);
                        $$->addChild($6);
                    }
                ;

iterRange       : simpleExp TO simpleExp
                    {
                        $$ = new RangeNode($1->getLineNum());
                        $$->addChild($1);
                        $$->addChild($3);
                    }
                | simpleExp TO simpleExp BY simpleExp
                    {
                        $$ = new RangeNode($1->getLineNum());
                        $$->addChild($1);
                        $$->addChild($3);
                        $$->addChild($5);
                    }
                ;

returnStmt      : RETURN SEMICOLON 
                    {
                        $$ = new ReturnNode($1->lineNum);
                    }
                | RETURN exp SEMICOLON
                    {
                        $$ = new ReturnNode($1->lineNum);
                        $$->addChild($2);
                    }
                ;

breakStmt       : BREAK SEMICOLON
                    {
                        $$ = new BreakNode($1->lineNum);
                    }
                ;

exp             : mutable assignop exp
                    {
                        $$ = $2;
                        $$->addChild($1);
                        $$->addChild($3);
                    }
                | mutable INC
                    {
                        $$ = new AssignOpNode($1->getLineNum(), AssignOpType::INC);
                        $$->addChild($1);

                    }
                | mutable DEC
                    {
                        $$ = new AssignOpNode($1->getLineNum(), AssignOpType::DEC);
                        $$->addChild($1);
                    }
                | simpleExp
                    {
                        $$ = $1;
                    }
                ;

assignop        : ASS
                    {
                        $$ = new AssignOpNode($1->lineNum, AssignOpType::ASS);
                    }
                | ADDASS
                    {
                        $$ = new AssignOpNode($1->lineNum, AssignOpType::ADDASS);
                    }
                | SUBASS
                    {
                        $$ = new AssignOpNode($1->lineNum, AssignOpType::SUBASS);
                    }
                | MULASS
                    {
                        $$ = new AssignOpNode($1->lineNum, AssignOpType::MULASS);
                    }
                | DIVASS
                    {
                        $$ = new AssignOpNode($1->lineNum, AssignOpType::DIVASS);
                    }
                ;

simpleExp       : simpleExp OR andExp
                    {
                        $$ = new RelOpNode($1->getLineNum(), RelOpType::Or);
                        $$->addChild($1);
                        $$->addChild($3);
                    }
                | andExp
                    {
                        $$ = $1;
                    }
                ;

andExp          : andExp AND unaryRelExp
                    {
                        $$ = new RelOpNode($1->getLineNum(), RelOpType::And);
                        $$->addChild($1);
                        $$->addChild($3);
                    }
                | unaryRelExp
                    {
                        $$ = $1;
                    }
                ;

unaryRelExp     : NOT unaryRelExp
                    {
                        $$ = new UnaryOpNode($1->lineNum, UnaryOpType::Not);
                        $$->addChild($2);
                    }
                | relExp
                    {
                        $$ = $1;
                    }
                ;

relExp          : sumExp relop sumExp
                    {
                        $$ = $2;
                        $$->addChild($1);
                        $$->addChild($3);
                    }
                | sumExp
                    {
                        $$ = $1;
                    }
                ;

relop           : LT
                    {
                        $$ = new RelOpNode($1->lineNum, RelOpType::LT);
                    }
                | LEQ
                    {
                        $$ = new RelOpNode($1->lineNum, RelOpType::LEQ);
                    }
                | GT
                    {
                        $$ = new RelOpNode($1->lineNum, RelOpType::GT);
                    }
                | GEQ
                    {
                        $$ = new RelOpNode($1->lineNum, RelOpType::GEQ);
                    }
                | EQ
                    {
                        $$ = new RelOpNode($1->lineNum, RelOpType::EQ);
                    }
                | NEQ
                    {
                        $$ = new RelOpNode($1->lineNum, RelOpType::NEQ);
                    }
                ;

sumExp          : sumExp sumOp mulExp
                    {
                        $$ = $2;
                        $$->addChild($1);
                        $$->addChild($3);
                    }
                | mulExp
                    {
                        $$ = $1;
                    }
                ;

sumOp           : PLUS
                    {
                        $$ = new BinaryOpNode($1->lineNum, BinaryOpType::Add);
                    }
                | DASH
                    {
                        $$ = new BinaryOpNode($1->lineNum, BinaryOpType::Sub);
                    }
                ;

mulExp          : mulExp mulOp unaryExp
                    {
                        $$ = $2;
                        $$->addChild($1);
                        $$->addChild($3);
                    }
                | unaryExp
                    {
                        $$ = $1;
                    }
                ;

mulOp           : ASTERISK
                    {
                        $$ = new BinaryOpNode($1->lineNum, BinaryOpType::Mul);
                    }
                | SLASH
                    {
                        $$ = new BinaryOpNode($1->lineNum, BinaryOpType::Div);
                    }
                | PERCENT
                    {
                        $$ = new BinaryOpNode($1->lineNum, BinaryOpType::Mod);
                    }
                ;

unaryExp        : unaryOp unaryExp
                    {
                        $$ = $1;
                        $$->addChild($2);
                    }
                | factor
                    {
                        $$ = $1;
                    }
                ;

unaryOp         : DASH 
                    {
                        $$ = new UnaryOpNode($1->lineNum, UnaryOpType::Chsign);
                    }
                | ASTERISK
                    {
                        $$ = new UnaryOpNode($1->lineNum, UnaryOpType::SizeOf);
                    }
                | QUESTION
                    {
                        $$ = new UnaryOpNode($1->lineNum, UnaryOpType::Question);
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
                        $$ = new IdNode($1->lineNum, $1->str, false);
                    }
                | ID LBRACK exp RBRACK
                    {
                        $$ = new BinaryOpNode($1->lineNum, BinaryOpType::Index);
                        ASTNode* id = new IdNode($1->lineNum, $1->str, true);
                        $$->addChild(id);
                        $$->addChild($3);
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
                        $$ = new CallNode($1->lineNum, $1->str);
                        $$->addChild($3);
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
                        $$ = new ConstNode($1->lineNum, ConstType::Int, $1->num);
                    }
                | BOOLCONST
                    {
                        $$ = new ConstNode($1->lineNum, ConstType::Bool, $1->boolV);
                    }
                | CHARCONST
                    {
                        $$ = new ConstNode($1->lineNum, ConstType::Char, $1->charV);
                    }
                
                | STRINGCONST
                    {
                        $$ = new ConstNode($1->lineNum, ConstType::String, $1->str);
                    }
                ;
%%
int main(int argc, char** argv)
{
    Options options(argc, argv);
    SymbolTable symTable = SymbolTable();
    symTable.debug(options.isDFlag());

    if (options.ishFlag())
    {
        options.printHelpScreen();
        delete root;
        return EXIT_SUCCESS;
    }

    yydebug = options.isdFlag();

    if (options.getFile())
    {
        yyin = options.getFile();
    }

    yyparse();

    // if AST print flag (-p) is on and tree is not null
    if (options.ispFlag() && root != nullptr)
    {
        root->print();
    }

    if (root == nullptr)
    {
        std::cout << "root is nullptr\n";
    }

    SemanticAnalyzer semantics = SemanticAnalyzer(root, &symTable);
    semantics.analyze();

    // do semantic analysis

    // if AST print annotated flag is set and tree not null
    if (options.isPFlag() && root != nullptr)
    {
        root->print(); // PRINT WITH TYPE INFO THOUGH
        // print root with type info stuff
    }

    std::cout << "Number of errors: " << Error::getErrorCount() << std::endl;
    std::cout << "Number of warnings: " << Error::getWarningCount() << std::endl;

    delete root;
    return EXIT_SUCCESS;
}
