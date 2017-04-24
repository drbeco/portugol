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
#include <math.h>
#include "portugol.h"

/* prototipos */

int debugArvore = 0;
int debugTabela = 0;
int lineno = 1;
char msg[120], *tmp;
//int imaxts, imaxtc, imaxtf, imaxtp;
tabelaSimb *ps;
extern char *sTipoDado[];
//extern char *sTipoBase[];
int ta[MAX_PARAM];
extern int indente;


#line 98 "y.tab.c" /* yacc.c:339  */

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
    RETORNE = 266,
    INT = 267,
    REAL = 268,
    TEXTO = 269,
    NADA = 270,
    FUNCAO = 271,
    EXTERNA = 272,
    FUNC = 273,
    DEFINE = 274,
    DEBUG = 275,
    ARVORE = 276,
    TABELA = 277,
    INC = 278,
    DEC = 279,
    INCPOS = 280,
    INCPRE = 281,
    DECPOS = 282,
    DECPRE = 283,
    PONT = 284,
    UPONT = 285,
    UEND = 286,
    PATTRIB = 287,
    PONTI = 288,
    PONTR = 289,
    PONTS = 290,
    IDENT = 291,
    INTCON = 292,
    REALCON = 293,
    TEXTOCON = 294,
    PRINCIPAL = 295,
    OU = 296,
    E = 297,
    NAO = 298,
    GE = 299,
    LE = 300,
    EQ = 301,
    NE = 302,
    GT = 303,
    LT = 304,
    UMENOS = 305
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
#define RETORNE 266
#define INT 267
#define REAL 268
#define TEXTO 269
#define NADA 270
#define FUNCAO 271
#define EXTERNA 272
#define FUNC 273
#define DEFINE 274
#define DEBUG 275
#define ARVORE 276
#define TABELA 277
#define INC 278
#define DEC 279
#define INCPOS 280
#define INCPRE 281
#define DECPOS 282
#define DECPRE 283
#define PONT 284
#define UPONT 285
#define UEND 286
#define PATTRIB 287
#define PONTI 288
#define PONTR 289
#define PONTS 290
#define IDENT 291
#define INTCON 292
#define REALCON 293
#define TEXTOCON 294
#define PRINCIPAL 295
#define OU 296
#define E 297
#define NAO 298
#define GE 299
#define LE 300
#define EQ 301
#define NE 302
#define GT 303
#define LT 304
#define UMENOS 305

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 33 "portugol.y" /* yacc.c:355  */

        tabelaSimb *pSimb;      /* yylval.pSimb ponteiro para o IDENT na TS */
        nodo *pNodo;            /* tipo do comando e expr */
        int intval;             /* valor do token para um dado tipo */

#line 244 "y.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 259 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   908

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  80
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  203

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   305

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    55,    61,     2,
      57,    58,    53,    51,    60,    52,     2,    54,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    59,
       2,    50,     2,     2,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    56
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    74,    74,    92,    95,    96,   101,   102,   105,   106,
     111,   113,   115,   117,   130,   132,   134,   143,   144,   148,
     149,   153,   154,   158,   159,   160,   163,   164,   165,   166,
     167,   168,   172,   173,   174,   175,   177,   178,   179,   180,
     182,   183,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   205,
     206,   210,   211,   212,   213,   214,   215,   219,   220,   223,
     224,   249,   250,   251,   257,   260,   261,   266,   267,   268,
     269
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SE", "ENTAO", "SENAO", "INICIO", "FIM",
  "ENQUANTO", "ABORTE", "PARA", "RETORNE", "INT", "REAL", "TEXTO", "NADA",
  "FUNCAO", "EXTERNA", "FUNC", "DEFINE", "DEBUG", "ARVORE", "TABELA",
  "INC", "DEC", "INCPOS", "INCPRE", "DECPOS", "DECPRE", "PONT", "UPONT",
  "UEND", "PATTRIB", "PONTI", "PONTR", "PONTS", "IDENT", "INTCON",
  "REALCON", "TEXTOCON", "PRINCIPAL", "OU", "E", "NAO", "GE", "LE", "EQ",
  "NE", "GT", "LT", "'='", "'+'", "'-'", "'*'", "'/'", "'%'", "UMENOS",
  "'('", "')'", "';'", "','", "'&'", "$accept", "programa", "conjunto",
  "preprocs", "preproc", "blocos", "bloco_funcoes", "principio",
  "retornar", "lista_comandos", "subordinados_comandos", "comando", "expr",
  "ftipo", "vtipo", "lista_tipos", "meio_vtipos", "constante",
  "funcaoexterna", "lista_funcaoexterna", "funcao", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
      61,    43,    45,    42,    47,    37,   305,    40,    41,    59,
      44,    38
};
# endif

