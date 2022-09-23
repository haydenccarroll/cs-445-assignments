/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_C_TAB_H_INCLUDED
# define YY_YY_C_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    WHILE = 258,                   /* WHILE  */
    IF = 259,                      /* IF  */
    FOR = 260,                     /* FOR  */
    TO = 261,                      /* TO  */
    RETURN = 262,                  /* RETURN  */
    BREAK = 263,                   /* BREAK  */
    BY = 264,                      /* BY  */
    DO = 265,                      /* DO  */
    NOT = 266,                     /* NOT  */
    AND = 267,                     /* AND  */
    OR = 268,                      /* OR  */
    ADD = 269,                     /* ADD  */
    DASH = 270,                    /* DASH  */
    RAND = 271,                    /* RAND  */
    ASTERISK = 272,                /* ASTERISK  */
    DIV = 273,                     /* DIV  */
    MOD = 274,                     /* MOD  */
    ASGN = 275,                    /* ASGN  */
    ADDASGN = 276,                 /* ADDASGN  */
    SUBASGN = 277,                 /* SUBASGN  */
    MULASGN = 278,                 /* MULASGN  */
    DIVASGN = 279,                 /* DIVASGN  */
    THEN = 280,                    /* THEN  */
    ELSE = 281,                    /* ELSE  */
    BGN = 282,                     /* BGN  */
    END = 283,                     /* END  */
    RPAREN = 284,                  /* RPAREN  */
    LPAREN = 285,                  /* LPAREN  */
    RBRACK = 286,                  /* RBRACK  */
    LBRACK = 287,                  /* LBRACK  */
    STATIC = 288,                  /* STATIC  */
    SEMI = 289,                    /* SEMI  */
    LT = 290,                      /* LT  */
    LEQ = 291,                     /* LEQ  */
    GT = 292,                      /* GT  */
    GEQ = 293,                     /* GEQ  */
    EQ = 294,                      /* EQ  */
    NEQ = 295,                     /* NEQ  */
    INC = 296,                     /* INC  */
    DEC = 297,                     /* DEC  */
    COL = 298,                     /* COL  */
    COM = 299,                     /* COM  */
    INT = 300,                     /* INT  */
    BOOL = 301,                    /* BOOL  */
    CHAR = 302,                    /* CHAR  */
    ID = 303,                      /* ID  */
    NUMCONST = 304,                /* NUMCONST  */
    CHARCONST = 305,               /* CHARCONST  */
    STRINGCONST = 306,             /* STRINGCONST  */
    BOOLCONST = 307                /* BOOLCONST  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 31 "c-.y"

    AST::Decl::Type type;
    AST::Node *node;
    TokenData *tokenData;
    double value;

#line 123 "c-.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_C_TAB_H_INCLUDED  */
