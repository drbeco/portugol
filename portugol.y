%{
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
char msg[80], *tmp;
int imaxts, imaxtc, imaxtf, imaxtp;
tabelaSimb *prox;
extern char *sTipoDado[];
//extern char *sTipoBase[];
int ta[MAX_PARAM];

%}

%union {
        tabelaSimb *pSimb;      /* yylval.pSimb ponteiro para o IDENT na TS */
        nodo *pNodo;            /* tipo do comando e expr */
        int intval;             /* valor do token para um dado tipo */
};

%token PRINCIPAL SE ENTAO SENAO INICIO FIM ENQUANTO ABORTE PARA RETORNE
%token INT REAL TEXTO NADA FUNCAO EXTERNA FUNC DEFINE
%token DEBUG ARVORE TABELA
%token INC DEC INCPOS INCPRE DECPOS DECPRE
%token PONT UPONT UEND PATTRIB
%token PONTI PONTR PONTS
%token <pSimb> IDENT INTCON REALCON TEXTOCON
 /* %token VAZIO */

%left INCPOS
%left OU
%left E
%left NAO
%left GE LE EQ NE GT LT
%left '='
%left '+' '-'
%left '*' '/' '%'
%left INCPRE
%nonassoc UPONT
%nonassoc UEND
%nonassoc UMENOS
%nonassoc ENTAO
%nonassoc SENAO

%type <pNodo> comando expr lista_comandos bloco_funcoes funcao principio constante subordinados_comandos retornar conjunto blocos
%type <intval> tipo
 /*preprocs*/
%%

programa:
    conjunto              {
                            //fprintf(yyout, "//    Gerado pelo compilador Portugol versao 3r\n");
                            //fprintf(yyout, "//    Autor: Ruben Carlo Benante\n");
                            //fprintf(yyout, "//    Email: rcb@beco.cc\n");
                            //fprintf(yyout, "//    Data: 23/05/2009, 10/03/2011\n");
                            //fprintf(yyout, "//    Compilado em: %s as %s\n\n", __DATE__, __TIME__);
                            cabecalhoMain[0]='\0';
                            strcpy(cabecalhoMain, "  loadfunc(tipoVoid, (void *)printf, \"imprima\", &tf[0], 2); /* funcao predefinida */\n  loadfunc(tipoVoid, (void *)scanf, \"leia\", &tf[1], 2); /* funcao predefinida */\n");
                            strcat(cabecalhoMain, "  loadfunc(tipoVoid, (void *)exit, \"saia\", &tf[2], 1); /* funcao predefinida */\n  loadfunc(tipoDouble, (void *)sqrt, \"raiz\", &tf[3], 1); /* funcao predefinida */\n");
                            //                 qres->dval=(*tf[idx].dfunc)(g[0]->dval); //sqrt(dval)
                            //addFunc("saia", (void *)exit, "exit" /*similar em c*/, 1/*num param*/, tipoIdFuncInt /*tipo de retorno e na TS*/, tipoConInt /*tipo arg*/);
                            //adiciona, substitui, ou cria! Criado por achaId
                            ta[0]=tipoStr;
                            ta[1]=tipoDouble;
                            addFunc("imprima", (void *)printf, "printf", 2, tipoIdFuncVoid, ta);
                            ta[0]=tipoStr;
                            ta[1]=tipoDouble;
                            addFunc("leia", (void *)scanf, "scanf", 2, tipoIdFuncVoid, ta);
                            ta[0]=tipoInt;
                            addFunc("saia", (void *)exit, "exit", 1, tipoIdFuncVoid, ta);
                            ta[0]=tipoDouble;
                            addFunc("raiz", (void *)sqrt, "sqrt", 1, tipoIdFuncDouble, ta);
                            tipoRet=tipoUndef; /*escopo da funcao atual*/
                            //fprintf(stderr, "gera_quad antes\n");
                            pass1($1, 0);
                            gera_quad($1,0);
                            //fprintf(stderr, "gera_quad depois: saida.h\n");
                            liberaNodo($1);
                            return 0;
                         }
    ;


conjunto:
     preprocs blocos principio             { $$ = opr(INICIO, 2, $2, $3); }
/*      preprocs blocos                      { $$ = opr(INICIO, 1, $2); } */
     ;

preprocs: /* nada */
        | preprocs preproc
/*        | preproc preproc */
        ;

preproc:
        DEBUG ARVORE                      { debugArvore = 1; }
        | DEBUG TABELA                    { debugTabela = 1; }
        ;