#define YYPACT_NINF -166

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-166)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -166,     6,  -166,   -10,  -166,    -1,  -166,    16,  -166,  -166,
      11,   103,  -166,  -166,  -166,  -166,  -166,   107,     3,  -166,
       2,  -166,  -166,     7,  -166,  -166,  -166,    -6,    18,    32,
      31,   133,   143,  -166,    10,   -11,    49,    68,    52,    91,
      53,    74,   129,   -47,   144,   -22,  -166,  -166,    90,   145,
     -11,    93,   154,   -11,   627,   102,   127,   627,   105,   134,
     108,   114,   120,   124,   638,   148,   149,    -9,  -166,  -166,
    -166,   680,   680,   150,   680,  -166,   164,  -166,   130,  -166,
      46,   165,  -166,  -166,   627,   122,   185,   627,    24,   680,
     680,  -166,   680,  -166,   718,  -166,  -166,  -166,  -166,   680,
     669,   853,  -166,   140,   766,  -166,   146,  -166,   680,   680,
     680,   680,   680,   680,   680,   680,   680,   680,   680,   680,
     680,  -166,   147,   240,   196,   151,   295,   197,   -11,   781,
     796,   734,  -166,   123,  -166,    25,   680,  -166,  -166,   841,
     853,   123,   123,   123,   123,   123,   123,    76,    76,  -166,
    -166,  -166,  -166,   152,   153,  -166,   156,   157,   168,   203,
     352,   680,  -166,   680,   123,  -166,   627,  -166,   627,   155,
     352,   158,  -166,  -166,   750,   698,   407,   462,   212,   214,
     627,   680,  -166,   680,   161,   166,   167,   352,   517,   811,
     826,  -166,  -166,   627,  -166,   170,   352,  -166,   572,  -166,
    -166,   171,  -166
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     2,    75,     1,     0,     5,     8,     6,     7,
       0,     0,    76,    61,    62,    63,    60,     0,     0,    59,
      61,     9,     3,     0,    64,    65,    66,     0,     0,     0,
      69,     0,     0,    67,     0,     0,     0,     0,     0,     0,
       0,    68,     0,     0,     0,     0,    74,    70,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    33,    71,    72,
      73,     0,     0,     0,     0,    23,     0,    31,     0,    19,
       0,     0,    32,    58,     0,     0,     0,     0,     0,     0,
       0,    26,     0,    17,     0,    37,    39,    36,    38,     0,
       0,    56,    42,    40,     0,    41,     0,    20,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    24,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    18,    34,    77,     0,     0,    57,    14,    55,
      54,    48,    49,    51,    50,    52,    53,    43,    44,    45,
      46,    47,    25,     0,     0,    10,     0,     0,     0,     0,
       0,     0,    78,     0,    35,    15,     0,    11,     0,     0,
       0,     0,    29,    21,     0,     0,     0,     0,     0,    27,
       0,     0,    79,     0,     0,     0,     0,     0,     0,     0,
       0,    16,    12,     0,    28,     0,     0,    80,     0,    22,
      30,     0,    13
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,   -57,
    -165,   -74,   -55,   216,    -3,  -166,  -166,  -166,  -166,  -166,
    -166
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     3,     6,    11,    21,    22,    77,    78,
     172,    79,    80,    18,    81,    34,    35,    82,    12,     7,
      83
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      86,    13,    14,    15,   107,   179,     4,    19,    19,    94,
       5,    49,   107,    50,    97,    98,   101,   102,    17,   104,
       8,     9,   194,    13,    14,    15,    16,   123,    37,    39,
     126,   200,    41,    10,   129,   130,    52,   131,    53,    27,
      17,    99,    28,    29,   133,   135,    33,    56,   100,   107,
      59,    30,   107,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   108,   109,    40,   110,
     111,   112,   113,   114,   115,    31,   116,   117,   118,   119,
     120,   164,   127,   162,   128,   163,   173,   108,   109,    32,
     110,   111,   112,   113,   114,   115,   173,   116,   117,   118,
     119,   120,   107,   107,    43,   121,   174,    42,   175,   176,
      44,   177,    46,   173,   107,    20,    14,    15,    16,    24,
      25,    26,   173,   188,   107,   158,   189,    45,   190,   118,
     119,   120,    17,    60,    47,    48,   198,   106,    61,    62,
      63,    64,    13,    14,    15,    13,    14,    15,    36,    54,
      51,    55,    57,    65,    66,    13,    14,    15,    38,    17,
      58,    84,    17,    85,    87,    89,    67,    68,    69,    70,
      88,    90,    17,    71,   116,   117,   118,   119,   120,    91,
     124,    92,    72,    73,    95,    96,   103,    74,    60,    75,
     136,    76,   125,    61,    62,    63,    64,    13,    14,    15,
     105,   122,   154,   157,   169,   138,   152,   170,    65,    66,
     155,   165,   166,   178,    17,   167,   168,   180,   186,   187,
     191,    67,    68,    69,    70,   192,   193,    23,    71,   199,
     202,     0,     0,     0,     0,     0,     0,    72,    73,     0,
       0,     0,    74,    60,    75,     0,    76,   153,    61,    62,
      63,    64,    13,    14,    15,     0,     0,     0,     0,     0,
       0,     0,     0,    65,    66,     0,     0,     0,     0,    17,
       0,     0,     0,     0,     0,     0,    67,    68,    69,    70,
       0,     0,     0,    71,     0,     0,     0,     0,     0,     0,
       0,     0,    72,    73,     0,     0,     0,    74,    60,    75,
       0,    76,   156,    61,    62,    63,    64,    13,    14,    15,
       0,     0,     0,     0,     0,     0,     0,     0,    65,    66,
       0,     0,     0,     0,    17,     0,     0,     0,     0,     0,
       0,    67,    68,    69,    70,     0,     0,     0,    71,     0,
       0,     0,     0,     0,     0,     0,     0,    72,    73,     0,
       0,     0,    74,     0,    75,    60,    76,     0,   171,     0,
      61,    62,    63,    64,    13,    14,    15,     0,     0,     0,
       0,     0,     0,     0,     0,    65,    66,     0,     0,     0,
       0,    17,     0,     0,     0,     0,     0,     0,    67,    68,
      69,    70,     0,     0,     0,    71,     0,     0,     0,     0,
       0,     0,     0,     0,    72,    73,     0,     0,     0,    74,
      60,    75,     0,    76,   184,    61,    62,    63,    64,    13,
      14,    15,     0,     0,     0,     0,     0,     0,     0,     0,
      65,    66,     0,     0,     0,     0,    17,     0,     0,     0,
       0,     0,     0,    67,    68,    69,    70,     0,     0,     0,
      71,     0,     0,     0,     0,     0,     0,     0,     0,    72,
      73,     0,     0,     0,    74,    60,    75,     0,    76,   185,
      61,    62,    63,    64,    13,    14,    15,     0,     0,     0,
       0,     0,     0,     0,     0,    65,    66,     0,     0,     0,
       0,    17,     0,     0,     0,     0,     0,     0,    67,    68,
      69,    70,     0,     0,     0,    71,     0,     0,     0,     0,
       0,     0,     0,     0,    72,    73,     0,     0,     0,    74,
      60,    75,     0,    76,   195,    61,    62,    63,    64,    13,
      14,    15,     0,     0,     0,     0,     0,     0,     0,     0,
      65,    66,     0,     0,     0,     0,    17,     0,     0,     0,
       0,     0,     0,    67,    68,    69,    70,     0,     0,     0,
      71,     0,     0,     0,     0,     0,     0,     0,     0,    72,
      73,     0,     0,     0,    74,    60,    75,     0,    76,   201,
      61,    62,    63,    64,    13,    14,    15,     0,     0,     0,
       0,     0,     0,     0,     0,    65,    66,     0,     0,     0,
       0,    17,     0,     0,     0,     0,     0,     0,    67,    68,
      69,    70,     0,     0,     0,    71,     0,     0,     0,     0,
       0,     0,     0,     0,    72,    73,     0,     0,     0,    74,
      60,    75,     0,    76,     0,    61,    62,    63,    64,    13,
      14,    15,     0,     0,     0,     0,     0,     0,     0,     0,
      65,    66,     0,     0,     0,     0,    17,     0,     0,     0,
       0,    65,    66,    67,    68,    69,    70,     0,     0,     0,
      71,     0,     0,     0,    67,    68,    69,    70,     0,    72,
      73,    71,     0,     0,    74,     0,    75,     0,    76,     0,
      72,    73,    65,    66,     0,    74,     0,    93,     0,    76,
       0,     0,     0,    65,    66,    67,    68,    69,    70,     0,
       0,     0,    71,     0,     0,     0,    67,    68,    69,    70,
       0,    72,    73,    71,     0,     0,    74,   134,     0,     0,
      76,     0,    72,    73,     0,     0,     0,    74,     0,   108,
     109,    76,   110,   111,   112,   113,   114,   115,     0,   116,
     117,   118,   119,   120,     0,     0,   182,     0,   183,   108,
     109,     0,   110,   111,   112,   113,   114,   115,     0,   116,
     117,   118,   119,   120,     0,   108,   109,   132,   110,   111,
     112,   113,   114,   115,     0,   116,   117,   118,   119,   120,
       0,   108,   109,   161,   110,   111,   112,   113,   114,   115,
       0,   116,   117,   118,   119,   120,     0,   108,   109,   181,
     110,   111,   112,   113,   114,   115,     0,   116,   117,   118,
     119,   120,   108,   109,   137,   110,   111,   112,   113,   114,
     115,     0,   116,   117,   118,   119,   120,   108,   109,   159,
     110,   111,   112,   113,   114,   115,     0,   116,   117,   118,
     119,   120,   108,   109,   160,   110,   111,   112,   113,   114,
     115,     0,   116,   117,   118,   119,   120,   108,   109,   196,
     110,   111,   112,   113,   114,   115,     0,   116,   117,   118,
     119,   120,     0,   109,   197,   110,   111,   112,   113,   114,
     115,     0,   116,   117,   118,   119,   120,   110,   111,   112,
     113,   114,   115,     0,   116,   117,   118,   119,   120
};

