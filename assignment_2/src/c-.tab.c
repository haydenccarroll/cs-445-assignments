/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "c-.y"

#include "AST/AST.h"
#include "scanType.h"  // TokenData Type
#include "helpers.h"
#include "Options/Options.h"

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


#line 99 "c-.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "c-.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_WHILE = 3,                      /* WHILE  */
  YYSYMBOL_IF = 4,                         /* IF  */
  YYSYMBOL_FOR = 5,                        /* FOR  */
  YYSYMBOL_TO = 6,                         /* TO  */
  YYSYMBOL_RETURN = 7,                     /* RETURN  */
  YYSYMBOL_BREAK = 8,                      /* BREAK  */
  YYSYMBOL_BY = 9,                         /* BY  */
  YYSYMBOL_DO = 10,                        /* DO  */
  YYSYMBOL_NOT = 11,                       /* NOT  */
  YYSYMBOL_AND = 12,                       /* AND  */
  YYSYMBOL_OR = 13,                        /* OR  */
  YYSYMBOL_ADD = 14,                       /* ADD  */
  YYSYMBOL_DASH = 15,                      /* DASH  */
  YYSYMBOL_RAND = 16,                      /* RAND  */
  YYSYMBOL_ASTERISK = 17,                  /* ASTERISK  */
  YYSYMBOL_DIV = 18,                       /* DIV  */
  YYSYMBOL_MOD = 19,                       /* MOD  */
  YYSYMBOL_ASGN = 20,                      /* ASGN  */
  YYSYMBOL_ADDASGN = 21,                   /* ADDASGN  */
  YYSYMBOL_SUBASGN = 22,                   /* SUBASGN  */
  YYSYMBOL_MULASGN = 23,                   /* MULASGN  */
  YYSYMBOL_DIVASGN = 24,                   /* DIVASGN  */
  YYSYMBOL_THEN = 25,                      /* THEN  */
  YYSYMBOL_ELSE = 26,                      /* ELSE  */
  YYSYMBOL_BGN = 27,                       /* BGN  */
  YYSYMBOL_END = 28,                       /* END  */
  YYSYMBOL_RPAREN = 29,                    /* RPAREN  */
  YYSYMBOL_LPAREN = 30,                    /* LPAREN  */
  YYSYMBOL_RBRACK = 31,                    /* RBRACK  */
  YYSYMBOL_LBRACK = 32,                    /* LBRACK  */
  YYSYMBOL_STATIC = 33,                    /* STATIC  */
  YYSYMBOL_SEMI = 34,                      /* SEMI  */
  YYSYMBOL_LT = 35,                        /* LT  */
  YYSYMBOL_LEQ = 36,                       /* LEQ  */
  YYSYMBOL_GT = 37,                        /* GT  */
  YYSYMBOL_GEQ = 38,                       /* GEQ  */
  YYSYMBOL_EQ = 39,                        /* EQ  */
  YYSYMBOL_NEQ = 40,                       /* NEQ  */
  YYSYMBOL_INC = 41,                       /* INC  */
  YYSYMBOL_DEC = 42,                       /* DEC  */
  YYSYMBOL_COL = 43,                       /* COL  */
  YYSYMBOL_COM = 44,                       /* COM  */
  YYSYMBOL_INT = 45,                       /* INT  */
  YYSYMBOL_BOOL = 46,                      /* BOOL  */
  YYSYMBOL_CHAR = 47,                      /* CHAR  */
  YYSYMBOL_ID = 48,                        /* ID  */
  YYSYMBOL_NUMCONST = 49,                  /* NUMCONST  */
  YYSYMBOL_CHARCONST = 50,                 /* CHARCONST  */
  YYSYMBOL_STRINGCONST = 51,               /* STRINGCONST  */
  YYSYMBOL_BOOLCONST = 52,                 /* BOOLCONST  */
  YYSYMBOL_YYACCEPT = 53,                  /* $accept  */
  YYSYMBOL_program = 54,                   /* program  */
  YYSYMBOL_declList = 55,                  /* declList  */
  YYSYMBOL_decl = 56,                      /* decl  */
  YYSYMBOL_varDecl = 57,                   /* varDecl  */
  YYSYMBOL_scopedVarDecl = 58,             /* scopedVarDecl  */
  YYSYMBOL_varDeclList = 59,               /* varDeclList  */
  YYSYMBOL_varDeclInit = 60,               /* varDeclInit  */
  YYSYMBOL_varDeclId = 61,                 /* varDeclId  */
  YYSYMBOL_typeSpec = 62,                  /* typeSpec  */
  YYSYMBOL_funDecl = 63,                   /* funDecl  */
  YYSYMBOL_parms = 64,                     /* parms  */
  YYSYMBOL_parmList = 65,                  /* parmList  */
  YYSYMBOL_parmTypeList = 66,              /* parmTypeList  */
  YYSYMBOL_parmIdList = 67,                /* parmIdList  */
  YYSYMBOL_parmId = 68,                    /* parmId  */
  YYSYMBOL_stmt = 69,                      /* stmt  */
  YYSYMBOL_expStmt = 70,                   /* expStmt  */
  YYSYMBOL_compoundStmt = 71,              /* compoundStmt  */
  YYSYMBOL_localDecls = 72,                /* localDecls  */
  YYSYMBOL_stmtList = 73,                  /* stmtList  */
  YYSYMBOL_closedStmt = 74,                /* closedStmt  */
  YYSYMBOL_openStmt = 75,                  /* openStmt  */
  YYSYMBOL_selectStmtOpen = 76,            /* selectStmtOpen  */
  YYSYMBOL_selectStmtClosed = 77,          /* selectStmtClosed  */
  YYSYMBOL_iterStmtOpen = 78,              /* iterStmtOpen  */
  YYSYMBOL_iterStmtClosed = 79,            /* iterStmtClosed  */
  YYSYMBOL_iterRange = 80,                 /* iterRange  */
  YYSYMBOL_returnStmt = 81,                /* returnStmt  */
  YYSYMBOL_breakStmt = 82,                 /* breakStmt  */
  YYSYMBOL_exp = 83,                       /* exp  */
  YYSYMBOL_assignop = 84,                  /* assignop  */
  YYSYMBOL_simpleExp = 85,                 /* simpleExp  */
  YYSYMBOL_andExp = 86,                    /* andExp  */
  YYSYMBOL_unaryRelExp = 87,               /* unaryRelExp  */
  YYSYMBOL_relExp = 88,                    /* relExp  */
  YYSYMBOL_relop = 89,                     /* relop  */
  YYSYMBOL_sumExp = 90,                    /* sumExp  */
  YYSYMBOL_sumop = 91,                     /* sumop  */
  YYSYMBOL_mulExp = 92,                    /* mulExp  */
  YYSYMBOL_mulop = 93,                     /* mulop  */
  YYSYMBOL_unaryExp = 94,                  /* unaryExp  */
  YYSYMBOL_unaryop = 95,                   /* unaryop  */
  YYSYMBOL_factor = 96,                    /* factor  */
  YYSYMBOL_mutable = 97,                   /* mutable  */
  YYSYMBOL_immutable = 98,                 /* immutable  */
  YYSYMBOL_call = 99,                      /* call  */
  YYSYMBOL_argList = 100,                  /* argList  */
  YYSYMBOL_constant = 101                  /* constant  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   207

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  110
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  171

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   307


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    59,    59,    66,    71,    77,    81,    87,    95,   102,
     110,   115,   121,   125,   132,   136,   142,   146,   150,   156,
     160,   167,   170,   176,   181,   187,   195,   200,   206,   210,
     216,   220,   226,   230,   236,   243,   246,   258,   261,   272,
     276,   280,   284,   288,   292,   298,   302,   308,   312,   318,
     324,   328,   336,   340,   348,   352,   358,   362,   368,   374,
     380,   384,   388,   394,   398,   402,   406,   410,   416,   420,
     426,   430,   436,   440,   446,   452,   458,   462,   466,   470,
     474,   478,   484,   490,   496,   500,   506,   512,   518,   522,
     526,   532,   538,   544,   548,   552,   558,   562,   568,   572,
     578,   582,   586,   592,   596,   602,   607,   613,   617,   621,
     625
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "WHILE", "IF", "FOR",
  "TO", "RETURN", "BREAK", "BY", "DO", "NOT", "AND", "OR", "ADD", "DASH",
  "RAND", "ASTERISK", "DIV", "MOD", "ASGN", "ADDASGN", "SUBASGN",
  "MULASGN", "DIVASGN", "THEN", "ELSE", "BGN", "END", "RPAREN", "LPAREN",
  "RBRACK", "LBRACK", "STATIC", "SEMI", "LT", "LEQ", "GT", "GEQ", "EQ",
  "NEQ", "INC", "DEC", "COL", "COM", "INT", "BOOL", "CHAR", "ID",
  "NUMCONST", "CHARCONST", "STRINGCONST", "BOOLCONST", "$accept",
  "program", "declList", "decl", "varDecl", "scopedVarDecl", "varDeclList",
  "varDeclInit", "varDeclId", "typeSpec", "funDecl", "parms", "parmList",
  "parmTypeList", "parmIdList", "parmId", "stmt", "expStmt",
  "compoundStmt", "localDecls", "stmtList", "closedStmt", "openStmt",
  "selectStmtOpen", "selectStmtClosed", "iterStmtOpen", "iterStmtClosed",
  "iterRange", "returnStmt", "breakStmt", "exp", "assignop", "simpleExp",
  "andExp", "unaryRelExp", "relExp", "relop", "sumExp", "sumop", "mulExp",
  "mulop", "unaryExp", "unaryop", "factor", "mutable", "immutable", "call",
  "argList", "constant", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-133)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      52,  -133,  -133,  -133,   -28,    38,    52,  -133,  -133,    23,
    -133,    61,  -133,  -133,    94,   -23,  -133,    31,    36,    58,
      75,  -133,    61,    71,  -133,    73,   149,    93,    87,  -133,
     107,    61,   109,   104,   114,  -133,   149,  -133,  -133,  -133,
     149,   115,  -133,  -133,  -133,  -133,   126,   139,  -133,  -133,
      13,    99,  -133,   141,  -133,  -133,  -133,  -133,  -133,   122,
      36,  -133,  -133,  -133,   107,  -133,  -133,   132,   126,    69,
      53,   149,   149,   149,  -133,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,   141,   141,  -133,  -133,  -133,   141,  -133,  -133,
    -133,     0,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
    -133,   149,  -133,  -133,   -21,   123,   139,  -133,    41,    99,
    -133,    61,  -133,    73,     9,  -133,  -133,   149,  -133,    73,
      10,   149,   149,   120,   133,   128,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,   135,
    -133,    29,  -133,     5,    -3,   150,  -133,   138,  -133,  -133,
    -133,   125,   125,   149,  -133,  -133,  -133,  -133,   152,   170,
      66,   125,   125,   149,  -133,  -133,  -133,  -133,   106,   149,
     126
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    18,    16,    17,     0,     0,     2,     4,     5,     0,
       6,    21,     1,     3,    14,     0,    11,    12,     0,     0,
      22,    24,    21,     0,     7,     0,     0,    28,    25,    27,
       0,     0,     0,     0,    14,    10,     0,    93,    95,    94,
       0,    98,   107,   108,   109,   110,    13,    69,    71,    73,
      75,    83,    87,     0,    92,    96,    97,   101,   102,     0,
       0,    35,    20,    23,     0,    15,    72,     0,    62,    96,
       0,     0,     0,     0,    84,    85,    76,    77,    78,    79,
      80,    81,     0,     0,    88,    89,    90,     0,    91,    29,
      26,    37,    19,   100,    63,    64,    65,    67,    66,    60,
      61,     0,   104,   106,     0,     0,    68,    70,    74,    82,
      86,     0,    36,     0,     0,    59,   103,     0,    99,     0,
       0,     0,     0,     0,     0,     0,    34,    33,    38,    41,
      42,    30,    31,    45,    39,    46,    40,    43,    44,     0,
     105,     0,     9,     0,     0,     0,    56,     0,    58,    32,
       8,     0,     0,     0,    57,    52,    50,    47,    30,     0,
       0,     0,     0,     0,    49,    48,    53,    51,    54,     0,
      55
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -133,  -133,  -133,   180,  -133,  -133,   -33,   162,  -133,     3,
    -133,   166,  -133,   163,  -133,   136,    43,  -133,   -24,  -133,
    -133,   -85,  -132,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
     -36,  -133,   -26,   130,   -31,  -133,  -133,   121,  -133,   124,
    -133,   -46,  -133,  -133,   -39,  -133,  -133,  -133,  -133
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,     6,     7,     8,   112,    15,    16,    17,    18,
      10,    19,    20,    21,    28,    29,   128,   129,   130,    91,
     114,   131,   132,   133,   134,   135,   136,   159,   137,   138,
     139,   101,    68,    47,    48,    49,    82,    50,    83,    51,
      87,    52,    53,    54,    55,    56,    57,   104,    58
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      46,    69,    11,     9,    67,    66,    62,    88,   116,     9,
      72,    24,   121,   122,   123,   151,   124,   125,    72,   156,
      36,    25,   152,   117,    37,    38,    39,    74,    75,   165,
     167,    69,    69,   111,   103,   105,    61,   126,    12,    40,
      92,   110,   107,   127,   142,     1,     2,     3,    76,    77,
      78,    79,    80,    81,    25,    74,    75,    41,    42,    43,
      44,    45,    69,   150,    36,   115,   155,   158,    37,    38,
      39,    14,   163,    25,    26,    69,   164,   166,    69,    72,
     120,   140,   102,    40,    27,    69,   141,    30,   147,    94,
      95,    96,    97,    98,   113,   143,   144,     1,     2,     3,
       4,    41,    42,    43,    44,    45,     1,     2,     3,    31,
      99,   100,    69,    69,   119,   169,    84,    85,    86,    72,
      33,    34,    69,    69,    22,    59,    23,   160,   121,   122,
     123,    60,   124,   125,    61,    65,    36,   168,    64,    72,
      37,    38,    39,   170,    36,    70,    23,    71,    37,    38,
      39,    73,    61,    89,   118,    40,    37,    38,    39,   127,
      36,    93,   148,    40,    37,    38,    39,   146,   145,   149,
     153,    40,   154,    41,    42,    43,    44,    45,   161,    40,
     162,    41,    42,    43,    44,    45,    13,    35,    32,    41,
      42,    43,    44,    45,    63,   157,    90,    41,    42,    43,
      44,    45,   106,   108,     0,     0,     0,   109
};

static const yytype_int16 yycheck[] =
{
      26,    40,    30,     0,    40,    36,    30,    53,    29,     6,
      13,    34,     3,     4,     5,    10,     7,     8,    13,   151,
      11,    44,    25,    44,    15,    16,    17,    14,    15,   161,
     162,    70,    71,    33,    70,    71,    27,    28,     0,    30,
      64,    87,    73,    34,    34,    45,    46,    47,    35,    36,
      37,    38,    39,    40,    44,    14,    15,    48,    49,    50,
      51,    52,   101,    34,    11,   101,   151,   152,    15,    16,
      17,    48,     6,    44,    43,   114,   161,   162,   117,    13,
     113,   117,    29,    30,    48,   124,   119,    29,   124,    20,
      21,    22,    23,    24,    91,   121,   122,    45,    46,    47,
      48,    48,    49,    50,    51,    52,    45,    46,    47,    34,
      41,    42,   151,   152,   111,     9,    17,    18,    19,    13,
      49,    48,   161,   162,    30,    32,    32,   153,     3,     4,
       5,    44,     7,     8,    27,    31,    11,   163,    29,    13,
      15,    16,    17,   169,    11,    30,    32,    32,    15,    16,
      17,    12,    27,    31,    31,    30,    15,    16,    17,    34,
      11,    29,    34,    30,    15,    16,    17,    34,    48,    34,
      20,    30,    34,    48,    49,    50,    51,    52,    26,    30,
      10,    48,    49,    50,    51,    52,     6,    25,    22,    48,
      49,    50,    51,    52,    31,   152,    60,    48,    49,    50,
      51,    52,    72,    82,    -1,    -1,    -1,    83
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    45,    46,    47,    48,    54,    55,    56,    57,    62,
      63,    30,     0,    56,    48,    59,    60,    61,    62,    64,
      65,    66,    30,    32,    34,    44,    43,    48,    67,    68,
      29,    34,    64,    49,    48,    60,    11,    15,    16,    17,
      30,    48,    49,    50,    51,    52,    85,    86,    87,    88,
      90,    92,    94,    95,    96,    97,    98,    99,   101,    32,
      44,    27,    71,    66,    29,    31,    87,    83,    85,    97,
      30,    32,    13,    12,    14,    15,    35,    36,    37,    38,
      39,    40,    89,    91,    17,    18,    19,    93,    94,    31,
      68,    72,    71,    29,    20,    21,    22,    23,    24,    41,
      42,    84,    29,    83,   100,    83,    86,    87,    90,    92,
      94,    33,    58,    62,    73,    83,    29,    44,    31,    62,
      59,     3,     4,     5,     7,     8,    28,    34,    69,    70,
      71,    74,    75,    76,    77,    78,    79,    81,    82,    83,
      83,    59,    34,    85,    85,    48,    34,    83,    34,    34,
      34,    10,    25,    20,    34,    74,    75,    69,    74,    80,
      85,    26,    10,     6,    74,    75,    74,    75,    85,     9,
      85
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    53,    54,    55,    55,    56,    56,    57,    58,    58,
      59,    59,    60,    60,    61,    61,    62,    62,    62,    63,
      63,    64,    64,    65,    65,    66,    67,    67,    68,    68,
      69,    69,    70,    70,    71,    72,    72,    73,    73,    74,
      74,    74,    74,    74,    74,    75,    75,    76,    76,    77,
      78,    78,    79,    79,    80,    80,    81,    81,    82,    83,
      83,    83,    83,    84,    84,    84,    84,    84,    85,    85,
      86,    86,    87,    87,    88,    88,    89,    89,    89,    89,
      89,    89,    90,    90,    91,    91,    92,    92,    93,    93,
      93,    94,    94,    95,    95,    95,    96,    96,    97,    97,
      98,    98,    98,    99,    99,   100,   100,   101,   101,   101,
     101
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     4,     3,
       3,     1,     1,     3,     1,     4,     1,     1,     1,     6,
       5,     0,     1,     3,     1,     2,     3,     1,     1,     3,
       1,     1,     2,     1,     4,     0,     2,     0,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     6,     6,
       4,     6,     4,     6,     3,     5,     2,     3,     2,     3,
       2,     2,     1,     1,     1,     1,     1,     1,     3,     1,
       3,     1,     2,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     3,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     4,
       3,     1,     1,     4,     3,     3,     1,     1,     1,     1,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: declList  */
