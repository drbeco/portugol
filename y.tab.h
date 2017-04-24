/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

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
    PRINCIPAL = 258,
    SE = 259,
    ENTAO = 260,
    SENAO = 261,
    INICIO = 262,
    FIM = 263,
    ENQUANTO = 264,
    ABORTE = 265,
    PARA = 266,
    RETORNE = 267,
    INT = 268,
    REAL = 269,
    TEXTO = 270,
    NADA = 271,
    FUNCAO = 272,
    EXTERNA = 273,
    FUNC = 274,
    DEFINE = 275,
    DEBUG = 276,
    ARVORE = 277,
    TABELA = 278,
    INC = 279,
    DEC = 280,
    INCPOS = 281,
    INCPRE = 282,
    DECPOS = 283,
    DECPRE = 284,
    PONT = 285,
    UPONT = 286,
    UEND = 287,
    PATTRIB = 288,
    PONTI = 289,
    PONTR = 290,
    PONTS = 291,
    IDENT = 292,
    INTCON = 293,
    REALCON = 294,
    TEXTOCON = 295,
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
#define PRINCIPAL 258
#define SE 259
#define ENTAO 260
#define SENAO 261
#define INICIO 262
#define FIM 263
#define ENQUANTO 264
#define ABORTE 265
#define PARA 266
#define RETORNE 267
#define INT 268
#define REAL 269
#define TEXTO 270
#define NADA 271
#define FUNCAO 272
#define EXTERNA 273
#define FUNC 274
#define DEFINE 275
#define DEBUG 276
#define ARVORE 277
#define TABELA 278
#define INC 279
#define DEC 280
#define INCPOS 281
#define INCPRE 282
#define DECPOS 283
#define DECPRE 284
#define PONT 285
#define UPONT 286
#define UEND 287
#define PATTRIB 288
#define PONTI 289
#define PONTR 290
#define PONTS 291
#define IDENT 292
#define INTCON 293
#define REALCON 294
#define TEXTOCON 295
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
#line 32 "portugol.y" /* yacc.c:1909  */

        tabelaSimb *pSimb;      /* yylval.pSimb ponteiro para o IDENT na TS */
        nodo *pNodo;            /* tipo do comando e expr */
        int intval;             /* valor do token para um dado tipo */

#line 160 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