static const yytype_int16 yycheck[] =
{
      57,    12,    13,    14,    78,   170,     0,    10,    11,    64,
      20,    58,    86,    60,    23,    24,    71,    72,    29,    74,
      21,    22,   187,    12,    13,    14,    15,    84,    31,    32,
      87,   196,    35,    17,    89,    90,    58,    92,    60,    36,
      29,    50,    40,    36,    99,   100,    15,    50,    57,   123,
      53,    57,   126,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,    41,    42,    58,    44,
      45,    46,    47,    48,    49,    57,    51,    52,    53,    54,
      55,   136,    58,    58,    60,    60,   160,    41,    42,    57,
      44,    45,    46,    47,    48,    49,   170,    51,    52,    53,
      54,    55,   176,   177,    36,    59,   161,    58,   163,   166,
      58,   168,    59,   187,   188,    12,    13,    14,    15,    12,
      13,    14,   196,   180,   198,   128,   181,    36,   183,    53,
      54,    55,    29,     3,    60,     6,   193,     7,     8,     9,
      10,    11,    12,    13,    14,    12,    13,    14,    15,    59,
       6,     6,    59,    23,    24,    12,    13,    14,    15,    29,
       6,    59,    29,    36,    59,    57,    36,    37,    38,    39,
      36,    57,    29,    43,    51,    52,    53,    54,    55,    59,
      58,    57,    52,    53,    36,    36,    36,    57,     3,    59,
      50,    61,     7,     8,     9,    10,    11,    12,    13,    14,
      36,    36,     6,     6,    36,    59,    59,     4,    23,    24,
      59,    59,    59,    58,    29,    59,    59,    59,     6,     5,
      59,    36,    37,    38,    39,    59,    59,    11,    43,    59,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    52,    53,    -1,
      -1,    -1,    57,     3,    59,    -1,    61,     7,     8,     9,
      10,    11,    12,    13,    14,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    23,    24,    -1,    -1,    -1,    -1,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    37,    38,    39,
      -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    52,    53,    -1,    -1,    -1,    57,     3,    59,
      -1,    61,     7,     8,     9,    10,    11,    12,    13,    14,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    24,
      -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    37,    38,    39,    -1,    -1,    -1,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    53,    -1,
      -1,    -1,    57,    -1,    59,     3,    61,    -1,     6,    -1,
       8,     9,    10,    11,    12,    13,    14,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    24,    -1,    -1,    -1,
      -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,    36,    37,
      38,    39,    -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    52,    53,    -1,    -1,    -1,    57,
       3,    59,    -1,    61,     7,     8,     9,    10,    11,    12,
      13,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      23,    24,    -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    37,    38,    39,    -1,    -1,    -1,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      53,    -1,    -1,    -1,    57,     3,    59,    -1,    61,     7,
       8,     9,    10,    11,    12,    13,    14,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    24,    -1,    -1,    -1,
      -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,    36,    37,
      38,    39,    -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    52,    53,    -1,    -1,    -1,    57,
       3,    59,    -1,    61,     7,     8,     9,    10,    11,    12,
      13,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      23,    24,    -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    37,    38,    39,    -1,    -1,    -1,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      53,    -1,    -1,    -1,    57,     3,    59,    -1,    61,     7,
       8,     9,    10,    11,    12,    13,    14,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    24,    -1,    -1,    -1,
      -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,    36,    37,
      38,    39,    -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    52,    53,    -1,    -1,    -1,    57,
       3,    59,    -1,    61,    -1,     8,     9,    10,    11,    12,
      13,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      23,    24,    -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,
      -1,    23,    24,    36,    37,    38,    39,    -1,    -1,    -1,
      43,    -1,    -1,    -1,    36,    37,    38,    39,    -1,    52,
      53,    43,    -1,    -1,    57,    -1,    59,    -1,    61,    -1,
      52,    53,    23,    24,    -1,    57,    -1,    59,    -1,    61,
      -1,    -1,    -1,    23,    24,    36,    37,    38,    39,    -1,
      -1,    -1,    43,    -1,    -1,    -1,    36,    37,    38,    39,
      -1,    52,    53,    43,    -1,    -1,    57,    58,    -1,    -1,
      61,    -1,    52,    53,    -1,    -1,    -1,    57,    -1,    41,
      42,    61,    44,    45,    46,    47,    48,    49,    -1,    51,
      52,    53,    54,    55,    -1,    -1,    58,    -1,    60,    41,
      42,    -1,    44,    45,    46,    47,    48,    49,    -1,    51,
      52,    53,    54,    55,    -1,    41,    42,    59,    44,    45,
      46,    47,    48,    49,    -1,    51,    52,    53,    54,    55,
      -1,    41,    42,    59,    44,    45,    46,    47,    48,    49,
      -1,    51,    52,    53,    54,    55,    -1,    41,    42,    59,
      44,    45,    46,    47,    48,    49,    -1,    51,    52,    53,
      54,    55,    41,    42,    58,    44,    45,    46,    47,    48,
      49,    -1,    51,    52,    53,    54,    55,    41,    42,    58,
      44,    45,    46,    47,    48,    49,    -1,    51,    52,    53,
      54,    55,    41,    42,    58,    44,    45,    46,    47,    48,
      49,    -1,    51,    52,    53,    54,    55,    41,    42,    58,
      44,    45,    46,    47,    48,    49,    -1,    51,    52,    53,
      54,    55,    -1,    42,    58,    44,    45,    46,    47,    48,
      49,    -1,    51,    52,    53,    54,    55,    44,    45,    46,
      47,    48,    49,    -1,    51,    52,    53,    54,    55
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    63,    64,    65,     0,    20,    66,    81,    21,    22,
      17,    67,    80,    12,    13,    14,    15,    29,    75,    76,
      12,    68,    69,    75,    12,    13,    14,    36,    40,    36,
      57,    57,    57,    15,    77,    78,    15,    76,    15,    76,
      58,    76,    58,    36,    58,    36,    59,    60,     6,    58,
      60,     6,    58,    60,    59,     6,    76,    59,     6,    76,
       3,     8,     9,    10,    11,    23,    24,    36,    37,    38,
      39,    43,    52,    53,    57,    59,    61,    70,    71,    73,
      74,    76,    79,    82,    59,    36,    71,    59,    36,    57,
      57,    59,    57,    59,    74,    36,    36,    23,    24,    50,
      57,    74,    74,    36,    74,    36,     7,    73,    41,    42,
      44,    45,    46,    47,    48,    49,    51,    52,    53,    54,
      55,    59,    36,    71,    58,     7,    71,    58,    60,    74,
      74,    74,    59,    74,    58,    74,    50,    58,    59,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    59,     7,     6,    59,     7,     6,    76,    58,
      58,    59,    58,    60,    74,    59,    59,    59,    59,    36,
       4,     6,    72,    73,    74,    74,    71,    71,    58,    72,
      59,    59,    58,    60,     7,     7,     6,     5,    71,    74,
      74,    59,    59,    59,    72,     7,    58,    58,    71,    59,
      72,     7,    59
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    62,    63,    64,    65,    65,    66,    66,    67,    67,
      68,    68,    68,    68,    69,    69,    69,    70,    70,    71,
      71,    72,    72,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    75,
      75,    76,    76,    76,    76,    76,    76,    77,    77,    78,
      78,    79,    79,    79,    80,    81,    81,    82,    82,    82,
      82
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     4,     0,     2,     2,     2,     0,     2,
      10,    11,    14,    17,    10,    11,    14,     2,     3,     1,
       2,     1,     5,     1,     2,     3,     2,     6,     8,     5,
       9,     1,     1,     1,     3,     4,     2,     2,     2,     2,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     3,     1,     1,
       1,     1,     1,     1,     2,     2,     2,     1,     2,     0,
       3,     1,     1,     1,     7,     0,     2,     3,     4,     6,
       8
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
#line 74 "portugol.y" /* yacc.c:1646  */
    {
                            //fprintf(yyout, "//    Gerado pelo compilador Portugol versao 3r\n");
                            fprintf(stderr, "pass 2... (geracao de arvore de escopo)\n");
                            carregaFuncoesPreTS();
                            pass2((yyvsp[0].pNodo), &esco, 0); //novo passo, para retirar informacoes de indentacao e escopo
                            fprintf(stderr, "pass 3... (analise semantica e geracao de codigo)\n");
                            pass3((yyvsp[0].pNodo),0); //pass3, geracao de codigo
                            //printTS();
                            fprintf(stderr, "pass 1, pass 2, pass 3. Compilado com sucesso\n");
                            //pass3c($1,0); //pass3, geracao de codigo
                            //fprintf(stderr, "gera_quad depois: saida.h\n");
                            liberaNodo((yyvsp[0].pNodo));
                            return 0;
                         }
#line 1626 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 92 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(INICIO, 2, (yyvsp[-2].pNodo), (yyvsp[-1].pNodo)); }
#line 1632 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 101 "portugol.y" /* yacc.c:1646  */
    { debugArvore = 1; }
#line 1638 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 102 "portugol.y" /* yacc.c:1646  */
    { debugTabela = 1; }
#line 1644 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 105 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = NULL; }
#line 1650 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 107 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr('l', 2, (yyvsp[-1].pNodo), (yyvsp[0].pNodo)); }
#line 1656 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 112 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr((yyvsp[-9].intval), 2, conv((yyvsp[-8].pSimb)), (yyvsp[-2].pNodo)); }
#line 1662 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 114 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr((yyvsp[-10].intval), 4, conv((yyvsp[-9].pSimb)), convtn((yyvsp[-7].intval)), conv((yyvsp[-6].pSimb)), (yyvsp[-2].pNodo)); }
#line 1668 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 116 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr((yyvsp[-13].intval), 6, conv((yyvsp[-12].pSimb)), convtn((yyvsp[-10].intval)), conv((yyvsp[-9].pSimb)), convtn((yyvsp[-7].intval)), conv((yyvsp[-6].pSimb)), (yyvsp[-2].pNodo)); }
#line 1674 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 118 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr((yyvsp[-16].intval), 8, conv((yyvsp[-15].pSimb)), convtn((yyvsp[-13].intval)), conv((yyvsp[-12].pSimb)), convtn((yyvsp[-10].intval)), conv((yyvsp[-9].pSimb)), convtn((yyvsp[-7].intval)), conv((yyvsp[-6].pSimb)), (yyvsp[-2].pNodo)); }
#line 1680 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 131 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(PRINCIPAL, 2, conv((yyvsp[-8].pSimb)), (yyvsp[-2].pNodo)); }
#line 1686 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 133 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(PRINCIPAL, 4, conv((yyvsp[-9].pSimb)), convtn((yyvsp[-7].intval)), conv((yyvsp[-6].pSimb)), (yyvsp[-2].pNodo)); }
#line 1692 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 135 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(PRINCIPAL, 6, conv((yyvsp[-12].pSimb)), convtn((yyvsp[-10].intval)), conv((yyvsp[-9].pSimb)), convtn((yyvsp[-7].intval)), conv((yyvsp[-6].pSimb)), (yyvsp[-2].pNodo)); }
#line 1698 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 143 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(RETORNE, 0); }
#line 1704 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 144 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(RETORNE, 1, (yyvsp[-1].pNodo)); }
#line 1710 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 148 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = (yyvsp[0].pNodo); }
#line 1716 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 149 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr('l', 2, (yyvsp[-1].pNodo), (yyvsp[0].pNodo)); }
#line 1722 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 153 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = (yyvsp[0].pNodo); }
#line 1728 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 154 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = (yyvsp[-2].pNodo); }
#line 1734 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 158 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(';', 2, NULL, NULL); }
#line 1740 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 159 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = (yyvsp[-1].pNodo); }
#line 1746 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 160 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr((yyvsp[-2].intval), 1, conv((yyvsp[-1].pSimb))); }
#line 1752 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 163 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(ABORTE, 0); }
#line 1758 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 164 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(SE, 2, (yyvsp[-3].pNodo), (yyvsp[0].pNodo)); }
#line 1764 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 165 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(SE, 3, (yyvsp[-5].pNodo), (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1770 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 166 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(ENQUANTO, 2, (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1776 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 167 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(PARA, 4, (yyvsp[-6].pNodo), (yyvsp[-4].pNodo), (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1782 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 168 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = (yyvsp[0].pNodo); }
#line 1788 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 172 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = (yyvsp[0].pNodo); }
#line 1794 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 173 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = conv((yyvsp[0].pSimb)); }
#line 1800 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 174 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr('=', 2, conv((yyvsp[-2].pSimb)), (yyvsp[0].pNodo)); }
#line 1806 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 175 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(PATTRIB, 2, conv((yyvsp[-2].pSimb)), (yyvsp[0].pNodo)); }
#line 1812 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 177 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(INCPOS, 1, conv((yyvsp[-1].pSimb))); }
#line 1818 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 178 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(INCPRE, 1, conv((yyvsp[0].pSimb))); }
#line 1824 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 179 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(DECPOS, 1, conv((yyvsp[-1].pSimb))); }
#line 1830 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 180 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(DECPRE, 1, conv((yyvsp[0].pSimb))); }
#line 1836 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 182 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(UPONT, 1, conv((yyvsp[0].pSimb))); }
#line 1842 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 183 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(UEND, 1, conv((yyvsp[0].pSimb))); }
#line 1848 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 185 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(UMENOS, 1, (yyvsp[0].pNodo)); }
#line 1854 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 186 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr('+', 2, (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1860 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 187 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr('-', 2, (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1866 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 188 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr('*', 2, (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1872 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 189 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr('/', 2, (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1878 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 190 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr('%', 2, (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1884 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 191 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(GE, 2, (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1890 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 192 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(LE, 2, (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1896 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 193 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(NE, 2, (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1902 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 194 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(EQ, 2, (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1908 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 195 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(GT, 2, (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1914 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 196 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(LT, 2, (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1920 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 197 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(E, 2, (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1926 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 198 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(OU, 2, (yyvsp[-2].pNodo), (yyvsp[0].pNodo)); }
#line 1932 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 199 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(NAO, 1, (yyvsp[0].pNodo)); }
#line 1938 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 200 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr('(', 1, (yyvsp[-1].pNodo)); }
#line 1944 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 201 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = (yyvsp[0].pNodo); }
#line 1950 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 205 "portugol.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[0].intval);    }
#line 1956 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 206 "portugol.y" /* yacc.c:1646  */
    { (yyval.intval) = NADA;  }
#line 1962 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 210 "portugol.y" /* yacc.c:1646  */
    { (yyval.intval) = INT;   }
#line 1968 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 211 "portugol.y" /* yacc.c:1646  */
    { (yyval.intval) = REAL;  }
#line 1974 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 212 "portugol.y" /* yacc.c:1646  */
    { (yyval.intval) = TEXTO; }
#line 1980 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 213 "portugol.y" /* yacc.c:1646  */
    { (yyval.intval) = PONTI; }
#line 1986 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 214 "portugol.y" /* yacc.c:1646  */
    { (yyval.intval) = PONTR; }
#line 1992 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 215 "portugol.y" /* yacc.c:1646  */
    { (yyval.intval) = PONTS; }
#line 1998 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 219 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = convtn(NADA); }
#line 2004 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 220 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr('l', 2, (yyvsp[-1].pNodo), (yyvsp[0].intval)); }
#line 2010 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 223 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = NULL; }
#line 2016 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 224 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr('l', 2, (yyvsp[-2].pNodo), (yyvsp[-1].intval)); }
#line 2022 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 249 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = conv((yyvsp[0].pSimb)); }
#line 2028 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 250 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = conv((yyvsp[0].pSimb)); }
#line 2034 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 251 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = conv((yyvsp[0].pSimb)); }
#line 2040 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 257 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(EXTERNA, 3, convtn((yyvsp[-5].intval)), conv((yyvsp[-4].pSimb)), (yyvsp[-2].pNodo)); }
#line 2046 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 260 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = NULL; }
#line 2052 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 261 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr('l', 2, (yyvsp[-1].pNodo), (yyvsp[0].pNodo)); }
#line 2058 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 266 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(FUNC, 1, conv((yyvsp[-2].pSimb))); }
#line 2064 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 267 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(FUNC, 2, conv((yyvsp[-3].pSimb)), (yyvsp[-1].pNodo)); }
#line 2070 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 268 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(FUNC, 3, conv((yyvsp[-5].pSimb)), (yyvsp[-3].pNodo), (yyvsp[-1].pNodo)); }
#line 2076 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 269 "portugol.y" /* yacc.c:1646  */
    { (yyval.pNodo) = opr(FUNC, 4, conv((yyvsp[-7].pSimb)), (yyvsp[-5].pNodo), (yyvsp[-3].pNodo), (yyvsp[-1].pNodo)); }
#line 2082 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2086 "y.tab.c" /* yacc.c:1646  */
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
#line 273 "portugol.y" /* yacc.c:1906  */


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
            ps->tipoD = tipoIdUndef;
            ps->idNome = strdup(nome);
            ps->pes=NULL;
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
            ps->pes=NULL;
            return ps;
        }
    }
    yyerror("Tabela de simbolos cheia!"); /* caso contrario */
    exit(1);
}

