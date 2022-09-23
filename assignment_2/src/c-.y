%{
#include "AST/AST.h"
#include "scanType.h"  // TokenData Type
#include "Options/Options.h"

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
AST::Node* root;

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
    AST::Decl::Type type;
    AST::Node *node;
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
                        AST::Decl::Var *var = (AST::Decl::Var *)$2;
                        var->setType($1);
                        $$ = var;
					}
                    ;

scopedVarDecl       : STATIC typeSpec varDeclList SEMI
                    {
                        AST::Decl::Var *var = (AST::Decl::Var *)$3;
                        var->setType($2);
                        var->setStatic();
                        $$ = var;
					}
                    | typeSpec varDeclList SEMI
                    {
                        AST::Decl::Var *var = (AST::Decl::Var *)$2;
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
                        $$ = new AST::Decl::Var($1->lineNum, $1->tokenStr, false);
                    }
                    | ID LBRACK NUMCONST RBRACK
                    {
                        $$ = new AST::Decl::Var($1->lineNum, $1->tokenStr, true);
                    }
                    ;

typeSpec            : BOOL
                    {
                        $$ = AST::Decl::Type::Bool;
                    }
                    | CHAR
                    {
                        $$ = AST::Decl::Type::Char;
                    }
                    | INT
                    {
                        $$ = AST::Decl::Type::Int;
                    }
                    ;

funDecl             : typeSpec ID LPAREN parms RPAREN compoundStmt
                    {
                        $$ = new AST::Decl::Func($2->lineNum, $1, $2->tokenStr, $4, $6);
                    }
                    | ID LPAREN parms RPAREN compoundStmt
                    {
                        $$ = new AST::Decl::Func($1->lineNum, $1->tokenStr, $3, $5);
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
                        AST::Decl::Parm *parms = (AST::Decl::Parm *)$2;
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
                        $$ = new AST::Decl::Parm($1->lineNum, $1->tokenStr, false);
					}
                    | ID LBRACK RBRACK
                    {
                        $$ = new AST::Decl::Parm($1->lineNum, $1->tokenStr, true);
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
                        $$ = new AST::Stmt::Compound($1->lineNum, $2, $3);
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
                        $$ = new AST::Stmt::Select($1->lineNum, $2, $4);
                    }
                    | IF simpleExp THEN closedStmt ELSE openStmt
                    {
                        $$ = new AST::Stmt::Select($1->lineNum, $2, $4, $6);
                    }
                    ;

selectStmtClosed    : IF simpleExp THEN closedStmt ELSE closedStmt
                    {
                        $$ = new AST::Stmt::Select($1->lineNum, $2, $4, $6);
                    }
                    ;

iterStmtOpen        : WHILE simpleExp DO openStmt
                    {
                        $$ = new AST::Stmt::While($1->lineNum, $2, $4);
                    }
                    | FOR ID ASGN iterRange DO openStmt
                    {
                        AST::Decl::Var *iterator = new AST::Decl::Var($1->lineNum, $2->tokenStr, false);
                        iterator->setType(AST::Decl::Type::Int);
                        $$ = new AST::Stmt::For($1->lineNum, iterator, $4, $6);
                    }
                    ;

iterStmtClosed      : WHILE simpleExp DO closedStmt
                    {
                        $$ = new AST::Stmt::While($1->lineNum, $2, $4);
                    }
                    | FOR ID ASGN iterRange DO closedStmt
                    {
                        AST::Decl::Var *iterator = new AST::Decl::Var($1->lineNum, $2->tokenStr, false);
                        iterator->setType(AST::Decl::Type::Int);
                        $$ = new AST::Stmt::For($1->lineNum, iterator, $4, $6);
                    }
                    ;

iterRange           : simpleExp TO simpleExp
                    {
                        $$ = new AST::Stmt::Range($1->lineNumber(), $1, $3);
                    }
                    | simpleExp TO simpleExp BY simpleExp
                    {
                        $$ = new AST::Stmt::Range($1->lineNumber(), $1, $3, $5);
                    }
                    ;

returnStmt          : RETURN SEMI
                    {
                        $$ = new AST::Stmt::Return($1->lineNum, nullptr);
                    }
                    | RETURN exp SEMI
                    {
                        $$ = new AST::Stmt::Return($1->lineNum, $2);
                    }
                    ;

breakStmt           : BREAK SEMI
                    {
                        $$ = new AST::Stmt::Break($1->lineNum);
                    }
                    ;

exp                 : mutable assignop exp
                    {
                        AST::Op::Asgn *op = (AST::Op::Asgn *)$2;
                        op->addChildren($1, $3);
                        $$ = op;
                    }
                    | mutable INC
                    {
                        $$ = new AST::Op::UnaryAsgn($1->lineNumber(), AST::Op::UnaryAsgn::Type::Inc, $1);
                    }
                    | mutable DEC
                    {
                        $$ = new AST::Op::UnaryAsgn($1->lineNumber(), AST::Op::UnaryAsgn::Type::Dec, $1);
                    }
                    | simpleExp
                    {
                        $$ = $1;
					}
                    ;

assignop            : ASGN
                    {
                        $$ = new AST::Op::Asgn($1->lineNum, AST::Op::Asgn::Type::Asgn);
					}
                    | ADDASGN
                    {
                        $$ = new AST::Op::Asgn($1->lineNum, AST::Op::Asgn::Type::AddAsgn);
					}
                    | SUBASGN
                    {
                        $$ = new AST::Op::Asgn($1->lineNum, AST::Op::Asgn::Type::SubAsgn);
					}
                    | DIVASGN
                    {
                        $$ = new AST::Op::Asgn($1->lineNum, AST::Op::Asgn::Type::DivAsgn);
					}
                    | MULASGN
                    {
                        $$ = new AST::Op::Asgn($1->lineNum, AST::Op::Asgn::Type::MulAsgn);
					}
                    ;

