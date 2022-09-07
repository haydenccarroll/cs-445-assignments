%{
// // // // // // // // // // // // // // // // // // // // // // // 
// CS445 - Calculator Example Program written in the style of the C-
// compiler for the class.
//
// Robert Heckendorn
// Jan 21, 2021    

#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>

#include "scanType.hpp"  // TokenData Type
#include "strutil.hpp"

double vars[26];    

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
statementlist : statementlist statement
              | statement
              ;

statement     : '\n'
              | ID                      { std::cout << "Line " << $1->linenum << " Token: ID Value: " << $1->tokenstr << std::endl; }
              | KEYWORD                 { std::cout << "Line " << $1->linenum << " Token: " << $1->tokenstr << std::endl; }
              | NUMCONST                { std::cout << "Line " << $1->linenum << " Token: NUMCONST Value: " << $1->numConst << "  Input: " << $1->tokenstr << std::endl; }
              | CHARCONST               {
                    if (strutil::str_len($1->tokenstr) > 3) {
                        std::cout << "WARNING(" << $1->linenum << "): character is " << $1->tokenstr.length() - 2 << " characters long and not a single character: '" << $1->tokenstr << "'.  The first char will be used.\n";
                    }
                    std::cout << "Line " << $1->linenum << " Token: CHARCONST Value: '" << $1->charConst << "'  Input: " << $1->tokenstr << std::endl; 
                  }
              | STRINGCONST             { std::cout << "Line " << $1->linenum << " Token: STRINGCONST Value: \"" << $1->stringConst << "\"  Len: " << $1->stringConst.length() << "  Input: " << $1->tokenstr << std::endl; }
              | BOOLCONST               { printf("Line %i Token: BOOLCONST Value: %d  Input: %s\n", $1->linenum, $1->boolConst, $1->tokenstr.c_str()); }
              | TOKEN                   {
                    std::cout << "Line " << $1->linenum << " Token: ";
                    if ($1->tokenstr == "<-") {
                        std::cout << "ASGN\n";
                    } else if ($1->tokenstr == "==") {
                        std::cout << "EQ\n";
                    } else if ($1->tokenstr == "+=") {
                        std::cout << "ADDASS\n";
                    } else if ($1->tokenstr == "++") {
                        std::cout << "INC\n";
                    } else if ($1->tokenstr == "--") {
                        std::cout << "DEC\n";
                    } else if ($1->tokenstr == ">=") {
                        std::cout << "GEQ\n";
                    } else if ($1->tokenstr == "<=") {
                        std::cout << "LEQ\n";
                    } else if ($1->tokenstr == "!=") {
                        std::cout << "NEQ\n";
                    } else {
                        std::cout << $1->tokenstr << std::endl;
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

    // init variables a through z
    for (int i=0; i<26; i++) vars[i] = 0.0;

    // do the parsing
    numErrors = 0;
    yyparse();

    return 0;
}