/* Acha/cria ConFloat e retorna o ponteiro para a TS */
tabelaSimb *achaDouble(float dv)
{
    char *p;
    tabelaSimb *ps;
    int i;

    for(ps=tabSimb; ps < &tabSimb[MAX_SIMB]; ps++)
    {
        if(ps->idNome && ps->dval==dv && ps->tipoD==tipoConDouble) /* encontrou ? */
            return ps; /* sim ! */
        if(!ps->idNome) /* ponteiro livre ? */
        {
            i=geraTC();
            ps->tipoD = tipoConDouble;
            ps->idNome = strdup("#ConDouble");
            ps->dval = dv;
            ps->idx = i;
            ps->pes=NULL;
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
            ps->pes=NULL;
            return ps;
        }
    }
    yyerror("Tabela de simbolos cheia!"); /* caso contrario */
    exit(1);
}



//tabelaSimb *achaFunc(char *id)
// {
//    tabelaSimb *ps = achaId(id);
//     char *p;
//
//     for(ps=tabSimb; ps < &tabSimb[MAX_SIMB]; ps++)
//     {
//         if(ps->idNome && !strcmp(ps->idNome, nome))
//             return ps;
//         if(!ps->idNome)
//         {
//            ps->tipoD = tipoIdUndef;
//            ps->idNome = strdup(nome);
//             return ps;
//         }
//     }
//    yyerror("Tabela de simbolos cheia!");
//    exit(1);
// }

