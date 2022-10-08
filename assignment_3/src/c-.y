%{
#include "Tree/Tree.h"
#include "scanType.h"  // TokenData Type
#include "Options/Options.h"
#include "SemanticsChecker/SemanticsChecker.h"

#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>

extern int yylex();
extern FILE* yyin;
extern int line;         // ERR line number from the scanner!!
extern int numErrors;    // ERR err count
extern char* yytext;
Tree::Node* root;

#define YYERROR_VERBOSE
void yyerror(const char *msg)
{
    std::cout << "ERROR(" << line << "): " << msg << std::endl;
    numErrors++;
}

%}

// this is included in the tab.h file
// so scanType.h must be included before the tab.h file!!!!
%union {
    Tree::DataType type;
    Tree::Node *node;
    TokenData *tokenData;
}

%token <tokenData> WHILE IF FOR TO RETURN BREAK BY DO
%token <tokenData> NOT AND OR
%token <tokenData> ADD DASH RAND ASTERISK DIV MOD ASGN ADDASGN SUBASGN MULASGN DIVASGN
%token <tokenData> THEN ELSE LCURL RCURL
%token <tokenData> RPAREN LPAREN RBRACK LBRACK
%token <tokenData> STATIC
%token <tokenData> SEMI LT LEQ GT GEQ EQ NEQ INC DEC COL COM
%token <type> INT BOOL CHAR 

%token <tokenData> ID NUMCONST CHARCONST STRINGCONST BOOLCONST
%type <node> program
%type <node> declList decl varDecl scopedVarDecl varDeclList varDeclInit varDeclId
%type <type> typeSpec
%type <node> funDecl parms parmList parmTypeList parmIdList parmId
%type <node> stmt expStmt compoundStmt localDecls stmtList closedStmt openStmt selectStmtOpen selectStmtClosed iterStmtOpen iterStmtClosed iterRange returnStmt breakStmt
%type <node> exp assignop simpleExp andExp unaryRelExp relExp relop sumExp sumop mulExp mulop unaryExp unaryop
%type <node> factor mutable immutable call argList constant


%%

program             : declList
                    {
                        $$ = $1;
                        root = $$;
                    }
                    ;

declList            : declList decl
                    {
                        $$ = $1;
                        $$->addSibling($2);
                    }
                    | decl
                    {
                        $$ = $1;
                    }
                    ;

decl                : varDecl
                    {
                        $$ = $1;
					}
                    | funDecl
                    {
                        $$ = $1;
					}
                    ;

varDecl             : typeSpec varDeclList SEMI
                    {
                        Tree::Decl::Var *var = (Tree::Decl::Var *)$2;
                        var->setType($1);
                        $$ = var;
					}
                    ;

scopedVarDecl       : STATIC typeSpec varDeclList SEMI
                    {
                        Tree::Decl::Var *var = (Tree::Decl::Var *)$3;
                        var->setType($2);
                        var->setStatic();
                        $$ = var;
					}
                    | typeSpec varDeclList SEMI
                    {
                        Tree::Decl::Var *var = (Tree::Decl::Var *)$2;
                        var->setType($1);
                        $$ = var;
					}
                    ;

varDeclList         : varDeclList COM varDeclInit
                    {
                        $$ = $1;
                        $$->addSibling($3);
                    }
                    | varDeclInit
                    {
                        $$ = $1;
					}
                    ;

varDeclInit         : varDeclId
                    {
                        $$ = $1;
					}
                    | varDeclId COL simpleExp
                    {
                        $$ = $1;
                        $$->addChild($3);
                    }
                    ;
                
varDeclId           : ID
                    {
                        $$ = new Tree::Decl::Var($1->lineNum, $1->tokenStr, false);
                    }
                    | ID LBRACK NUMCONST RBRACK
                    {
                        $$ = new Tree::Decl::Var($1->lineNum, $1->tokenStr, true);
                    }
                    ;

typeSpec            : BOOL
                    {
                        $$ = Tree::DataType::Bool;
                    }
                    | CHAR
                    {
                        $$ = Tree::DataType::Char;
                    }
                    | INT
                    {
                        $$ = Tree::DataType::Int;
                    }
                    ;

funDecl             : typeSpec ID LPAREN parms RPAREN compoundStmt
                    {
                        $$ = new Tree::Decl::Func($2->lineNum, $1, $2->tokenStr, $4, $6);
                    }
                    | ID LPAREN parms RPAREN compoundStmt
                    {
                        $$ = new Tree::Decl::Func($1->lineNum, $1->tokenStr, $3, $5);
                    }
                    ;

