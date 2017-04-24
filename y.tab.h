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
    SE = 258,
    ENTAO = 259,
    SENAO = 260,
    INICIO = 261,
    FIM = 262,
    IMPRIMA = 263,
    LEIA = 264,
    ENQUANTO = 265,
    ABORTE = 266,
    SAIA = 267,
    PARA = 268,
    INT = 269,
    REAL = 270,
    TEXTO = 271,
    DEFINE = 272,
    IMPORTE = 273,
    FUNC = 274,
    DEBUG = 275,
    ARVORE = 276,
    TABELA = 277,
    IDENT = 278,
    INTCON = 279,
    REALCON = 280,
    TEXTOCON = 281,
    OU = 282,
    E = 283,
    NAO = 284,
    GE = 285,
    LE = 286,
    EQ = 287,
    NE = 288,
    GT = 289,
    LT = 290,
    UMENOS = 291
  };
#endif
/* Tokens.  */
#define SE 258
#define ENTAO 259
#define SENAO 260
#define INICIO 261
#define FIM 262
#define IMPRIMA 263
#define LEIA 264
#define ENQUANTO 265
#define ABORTE 266
#define SAIA 267
#define PARA 268
#define INT 269
#define REAL 270
#define TEXTO 271
#define DEFINE 272
#define IMPORTE 273
#define FUNC 274
#define DEBUG 275
#define ARVORE 276
#define TABELA 277
#define IDENT 278
#define INTCON 279
#define REALCON 280
#define TEXTOCON 281
#define OU 282
#define E 283
#define NAO 284
#define GE 285
#define LE 286
#define EQ 287
#define NE 288
#define GT 289
#define LT 290
#define UMENOS 291

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 28 "portugol.y" /* yacc.c:1909  */

        tabelaSimb *pSimb;      /* yylval.pSimb ponteiro para o IDENT na TS */
        nodo *pNodo;            /* tipo do comando e expr */

#line 131 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