#line 60 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
                        tree_root = (yyval.node);
                    }
#line 1327 "c-.tab.c"
    break;

  case 3: /* declList: declList decl  */
#line 67 "c-.y"
                    {
                        (yyval.node) = (yyvsp[-1].node);
                        (yyval.node)->addSibling((yyvsp[0].node));
                    }
#line 1336 "c-.tab.c"
    break;

  case 4: /* declList: decl  */
#line 72 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 1344 "c-.tab.c"
    break;

  case 5: /* decl: varDecl  */
#line 78 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
					}
#line 1352 "c-.tab.c"
    break;

  case 6: /* decl: funDecl  */
#line 82 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
					}
#line 1360 "c-.tab.c"
    break;

  case 7: /* varDecl: typeSpec varDeclList SEMI  */
#line 88 "c-.y"
                    {
                        AST::Decl::Var *var = (AST::Decl::Var *)(yyvsp[-1].node);
                        var->setType((yyvsp[-2].type));
                        (yyval.node) = var;
					}
#line 1370 "c-.tab.c"
    break;

  case 8: /* scopedVarDecl: STATIC typeSpec varDeclList SEMI  */
#line 96 "c-.y"
                    {
                        AST::Decl::Var *var = (AST::Decl::Var *)(yyvsp[-1].node);
                        var->setType((yyvsp[-2].type));
                        var->setStatic();
                        (yyval.node) = var;
					}
