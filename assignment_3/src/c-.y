%{
#include "AST/AST.hpp"
#include "scanType.hpp"  // TokenData Type
#include "strutil.hpp"
#include "Options/Options.hpp"
#include "SemanticsChecker/SemanticsChecker.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>

extern int yylex();
extern FILE *yyin;
extern int line;         // ERR line number from the scanner!!
extern int numErrors;    // ERR err count
extern char *yytext;
AST::Node* tree_root;

#define YYERROR_VERBOSE
void yyerror(const char *msg)
{
    std::cout << "ERROR(" << line << "): " << msg << std::endl;
    numErrors++;
}

%}

// this is included in the tab.h file
// so scanType.hpp must be included before the tab.h file!!!!
%union {
    AST::Type type;
    AST::Node *node;
    TokenData *tokenData;
    double value;
}

%token <tokenData> WHILE IF FOR TO RETURN BREAK BY DO
%token <tokenData> NOT AND OR
%token <tokenData> ADD DASH RAND ASTERISK DIV MOD ASGN ADDASGN SUBASGN MULASGN DIVASGN
%token <tokenData> THEN ELSE BGN END
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
                        tree_root = $$;
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
                        $$ = new AST::Decl::Var($1->linenum, $1->tokenstr, false);
                    }
                    | ID LBRACK NUMCONST RBRACK
                    {
                        $$ = new AST::Decl::Var($1->linenum, $1->tokenstr, true);
                    }
                    ;

typeSpec            : BOOL
                    {
                        $$ = AST::Type::Bool;
                    }
                    | CHAR
                    {
                        $$ = AST::Type::Char;
                    }
                    | INT
                    {
                        $$ = AST::Type::Int;
                    }
                    ;

