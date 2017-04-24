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
#line 33 "portugol.y" /* yacc.c:1909  */

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