#line 1381 "c-.tab.c"
    break;

  case 9: /* scopedVarDecl: typeSpec varDeclList SEMI  */
#line 103 "c-.y"
                    {
                        AST::Decl::Var *var = (AST::Decl::Var *)(yyvsp[-1].node);
                        var->setType((yyvsp[-2].type));
                        (yyval.node) = var;
					}
#line 1391 "c-.tab.c"
    break;

  case 10: /* varDeclList: varDeclList COM varDeclInit  */
#line 111 "c-.y"
                    {
                        (yyval.node) = (yyvsp[-2].node);
                        (yyval.node)->addSibling((yyvsp[0].node));
                    }
#line 1400 "c-.tab.c"
    break;

  case 11: /* varDeclList: varDeclInit  */
#line 116 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
					}
#line 1408 "c-.tab.c"
    break;

  case 12: /* varDeclInit: varDeclId  */
#line 122 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
					}
#line 1416 "c-.tab.c"
    break;

  case 13: /* varDeclInit: varDeclId COL simpleExp  */
#line 126 "c-.y"
                    {
                        (yyval.node) = (yyvsp[-2].node);
                        (yyval.node)->addChild((yyvsp[0].node));
                    }
#line 1425 "c-.tab.c"
    break;

  case 14: /* varDeclId: ID  */
