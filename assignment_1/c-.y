%{
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "scanType.h"  // TokenData Type
#include "helpers.h"

extern int yylex();
extern FILE *yyin;
extern int line;         // ERR line number from the scanner!!
extern int numErrors;    // ERR err count

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
    TokenData *tokenData;
    double value;
}

%token <tokenData> ID NUMCONST CHARCONST STRINGCONST BOOLCONST TOKEN KEYWORD

%%
statements : statements statement
              | statement
              ;

statement     : '\n'
              | ID                      { std::cout << "Line " << $1->lineNum << " Token: ID Value: " << $1->tokenStr << std::endl; }
              | KEYWORD                 { std::cout << "Line " << $1->lineNum << " Token: " << $1->tokenStr << std::endl; }
              | NUMCONST                { std::cout << "Line " << $1->lineNum << " Token: NUMCONST Value: " << $1->numConst << "  Input: " << $1->tokenStr << std::endl; }
              | CHARCONST               {
                    if ($1->stringConst.length() > 1) {
                        std::cout << "WARNING(" << $1->lineNum << "): character is " << $1->stringConst.length() << " characters long and not a single character: ''" << $1->stringConst << "''.  The first char will be used.\n";
                    }
                    std::cout << "Line " << $1->lineNum << " Token: CHARCONST Value: '" << $1->charConst << "'  Input: " << $1->tokenStr << std::endl; 
                  }
              | STRINGCONST             { std::cout << "Line " << $1->lineNum << " Token: STRINGCONST Value: \"" << $1->stringConst << "\"  Len: " << $1->stringConst.length() << "  Input: " << $1->tokenStr << std::endl; }
              | BOOLCONST               { printf("Line %i Token: BOOLCONST Value: %d  Input: %s\n", $1->lineNum, $1->boolConst, $1->tokenStr.c_str()); }
              | TOKEN                   {
                    std::cout << "Line " << $1->lineNum << " Token: ";
                    if ($1->tokenStr == "=") {
                        std::cout << "ASGN\n";
                    } else if ($1->tokenStr == "==") {
                        std::cout << "EQ\n";
                    } else if ($1->tokenStr == "+=") {
                        std::cout << "ADDASS\n";
                    } else if ($1->tokenStr == "++") {
                        std::cout << "INC\n";
                    } else if ($1->tokenStr == "--") {
                        std::cout << "DEC\n";
                    } else if ($1->tokenStr == ">=") {
                        std::cout << "GEQ\n";
                    } else if ($1->tokenStr == "<=") {
                        std::cout << "LEQ\n";
                    } else if ($1->tokenStr == "!=") {
                        std::cout << "NEQ\n";
                    } else {
                        std::cout << $1->tokenStr << std::endl;
                    }
                  }

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

    numErrors = 0;
    yyparse();

    return 0;
}
