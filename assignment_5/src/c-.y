%{
// C++ header stuff
#include "options/include.hpp"
#include "error/include.hpp"
#include "symTable/include.hpp"
#include "semantics/include.hpp"
#include "types/include.hpp" // must be included before tab.h
#include "ast/include.hpp" // must be included before tab.h
#include "yyerror/include.hpp"

#include <iostream>
#include <string>
#include <stdexcept>
#include <stdlib.h>

#include "c-.tab.h"

extern int yylex();

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
                        if ($$ != nullptr)
                        {
                            $$->addSibling($2);
                        }
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
                | error
                    {
                        $$ = nullptr;
                    }
                ;

varDecl         : typeSpec varDeclList SEMICOLON
                    {
                        yyerrok;
                        $$ = $2;
                        if ($$ != nullptr)
                        {
                            auto declNode = dynamic_cast<VarDeclNode*>($$);
                            if (declNode == nullptr)
                            {
                                Error::error($2->getLineNum(), "dynamic_cast<VarDeclNode*> failed. node is of the wrong type.");
                            }
                            declNode->setTypeSpec($1);
                        }
                    }
                | error varDeclList SEMICOLON
                    {
                        $$ = nullptr;
                        yyerrok;
                    }
                | typeSpec error SEMICOLON
                    {
                        $$ = nullptr;
                        yyerrok;
                    }
                ;

scopedVarDecl   : STATIC typeSpec varDeclList SEMICOLON
                    {
                        yyerrok;
                        $$ = $3;
                        if ($$ != nullptr)
                        {
                            VarDeclNode* declNode = dynamic_cast<VarDeclNode*>($$);
                            if (declNode == nullptr)
                            {
                                Error::critical($3->getLineNum(), "dynamic_cast<VarDeclNode*> failed. Node is wrong type.");
                            }
                            declNode->setStatic(true);
                            declNode->setInitialized(true);
                            declNode->setTypeSpec($2);
                        }
                    }
                | typeSpec varDeclList SEMICOLON
                    {
                        yyerrok;
                        $$ = $2;
                        if ($$ != nullptr)
                        {
                            VarDeclNode* declNode = dynamic_cast<VarDeclNode*>($2);
                            if (declNode == nullptr)
                            {
                                Error::critical($2->getLineNum(), "dynamic_cast<VarDeclNode*> failed. node is wrong type.");
                            }
                            declNode->setTypeSpec($1);
                        }
                    }
                ;

varDeclList     : varDeclList COMMA varDeclInit
                    {
                        yyerrok;
                        $$ = $1;
                        if ($$ != nullptr)
                        {
                            $$->addSibling($3);
                        }
                    }
                | varDeclInit
                    {
                        $$ = $1;
                    }
                | varDeclList COMMA error
                    {
                        $$ = nullptr;
                    }
                | error
                    {
                        $$ = nullptr;
                    }
                ;

varDeclInit     : varDeclId
                    {
                        $$ = $1;
                    }
                | varDeclId COLON simpleExp
                    {
                        if ($1 != nullptr)
                        {
                            auto decl = dynamic_cast<VarDeclNode*>($1);
                            if (decl == nullptr)
                            {
                                throw std::runtime_error("dynamic cast failed for varDeclInit.");
                            }
                            decl->setInitialized(true);
                            $$ = decl;
                            $$->addChild($3);
                        }
                    }
                | error COLON simpleExp
                    {
                        yyerrok;
                        $$ = nullptr;
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
                | ID LBRACK error
                    {
                        $$ = nullptr;
                    }
                | error RBRACK
                    {
                        yyerrok;
                        $$ = nullptr;
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
                        $$->addChild(compStmt);
                    }
                | ID LPAREN parms RPAREN compoundStmt
                    {
                        DataType dataType = DataType(DataTypeEnum::Void);
                        $$ = new FunDeclNode($1->lineNum, $1->str, dataType);
                        $$->addChild($3);

                        auto compStmt = dynamic_cast<CompoundStmtNode*>($5);
                        if (compStmt == nullptr)
                        {
                            Error::critical($5->getLineNum(), "Failed converting node to compstmt");
                        }
                        $$->addChild(compStmt);
                    }
                | typeSpec error
                    {
                        $$ = nullptr;
                    }
                | typeSpec ID LPAREN error
                    {
                        $$ = nullptr;
                    }
                | ID LPAREN error
                    {
                        $$ = nullptr;
                    }
                | ID LPAREN parms RPAREN error
                    {
                        $$ = nullptr;
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
                        if ($$ != nullptr)
                        {
                            $$->addSibling($3);
                        }
                    }
                | parmTypeList
                    {
                        $$ = $1;
                    }
                | parmList SEMICOLON error
                    {
                        $$ = nullptr;
                    }
                | error
                    {
                        $$ = nullptr;
                    }
                ;

parmTypeList    : typeSpec parmIdList
                    {
                        $$ = $2;
                        if ($$ != nullptr)
                        {
                            auto param = dynamic_cast<VarDeclNode*>($$);
                            if (param == nullptr)
                            {
                                Error::error($2->getLineNum(), "dynamic_cast<VarDeclNode*> failed. Node is wrong type.");
                            }
                            param->setTypeSpec($1);
                        }
                    }
                | typeSpec error
                    {
                        $$ = nullptr;
                    }
                ;

parmIdList      : parmIdList COMMA parmId
                    {
                        yyerrok;
                        if ($1 == nullptr)
                        {
                            $$ = $3;
                        }
                        else {
                            $$ = $1;
                        }
                        if ($$ != nullptr)
                        {
                            $$->addSibling($3);
                        }
                    }
                | parmId
                    {
                        $$ = $1;
                    }
                | parmIdList COMMA error
                    {
                        $$ = nullptr;
                    }
                ;

parmId          : ID
                    {
                        DataType dataType = DataType(DataTypeEnum::Void);
                        auto param = new VarDeclNode($1->lineNum, $1->str, dataType, false, true);
                        param->setInitialized(true);
                        $$ = param;
                    }
                | ID LBRACK RBRACK
                    {
                        DataType dataType = DataType(DataTypeEnum::Void, true);
                        auto param = new VarDeclNode($1->lineNum, $1->str, dataType, false, true);
                        param->setInitialized(true);
                        $$ = param;
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
                | IF error THEN stmt
                    {
                        yyerrok;
                        $$ = nullptr;
                    }
                | IF error THEN closedStmt ELSE openStmt
                    {
                        yyerrok;
                        $$ = nullptr;
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
                | IF error
                    {
                        $$ = nullptr;
                    }
                | IF error ELSE closedStmt
                    {
                        yyerrok;
                        $$ = nullptr;
                    }
                | IF error THEN closedStmt ELSE closedStmt
                    {
                        yyerrok;
                        $$ = nullptr;
                    }
                | WHILE error DO closedStmt
                    {
                        yyerrok;
                        $$ = nullptr; 
                    }
                | WHILE error
                    {
                        $$ = nullptr;
                    }
                | FOR ID ASS error DO closedStmt
                    {
                        yyerrok;
                        $$ = nullptr;
                    }
                | FOR error
                    {
                        $$ = nullptr;
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
                | error SEMICOLON
                    {
                        yyerrok;
                        $$ = nullptr;
                    }
                ;

compoundStmt    : LCURL localDecls stmtList RCURL
                    {
                        yyerrok;

                        $$ = new CompoundStmtNode($1->lineNum);
                        $$->addChild($2);
                        $$->addChild($3);
                    }
                ;

localDecls      : localDecls scopedVarDecl
                    {
                        if ($1 == nullptr && $2 == nullptr)
                        {
                        } else if ($1 == nullptr)
                        {
                            $$ = $2;
                        } else
                        {
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
                        if ($1 == nullptr && $2 == nullptr)
                        {
                        } else if ($1 == nullptr)
                        {
                            $$ = $2;
                        } else
                        {
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
                        auto var = new VarDeclNode($2->lineNum, $2->str, dataType);
                        var->setInitialized(true);
                        var->setTypeSpec(DataTypeEnum::Int);
                        $$->addChild(var);
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
                        auto var = new VarDeclNode($2->lineNum, $2->str, dataType);
                        var->setInitialized(true);
                        var->setTypeSpec(DataTypeEnum::Int);

                        $$->addChild(var);
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
                | simpleExp TO error
                    {
                        $$ = nullptr;
                    }
                | error BY error
                    {
                        $$ = nullptr;
                        yyerrok;
                    }
                | simpleExp TO simpleExp BY error
                    {
                        $$ = nullptr;
                    }
                ;

returnStmt      : RETURN SEMICOLON 
                    {
                        $$ = new ReturnNode($1->lineNum);
                    }
                | RETURN exp SEMICOLON
                    {
                        yyerrok;
                        $$ = new ReturnNode($1->lineNum);
                        $$->addChild($2);
                    }
                | RETURN error SEMICOLON
                    {
                        $$ = nullptr;
                        yyerrok;
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
                        $$ = new UnaryOpNode($1->getLineNum(), UnaryOpType::Inc);
                        $$->addChild($1);

                    }
                | mutable DEC
                    {
                        $$ = new UnaryOpNode($1->getLineNum(), UnaryOpType::Dec);
                        $$->addChild($1);
                    }
                | simpleExp
                    {
                        $$ = $1;
                    }
                | error assignop exp
                    {
                        $$ = nullptr;
                        yyerrok;
                    }
                | mutable assignop error
                    {
                        $$ = nullptr;
                    }
                | error INC
                    {
                        $$ = nullptr;
                        yyerrok;
                    }
                | error DEC
                    {
                        $$ = nullptr;
                        yyerrok;
                    }
                ;

assignop        : ASS
                    {
                        $$ = new BinaryOpNode($1->lineNum, BinaryOpType::Ass);
                    }
                | ADDASS
                    {
                        $$ = new BinaryOpNode($1->lineNum, BinaryOpType::AddAss);
                    }
                | SUBASS
                    {
                        $$ = new BinaryOpNode($1->lineNum, BinaryOpType::SubAss);
                    }
                | MULASS
                    {
                        $$ = new BinaryOpNode($1->lineNum, BinaryOpType::MulAss);
                    }
                | DIVASS
                    {
                        $$ = new BinaryOpNode($1->lineNum, BinaryOpType::DivAss);
                    }
                ;

simpleExp       : simpleExp OR andExp
                    {
                        if ($1 != nullptr)
                        {
                            $$ = new BinaryOpNode($1->getLineNum(), BinaryOpType::Or);
                            $$->addChild($1);
                            $$->addChild($3);
                        }

                    }
                | andExp
                    {
                        $$ = $1;
                    }
                | simpleExp OR error
                    {
                        $$ = nullptr;
                    }
                ;

andExp          : andExp AND unaryRelExp
                    {
                        if ($1 != nullptr)
                        {
                            $$ = new BinaryOpNode($1->getLineNum(), BinaryOpType::And);
                            $$->addChild($1);
                            $$->addChild($3);
                        }

                    }
                | unaryRelExp
                    {
                        $$ = $1;
                    }
                | andExp AND error
                    {
                        $$ = nullptr;
                    }
                ;

unaryRelExp     : NOT unaryRelExp
                    {
                        if ($1 != nullptr)
                        {
                            $$ = new UnaryOpNode($1->lineNum, UnaryOpType::Not);
                            $$->addChild($2);
                        }
                    }
                | relExp
                    {
                        $$ = $1;
                    }
                | NOT error
                    {
                        $$ = nullptr;
                    }
                ;

relExp          : sumExp relop sumExp
                    {
                        $$ = $2;
                        if ($$ != nullptr)
                        {
                            $$->addChild($1);
                            $$->addChild($3);
                        }
                    }
                | sumExp
                    {
                        $$ = $1;
                    }
                ;

relop           : LT
                    {
                        if ($1 != nullptr)
                        {
                            $$ = new BinaryOpNode($1->lineNum, BinaryOpType::LT);
                        }
                    }
                | LEQ
                    {
                        if ($1 != nullptr)
                        {
                            $$ = new BinaryOpNode($1->lineNum, BinaryOpType::LEQ);
                        }
                    }
                | GT
                    {
                        if ($1 != nullptr)
                        {
                            $$ = new BinaryOpNode($1->lineNum, BinaryOpType::GT);
                        }
                    }
                | GEQ
                    {
                        if ($1 != nullptr)
                        {
                            $$ = new BinaryOpNode($1->lineNum, BinaryOpType::GEQ);
                        }
                    }
                | EQ
                    {
                        if ($1 != nullptr)
                        {
                            $$ = new BinaryOpNode($1->lineNum, BinaryOpType::EQ);
                        }
                    }
                | NEQ
                    {
                        if ($1 != nullptr)
                        {
                            $$ = new BinaryOpNode($1->lineNum, BinaryOpType::NEQ);
                        }
                    }
                ;

sumExp          : sumExp sumOp mulExp
                    {
                        $$ = $2;
                        if ($$ != nullptr)
                        {
                            $$->addChild($1);
                            $$->addChild($3);
                        }
                    }
                | mulExp
                    {
                        $$ = $1;
                    }
                | sumExp sumOp error
                    {
                        $$ = nullptr;
                    }
                ;

sumOp           : PLUS
                    {
                        if ($1 != nullptr)
                        {
                            $$ = new BinaryOpNode($1->lineNum, BinaryOpType::Add);
                        }
                    }
                | DASH
                    {
                        if ($1 != nullptr)
                        {
                            $$ = new BinaryOpNode($1->lineNum, BinaryOpType::Sub);
                        }
                    }
                ;

mulExp          : mulExp mulOp unaryExp
                    {
                        $$ = $2;
                        if ($$ != nullptr)
                        {
                            $$->addChild($1);
                            $$->addChild($3);
                        }
                    }
                | unaryExp
                    {
                        $$ = $1;
                    }
                | mulExp mulOp error
                    {
                        $$ = nullptr;
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
                        if ($$ != nullptr)
                        {
                        $$->addChild($2);
                        }
                    }
                | factor
                    {
                        $$ = $1;
                    }
                | unaryOp error
                    {
                        $$ = nullptr;
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
                        $$ = new UnaryOpNode($1->lineNum, UnaryOpType::Random);
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
                        $$ = new IdNode($1->lineNum, $1->str);
                    }
                | ID LBRACK exp RBRACK
                    {
                        $$ = new BinaryOpNode($1->lineNum, BinaryOpType::Index);
                        ASTNode* id = new IdNode($1->lineNum, $1->str);
                        $$->addChild(id);
                        $$->addChild($3);
                    }
                ;

immutable       : LPAREN exp RPAREN
                    {
                        yyerrok;
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
                | LPAREN error
                    {
                        $$ = nullptr;
                    }
                ;

call            : ID LPAREN args RPAREN
                    {
                        $$ = new CallNode($1->lineNum, $1->str);
                        $$->addChild($3);
                    }
                | error LPAREN
                    {
                        $$ = nullptr;
                        yyerrok;
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
                        yyerrok;
                        $$ = $1;
                        if ($$ != nullptr)
                        {
                        $$->addSibling($3);
                        }
                    }
                | exp
                    {
                        $$ = $1;
                    }
                | argList COMMA error
                    {
                        $$ = nullptr;
                    }
                ;

constant        : NUMCONST
                    {
                        $$ = new ConstNode($1->lineNum, $1->num);
                    }
                | BOOLCONST
                    {
                        $$ = new ConstNode($1->lineNum, $1->boolV);
                    }
                | CHARCONST
                    {
                        $$ = new ConstNode($1->lineNum, $1->charV);
                    }
                
                | STRINGCONST
                    {
                        $$ = new ConstNode($1->lineNum, $1->str);
                    }
                ;
%%
int main(int argc, char** argv)
{
    // for yyerror/ stuff
    initErrorProcessing();
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


    if (options.getFileName() != "")
    {
    std::cout << "====================================" << std::endl;
    std::cout << "FILE: " << options.getFileName().substr(options.getFileName().find_last_of("/\\") + 1) << std::endl;
    auto file = fopen(options.getFileName().c_str(), "r");
        if (file == nullptr)
        {
            std::stringstream ss;
            ss << "source file \"" << options.getFileName() << "\" could not be opened.";
            Error::arglist(ss.str());
            std::cout << "Number of warnings: " << Error::getWarningCount() << std::endl;
            std::cout << "Number of errors: " << Error::getErrorCount() << std::endl;
            exit(EXIT_FAILURE);
        }

        yyin = file;
    }

    yyparse();

    if (Error::getErrorCount() != 0)
    {
        std::cout << "Number of warnings: " << Error::getWarningCount() << std::endl;
        std::cout << "Number of errors: " << Error::getErrorCount() << std::endl;
        return EXIT_SUCCESS;
    }

    // if AST print flag (-p) is on and tree is not null
    if (options.ispFlag() && root != nullptr)
    {
        root->print();
    }

    SemanticAnalyzer semantics = SemanticAnalyzer(root, &symTable);
    semantics.analyze();

    // do semantic analysis

    // if AST print annotated flag is set and tree not null
    if (options.isPFlag() && root != nullptr && Error::getErrorCount() == 0)
    {
        root->print(0, 0, -1, true); // PRINT WITH TYPE INFO THOUGH
        // print root with type info stuff
    }

    std::cout << "Number of warnings: " << Error::getWarningCount() << std::endl;
    std::cout << "Number of errors: " << Error::getErrorCount() << std::endl;

    delete root;
    return EXIT_SUCCESS;
}