#line 133 "c-.y"
                    {
                        (yyval.node) = new AST::Decl::Var((yyvsp[0].tokenData)->linenum, (yyvsp[0].tokenData)->tokenstr, false);
                    }
#line 1433 "c-.tab.c"
    break;

  case 15: /* varDeclId: ID LBRACK NUMCONST RBRACK  */
#line 137 "c-.y"
                    {
                        (yyval.node) = new AST::Decl::Var((yyvsp[-3].tokenData)->linenum, (yyvsp[-3].tokenData)->tokenstr, true);
                    }
#line 1441 "c-.tab.c"
    break;

  case 16: /* typeSpec: BOOL  */
#line 143 "c-.y"
                    {
                        (yyval.type) = AST::Decl::Type::Bool;
                    }
#line 1449 "c-.tab.c"
    break;

  case 17: /* typeSpec: CHAR  */
#line 147 "c-.y"
                    {
                        (yyval.type) = AST::Decl::Type::Char;
                    }
#line 1457 "c-.tab.c"
    break;

  case 18: /* typeSpec: INT  */
#line 151 "c-.y"
                    {
                        (yyval.type) = AST::Decl::Type::Int;
                    }
#line 1465 "c-.tab.c"
    break;

  case 19: /* funDecl: typeSpec ID LPAREN parms RPAREN compoundStmt  */
#line 157 "c-.y"
                    {
                        (yyval.node) = new AST::Decl::Func((yyvsp[-4].tokenData)->linenum, (yyvsp[-5].type), (yyvsp[-4].tokenData)->tokenstr, (yyvsp[-2].node), (yyvsp[0].node));
                    }
#line 1473 "c-.tab.c"
    break;

  case 20: /* funDecl: ID LPAREN parms RPAREN compoundStmt  */
#line 161 "c-.y"
                    {
                        (yyval.node) = new AST::Decl::Func((yyvsp[-4].tokenData)->linenum, (yyvsp[-4].tokenData)->tokenstr, (yyvsp[-2].node), (yyvsp[0].node));
                    }
#line 1481 "c-.tab.c"
    break;

  case 21: /* parms: %empty  */
#line 167 "c-.y"
                    {
                        (yyval.node) = nullptr;
					}
#line 1489 "c-.tab.c"
    break;

  case 22: /* parms: parmList  */
#line 171 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
					}
