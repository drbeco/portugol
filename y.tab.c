/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "portugol.y" /* yacc.c:339  */

/*
    Compilador PORTUGOL v.3q
    Autor: Ruben Carlo Benante
    Email: benante@gmail.com
    Data criação: 23/04/2009
    Data modificação: 25/05/2009
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "portugol.h"

/* prototipos */

int debugArvore = 0;
int debugTabela = 0;
int lineno = 1;
char msg[80], *tmp;
int imaxts, imaxtc, imaxtf, imaxtp;
tabelaSimb *prox;
extern char *sTipoDado[];
//extern char *sTipoBase[];


#line 95 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SE = 258,
    ENTAO = 259,
    SENAO = 260,
    INICIO = 261,
    FIM = 262,
    ENQUANTO = 263,
    ABORTE = 264,
    PARA = 265,
    INT = 266,
    REAL = 267,
    TEXTO = 268,
    DEFINE = 269,
    IMPORTE = 270,
    FUNC = 271,
    DEBUG = 272,
    ARVORE = 273,
    TABELA = 274,
    INC = 275,
    DEC = 276,
    INCPOS = 277,
    INCPRE = 278,
    DECPOS = 279,
    DECPRE = 280,
    PONT = 281,
    UPONT = 282,
    UEND = 283,
    PONTI = 284,
    PONTR = 285,
    PONTS = 286,
    PATTRIB = 287,
    IDENT = 288,
    INTCON = 289,
    REALCON = 290,
    TEXTOCON = 291,
    OU = 292,
    E = 293,
    NAO = 294,
    GE = 295,
    LE = 296,
    EQ = 297,
    NE = 298,
    GT = 299,
    LT = 300,
    UMENOS = 301
  };
#endif
/* Tokens.  */
#define SE 258
#define ENTAO 259
#define SENAO 260
#define INICIO 261
#define FIM 262
#define ENQUANTO 263
#define ABORTE 264
#define PARA 265
#define INT 266
#define REAL 267
#define TEXTO 268
#define DEFINE 269
#define IMPORTE 270
#define FUNC 271
#define DEBUG 272
#define ARVORE 273
#define TABELA 274
#define INC 275
#define DEC 276
#define INCPOS 277
#define INCPRE 278
#define DECPOS 279
#define DECPRE 280
#define PONT 281
#define UPONT 282
#define UEND 283
#define PONTI 284
#define PONTR 285
#define PONTS 286
#define PATTRIB 287
#define IDENT 288
#define INTCON 289
#define REALCON 290
#define TEXTOCON 291
#define OU 292
#define E 293
#define NAO 294
#define GE 295
#define LE 296
#define EQ 297
#define NE 298
#define GT 299
#define LT 300
#define UMENOS 301

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 30 "portugol.y" /* yacc.c:355  */

        tabelaSimb *pSimb;      /* yylval.pSimb ponteiro para o IDENT na TS */
        nodo *pNodo;            /* tipo do comando e expr */

#line 232 "y.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 247 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   340

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  9
/* YYNRULES -- Number of rules.  */
#define YYNRULES  56
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  122

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    51,    56,     2,
      54,    55,    49,    47,    57,    48,     2,    50,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    53,
       2,    46,     2,     2,     2,     2,     2,     2,     2,     2,
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
      45,    52
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    62,    62,   131,   135,   136,   137,   141,   142,   146,
     147,   151,   152,   153,   154,   155,   156,   157,   158,   160,
     161,   162,   163,   164,   165,   169,   170,   171,   172,   173,
     174,   176,   177,   178,   179,   181,   182,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   205,   206,   207
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SE", "ENTAO", "SENAO", "INICIO", "FIM",
  "ENQUANTO", "ABORTE", "PARA", "INT", "REAL", "TEXTO", "DEFINE",
  "IMPORTE", "FUNC", "DEBUG", "ARVORE", "TABELA", "INC", "DEC", "INCPOS",
  "INCPRE", "DECPOS", "DECPRE", "PONT", "UPONT", "UEND", "PONTI", "PONTR",
  "PONTS", "PATTRIB", "IDENT", "INTCON", "REALCON", "TEXTOCON", "OU", "E",
  "NAO", "GE", "LE", "EQ", "NE", "GT", "LT", "'='", "'+'", "'-'", "'*'",
  "'/'", "'%'", "UMENOS", "';'", "'('", "')'", "'&'", "','", "$accept",
  "programa", "bloco_comandos", "preprocs", "preproc", "lista_comandos",
  "comando", "expr", "funcao", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,    61,    43,    45,    42,
      47,    37,   301,    59,    40,    41,    38,    44
};
# endif

