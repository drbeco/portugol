%{
/*
    Compilador PORTUGOL v.1.1
    Autor: Ruben Carlo Benante
    Email: benante@gmail.com
    Data: 23/04/2009
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "portugol.h"

/* prototipos */

tipoNodo *opr(int oper, int nops, ...);
tipoNodo *id(int i, nodoEnum typenode);
tipoNodo *conf(float fvalue);
void liberaNodo(tipoNodo *p);

%}

%union {
        float floatval; /* yylval.floatval tipo do FLUTUANTE */
        tipoNodo *nPtr; /* tipo do comando e expr */
        int varno;      /* yylval.varno tipo do ID */
}

%token SE ENTAO SENAO IMPRIMA INICIO FIM
%token <varno> ID
%token <floatval> FLUTUANTE

%left OU
%left E
%left NAO
%left GE LE EQ NE GT LT
%left '+' '-'
%left '*' '/'
%nonassoc UMENOS
%nonassoc ENTAO
%nonassoc SENAO

%type <nPtr> comando expr lista_comandos bloco_comandos

%%

programa:
    funcao  { return 0; }
    ;

funcao:
    funcao bloco_comandos       { gerac($2,0); liberaNodo($2); }
    | /* vazio */
    ;

bloco_comandos:
    INICIO ';' lista_comandos FIM ';'             { $$ = opr(INICIO, 1, $3); }
    ;

lista_comandos:
    comando                  { $$ = $1; }
    | lista_comandos comando { $$ = opr('l', 2, $1, $2); } /* l para lista de comandos */
    ;

comando:
        ';' /* nop ; */                                 { $$ = opr(';', 2, NULL, NULL); }
        | ID '=' expr ';'                               { $$ = opr('=', 2, id($1, tipoID), $3); }
        | SE '(' expr ')' ENTAO comando                 { $$ = opr(SE, 2, $3, $6); }
        | SE '(' expr ')' ENTAO comando SENAO comando   { $$ = opr(SE, 3, $3, $6, $8); }
        | IMPRIMA expr ';'                              { $$ = opr(IMPRIMA, 1, $2); }
        | bloco_comandos                                { $$ = $1; }
        ;

expr:
    FLUTUANTE                   { $$ = conf($1); }
    | ID                        { $$ = id($1, tipoID); }
    | '-' expr %prec UMENOS     { $$ = opr(UMENOS, 1, $2); }
    | expr '+' expr             { $$ = opr('+', 2, $1, $3); }
    | expr '-' expr             { $$ = opr('-', 2, $1, $3); }
    | expr '*' expr             { $$ = opr('*', 2, $1, $3); }
    | expr '/' expr             { $$ = opr('/', 2, $1, $3); }
    | expr GE expr              { $$ = opr(GE, 2, $1, $3); }
    | expr LE expr              { $$ = opr(LE, 2, $1, $3); }
    | expr NE expr              { $$ = opr(NE, 2, $1, $3); }
    | expr EQ expr              { $$ = opr(EQ, 2, $1, $3); }
    | expr GT expr              { $$ = opr(GT, 2, $1, $3); }
    | expr LT expr              { $$ = opr(LT, 2, $1, $3); }
    | expr E expr               { $$ = opr(E, 2, $1, $3); }
    | expr OU expr              { $$ = opr(OU, 2, $1, $3); }
    | NAO expr                  { $$ = opr(NAO, 1, $2); }
    | '(' expr ')'              { $$ = opr('(', 1, $2); }
    ;

%%

/* Converte constante flutuante em tipoNodo */
tipoNodo *conf(float valor)
{
    tipoNodo *p;

    if((p=malloc(sizeof(fconTipoNodo)))==NULL) /* aloca nodo */
        yyerror("Faltou memoria (cod. 1)");
    p->tipo = tipoConFlutuante;
    p->fcon.fval = valor;
    return p;
}

/* Converte identificador do tipo tipoenum em tipoNodo */
tipoNodo *id(int i, nodoEnum tipoenum)
{
    tipoNodo *p;

    if((p=malloc(sizeof(idTipoNodo)))==NULL) /* aloca nodo */
        yyerror("Faltou memoria (cod. 2)");
    p->tipo = tipoenum;
    p->id.i = i;
    return p;
}

/* Converte operador em tipoNodo */
tipoNodo *opr(int oper, int nops, ...)
{
    va_list ap;
    tipoNodo *p;
    size_t tam;
    int i;

    tam = sizeof(oprTipoNodo) + (nops - 1) * sizeof(tipoNodo*);
    if((p=malloc(tam))==NULL) /* aloca nodo */
        yyerror("Faltou memoria (cod. 3)");

    p->tipo = tipoOpr;
    p->opr.oper = oper;
    p->opr.nops = nops;
    va_start(ap, nops);
    for(i=0; i<nops; i++)
        p->opr.op[i] = va_arg(ap, tipoNodo*);
    va_end(ap);
    return p;
}

/* Libera memoria de um nodo tipoNodo */
void liberaNodo(tipoNodo *p)
{
    int i;

    if(!p)
        return;
    if(p->tipo == tipoOpr)
    {
        for(i=0; i<p->opr.nops; i++)
            liberaNodo(p->opr.op[i]);
    }
    free(p);
}
