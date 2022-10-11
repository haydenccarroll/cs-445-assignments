/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_C_TAB_H_INCLUDED
# define YY_YY_C_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    NUMCONST = 259,
    CHARCONST = 260,
    STRINGCONST = 261,
    BOOLCONST = 262,
    BOOL = 263,
    CHAR = 264,
    INT = 265,
    IF = 266,
    THEN = 267,
    ELSE = 268,
    STATIC = 269,
    WHILE = 270,
    DO = 271,
    FOR = 272,
    TO = 273,
    BY = 274,
    RETURN = 275,
    BREAK = 276,
    OR = 277,
    AND = 278,
    NOT = 279,
    SEMICOLON = 280,
    COMMA = 281,
    COLON = 282,
    LBRACK = 283,
    RBRACK = 284,
    LPAREN = 285,
    RPAREN = 286,
    LCURL = 287,
    RCURL = 288,
    INC = 289,
    DEC = 290,
    ASS = 291,
    ADDASS = 292,
    SUBASS = 293,
    MULASS = 294,
    DIVASS = 295,
    PERCENT = 296,
    LT = 297,
    LEQ = 298,
    GT = 299,
    GEQ = 300,
    EQ = 301,
    NEQ = 302,
    PLUS = 303,
    DASH = 304,
    SLASH = 305,
    ASTERISK = 306,
    QUESTION = 307
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 22 "c-.y"

    struct TokenData* tokenData;

#line 114 "c-.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_C_TAB_H_INCLUDED  */