funDecl             : typeSpec ID LPAREN parms RPAREN compoundStmt
                    {
                        $$ = new AST::Decl::Func($2->linenum, $1, $2->tokenstr, $4, $6);
                    }
                    | ID LPAREN parms RPAREN compoundStmt
                    {
                        $$ = new AST::Decl::Func($1->linenum, $1->tokenstr, $3, $5);
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
                        $$ = new AST::Decl::Parm($1->linenum, $1->tokenstr, false);
					}
                    | ID LBRACK RBRACK
                    {
                        $$ = new AST::Decl::Parm($1->linenum, $1->tokenstr, true);
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

compoundStmt        : BGN localDecls stmtList END
                    {
                        $$ = new AST::Stmt::Compound($1->linenum, $2, $3);
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
                        $$ = new AST::Stmt::Select($1->linenum, $2, $4);
                    }
                    | IF simpleExp THEN closedStmt ELSE openStmt
                    {
                        $$ = new AST::Stmt::Select($1->linenum, $2, $4, $6);
                    }
                    ;

selectStmtClosed    : IF simpleExp THEN closedStmt ELSE closedStmt
                    {
                        $$ = new AST::Stmt::Select($1->linenum, $2, $4, $6);
                    }
                    ;

iterStmtOpen        : WHILE simpleExp DO openStmt
                    {
                        $$ = new AST::Stmt::While($1->linenum, $2, $4);
                    }
                    | FOR ID ASGN iterRange DO openStmt
                    {
                        AST::Decl::Var *iterator = new AST::Decl::Var($1->linenum, $2->tokenstr, false);
                        iterator->setType(AST::Type::Int);
                        $$ = new AST::Stmt::For($1->linenum, iterator, $4, $6);
                    }
                    ;

iterStmtClosed      : WHILE simpleExp DO closedStmt
                    {
                        $$ = new AST::Stmt::While($1->linenum, $2, $4);
                    }
                    | FOR ID ASGN iterRange DO closedStmt
                    {
                        AST::Decl::Var *iterator = new AST::Decl::Var($1->linenum, $2->tokenstr, false);
                        iterator->setType(AST::Type::Int);
                        $$ = new AST::Stmt::For($1->linenum, iterator, $4, $6);
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
                        $$ = new AST::Stmt::Return($1->linenum, nullptr);
                    }
                    | RETURN exp SEMI
                    {
                        $$ = new AST::Stmt::Return($1->linenum, $2);
                    }
                    ;

breakStmt           : BREAK SEMI
                    {
                        $$ = new AST::Stmt::Break($1->linenum);
                    }
                    ;

exp                 : mutable assignop exp
                    {
                        AST::Exp::Op::Asgn *op = (AST::Exp::Op::Asgn *)$2;
                        op->addChildren($1, $3);
                        $$ = op;
                    }
                    | mutable INC
                    {
                        $$ = new AST::Exp::Op::UnaryAsgn($1->lineNumber(), AST::UnaryAsgnType::Inc, $1);
                    }
                    | mutable DEC
                    {
                        $$ = new AST::Exp::Op::UnaryAsgn($1->lineNumber(), AST::UnaryAsgnType::Dec, $1);
                    }
                    | simpleExp
                    {
                        $$ = $1;
					}
                    ;

assignop            : ASGN
                    {
                        $$ = new AST::Exp::Op::Asgn($1->linenum, AST::AsgnType::Asgn);
					}
                    | ADDASGN
                    {
                        $$ = new AST::Exp::Op::Asgn($1->linenum, AST::AsgnType::AddAsgn);
					}
                    | SUBASGN
                    {
                        $$ = new AST::Exp::Op::Asgn($1->linenum, AST::AsgnType::SubAsgn);
					}
                    | DIVASGN
                    {
                        $$ = new AST::Exp::Op::Asgn($1->linenum, AST::AsgnType::DivAsgn);
					}
                    | MULASGN
                    {
                        $$ = new AST::Exp::Op::Asgn($1->linenum, AST::AsgnType::MulAsgn);
					}
                    ;

simpleExp           : simpleExp OR andExp
                    {
                        AST::Exp::Op::Bool* boolop = new AST::Exp::Op::Bool($1->lineNumber(), AST::BoolOpType::Or);
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
                        AST::Exp::Op::Bool* boolop = new AST::Exp::Op::Bool($1->lineNumber(), AST::BoolOpType::And);
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
                        $$ = new AST::Exp::Op::Unary($1->linenum, AST::UnaryOpType::Not, $2);
                    }
                    | relExp
                    {
                        $$ = $1;
					}
                    ;

relExp              : sumExp relop sumExp
                    {
                        AST::Exp::Op::Binary *op = (AST::Exp::Op::Binary *)$2;
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
                        $$ = new AST::Exp::Op::Bool($1->linenum, AST::BoolOpType::LT);
					}
                    | LEQ
                    {
                        $$ = new AST::Exp::Op::Bool($1->linenum, AST::BoolOpType::LEQ);
					}
                    | GT
                    {
                        $$ = new AST::Exp::Op::Bool($1->linenum, AST::BoolOpType::GT);
					}
                    | GEQ
                    {
                        $$ = new AST::Exp::Op::Bool($1->linenum, AST::BoolOpType::GEQ);
					}
                    | EQ
                    {
                        $$ = new AST::Exp::Op::Bool($1->linenum, AST::BoolOpType::EQ);
					}
                    | NEQ
                    {
                        $$ = new AST::Exp::Op::Bool($1->linenum, AST::BoolOpType::NEQ);
					}
                    ;

sumExp              : sumExp sumop mulExp
                    {
                        AST::Exp::Op::Binary *op = (AST::Exp::Op::Binary *)$2;
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
                        $$ = new AST::Exp::Op::Binary($1->linenum, AST::BinaryOpType::Add);
					}
                    | DASH
                    {
                        $$ = new AST::Exp::Op::Binary($1->linenum, AST::BinaryOpType::Subtract);
					}
                    ;

mulExp              : mulExp mulop unaryExp
                    {
                        AST::Exp::Op::Binary *op = (AST::Exp::Op::Binary *)$2;
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
                        $$ = new AST::Exp::Op::Binary($1->linenum, AST::BinaryOpType::Mul);
					}
                    | DIV
                    {
                        $$ = new AST::Exp::Op::Binary($1->linenum, AST::BinaryOpType::Div);
					}
                    | MOD
                    {
                        $$ = new AST::Exp::Op::Binary($1->linenum, AST::BinaryOpType::Mod);
					}
                    ;

unaryExp            : unaryop unaryExp
                    {
                        AST::Exp::Op::Unary *op = (AST::Exp::Op::Unary *)$1;
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
                        $$ = new AST::Exp::Op::Unary($1->linenum, AST::UnaryOpType::Chsign);
					}
                    | ASTERISK
                    {
                        $$ = new AST::Exp::Op::Unary($1->linenum, AST::UnaryOpType::Sizeof);
					}
                    | RAND
                    {
                        $$ = new AST::Exp::Op::Unary($1->linenum, AST::UnaryOpType::Random);
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
                        $$ = new AST::Exp::Id($1->linenum, $1->tokenstr);
					}
                    | ID LBRACK exp RBRACK
                    {
                        $$ = new AST::Exp::Op::Binary($1->linenum, AST::BinaryOpType::Index, new AST::Exp::Id($1->linenum, $1->tokenstr), $3);
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
                        $$ = new AST::Exp::Call($1->linenum, $1->tokenstr, $3);
                    }
                    | ID LPAREN RPAREN
                    {
                        $$ = new AST::Exp::Call($1->linenum, $1->tokenstr);
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
                        AST::TypeInfo type = {AST::Type::Int, false, false};
                        $$ = new AST::Exp::Const($1->linenum, type, $1->tokenstr);
                    }
                    | CHARCONST
                    {
                        AST::TypeInfo type = {AST::Type::Char, false, false};
                        $$ = new AST::Exp::Const($1->linenum, type, $1->tokenstr);
                    }
                    | STRINGCONST
                    {
                        AST::TypeInfo type = {AST::Type::Char, true, false};
                        $$ = new AST::Exp::Const($1->linenum, type, $1->tokenstr);
                    }
                    | BOOLCONST
                    {
                        AST::TypeInfo type = {AST::Type::Bool, false, false};
                        $$ = new AST::Exp::Const($1->linenum, type, $1->tokenstr);
                    }
                    ;

%%
extern int yydebug;
extern std::vector<std::unique_ptr<TokenData>> tokens;
int main(int argc, char *argv[])
{
    Options options(argc, argv);
    bool fileExists = true;
    yydebug = options.debug();
    std::optional<std::string> file = options.file();

    if (file.has_value()) {
        SemanticsChecker semantics = SemanticsChecker(options.debugSymbolTable());
        if ((yyin = fopen(file.value().c_str(), "r"))) {
            // file open successful
            // do the parsing
            numErrors = 0;
            yyparse();

            if (options.print()) {
                tree_root->print(false);
            }

            semantics.analyze(tree_root);

            if (options.printTypeInfo()) {
                semantics.print();
            }

            // Free memory
            if (tree_root != nullptr) {
                delete tree_root;
            }
            tokens.clear();
        }
        else {
            std::cout << "ERROR(ARGLIST): source file \"" + file.value() + "\" could not be opened." << std::endl;
            fileExists = false;
        }
        std::cout << "Number of warnings: " << semantics.numWarnings() << std::endl;
        std::cout << "Number of errors: " << semantics.numErrors() + !fileExists << std::endl;
    } else {
        yyparse();
    }
    
    return 0;
}