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
#line 30 "portugol.y" /* yacc.c:1909  */

        tabelaSimb *pSimb;      /* yylval.pSimb ponteiro para o IDENT na TS */
        nodo *pNodo;            /* tipo do comando e expr */

#line 151 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