parms               :
                    {
                        $$ = nullptr;
					}
                    | parmList
                    {
                        $$ = $1;
					}
                    ;

parmList            : parmList SEMI parmTypeList
                    {
                        $$ = $1;
                        $$->addSibling($3);
                    }
                    | parmTypeList
                    {
                        $$ = $1;
					}
                    ;

parmTypeList        : typeSpec parmIdList
                    {
                        Tree::Decl::Parm *parms = (Tree::Decl::Parm *)$2;
                        parms->setType($1);
                        $$ = parms;
					}
                    ;

parmIdList          : parmIdList COM parmId
                    {
                        $$ = $1;
                        $$->addSibling($3);
                    }
                    | parmId
                    {
                        $$ = $1;
					}
                    ;

parmId              : ID
                    {
                        $$ = new Tree::Decl::Parm($1->lineNum, $1->tokenStr, false);
					}
                    | ID LBRACK RBRACK
                    {
                        $$ = new Tree::Decl::Parm($1->lineNum, $1->tokenStr, true);
					}
                    ;

stmt                : closedStmt
                    {
                        $$ = $1;
					}
                    | openStmt
                    {
                        $$ = $1;
					}
                    ;

expStmt             : exp SEMI
                    {
                        $$ = $1;
					}
                    | SEMI
                    {
                        $$ = nullptr;
					}
                    ;

compoundStmt        : LCURL localDecls stmtList RCURL
                    {
                        $$ = new Tree::Stmt::Compound($1->lineNum, $2, $3);
                    }
                    ;

localDecls          :
                    {
                        $$ = nullptr;
					}
                    | localDecls scopedVarDecl
                    {
                        if ($1 == nullptr) {
                            $$ = $2;
                        } else {
                            $$ = $1;
                            $$->addSibling($2);
                        }
                    }
                    ;

stmtList            :
                    {
                        $$ = nullptr;
					}
                    | stmtList stmt
                    {
                        if ($1 == nullptr) {
                            $$ = $2;
                        } else {
                            $$ = $1;
                            $$->addSibling($2);
                        }
                    }
                    ;

closedStmt          : selectStmtClosed
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

openStmt            : selectStmtOpen
                    {
                        $$ = $1;
					}
                    | iterStmtOpen
                    {
                        $$ = $1;
					}
                    ;

selectStmtOpen      : IF simpleExp THEN stmt
                    {
                        $$ = new Tree::Stmt::Select($1->lineNum, $2, $4);
                    }
                    | IF simpleExp THEN closedStmt ELSE openStmt
                    {
                        $$ = new Tree::Stmt::Select($1->lineNum, $2, $4, $6);
                    }
                    ;

selectStmtClosed    : IF simpleExp THEN closedStmt ELSE closedStmt
                    {
                        $$ = new Tree::Stmt::Select($1->lineNum, $2, $4, $6);
                    }
                    ;

iterStmtOpen        : WHILE simpleExp DO openStmt
                    {
                        $$ = new Tree::Stmt::While($1->lineNum, $2, $4);
                    }
                    | FOR ID ASGN iterRange DO openStmt
                    {
                        Tree::Decl::Var *iterator = new Tree::Decl::Var($1->lineNum, $2->tokenStr, false);
                        iterator->setType(Tree::DataType::Int);
                        $$ = new Tree::Stmt::For($1->lineNum, iterator, $4, $6);
                    }
                    ;

iterStmtClosed      : WHILE simpleExp DO closedStmt
                    {
                        $$ = new Tree::Stmt::While($1->lineNum, $2, $4);
                    }
                    | FOR ID ASGN iterRange DO closedStmt
                    {
                        Tree::Decl::Var *iterator = new Tree::Decl::Var($1->lineNum, $2->tokenStr, false);
                        iterator->setType(Tree::DataType::Int);
                        $$ = new Tree::Stmt::For($1->lineNum, iterator, $4, $6);
                    }
                    ;

iterRange           : simpleExp TO simpleExp
                    {
                        $$ = new Tree::Stmt::Range($1->lineNumber(), $1, $3);
                    }
                    | simpleExp TO simpleExp BY simpleExp
                    {
                        $$ = new Tree::Stmt::Range($1->lineNumber(), $1, $3, $5);
                    }
                    ;

returnStmt          : RETURN SEMI
                    {
                        $$ = new Tree::Stmt::Return($1->lineNum, nullptr);
                    }
                    | RETURN exp SEMI
                    {
                        $$ = new Tree::Stmt::Return($1->lineNum, $2);
                    }
                    ;