blocos: /* nada */                        { $$ = NULL; /*opr(VAZIO, 0);*/ }
    | blocos bloco_funcoes
                                          {
                                            $$ = opr('l', 2, $1, $2);
                                            //fprintf(yyout, "  nop(NULL,NULL,NULL);\t/* 160.y no operation */\n}\n"); /* fecha chave do main */
                                          } /* l para lista de comandos */
    ;

bloco_funcoes:
    tipo IDENT '(' tipo ')' INICIO ';' lista_comandos FIM ';'
                          {
                            //fprintf(stderr, "tipo%d %s ( tipo%d );\n", $1, $2->idNome, $4 );
                            $$ = opr($1, 3, conv($2), convtn($4), $8);  /* como comparar o retorno com o tipo? comparar tipo $1 com $9*/
                            //fprintf(yyout, "  nop(NULL,NULL,NULL);\t/* no operation */\n} /* close function */\n"); /* fecha chave da funcao */
                          } /* nop()\n} */
    | tipo IDENT '(' tipo ',' tipo ')' INICIO ';' lista_comandos FIM ';'
                          {
                            $$ = opr($1, 4, conv($2), convtn($4), convtn($6), $10);
                            //fprintf(yyout, "  nop(NULL,NULL,NULL);\t/* no operation */\n} /* close function */\n"); /* fecha chave da funcao */
                          } /* nop()\n} */
    | tipo IDENT '(' tipo ',' tipo ',' tipo ')' INICIO ';' lista_comandos FIM ';'
                          {
                            $$ = opr($1, 5, conv($2), convtn($4), convtn($6), convtn($8), $12);
                            //fprintf(yyout, "  nop(NULL,NULL,NULL);\t/* no operation */\n} /* close function */\n"); /* fecha chave da funcao */
                          } /* nop()\n} */
    ;

principio:
    INT PRINCIPAL '(' tipo ')' INICIO ';' lista_comandos FIM ';'
                          {
                            //fprintf(stderr, "linha 183.y : int main(void)\n");
                            /*fprintf(yyout, "{\n  filltf();\n\n");*/
                            $$ = opr(INT, 2, convtn($4), $8);
                          }
    ;

retornar:
    RETORNE ';'                 {$$ = opr(RETORNE, 0); }
    | RETORNE expr ';'          {$$ = opr(RETORNE, 1, $2); }
    ;

lista_comandos:
    comando                     { $$ = $1; }
    | lista_comandos comando    { $$ = opr('l', 2, $1, $2); } /* l para lista de comandos */
    ;

subordinados_comandos:
    comando                             {$$ = $1; }
    | INICIO ';' lista_comandos FIM ';' {$$ = $3; }

comando:
        ';' /* nop ; */         { $$ = opr(';', 2, NULL, NULL); }
        | expr ';'              { $$ = $1; }
        /*| INT IDENT ';'         { $$ = opr(INT, 1, conv($2)); }
        | REAL IDENT ';'        { $$ = opr(REAL, 1, conv($2)); }
        | TEXTO IDENT ';'       { $$ = opr(TEXTO, 1, conv($2)); }
        | PONT INT IDENT ';'    { $$ = opr(PONTI, 1, conv($3)); }
        | PONT REAL IDENT ';'   { $$ = opr(PONTR, 1, conv($3)); }
        | PONT TEXTO IDENT ';'  { $$ = opr(PONTS, 1, conv($3)); }*/
        | tipo IDENT ';'             { $$ = opr($1, 1, conv($2)); }
        /* | PONT tipo IDENT ';'        { $$ = opr(PONTI, 2, $2, conv($3)); } */
        /*| INT IDENT '(' ')' ';'         { $$ = opr(INT, 1, conv($2)); }
        | REAL IDENT '(' ')' ';'        { $$ = opr(REAL, 1, conv($2)); }
        | TEXTO IDENT '(' ')' ';'       { $$ = opr(TEXTO, 1, conv($2)); }
        | PONT INT IDENT '(' ')' ';'    { $$ = opr(PONTI, 1, conv($3)); }
        | PONT REAL IDENT '(' ')' ';'   { $$ = opr(PONTR, 1, conv($3)); }
        | PONT TEXTO IDENT '(' ')' ';'  { $$ = opr(PONTS, 1, conv($3)); }*/
        //| IMPORTE REAL IDENT '(' REAL ')' ';' { $$ = opr(IMPORTE, 1, conv($3)); }
        | ABORTE ';'                                                              { $$ = opr(ABORTE, 0); }
        | SE '(' expr ')' ENTAO subordinados_comandos                             { $$ = opr(SE, 2, $3, $6); }
        | SE '(' expr ')' ENTAO subordinados_comandos SENAO subordinados_comandos { $$ = opr(SE, 3, $3, $6, $8); }
        | ENQUANTO '(' expr ')' subordinados_comandos                             { $$ = opr(ENQUANTO, 2, $3, $5); }
        // | PARA '(' comando expr ';' comando ')' comando  { $$ = opr(PARA, 4, $3, $4, $6, $8); }
        | PARA '(' expr ';' expr ';' expr ')' subordinados_comandos               { $$ = opr(PARA, 4, $3, $5, $7, $9); }
        | retornar                                                                { $$ = $1; }
        /* defuncoes: */
        /* | defuncao               { $$ = $1; } */
        /* | defuncoes defuncao     { $$ = opr('f', 2, $1, $2); }  f para lista de comandos */
        /* |  nada */
        /* | funcao                                         { $$ = opr(FUNC,  ---> esta em expr*/
        /* | bloco_comandos                                 { $$ = $1; } */
        /* | lista_comandos                                 { $$ = $1; } */
        ;