#line 1497 "c-.tab.c"
    break;

  case 23: /* parmList: parmList SEMI parmTypeList  */
#line 177 "c-.y"
                    {
                        (yyval.node) = (yyvsp[-2].node);
                        (yyval.node)->addSibling((yyvsp[0].node));
                    }
#line 1506 "c-.tab.c"
    break;

  case 24: /* parmList: parmTypeList  */
#line 182 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
					}
#line 1514 "c-.tab.c"
    break;

  case 25: /* parmTypeList: typeSpec parmIdList  */
#line 188 "c-.y"
                    {
                        AST::Decl::Parm *parms = (AST::Decl::Parm *)(yyvsp[0].node);
                        parms->setType((yyvsp[-1].type));
                        (yyval.node) = parms;
					}
#line 1524 "c-.tab.c"
    break;

  case 26: /* parmIdList: parmIdList COM parmId  */
#line 196 "c-.y"
                    {
                        (yyval.node) = (yyvsp[-2].node);
                        (yyval.node)->addSibling((yyvsp[0].node));
                    }
#line 1533 "c-.tab.c"
    break;

  case 27: /* parmIdList: parmId  */
#line 201 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
					}
#line 1541 "c-.tab.c"
    break;

  case 28: /* parmId: ID  */
#line 207 "c-.y"
                    {
                        (yyval.node) = new AST::Decl::Parm((yyvsp[0].tokenData)->linenum, (yyvsp[0].tokenData)->tokenstr, false);
					}
#line 1549 "c-.tab.c"
    break;

  case 29: /* parmId: ID LBRACK RBRACK  */
#line 211 "c-.y"
                    {
                        (yyval.node) = new AST::Decl::Parm((yyvsp[-2].tokenData)->linenum, (yyvsp[-2].tokenData)->tokenstr, true);
					}
#line 1557 "c-.tab.c"
    break;

  case 30: /* stmt: closedStmt  */
#line 217 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
					}
#line 1565 "c-.tab.c"
    break;

  case 31: /* stmt: openStmt  */
#line 221 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
					}
#line 1573 "c-.tab.c"
    break;

  case 32: /* expStmt: exp SEMI  */
#line 227 "c-.y"
                    {
                        (yyval.node) = (yyvsp[-1].node);
					}
#line 1581 "c-.tab.c"
    break;

  case 33: /* expStmt: SEMI  */
#line 231 "c-.y"
                    {
                        (yyval.node) = nullptr;
					}
#line 1589 "c-.tab.c"
    break;

  case 34: /* compoundStmt: BGN localDecls stmtList END  */
#line 237 "c-.y"
                    {
                        (yyval.node) = new AST::Stmt::Compound((yyvsp[-3].tokenData)->linenum, (yyvsp[-2].node), (yyvsp[-1].node));
                    }
#line 1597 "c-.tab.c"
    break;

  case 35: /* localDecls: %empty  */
#line 243 "c-.y"
                    {
                        (yyval.node) = nullptr;
					}
#line 1605 "c-.tab.c"
    break;

  case 36: /* localDecls: localDecls scopedVarDecl  */
#line 247 "c-.y"
                    {
                        if ((yyvsp[-1].node) == nullptr) {
                            (yyval.node) = (yyvsp[0].node);
                        } else {
                            (yyval.node) = (yyvsp[-1].node);
                            (yyval.node)->addSibling((yyvsp[0].node));
                        }
                    }
#line 1618 "c-.tab.c"
    break;

  case 37: /* stmtList: %empty  */
#line 258 "c-.y"
                    {
                        (yyval.node) = nullptr;
					}
#line 1626 "c-.tab.c"
    break;

  case 38: /* stmtList: stmtList stmt  */
#line 262 "c-.y"
                    {
                        if ((yyvsp[-1].node) == nullptr) {
                            (yyval.node) = (yyvsp[0].node);
                        } else {
                            (yyval.node) = (yyvsp[-1].node);
                            (yyval.node)->addSibling((yyvsp[0].node));
                        }
                    }
#line 1639 "c-.tab.c"
    break;

  case 39: /* closedStmt: selectStmtClosed  */
#line 273 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
					}
#line 1647 "c-.tab.c"
    break;

  case 40: /* closedStmt: iterStmtClosed  */
#line 277 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
					}
#line 1655 "c-.tab.c"
    break;

  case 41: /* closedStmt: expStmt  */
#line 281 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
					}
#line 1663 "c-.tab.c"
    break;

  case 42: /* closedStmt: compoundStmt  */
#line 285 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
					}
#line 1671 "c-.tab.c"
    break;

  case 43: /* closedStmt: returnStmt  */
#line 289 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
					}
#line 1679 "c-.tab.c"
    break;

  case 44: /* closedStmt: breakStmt  */
#line 293 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
					}
#line 1687 "c-.tab.c"
    break;

  case 45: /* openStmt: selectStmtOpen  */
#line 299 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
					}
#line 1695 "c-.tab.c"
    break;

  case 46: /* openStmt: iterStmtOpen  */
#line 303 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
					}
#line 1703 "c-.tab.c"
    break;

  case 47: /* selectStmtOpen: IF simpleExp THEN stmt  */
#line 309 "c-.y"
                    {
                        (yyval.node) = new AST::Stmt::Select((yyvsp[-3].tokenData)->linenum, (yyvsp[-2].node), (yyvsp[0].node));
                    }
#line 1711 "c-.tab.c"
    break;

  case 48: /* selectStmtOpen: IF simpleExp THEN closedStmt ELSE openStmt  */