breakStmt           : BREAK SEMI
                    {
                        $$ = new Tree::Stmt::Break($1->lineNum);
                    }
                    ;

exp                 : mutable assignop exp
                    {
                        Tree::Exp::Op::Asgn *op = (Tree::Exp::Op::Asgn *)$2;
                        op->addChildren($1, $3);
                        $$ = op;
                    }
                    | mutable INC
                    {
                        $$ = new Tree::Exp::Op::UnaryAsgn($1->lineNumber(), Tree::UnaryAsgnType::Inc, $1);
                    }
                    | mutable DEC
                    {
                        $$ = new Tree::Exp::Op::UnaryAsgn($1->lineNumber(), Tree::UnaryAsgnType::Dec, $1);
                    }
                    | simpleExp
                    {
                        $$ = $1;
					}
                    ;

assignop            : ASGN
                    {
                        $$ = new Tree::Exp::Op::Asgn($1->lineNum, Tree::AsgnType::Asgn);
                    }
                    | ADDASGN
                    {
                        $$ = new Tree::Exp::Op::Asgn($1->lineNum, Tree::AsgnType::AddAsgn);
					}
                    | SUBASGN
                    {
                        $$ = new Tree::Exp::Op::Asgn($1->lineNum, Tree::AsgnType::SubAsgn);
					}
                    | MULASGN
                    {
                        $$ = new Tree::Exp::Op::Asgn($1->lineNum, Tree::AsgnType::MulAsgn);
					}
                    | DIVASGN
                    {
                        $$ = new Tree::Exp::Op::Asgn($1->lineNum, Tree::AsgnType::DivAsgn);
					}
                    ;

simpleExp           : simpleExp OR andExp
                    {
                        Tree::Exp::Op::Bool* boolop = new Tree::Exp::Op::Bool($1->lineNumber(), Tree::BoolOpType::Or);
                        boolop->addChildren($1, $3);
                        $$ = boolop;
                    }
                    | andExp
                    {
                        $$ = $1;
					}
                    ;

andExp              : andExp AND unaryRelExp
                    {
                        Tree::Exp::Op::Bool* boolop = new Tree::Exp::Op::Bool($1->lineNumber(), Tree::BoolOpType::And);
                        boolop->addChildren($1, $3);
                        $$ = boolop;
                    }
                    | unaryRelExp
                    {
                        $$ = $1;
					}
                    ;

unaryRelExp         : NOT unaryRelExp
                    {
                        $$ = new Tree::Exp::Op::Unary($1->lineNum, Tree::UnaryOpType::Not, $2);
                    }
                    | relExp
                    {
                        $$ = $1;
					}
                    ;

relExp              : sumExp relop sumExp
                    {
                        Tree::Exp::Op::Binary *op = (Tree::Exp::Op::Binary *)$2;
                        op->addChildren($1, $3);
                        $$ = op;
                    }
                    | sumExp
                    {
                        $$ = $1;
					}
                    ;

relop               : LT
                    {
                        $$ = new Tree::Exp::Op::Bool($1->lineNum, Tree::BoolOpType::LT);
					}
                    | LEQ
                    {
                        $$ = new Tree::Exp::Op::Bool($1->lineNum, Tree::BoolOpType::LEQ);
					}
                    | GT
                    {
                        $$ = new Tree::Exp::Op::Bool($1->lineNum, Tree::BoolOpType::GT);
					}
                    | GEQ
                    {
                        $$ = new Tree::Exp::Op::Bool($1->lineNum, Tree::BoolOpType::GEQ);
					}
                    | EQ
                    {
                        $$ = new Tree::Exp::Op::Bool($1->lineNum, Tree::BoolOpType::EQ);
					}
                    | NEQ
                    {
                        $$ = new Tree::Exp::Op::Bool($1->lineNum, Tree::BoolOpType::NEQ);
					}
                    ;

sumExp              : sumExp sumop mulExp
                    {
                        Tree::Exp::Op::Binary *op = (Tree::Exp::Op::Binary *)$2;
                        op->addChildren($1, $3);
                        $$ = op;
					}
                    | mulExp
                    {
                        $$ = $1;
					}
                    ;

sumop               : ADD
                    {
                        $$ = new Tree::Exp::Op::Binary($1->lineNum, Tree::BinaryOpType::Add);
					}
                    | DASH
                    {
                        $$ = new Tree::Exp::Op::Binary($1->lineNum, Tree::BinaryOpType::Subtract);
					}
                    ;

