%{
    #include "scanType.h"
    int lines=0;
%}

%option noyywrap

BOOLCONST true|false
NUMCONST idk
STRINGCONST idk
ID idk

%%
[ \t] ; /* ignore whitespace */
\n    ++lines;
{BOOLCONST} {
    struct TokenData tokenData;
    tokenData.tokenclass = 0;
    tokenData.linenum = 0;
    tokenData.tokenstr = "hello";
    tokenData.cvalue = '\0';
    tokenData.nvalue = 0;
    tokenData.svalue = "hello2";

    printf("FOUND A BOOL HERE");
}


%%
int main(int argc, char *argv[]) {
    if (argc == 1) {
        yyin = fopen(argv[1], "r");
    }

    yylex();
    fclose(yyin);
}
 