#line 313 "c-.y"
                    {
                        (yyval.node) = new AST::Stmt::Select((yyvsp[-5].tokenData)->linenum, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
                    }
#line 1719 "c-.tab.c"
    break;

  case 49: /* selectStmtClosed: IF simpleExp THEN closedStmt ELSE closedStmt  */
#line 319 "c-.y"
                    {
                        (yyval.node) = new AST::Stmt::Select((yyvsp[-5].tokenData)->linenum, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
                    }
#line 1727 "c-.tab.c"
    break;

  case 50: /* iterStmtOpen: WHILE simpleExp DO openStmt  */
#line 325 "c-.y"
                    {
                        (yyval.node) = new AST::Stmt::While((yyvsp[-3].tokenData)->linenum, (yyvsp[-2].node), (yyvsp[0].node));
                    }
#line 1735 "c-.tab.c"
    break;

  case 51: /* iterStmtOpen: FOR ID ASGN iterRange DO openStmt  */
#line 329 "c-.y"
                    {
                        AST::Decl::Var *iterator = new AST::Decl::Var((yyvsp[-5].tokenData)->linenum, (yyvsp[-4].tokenData)->tokenstr, false);
                        iterator->setType(AST::Decl::Type::Int);
                        (yyval.node) = new AST::Stmt::For((yyvsp[-5].tokenData)->linenum, iterator, (yyvsp[-2].node), (yyvsp[0].node));
                    }
#line 1745 "c-.tab.c"
    break;

  case 52: /* iterStmtClosed: WHILE simpleExp DO closedStmt  */
#line 337 "c-.y"
                    {
                        (yyval.node) = new AST::Stmt::While((yyvsp[-3].tokenData)->linenum, (yyvsp[-2].node), (yyvsp[0].node));
                    }
#line 1753 "c-.tab.c"
    break;

  case 53: /* iterStmtClosed: FOR ID ASGN iterRange DO closedStmt  */
#line 341 "c-.y"
                    {
                        AST::Decl::Var *iterator = new AST::Decl::Var((yyvsp[-5].tokenData)->linenum, (yyvsp[-4].tokenData)->tokenstr, false);
                        iterator->setType(AST::Decl::Type::Int);
                        (yyval.node) = new AST::Stmt::For((yyvsp[-5].tokenData)->linenum, iterator, (yyvsp[-2].node), (yyvsp[0].node));
                    }
#line 1763 "c-.tab.c"
    break;

  case 54: /* iterRange: simpleExp TO simpleExp  */
#line 349 "c-.y"
                    {
                        (yyval.node) = new AST::Exp::Range((yyvsp[-2].node)->lineNumber(), (yyvsp[-2].node), (yyvsp[0].node));
                    }
#line 1771 "c-.tab.c"
    break;

  case 55: /* iterRange: simpleExp TO simpleExp BY simpleExp  */
#line 353 "c-.y"
                    {
                        (yyval.node) = new AST::Exp::Range((yyvsp[-4].node)->lineNumber(), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
                    }
#line 1779 "c-.tab.c"
    break;

  case 56: /* returnStmt: RETURN SEMI  */
#line 359 "c-.y"
                    {
                        (yyval.node) = new AST::Stmt::Return((yyvsp[-1].tokenData)->linenum, nullptr);
                    }
#line 1787 "c-.tab.c"
    break;

  case 57: /* returnStmt: RETURN exp SEMI  */
#line 363 "c-.y"
                    {
                        (yyval.node) = new AST::Stmt::Return((yyvsp[-2].tokenData)->linenum, (yyvsp[-1].node));
                    }
#line 1795 "c-.tab.c"
    break;

  case 58: /* breakStmt: BREAK SEMI  */
#line 369 "c-.y"
                    {
                        (yyval.node) = new AST::Stmt::Break((yyvsp[-1].tokenData)->linenum);
                    }
#line 1803 "c-.tab.c"
    break;

  case 59: /* exp: mutable assignop exp  */
#line 375 "c-.y"
                    {
                        AST::Op::Asgn *op = (AST::Op::Asgn *)(yyvsp[-1].node);
                        op->addChildren((yyvsp[-2].node), (yyvsp[0].node));
                        (yyval.node) = op;
                    }
#line 1813 "c-.tab.c"
    break;

  case 60: /* exp: mutable INC  */
#line 381 "c-.y"
                    {
                        (yyval.node) = new AST::Op::UnaryAsgn((yyvsp[-1].node)->lineNumber(), AST::Op::UnaryAsgn::Type::Inc, (yyvsp[-1].node));
                    }
#line 1821 "c-.tab.c"
    break;

  case 61: /* exp: mutable DEC  */
#line 385 "c-.y"
                    {
                        (yyval.node) = new AST::Op::UnaryAsgn((yyvsp[-1].node)->lineNumber(), AST::Op::UnaryAsgn::Type::Dec, (yyvsp[-1].node));
                    }
#line 1829 "c-.tab.c"
    break;

  case 62: /* exp: simpleExp  */
#line 389 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
					}
#line 1837 "c-.tab.c"
    break;

  case 63: /* assignop: ASGN  */
#line 395 "c-.y"
                    {
                        (yyval.node) = new AST::Op::Asgn((yyvsp[0].tokenData)->linenum, AST::Op::Asgn::Type::Asgn);
					}
#line 1845 "c-.tab.c"
    break;

  case 64: /* assignop: ADDASGN  */
#line 399 "c-.y"
                    {
                        (yyval.node) = new AST::Op::Asgn((yyvsp[0].tokenData)->linenum, AST::Op::Asgn::Type::AddAsgn);
					}
#line 1853 "c-.tab.c"
    break;

  case 65: /* assignop: SUBASGN  */
#line 403 "c-.y"
                    {
                        (yyval.node) = new AST::Op::Asgn((yyvsp[0].tokenData)->linenum, AST::Op::Asgn::Type::SubAsgn);
					}
#line 1861 "c-.tab.c"
    break;

  case 66: /* assignop: DIVASGN  */
#line 407 "c-.y"
                    {
                        (yyval.node) = new AST::Op::Asgn((yyvsp[0].tokenData)->linenum, AST::Op::Asgn::Type::DivAsgn);
					}
#line 1869 "c-.tab.c"
    break;

  case 67: /* assignop: MULASGN  */
#line 411 "c-.y"
                    {
                        (yyval.node) = new AST::Op::Asgn((yyvsp[0].tokenData)->linenum, AST::Op::Asgn::Type::MulAsgn);
					}
#line 1877 "c-.tab.c"
    break;

  case 68: /* simpleExp: simpleExp OR andExp  */
#line 417 "c-.y"
                    {
                        (yyval.node) = new AST::Op::Binary((yyvsp[-2].node)->lineNumber(), AST::Op::Binary::Type::Or, (yyvsp[-2].node), (yyvsp[0].node));
                    }
#line 1885 "c-.tab.c"
    break;

  case 69: /* simpleExp: andExp  */
#line 421 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
					}
#line 1893 "c-.tab.c"
    break;

  case 70: /* andExp: andExp AND unaryRelExp  */
#line 427 "c-.y"
                    {
                        (yyval.node) = new AST::Op::Binary((yyvsp[-2].node)->lineNumber(), AST::Op::Binary::Type::And, (yyvsp[-2].node), (yyvsp[0].node));
                    }
#line 1901 "c-.tab.c"
    break;

  case 71: /* andExp: unaryRelExp  */
#line 431 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
					}