expr:
    constante                   { $$ = $1; }
    | IDENT                     { $$ = conv($1); }
    | IDENT '=' expr            { $$ = opr('=', 2, conv($1), $3); }
    | '*' IDENT '=' expr        { $$ = opr(PATTRIB, 2, conv($2), $4); }
    //incremento decremento
    | IDENT INC                 { $$ = opr(INCPOS, 1, conv($1)); }
    | INC IDENT                 { $$ = opr(INCPRE, 1, conv($2)); }
    | IDENT DEC                 { $$ = opr(DECPOS, 1, conv($1)); }
    | DEC IDENT                 { $$ = opr(DECPRE, 1, conv($2)); }
    //  Ponteiros
    | '*' IDENT %prec UPONT     { $$ = opr(UPONT, 1, conv($2)); }
    | '&' IDENT %prec UEND      { $$ = opr(UEND, 1, conv($2)); }
    // Expressoes matematicas e logicas
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
    | funcao                    { $$ = $1; }
    ;

tipo:
    INT                         { $$ = INT;   }
    | REAL                      { $$ = REAL;  }
    | TEXTO                     { $$ = TEXTO; }
    | PONT INT                  { $$ = PONTI; }
    | PONT REAL                 { $$ = PONTR; }
    | PONT TEXTO                { $$ = PONTS; }
    | NADA                      { $$ = NADA;  }
    ;

constante:
    INTCON                      { $$ = conv($1); }
    | REALCON                   { $$ = conv($1); }
    | TEXTOCON                  { $$ = conv($1); }
    ;


    /* definicao do prototipo da funcao */
/* funcaoexterna:
    | EXTERNA tipo IDENT '(' tipo ')' ';'              { $$ = opr(EXTERNA, 3, $2, conv($3), $5); }
    | EXTERNA tipo IDENT '(' tipo ',' tipo ')' ';'   { $$ = opr(EXTERNA, 4, $2, conv($3), $5, $7); }
    ;
*/

 /*defuncaoargs:
    tipo IDENT '(' lista_args ')' ';'
    ;
 lista_args:
    | lista_arg1
    |
    ;
 lista_arg1:
    tipo
    | tipo ',' lista_arg1                    { $$ = opr($ ??????
    ; */

 /* chamada da funcao */
funcao:
    IDENT '(' ')'                            { $$ = opr(FUNC, 1, conv($1)); }
    | IDENT '(' expr ')'                     { $$ = opr(FUNC, 2, conv($1), $3); }
    | IDENT '(' expr ',' expr ')'            { $$ = opr(FUNC, 3, conv($1), $3, $5); }
    | IDENT '(' expr ',' expr ',' expr ')'   { $$ = opr(FUNC, 4, conv($1), $3, $5, $7); }
    ;
%%

/* Acha variavel (nao funcoes) (nao cria) Id pelo seu IDX */
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

    if((tn=malloc(sizeof(nodo)))==NULL) /* aloca nodo */
        yyerror("Faltou memoria (cod. 1: convtn)");

    tn->linha = lineno;
    tn->tipoN = tipoTipo;
    tn->tt = tok2tb(tipo);
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