mulExp              : mulExp mulop unaryExp
                    {
                        Tree::Exp::Op::Binary *op = (Tree::Exp::Op::Binary *)$2;
                        op->addChildren($1, $3);
                        $$ = op;
					}
                    | unaryExp
                    {
                        $$ = $1;
					}
                    ;

mulop               : ASTERISK
                    {
                        $$ = new Tree::Exp::Op::Binary($1->lineNum, Tree::BinaryOpType::Mul);
					}
                    | DIV
                    {
                        $$ = new Tree::Exp::Op::Binary($1->lineNum, Tree::BinaryOpType::Div);
					}
                    | MOD
                    {
                        $$ = new Tree::Exp::Op::Binary($1->lineNum, Tree::BinaryOpType::Mod);
					}
                    ;

unaryExp            : unaryop unaryExp
                    {
                        Tree::Exp::Op::Unary *op = (Tree::Exp::Op::Unary *)$1;
                        op->addExp($2);
                        $$ = op;
					}
                    | factor
                    {
                        $$ = $1;
					}
                    ;

unaryop             : DASH
                    {
                        $$ = new Tree::Exp::Op::Unary($1->lineNum, Tree::UnaryOpType::Chsign);
					}
                    | ASTERISK
                    {
                        $$ = new Tree::Exp::Op::Unary($1->lineNum, Tree::UnaryOpType::Sizeof);
					}
                    | RAND
                    {
                        $$ = new Tree::Exp::Op::Unary($1->lineNum, Tree::UnaryOpType::Random);
					}
                    ;

factor              : mutable
                    {
                        $$ = $1;
					}
                    | immutable
                    {
                        $$ = $1;
					}
                    ;

mutable             : ID
                    {
                        $$ = new Tree::Exp::Id($1->lineNum, $1->tokenStr);
					}
                    | ID LBRACK exp RBRACK
                    {
                        $$ = new Tree::Exp::Op::Binary($1->lineNum, Tree::BinaryOpType::Index, new Tree::Exp::Id($1->lineNum, $1->tokenStr), $3);                    }
                    ;

immutable           : LPAREN exp RPAREN
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

call                : ID LPAREN argList RPAREN
                    {
                        $$ = new Tree::Exp::Call($1->lineNum, $1->tokenStr, $3);
                    }
                    | ID LPAREN RPAREN
                    {
                        $$ = new Tree::Exp::Call($1->lineNum, $1->tokenStr);
                    }
                    ;

argList             : argList COM exp
                    {
                        $$ = $1;
                        $$->addSibling($3);
                    }
                    | exp
                    {
                        $$ = $1;
                    }
                    ;

constant            : NUMCONST
                    {
                        Tree::SuperDataType type = {Tree::DataType::Int, false, false};
                        $$ = new Tree::Exp::Const($1->lineNum, type, $1->tokenStr);
                    }
                    | CHARCONST
                    {
                        Tree::SuperDataType type = {Tree::DataType::Char, false, false};
                        $$ = new Tree::Exp::Const($1->lineNum, type, $1->tokenStr);
                    }
                    | STRINGCONST
                    {
                        Tree::SuperDataType type = {Tree::DataType::Char, true, false};
                        $$ = new Tree::Exp::Const($1->lineNum, type, $1->tokenStr);
                    }
                    | BOOLCONST
                    {
                        Tree::SuperDataType type = {Tree::DataType::Bool, false, false};
                        $$ = new Tree::Exp::Const($1->lineNum, type, $1->tokenStr);
                    }
                    ;

%%extern int yydebug;
extern std::vector<std::unique_ptr<TokenData>> token_vec;
int main(int argc, char *argv[])
{
    numErrors = 0;
    Options::Options options(argc, argv);
    yydebug = options.isYYdebug();
    std::optional<std::string> file = options.file();

    if (file.has_value()) {
        SemanticsChecker semantics = SemanticsChecker(options.isSymbolTableDebug());
        if ((yyin = fopen(file.value().c_str(), "r"))) {
            // file open successful
            yyparse();

            if (options.isPrintAST()) {
                root->print(false);
            }
            semantics.analyze(root);

            if (options.isPrintASTWithTypes()) {
                semantics.print();
            }

            // Free memory
            if (root != nullptr) {
                delete root;
            }
            token_vec.clear();
        }

        std::cout << "Number of warnings: " << semantics.numWarnings() << std::endl;
        std::cout << "Number of errors: " << semantics.numErrors() << std::endl;
    } else {
        // do this forever, since it will always be pulling from stdin
        yyparse();
    }
    
    return 0;
}