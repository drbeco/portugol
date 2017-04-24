%{
/*
    Compilador PORTUGOL v.2q
    Autor: Ruben Carlo Benante
    Email: benante@gmail.com
    Data criação: 23/04/2009
    Data modificação: 24/05/2009
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

%}

%union {
        tabelaSimb *pSimb;      /* yylval.pSimb ponteiro para o IDENT na TS */
        nodo *pNodo;            /* tipo do comando e expr */
};

%token SE ENTAO SENAO INICIO FIM IMPRIMA LEIA ENQUANTO ABORTE SAIA PARA
%token INT REAL TEXTO DEFINE IMPORTE FUNC
%token DEBUG ARVORE TABELA
%token <pSimb> IDENT INTCON REALCON TEXTOCON

%left OU
%left E
%left NAO
%left GE LE EQ NE GT LT
%left '+' '-'
%left '*' '/' '%'
%nonassoc UMENOS
%nonassoc ENTAO
%nonassoc SENAO

%type <pNodo> comando expr lista_comandos bloco_comandos

%%

programa:
    bloco_comandos       {
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
                                        fprintf(yyout, "  tf[%d].ifunc=%s;\n", prox->idx, prox->idFunc);
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
                            gera_quad($1,0);
                            liberaNodo($1);

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
    ;

bloco_comandos:
    preprocs INICIO ';' lista_comandos FIM ';'             { $$ = opr(INICIO, 1, $4); }
    ;

preprocs:
        preproc
        | preproc preproc
        | /* nada */
        ;

preproc:
        DEBUG ARVORE                                       { debugArvore = 1; }
        | DEBUG TABELA                                     { debugTabela = 1; }
        ;

lista_comandos:
    comando                  { $$ = $1; }
    | lista_comandos comando { $$ = opr('l', 2, $1, $2); } /* l para lista de comandos */
    ;

comando:
        ';' /* nop ; */         { $$ = opr(';', 2, NULL, NULL); }
        | expr ';'              { $$ = $1; }
        | INT IDENT ';'         { $$ = opr(INT, 1, conv($2)); }
        | REAL IDENT ';'        { $$ = opr(REAL, 1, conv($2)); }
        | TEXTO IDENT ';'       { $$ = opr(TEXTO, 1, conv($2)); }
        | SE '(' expr ')' ENTAO comando                  { $$ = opr(SE, 2, $3, $6); }
        | SE '(' expr ')' ENTAO comando SENAO comando    { $$ = opr(SE, 3, $3, $6, $8); }
        | ENQUANTO '(' expr ')' comando                  { $$ = opr(ENQUANTO, 2, $3, $5); }
        | PARA '(' comando expr ';' comando ')' comando  { $$ = opr(PARA, 4, $3, $4, $6, $8); }
        | ABORTE ';'                                     { $$ = opr(ABORTE, 0); }
        | IMPRIMA expr ';'                               { $$ = opr(IMPRIMA, 1, $2); }
        | LEIA IDENT ';'                                 { $$ = opr(LEIA, 1, conv($2)); }
        | SAIA expr ';'                                  { $$ = opr(SAIA, 1, $2); }
        | bloco_comandos                                 { $$ = $1; }
        ;

expr:
    INTCON                      { $$ = conv($1); }
    | REALCON                   { $$ = conv($1); }
    | TEXTOCON                  { $$ = conv($1); }
    | IDENT                     { $$ = conv($1); }
    | IDENT '=' expr            { $$ = opr('=', 2, conv($1), $3); }
    | IDENT '(' expr ')'        { $$ = opr(FUNC, 2, conv($1), $3); }
    | '-' expr %prec UMENOS     { $$ = opr(UMENOS, 1, $2); }
    | expr '+' expr             { $$ = opr('+', 2, $1, $3); }
    | expr '-' expr             { $$ = opr('-', 2, $1, $3); }
    | expr '*' expr             { $$ = opr('*', 2, $1, $3); }
    | expr '/' expr             { $$ = opr('/', 2, $1, $3); }
    | expr '%' expr             { $$ = opr('%', 2, $1, $3); }
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