#define YYPACT_NINF -35

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-35)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -11,   -15,    11,   -35,     8,   -11,   -35,   -35,   -35,   -29,
     -35,   104,   -34,   -23,   -28,   -22,   -12,     0,     1,    16,
      17,    -3,     2,   -35,   -35,   -35,   141,   141,    19,   -35,
     141,    20,   -35,    55,   -35,   246,   -35,   141,   141,   -35,
     104,     4,     6,     7,   -35,   -35,    21,    22,    36,   -35,
     -35,   141,   115,   289,   -35,    25,   182,   -35,    24,   -35,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   -35,   198,   214,   141,   -35,   -35,   -35,
      26,    29,    30,   -32,   -35,   161,   141,   -35,   -35,   277,
     289,   -32,   -32,   -32,   -32,   -32,   -32,   -21,   -21,   -35,
     -35,   -35,    69,   104,   263,   -35,   -35,   -35,   -35,   141,
     -32,   104,   -35,   104,   230,    82,    37,   -35,   104,   104,
     -35,   -35
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       6,     0,     0,     2,     0,     4,     7,     8,     1,     0,
       5,     6,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    28,    25,    26,    27,     0,     0,     0,    11,
       0,     0,    24,     6,     9,     0,    53,     0,     0,    23,
       6,     0,     0,     0,    32,    34,     0,     0,     0,    31,
      33,     0,     0,    51,    37,    35,     0,    36,     0,    10,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    12,     0,     0,     0,    13,    14,    15,
       0,     0,     0,    29,    54,     0,     0,    52,     3,    50,
      49,    43,    44,    46,    45,    47,    48,    38,    39,    40,
      41,    42,     0,     6,     0,    16,    17,    18,    55,     0,
      30,     6,    21,     6,     0,    19,     0,    56,     6,     6,
      20,    22
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -35,   -35,    74,   -35,    88,   -35,   -33,   -25,   -35
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,    32,     4,     5,    33,    34,    35,    36
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      59,    53,    54,     6,     7,    56,     1,    76,    46,    47,
      48,     8,    74,    75,     9,    68,    69,    70,    71,    72,
      37,    41,    49,    50,    11,    39,    83,    85,    70,    71,
      72,    38,    40,    42,    43,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,    51,    44,
      45,   104,    55,    57,    80,    81,    52,    77,    12,    78,
      79,   110,    58,    13,    14,    15,    16,    17,    18,    82,
     112,    86,     1,   111,     3,    19,    20,    88,   115,   105,
     116,    21,   106,   107,   114,   120,   121,   118,    22,    23,
      24,    25,   119,    10,    26,     0,     0,     0,     0,     0,
       0,     0,     0,    27,    28,     0,     0,    12,    29,    30,
       0,    31,    13,    14,    15,    16,    17,    18,     0,     0,
       0,     1,     0,     0,    19,    20,     0,     0,     0,     0,
      21,     0,     0,     0,     0,    19,    20,    22,    23,    24,
      25,     0,     0,    26,     0,     0,     0,     0,    22,    23,
      24,    25,    27,    28,    26,     0,     0,    29,    30,     0,
      31,    19,    20,    27,    28,     0,     0,     0,     0,    30,
      84,    31,     0,     0,    22,    23,    24,    25,     0,     0,
      26,     0,     0,     0,     0,     0,     0,     0,     0,    27,
      28,     0,     0,     0,     0,    30,     0,    31,    60,    61,
       0,    62,    63,    64,    65,    66,    67,     0,    68,    69,
      70,    71,    72,     0,     0,     0,   108,     0,   109,    60,
      61,     0,    62,    63,    64,    65,    66,    67,     0,    68,
      69,    70,    71,    72,     0,    60,    61,    87,    62,    63,
      64,    65,    66,    67,     0,    68,    69,    70,    71,    72,
       0,    60,    61,   102,    62,    63,    64,    65,    66,    67,
       0,    68,    69,    70,    71,    72,     0,    60,    61,   103,
      62,    63,    64,    65,    66,    67,     0,    68,    69,    70,
      71,    72,     0,    60,    61,   117,    62,    63,    64,    65,
      66,    67,     0,    68,    69,    70,    71,    72,     0,    73,
      60,    61,     0,    62,    63,    64,    65,    66,    67,     0,
      68,    69,    70,    71,    72,    61,   113,    62,    63,    64,
      65,    66,    67,     0,    68,    69,    70,    71,    72,    62,
      63,    64,    65,    66,    67,     0,    68,    69,    70,    71,
      72
};

