%{
    int lines=0;
%}

LINE \n

%%
{LINE} ++lines
[ \t] ; /* ignore whitespace */

%%
int yywrap(){return 1;}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        yyin = fopen(argv[1], "r");
    }

    yylex();
    fclose(yyin);
}