#line 1909 "c-.tab.c"
    break;

  case 72: /* unaryRelExp: NOT unaryRelExp  */
#line 437 "c-.y"
                    {
                        (yyval.node) = new AST::Op::Unary((yyvsp[-1].tokenData)->linenum, AST::Op::Unary::Type::Not, (yyvsp[0].node));
                    }
#line 1917 "c-.tab.c"
    break;

  case 73: /* unaryRelExp: relExp  */
#line 441 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
					}
#line 1925 "c-.tab.c"
    break;

  case 74: /* relExp: sumExp relop sumExp  */
#line 447 "c-.y"
                    {
                        AST::Op::Binary *op = (AST::Op::Binary *)(yyvsp[-1].node);
                        op->addChildren((yyvsp[-2].node), (yyvsp[0].node));
                        (yyval.node) = op;
                    }
#line 1935 "c-.tab.c"
    break;

  case 75: /* relExp: sumExp  */
#line 453 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
					}
#line 1943 "c-.tab.c"
    break;

  case 76: /* relop: LT  */
#line 459 "c-.y"
                    {
                        (yyval.node) = new AST::Op::Binary((yyvsp[0].tokenData)->linenum, AST::Op::Binary::Type::LT);
					}
#line 1951 "c-.tab.c"
    break;

  case 77: /* relop: LEQ  */
#line 463 "c-.y"
                    {
                        (yyval.node) = new AST::Op::Binary((yyvsp[0].tokenData)->linenum, AST::Op::Binary::Type::LEQ);
					}
#line 1959 "c-.tab.c"
    break;

  case 78: /* relop: GT  */
#line 467 "c-.y"
                    {
                        (yyval.node) = new AST::Op::Binary((yyvsp[0].tokenData)->linenum, AST::Op::Binary::Type::GT);
					}
#line 1967 "c-.tab.c"
    break;

  case 79: /* relop: GEQ  */
#line 471 "c-.y"
                    {
                        (yyval.node) = new AST::Op::Binary((yyvsp[0].tokenData)->linenum, AST::Op::Binary::Type::GEQ);
					}
#line 1975 "c-.tab.c"
    break;

  case 80: /* relop: EQ  */
#line 475 "c-.y"
                    {
                        (yyval.node) = new AST::Op::Binary((yyvsp[0].tokenData)->linenum, AST::Op::Binary::Type::EQ);
					}
#line 1983 "c-.tab.c"
    break;

  case 81: /* relop: NEQ  */
#line 479 "c-.y"
                    {
                        (yyval.node) = new AST::Op::Binary((yyvsp[0].tokenData)->linenum, AST::Op::Binary::Type::NEQ);
					}
#line 1991 "c-.tab.c"
    break;

  case 82: /* sumExp: sumExp sumop mulExp  */
#line 485 "c-.y"
                    {
                        AST::Op::Binary *op = (AST::Op::Binary *)(yyvsp[-1].node);
                        op->addChildren((yyvsp[-2].node), (yyvsp[0].node));
                        (yyval.node) = op;
					}
#line 2001 "c-.tab.c"
    break;

  case 83: /* sumExp: mulExp  */
#line 491 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
					}
#line 2009 "c-.tab.c"
    break;

  case 84: /* sumop: ADD  */
#line 497 "c-.y"
                    {
                        (yyval.node) = new AST::Op::Binary((yyvsp[0].tokenData)->linenum, AST::Op::Binary::Type::Add);
					}
#line 2017 "c-.tab.c"
    break;

  case 85: /* sumop: DASH  */
#line 501 "c-.y"
                    {
                        (yyval.node) = new AST::Op::Binary((yyvsp[0].tokenData)->linenum, AST::Op::Binary::Type::Subtract);
					}
#line 2025 "c-.tab.c"
    break;

  case 86: /* mulExp: mulExp mulop unaryExp  */
#line 507 "c-.y"
                    {
                        AST::Op::Binary *op = (AST::Op::Binary *)(yyvsp[-1].node);
                        op->addChildren((yyvsp[-2].node), (yyvsp[0].node));
                        (yyval.node) = op;
					}
#line 2035 "c-.tab.c"
    break;

  case 87: /* mulExp: unaryExp  */
#line 513 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
					}
#line 2043 "c-.tab.c"
    break;

  case 88: /* mulop: ASTERISK  */
#line 519 "c-.y"
                    {
                        (yyval.node) = new AST::Op::Binary((yyvsp[0].tokenData)->linenum, AST::Op::Binary::Type::Mul);
					}
#line 2051 "c-.tab.c"
    break;

  case 89: /* mulop: DIV  */
#line 523 "c-.y"
                    {
                        (yyval.node) = new AST::Op::Binary((yyvsp[0].tokenData)->linenum, AST::Op::Binary::Type::Div);
					}
#line 2059 "c-.tab.c"
    break;

  case 90: /* mulop: MOD  */
#line 527 "c-.y"
                    {
                        (yyval.node) = new AST::Op::Binary((yyvsp[0].tokenData)->linenum, AST::Op::Binary::Type::Mod);
					}
#line 2067 "c-.tab.c"
    break;

  case 91: /* unaryExp: unaryop unaryExp  */