/* Apenas procura (nao cria) TODAS funcoes, a partir da ultima procurada, ou NULL para a primeira */
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

/* Converte tipo em nodo */
nodo *convtn(int tipo)
{
    nodo *tn;
    //char *sTipoBase[8]={"tipoUndef", "tipoInt", "tipoDouble", "tipoStr", "tipoVoid", "tipoPointInt", "tipoPointDouble", "tipoPointStr"};

    if((tn=malloc(sizeof(nodo)))==NULL) /* aloca nodo */
        yyerror("Faltou memoria (cod. 1: convtn)");

    tn->linha = lineno;
    tn->tipoN = tipoTipo;
    tn->tt = tok2tb(tipo);
//    fprintf(stderr, "convtn tt %d=(s) \n", tn->tt);//, sTipoBase[tn->tt]);
    return tn;
}

/* Converte constante/identificador da TS em nodo */
nodo *conv(tabelaSimb *ps)
{
    nodo *tn;

    if((tn=malloc(sizeof(nodo)))==NULL) /* aloca nodo */
        yyerror("Faltou memoria (cod. 2: conv)");

    tn->linha = lineno;
    tn->tipoN = tipoSimb;
    tn->pSimb = ps;
    return tn;
}

/* Converte operador em nodo */
/* reticencias eh tipo (nodo*) */
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
    /* aponta para todos os seus nodos filhos: */
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

void carregaFuncoesPreTS(void)
{
    int paramTipo[MAX_PARAM];
    tabelaSimb *ps;

    ps=addIdEsc("imprima", &esco);
    paramTipo[0]=tipoStr;
    paramTipo[1]=tipoDouble;
    ps=addFunc("imprima", (void *)printf, "printf", 2, tipoIdFuncVoid, paramTipo);
    //ps->pes=&esco;

    ps=addIdEsc("leia", &esco);
    paramTipo[0]=tipoStr;
    paramTipo[1]=tipoDouble;
    ps=addFunc("leia", (void *)scanf, "scanf", 2, tipoIdFuncVoid, paramTipo);
    //ps->pes=&esco;

    ps=addIdEsc("saia", &esco);
    paramTipo[0]=tipoInt;
    ps=addFunc("saia", (void *)exit, "exit", 1, tipoIdFuncVoid, paramTipo);
    //ps->pes=&esco;

    ps=addIdEsc("raiz", &esco);
    paramTipo[0]=tipoDouble;
    ps=addFunc("raiz", (void *)sqrt, "sqrt", 1, tipoIdFuncDouble, paramTipo);
    //ps->pes=&esco;
}