static const yytype_int8 yycheck[] =
{
      33,    26,    27,    18,    19,    30,    17,    40,    11,    12,
      13,     0,    37,    38,     6,    47,    48,    49,    50,    51,
      54,    33,    20,    21,    53,    53,    51,    52,    49,    50,
      51,    54,    54,    33,    33,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    46,    33,
      33,    76,    33,    33,    33,    33,    54,    53,     3,    53,
      53,    86,     7,     8,     9,    10,    11,    12,    13,    33,
     103,    46,    17,     4,     0,    20,    21,    53,   111,    53,
     113,    26,    53,    53,   109,   118,   119,     5,    33,    34,
      35,    36,    55,     5,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    49,    -1,    -1,     3,    53,    54,
      -1,    56,     8,     9,    10,    11,    12,    13,    -1,    -1,
      -1,    17,    -1,    -1,    20,    21,    -1,    -1,    -1,    -1,
      26,    -1,    -1,    -1,    -1,    20,    21,    33,    34,    35,
      36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    33,    34,
      35,    36,    48,    49,    39,    -1,    -1,    53,    54,    -1,
      56,    20,    21,    48,    49,    -1,    -1,    -1,    -1,    54,
      55,    56,    -1,    -1,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      49,    -1,    -1,    -1,    -1,    54,    -1,    56,    37,    38,
      -1,    40,    41,    42,    43,    44,    45,    -1,    47,    48,
      49,    50,    51,    -1,    -1,    -1,    55,    -1,    57,    37,
      38,    -1,    40,    41,    42,    43,    44,    45,    -1,    47,
      48,    49,    50,    51,    -1,    37,    38,    55,    40,    41,
      42,    43,    44,    45,    -1,    47,    48,    49,    50,    51,
      -1,    37,    38,    55,    40,    41,    42,    43,    44,    45,
      -1,    47,    48,    49,    50,    51,    -1,    37,    38,    55,
      40,    41,    42,    43,    44,    45,    -1,    47,    48,    49,
      50,    51,    -1,    37,    38,    55,    40,    41,    42,    43,
      44,    45,    -1,    47,    48,    49,    50,    51,    -1,    53,
      37,    38,    -1,    40,    41,    42,    43,    44,    45,    -1,
      47,    48,    49,    50,    51,    38,    53,    40,    41,    42,
      43,    44,    45,    -1,    47,    48,    49,    50,    51,    40,
      41,    42,    43,    44,    45,    -1,    47,    48,    49,    50,
      51
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    17,    59,    60,    61,    62,    18,    19,     0,     6,
      62,    53,     3,     8,     9,    10,    11,    12,    13,    20,
      21,    26,    33,    34,    35,    36,    39,    48,    49,    53,
      54,    56,    60,    63,    64,    65,    66,    54,    54,    53,
      54,    33,    33,    33,    33,    33,    11,    12,    13,    20,
      21,    46,    54,    65,    65,    33,    65,    33,     7,    64,
      37,    38,    40,    41,    42,    43,    44,    45,    47,    48,
      49,    50,    51,    53,    65,    65,    64,    53,    53,    53,
      33,    33,    33,    65,    55,    65,    46,    55,    53,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    55,    55,    65,    53,    53,    53,    55,    57,
      65,     4,    64,    53,    65,    64,    64,    55,     5,    55,
      64,    64
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    58,    59,    60,    61,    61,    61,    62,    62,    63,
      63,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    66,    66,    66
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     6,     1,     2,     0,     2,     2,     1,
       2,     1,     2,     3,     3,     3,     4,     4,     4,     6,
       8,     5,     8,     2,     1,     1,     1,     1,     1,     3,
       4,     2,     2,     2,     2,     2,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     3,     1,     3,     4,     6
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 62 "portugol.y" /* yacc.c:1646  */
    {
                            fprintf(yyout, "//    Gerado pelo compilador Portugol versao 2q\n");
                            fprintf(yyout, "//    Autor: Ruben Carlo Benante\n");
                            fprintf(yyout, "//    Email: benante@gmail.com\n");
                            fprintf(yyout, "//    Data: 23/05/2009\n\n");
                            fprintf(yyout, "#include <math.h>\n");
                            fprintf(yyout, "#include \"quadruplas.h\"\n");
                            fprintf(yyout, "#include \"saida.h\"\n\n");
                            fprintf(yyout, "void filltf(void)\n{\n");
                            prox=achaFuncs(NULL);
                            while(prox!=NULL)
                            {
                                fprintf(yyout, "  tf[%d].tipoRet=", prox->idx);
                                switch(prox->tipoD)
                                {
                                    case tipoIdFuncInt:
                                        fprintf(yyout, "tipoRetFuncInt;\n");
                                        fprintf(yyout, "  tf[%d].i2func=%s;\n", prox->idx, prox->idFunc); //bug2--------
                                        break;
                                    case tipoIdFuncFloat:
                                        fprintf(yyout, "tipoRetFuncFloat;\n");
                                        fprintf(yyout, "  tf[%d].ffunc=%s;\n", prox->idx, prox->idFunc);
                                        break;
                                    case tipoIdFuncDouble:
                                        fprintf(yyout, "tipoRetFuncDouble;\n");
                                        fprintf(yyout, "  tf[%d].dfunc=%s;\n", prox->idx, prox->idFunc);
                                        break;
                                    case tipoIdFuncStr:
                                        fprintf(yyout, "tipoRetFuncStr;\n");
                                        fprintf(yyout, "  tf[%d].sfunc=%s;\n", prox->idx, prox->idFunc);
                                        break;
                                    case tipoIdFuncVoid:
                                        fprintf(yyout, "tipoRetFuncVoid;\n");
                                        fprintf(yyout, "  tf[%d].vfunc=(void *)%s;\n", prox->idx, prox->idFunc);
                                        break;
                                    default:
                                        yyerror("Funcao de tipo desconhecido.\n");
                                        exit(1);
                                }
                                fprintf(yyout, "  tf[%d].idNome=malloc(strlen(\"%s\")+1);\n", prox->idx, prox->idNome);
                                fprintf(yyout, "  strcpy(tf[%d].idNome,\"%s\");\n\n", prox->idx, prox->idNome);
                                prox=achaFuncs(prox);
                            }
                            fprintf(yyout, "}\n\n");
                            fprintf(yyout, "int main(void)\n");
                            fprintf(yyout, "{\n  filltf();\n\n");
                            gera_quad((yyvsp[0].pNodo),0);
                            liberaNodo((yyvsp[0].pNodo));
                            imaxts=geraTS();
                            imaxtc=geraTC();
                            imaxtf=geraTF();
                            tmp=geraTP(&imaxtp);
                            fprintf(fhead, "//    Gerado pelo compilador Portugol versao 2q\n");
                            fprintf(fhead, "//    Autor: Ruben Carlo Benante\n");
                            fprintf(fhead, "//    Email: benante@gmail.com\n");
                            fprintf(fhead, "//    Data: 23/05/2009\n\n");
                            fprintf(fhead, "#define MAX_TS %d /* tabela de variaveis */\n", imaxts);
                            fprintf(fhead, "#define MAX_TC %d /* tabela de constantes */\n", imaxtc);
                            fprintf(fhead, "#define MAX_TP %d /* tabela de temporarios */\n\n", imaxtp);
                            fprintf(fhead, "#define MAX_TF %d /* tabela de funcoes */\n\n", imaxtf);
                            fprintf(fhead, "superTipo ts[MAX_TS];\n");
                            fprintf(fhead, "superTipo tc[MAX_TC];\n");
                            fprintf(fhead, "superTipo tp[MAX_TP];\n");
                            fprintf(fhead, "superFunc tf[MAX_TF];\n\n");
                            return 0;
                         }
#line 1513 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 131 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(INICIO, 1, (yyvsp[-2].pNodo)); }
#line 1519 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 141 "portugol.y" /* yacc.c:1646  */
    { debugArvore = 1; }
#line 1525 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 142 "portugol.y" /* yacc.c:1646  */
    { debugTabela = 1; }
#line 1531 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 146 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = (yyvsp[0].pNodo); }
#line 1537 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 147 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr('l', 2, (yyvsp[-1].pNodo), (yyvsp[0].pNodo)); }
#line 1543 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 151 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(';', 2, NULL, NULL); }
#line 1549 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 152 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = (yyvsp[-1].pNodo); }
#line 1555 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 153 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(INT, 1, conv((yyvsp[-1].pSimb))); }
#line 1561 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 154 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(REAL, 1, conv((yyvsp[-1].pSimb))); }
#line 1567 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 155 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(TEXTO, 1, conv((yyvsp[-1].pSimb))); }
#line 1573 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 156 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(PONTI, 1, conv((yyvsp[-1].pSimb))); }
#line 1579 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 157 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(PONTR, 1, conv((yyvsp[-1].pSimb))); }
#line 1585 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 158 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(PONTS, 1, conv((yyvsp[-1].pSimb))); }
#line 1591 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 160 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(SE, 2, (yyvsp[-3].pNodo), (yyvsp[0].pNodo)); }
#line 1597 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 161 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(SE, 3, (yyvsp[-5].pNodo), (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1603 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 162 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(ENQUANTO, 2, (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1609 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 163 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(PARA, 4, (yyvsp[-5].pNodo), (yyvsp[-4].pNodo), (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1615 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 164 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(ABORTE, 0); }
#line 1621 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 165 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = (yyvsp[0].pNodo); }
#line 1627 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 169 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = conv((yyvsp[0].pSimb)); }
#line 1633 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 170 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = conv((yyvsp[0].pSimb)); }
#line 1639 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 171 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = conv((yyvsp[0].pSimb)); }
#line 1645 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 172 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = conv((yyvsp[0].pSimb)); }
#line 1651 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 173 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr('=', 2, conv((yyvsp[-2].pSimb)), (yyvsp[0].pNodo)); }
#line 1657 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 174 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(PATTRIB, 2, conv((yyvsp[-2].pSimb)), (yyvsp[0].pNodo)); }
#line 1663 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 176 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(INCPOS, 1, conv((yyvsp[-1].pSimb))); }
#line 1669 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 177 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(INCPRE, 1, conv((yyvsp[0].pSimb))); }
#line 1675 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 178 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(DECPOS, 1, conv((yyvsp[-1].pSimb))); }
#line 1681 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 179 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(DECPRE, 1, conv((yyvsp[0].pSimb))); }
#line 1687 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 181 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(UPONT, 1, conv((yyvsp[0].pSimb))); }
#line 1693 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 182 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(UEND, 1, conv((yyvsp[0].pSimb))); }
#line 1699 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 184 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(UMENOS, 1, (yyvsp[0].pNodo)); }
#line 1705 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 185 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr('+', 2, (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1711 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 186 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr('-', 2, (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1717 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 187 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr('*', 2, (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1723 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 188 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr('/', 2, (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1729 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 189 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr('%', 2, (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1735 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 190 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(GE, 2, (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1741 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 191 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(LE, 2, (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1747 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 192 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(NE, 2, (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1753 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 193 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(EQ, 2, (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1759 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 194 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(GT, 2, (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1765 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 195 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(LT, 2, (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1771 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 196 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(E, 2, (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1777 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 197 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(OU, 2, (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1783 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 198 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(NAO, 1, (yyvsp[0].pNodo)); }
#line 1789 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 199 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr('(', 1, (yyvsp[-1].pNodo)); }
#line 1795 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 200 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = (yyvsp[0].pNodo); }
#line 1801 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 205 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(FUNC, 1, conv((yyvsp[-2].pSimb))); }
#line 1807 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 206 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(FUNC, 2, conv((yyvsp[-3].pSimb)), (yyvsp[-1].pNodo)); }
#line 1813 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 207 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(FUNC, 3, conv((yyvsp[-5].pSimb)), (yyvsp[-3].pNodo), (yyvsp[-1].pNodo)); }
#line 1819 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1823 "y.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 209 "portugol.y" /* yacc.c:1906  */


/* Acha (nao cria) Id pelo seu IDX */
tabelaSimb *achaIdx(int i)
{
    char *p;
    tabelaSimb *ps;
    int t1;

    if(i==-1)
        return NULL;

    for(ps=tabSimb; ps < &tabSimb[MAX_SIMB]; ps++)
    {
//        if(ps->idNome && ps->idx==i && ps->tipoD!=tipoIndef && ps->tipoD!=tipoVoid) /* encontrou ? */
//        if(ps->idNome && ps->idx==i && (varips->tipoD==tipoIdInt || ps->tipoD==tipoIdFloat || ps->tipoD==tipoIdStr || ps->tipoD==tipoIdPointInt || ps->tipoD==tipoIdPointFloat || ps->tipoD==tipoIdPointStr )) /* encontrou ? */
        if(ps->idNome && ps->idx==i && variavelT(ps->tipoD)) /* encontrou ? */
            return ps; /* sim ! */
    }
    //printf("achaIDX nao achou!!\n");
    return NULL;
}

/* Acha/cria ID e retorna o ponteiro para a tabelaSimb */
tabelaSimb *achaId(char *nome)
{
    char *p;
    tabelaSimb *ps;

    for(ps=tabSimb; ps < &tabSimb[MAX_SIMB]; ps++)
    {
        if(ps->idNome && !strcmp(ps->idNome, nome)) /* encontrou ? */
            return ps; /* sim ! */
        if(!ps->idNome) /* ponteiro livre ? */
        {
            ps->tipoD = tipoIdIndef;
            ps->idNome = strdup(nome);
            return ps;
        }
    }
    yyerror("Tabela de simbolos cheia!"); /* caso contrario */
    exit(1);
}

/* Acha/cria ConInt e retorna o ponteiro para a TS */
tabelaSimb *achaInt(int iv)
{
    char *p;
    tabelaSimb *ps;
    int i;

    for(ps=tabSimb; ps < &tabSimb[MAX_SIMB]; ps++)
    {
        if(ps->idNome && ps->ival==iv && ps->tipoD==tipoConInt) /* encontrou ? */
            return ps; /* sim ! */
        if(!ps->idNome) /* ponteiro livre ? */
        {
            i=geraTC();
            ps->tipoD = tipoConInt;
            ps->idNome = strdup("#ConInt");
            ps->ival = iv;
            ps->idx = i;
            return ps;
        }
    }
    yyerror("Tabela de simbolos cheia!"); /* caso contrario */
    exit(1);
}

/* Acha/cria ConFloat e retorna o ponteiro para a TS */
tabelaSimb *achaFloat(float fv)
{
    char *p;
    tabelaSimb *ps;
    int i;

    for(ps=tabSimb; ps < &tabSimb[MAX_SIMB]; ps++)
    {
        if(ps->idNome && ps->fval==fv && ps->tipoD==tipoConFloat) /* encontrou ? */
            return ps; /* sim ! */
        if(!ps->idNome) /* ponteiro livre ? */
        {
            i=geraTC();
            ps->tipoD = tipoConFloat;
            ps->idNome = strdup("#ConFloat");
            ps->fval = fv;
            ps->idx = i;
            return ps;
        }
    }
    yyerror("Tabela de simbolos cheia!"); /* caso contrario */
    exit(1);
}

/* Acha/cria ConStr e retorna o ponteiro para a TS */
tabelaSimb *achaStr(char *sv)
{
    char *p;
    tabelaSimb *ps;
    int i;

    for(ps=tabSimb; ps < &tabSimb[MAX_SIMB]; ps++)
    {
        if(ps->idNome && !strcmp(ps->sval, sv)) /* encontrou ? */
            return ps; /* sim ! */
        if(!ps->idNome) /* ponteiro livre ? */
        {
            i=geraTC();
            ps->tipoD = tipoConStr;
            ps->idNome = strdup("#ConStr");
            strcpy(ps->sval,sv);
            ps->idx = i;
            return ps;
        }
    }
    yyerror("Tabela de simbolos cheia!"); /* caso contrario */
    exit(1);
}

/* Apenas procura (nao cria) todas funcoes, a partir da ultima procurada, ou NULL para a primeira */
tabelaSimb *achaFuncs(tabelaSimb *ultima)
{
    char *p;
    tabelaSimb *ps;

    if(ultima==NULL) //null? a partir do primeiro
        ps=tabSimb;
    else
        ps=++ultima; //senao a partir do proximo
    while(ps < &tabSimb[MAX_SIMB])
    {
        if(ps->tipoD>=tipoIdFuncInt) /* encontrou func? */
            return ps; /* sim ! */
        ps++;
    }
    return NULL;
}

/* Converte constante/identificador da TS em nodo */
nodo *conv(tabelaSimb *ps)
{
    nodo *tn;

    if((tn=malloc(sizeof(nodo)))==NULL) /* aloca nodo */
        yyerror("Faltou memoria (cod. 2: conf)");

    tn->linha = lineno;
    tn->tipoN = tipoSimb;
    tn->pSimb = ps;
    return tn;
}

/* Converte operador em nodo */
nodo *opr(int oper, int nops, ...)
{
    va_list ap;
    nodo *tn;
    size_t tam;
    int i;

    tam = sizeof(nodo) + (nops - 1) * sizeof(nodo *);

    if((tn=malloc(tam))==NULL) /* aloca nodo */
        yyerror("Faltou memoria (cod. 4: opr)");

    tn->linha = lineno;
    tn->tipoN = tipoOper;
    tn->opr.oper = oper;
    tn->opr.nops = nops;
    va_start(ap, nops);
    for(i=0; i<nops; i++)
        tn->opr.ptn[i] = va_arg(ap, nodo*);
    va_end(ap);

    return tn;
}

/* Libera memoria de um nodo tipoNodo */
void liberaNodo(nodo *tn)
{
    int i;

    if(!tn)
        return;
    if(tn->tipoN == tipoOper)
    {
        for(i=0; i<tn->opr.nops; i++)
            liberaNodo(tn->opr.ptn[i]);
    }
    free(tn);
}