#line 533 "c-.y"
                    {
                        AST::Op::Unary *op = (AST::Op::Unary *)(yyvsp[-1].node);
                        op->addExp((yyvsp[0].node));
                        (yyval.node) = op;
					}
#line 2077 "c-.tab.c"
    break;

  case 92: /* unaryExp: factor  */
#line 539 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
					}
#line 2085 "c-.tab.c"
    break;

  case 93: /* unaryop: DASH  */
#line 545 "c-.y"
                    {
                        (yyval.node) = new AST::Op::Unary((yyvsp[0].tokenData)->linenum, AST::Op::Unary::Type::Chsign);
					}
#line 2093 "c-.tab.c"
    break;

  case 94: /* unaryop: ASTERISK  */
#line 549 "c-.y"
                    {
                        (yyval.node) = new AST::Op::Unary((yyvsp[0].tokenData)->linenum, AST::Op::Unary::Type::Sizeof);
					}
#line 2101 "c-.tab.c"
    break;

  case 95: /* unaryop: RAND  */
#line 553 "c-.y"
                    {
                        (yyval.node) = new AST::Op::Unary((yyvsp[0].tokenData)->linenum, AST::Op::Unary::Type::Random);
					}
#line 2109 "c-.tab.c"
    break;

  case 96: /* factor: mutable  */
#line 559 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
					}
#line 2117 "c-.tab.c"
    break;

  case 97: /* factor: immutable  */
#line 563 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
					}
#line 2125 "c-.tab.c"
    break;

  case 98: /* mutable: ID  */
#line 569 "c-.y"
                    {
                        (yyval.node) = new AST::Exp::Id((yyvsp[0].tokenData)->linenum, (yyvsp[0].tokenData)->tokenstr);
					}
#line 2133 "c-.tab.c"
    break;

  case 99: /* mutable: ID LBRACK exp RBRACK  */
#line 573 "c-.y"
                    {
                        (yyval.node) = new AST::Op::Binary((yyvsp[-3].tokenData)->linenum, AST::Op::Binary::Type::Index, new AST::Exp::Id((yyvsp[-3].tokenData)->linenum, (yyvsp[-3].tokenData)->tokenstr), (yyvsp[-1].node));
                    }
#line 2141 "c-.tab.c"
    break;

  case 100: /* immutable: LPAREN exp RPAREN  */
#line 579 "c-.y"
                    {
                        (yyval.node) = (yyvsp[-1].node);
                    }
#line 2149 "c-.tab.c"
    break;

  case 101: /* immutable: call  */
#line 583 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 2157 "c-.tab.c"
    break;

  case 102: /* immutable: constant  */
#line 587 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 2165 "c-.tab.c"
    break;

  case 103: /* call: ID LPAREN argList RPAREN  */
#line 593 "c-.y"
                    {
                        (yyval.node) = new AST::Exp::Call((yyvsp[-3].tokenData)->linenum, (yyvsp[-3].tokenData)->tokenstr, (yyvsp[-1].node));
                    }
#line 2173 "c-.tab.c"
    break;

  case 104: /* call: ID LPAREN RPAREN  */
#line 597 "c-.y"
                    {
                        (yyval.node) = new AST::Exp::Call((yyvsp[-2].tokenData)->linenum, (yyvsp[-2].tokenData)->tokenstr);
                    }
#line 2181 "c-.tab.c"
    break;

  case 105: /* argList: argList COM exp  */
#line 603 "c-.y"
                    {
                        (yyval.node) = (yyvsp[-2].node);
                        (yyval.node)->addSibling((yyvsp[0].node));
                    }
#line 2190 "c-.tab.c"
    break;

  case 106: /* argList: exp  */
#line 608 "c-.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 2198 "c-.tab.c"
    break;

  case 107: /* constant: NUMCONST  */
#line 614 "c-.y"
                    {
                        (yyval.node) = new AST::Exp::Const((yyvsp[0].tokenData)->linenum, AST::Exp::Const::Type::Int, (yyvsp[0].tokenData)->tokenstr);
                    }
#line 2206 "c-.tab.c"
    break;

  case 108: /* constant: CHARCONST  */
#line 618 "c-.y"
                    {
                        (yyval.node) = new AST::Exp::Const((yyvsp[0].tokenData)->linenum, AST::Exp::Const::Type::Char, (yyvsp[0].tokenData)->tokenstr);
                    }
#line 2214 "c-.tab.c"
    break;

  case 109: /* constant: STRINGCONST  */
#line 622 "c-.y"
                    {
                        (yyval.node) = new AST::Exp::Const((yyvsp[0].tokenData)->linenum, AST::Exp::Const::Type::String, (yyvsp[0].tokenData)->tokenstr);
                    }
#line 2222 "c-.tab.c"
    break;

  case 110: /* constant: BOOLCONST  */
#line 626 "c-.y"
                    {
                        (yyval.node) = new AST::Exp::Const((yyvsp[0].tokenData)->linenum, AST::Exp::Const::Type::Bool, (yyvsp[0].tokenData)->tokenstr);
                    }
#line 2230 "c-.tab.c"
    break;


#line 2234 "c-.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 631 "c-.y"

extern int yydebug;
extern std::vector<std::unique_ptr<TokenData>> tokens;
int main(int argc, char *argv[])
{
    Options options(argc, argv);
    yydebug = options.debug();

    if (!options.files().empty()) {
        for (unsigned i = 0; i < options.files().size(); i++) {
            std::string file = options.files()[i];
            if ((yyin = fopen(file.c_str(), "r"))) {
                // file open successful
                // do the parsing
                numErrors = 0;
                yyparse();

                if (tree_root != nullptr && options.print()) {
                    tree_root->print();
                    delete tree_root;
                    
                    /// Smart pointers, so destructors are called when vector is cleared
                    /// Frees all tokens
                    tokens.clear();

                    if (i != options.files().size() - 1) {
                        std::cout << std::endl;
                    }
                }
            }
            else {
                // failed to open file
                printf("ERROR: failed to open \'%s\'\n", argv[1]);
                exit(1);
            }
        }
    } else {
        yyparse();
    }



    return 0;
}