simpleExp           : simpleExp OR andExp
                    {
                        $$ = new AST::Op::Binary($1->lineNumber(), AST::Op::Binary::Type::Or, $1, $3);
                    }
                    | andExp
                    {
                        $$ = $1;
					}
                    ;

andExp              : andExp AND unaryRelExp
                    {
                        $$ = new AST::Op::Binary($1->lineNumber(), AST::Op::Binary::Type::And, $1, $3);
                    }
                    | unaryRelExp
                    {
                        $$ = $1;
					}
                    ;

unaryRelExp         : NOT unaryRelExp
                    {
                        $$ = new AST::Op::Unary($1->lineNum, AST::Op::Unary::Type::Not, $2);
                    }
                    | relExp
                    {
                        $$ = $1;
					}
                    ;

relExp              : sumExp relop sumExp
                    {
                        AST::Op::Binary *op = (AST::Op::Binary *)$2;
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
                        $$ = new AST::Op::Binary($1->lineNum, AST::Op::Binary::Type::LT);
					}
                    | LEQ
                    {
                        $$ = new AST::Op::Binary($1->lineNum, AST::Op::Binary::Type::LEQ);
					}
                    | GT
                    {
                        $$ = new AST::Op::Binary($1->lineNum, AST::Op::Binary::Type::GT);
					}
                    | GEQ
                    {
                        $$ = new AST::Op::Binary($1->lineNum, AST::Op::Binary::Type::GEQ);
					}
                    | EQ
                    {
                        $$ = new AST::Op::Binary($1->lineNum, AST::Op::Binary::Type::EQ);
					}
                    | NEQ
                    {
                        $$ = new AST::Op::Binary($1->lineNum, AST::Op::Binary::Type::NEQ);
					}
                    ;

sumExp              : sumExp sumop mulExp
                    {
                        AST::Op::Binary *op = (AST::Op::Binary *)$2;
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
                        $$ = new AST::Op::Binary($1->lineNum, AST::Op::Binary::Type::Add);
					}
                    | DASH
                    {
                        $$ = new AST::Op::Binary($1->lineNum, AST::Op::Binary::Type::Subtract);
					}
                    ;

mulExp              : mulExp mulop unaryExp
                    {
                        AST::Op::Binary *op = (AST::Op::Binary *)$2;
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
                        $$ = new AST::Op::Binary($1->lineNum, AST::Op::Binary::Type::Mul);
					}
                    | DIV
                    {
                        $$ = new AST::Op::Binary($1->lineNum, AST::Op::Binary::Type::Div);
					}
                    | MOD
                    {
                        $$ = new AST::Op::Binary($1->lineNum, AST::Op::Binary::Type::Mod);
					}
                    ;

unaryExp            : unaryop unaryExp
                    {
                        AST::Op::Unary *op = (AST::Op::Unary *)$1;
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
                        $$ = new AST::Op::Unary($1->lineNum, AST::Op::Unary::Type::Chsign);
					}
                    | ASTERISK
                    {
                        $$ = new AST::Op::Unary($1->lineNum, AST::Op::Unary::Type::Sizeof);
					}
                    | RAND
                    {
                        $$ = new AST::Op::Unary($1->lineNum, AST::Op::Unary::Type::Random);
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
                        $$ = new AST::Stmt::Id($1->lineNum, $1->tokenStr);
					}
                    | ID LBRACK exp RBRACK
                    {
                        $$ = new AST::Op::Binary($1->lineNum, AST::Op::Binary::Type::Index, new AST::Stmt::Id($1->lineNum, $1->tokenStr), $3);
                    }
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
                        $$ = new AST::Stmt::Call($1->lineNum, $1->tokenStr, $3);
                    }
                    | ID LPAREN RPAREN
                    {
                        $$ = new AST::Stmt::Call($1->lineNum, $1->tokenStr);
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
                        $$ = new AST::Stmt::Const($1->lineNum, AST::Stmt::Const::Type::Int, $1->tokenStr);
                    }
                    | CHARCONST
                    {
                        $$ = new AST::Stmt::Const($1->lineNum, AST::Stmt::Const::Type::Char, $1->tokenStr);
                    }
                    | STRINGCONST
                    {
                        $$ = new AST::Stmt::Const($1->lineNum, AST::Stmt::Const::Type::String, $1->tokenStr);
                    }
                    | BOOLCONST
                    {
                        $$ = new AST::Stmt::Const($1->lineNum, AST::Stmt::Const::Type::Bool, $1->tokenStr);
                    }
                    ;

%%
extern int yydebug;
extern std::vector<std::unique_ptr<TokenData>> token_vec;
int main(int argc, char *argv[])
{
    Options options(argc, argv);
    yydebug = options.debug();

    if (!options.files().empty()) {
        for (unsigned i = 0; i < options.files().size(); i++) {
            std::string file = options.files()[i];
            if ((yyin = fopen(file.c_str(), "r"))) {
                numErrors = 0;
                yyparse();

                if (root != nullptr && options.print()) {
                    root->print();
                    delete root;
                    
                    /// Gets rid of all unique_ptr tokens
                    token_vec.clear();

                    if (i != options.files().size() - 1) {
                        std::cout << std::endl;
                    }
                }
            }
            else {
                printf("ERROR: failed to open \'%s\'\n", argv[1]);
                exit(1);
            }
        }
    } else {
        yyparse();
    }



    return 0;
}
