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
char msg[120], *tmp;
//int imaxts, imaxtc, imaxtf, imaxtp;
tabelaSimb *ps;
extern char *sTipoDado[];
//extern char *sTipoBase[];
int ta[MAX_PARAM];
extern int indente;

%}

%union {
        tabelaSimb *pSimb;      /* yylval.pSimb ponteiro para o IDENT na TS */
        nodo *pNodo;            /* tipo do comando e expr */
        int intval;             /* valor do token para um dado tipo */
};

%token SE ENTAO SENAO INICIO FIM ENQUANTO ABORTE PARA RETORNE
%token INT REAL TEXTO NADA FUNCAO EXTERNA FUNC DEFINE
%token DEBUG ARVORE TABELA
%token INC DEC INCPOS INCPRE DECPOS DECPRE
%token PONT UPONT UEND PATTRIB
%token PONTI PONTR PONTS
%token <pSimb> IDENT INTCON REALCON TEXTOCON PRINCIPAL
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
%type <pNodo> funcaoexterna lista_funcaoexterna lista_tipos meio_vtipos
%type <intval> vtipo ftipo
//%type <pNodo> declaracao
//%type <pNodo> lista_declaracao meio_declaracao
//%type <pNodo> lista_args meio_args
//%type <pNodo> lista_expr meio_expr

%%

programa:
    conjunto              {
                            //fprintf(yyout, "//    Gerado pelo compilador Portugol versao 3r\n");
                            carregaFuncoesPreTS();
                            //void printNodo(nodo *tn, int n, char *var)
                            printNodo($1, 0, "$1");
                            //printf("->opr.oper='%s'\n", token($1->opr.ptn[0]->opr.oper));
                            if($1->opr.ptn[0]!=NULL);
                                printf("->opr.oper=%d\n", $1->opr.ptn[0]->opr.oper);

                            fprintf(stderr, "pass 2... (geracao de arvore de escopo)\n");
                            exit(0);
                            pass2($1, &esco, 0); //novo passo, para retirar informacoes de indentacao e escopo
                            fprintf(stderr, "pass 3... (analise semantica e geracao de codigo)\n");
                            pass3($1,0); //pass3, geracao de codigo
                            //printTS();
                            fprintf(stderr, "pass 1, pass 2, pass 3. Compilado com sucesso\n");
                            //pass3c($1,0); //pass3, geracao de codigo
                            //fprintf(stderr, "gera_quad depois: saida.h\n");
                            liberaNodo($1);
                            return 0;
                         }
    ;


conjunto:
     preprocs lista_funcaoexterna blocos principio             { $$ = opr(INICIO, 2, $2, $3); }
     ;

preprocs: /* nada */
        | preprocs preproc
/*        | preproc preproc */
        ;

preproc:
        DEBUG ARVORE                      { debugArvore = 1; }
        | DEBUG TABELA                    { debugTabela = 1; }
        ;

blocos: /* nada */                        { $$ = NULL; }
    | blocos bloco_funcoes
                                          { $$ = opr('l', 2, $1, $2); }
    ;

bloco_funcoes:
    ftipo IDENT '(' NADA ')' INICIO ';' lista_comandos FIM ';'
                                    { $$ = opr($1, 2, conv($2), $8); }
    | ftipo IDENT '(' vtipo IDENT ')' INICIO ';' lista_comandos FIM ';'
                                    { $$ = opr($1, 4, conv($2), convtn($4), conv($5), $9); }
    | ftipo IDENT '(' vtipo IDENT ',' vtipo IDENT ')' INICIO ';' lista_comandos FIM ';'
                                    { $$ = opr($1, 6, conv($2), convtn($4), conv($5), convtn($7), conv($8), $12); }
    | ftipo IDENT '(' vtipo IDENT ',' vtipo IDENT ',' vtipo IDENT ')' INICIO ';' lista_comandos FIM ';'
                                    { $$ = opr($1, 8, conv($2), convtn($4), conv($5), convtn($7), conv($8), convtn($10), conv($11), $15); }
/*     | ftipo IDENT '(' declaracao ')' INICIO ';' lista_comandos FIM ';' */
/*                                     { $$ = opr($1, 3, conv($2), $4, $8); } */
/*     | ftipo IDENT '(' declaracao ',' declaracao ')' INICIO ';' lista_comandos FIM ';' */
/*                                     { $$ = opr($1, 4, conv($2), $4, $6, $10); } */
/*     | ftipo IDENT '(' declaracao ',' declaracao ',' declaracao ')' INICIO ';' lista_comandos FIM ';' */
/*                                     { $$ = opr($1, 5, conv($2), $4, $6, $8, $12); } */
//    | ftipo IDENT '(' lista_args ')' INICIO ';' lista_comandos FIM ';'
//                                    { $$ = opr($1, 3, conv($2), $4, $8); }
    ;

principio:
   INT PRINCIPAL '(' NADA ')' INICIO ';' lista_comandos FIM ';'
                                    { $$ = opr(PRINCIPAL, 2, conv($2), $8); }
    | INT PRINCIPAL '(' vtipo IDENT ')' INICIO ';' lista_comandos FIM ';'
                                    { $$ = opr(PRINCIPAL, 4, conv($2), convtn($4), conv($5), $9); }
    | INT PRINCIPAL '(' vtipo IDENT ',' vtipo IDENT ')' INICIO ';' lista_comandos FIM ';'
                                    { $$ = opr(PRINCIPAL, 6, conv($2), convtn($4), conv($5), convtn($7), conv($8), $12); }
/*     | INT PRINCIPAL '(' declaracao ')' INICIO ';' lista_comandos FIM ';' */
/*                                     { $$ = opr(PRINCIPAL, 3, conv($2), $4, $8); } */
/*     | INT PRINCIPAL '(' declaracao ',' declaracao ')' INICIO ';' lista_comandos FIM ';' */
/*                                     { $$ = opr(PRINCIPAL, 4, conv($2), $4, $6, $10); } */
    ;

retornar:
    RETORNE ';'                 { $$ = opr(RETORNE, 0); }
    | RETORNE expr ';'          { $$ = opr(RETORNE, 1, $2); }
    ;

lista_comandos:
    comando                     { $$ = $1; }
    | lista_comandos comando    { $$ = opr('l', 2, $1, $2); } /* l para lista de comandos */
    ;

subordinados_comandos:
    comando                             { $$ = $1; }
    | INICIO ';' lista_comandos FIM ';' { $$ = $3; }
    ;

comando:
        ';' /* nop ; */                                                           { $$ = opr(';', 2, NULL, NULL); }
        | expr ';'                                                                { $$ = $1; }
        | vtipo IDENT';'                                                          { $$ = opr($1, 1, conv($2)); }
//        | declaracao ';'                                                          { $$=$1; }
//        | lista_declaracao ';'                                                    { $$=$1; } //$$ = opr($1, 1, conv($2)); }
        | ABORTE ';'                                                              { $$ = opr(ABORTE, 0); }
        | SE '(' expr ')' ENTAO subordinados_comandos                             { $$ = opr(SE, 2, $3, $6); }
        | SE '(' expr ')' ENTAO subordinados_comandos SENAO subordinados_comandos { $$ = opr(SE, 3, $3, $6, $8); }
        | ENQUANTO '(' expr ')' subordinados_comandos                             { $$ = opr(ENQUANTO, 2, $3, $5); }
        | PARA '(' expr ';' expr ';' expr ')' subordinados_comandos               { $$ = opr(PARA, 4, $3, $5, $7, $9); }
        | retornar                                                                { $$ = $1; }
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

ftipo:
    vtipo                       { $$ = $1;    }
    | NADA                      { $$ = NADA;  }
    ;

vtipo:
    INT                         { $$ = INT;   }
    | REAL                      { $$ = REAL;  }
    | TEXTO                     { $$ = TEXTO; }
    | PONT INT                  { $$ = PONTI; }
    | PONT REAL                 { $$ = PONTR; }
    | PONT TEXTO                { $$ = PONTS; }
    ;

lista_tipos:
    NADA                        { $$ = convtn(NADA); }
    | meio_vtipos vtipo         { $$ = opr('l', 2, $1, $2); }
    ;

meio_vtipos: /* vazio */        { $$ = NULL; }
    | meio_vtipos vtipo ','     { $$ = opr('l', 2, $1, $2); }
    ;

/*declaracao:
    vtipo IDENT                 { $$ = opr($1, 1, conv($2)); }
    ;*/

/*lista_args:
    NADA                        { $$ = convtn(NADA); }
    | meio_args declaracao      { $$ = opr('l', 2, $1, $2); }
    ;

meio_args: / vazio /          { $$ = NULL; }
    | meio_args declaracao ','  { $$ = opr('l', 2, $1, $2); }
    ;*/

/* lista_declaracao:
    vtipo meio_declaracao IDENT  { $$ = opr('l', 2, $1, conv($2); }
    ;

meio_declaracao: / vazio /    { $$ =  NULL; }
    | meio_declaracao IDENT ',' { $$ = opr('l', 2, $1, conv($2); }
    ;*/

constante:
    INTCON                         { $$ = conv($1); }
    | REALCON                      { $$ = conv($1); }
    | TEXTOCON                     { $$ = conv($1); }
    ;

  /* definicao do prototipo da funcao */
/*  sprintf(cabecalhoMain, "%s  loadfunc(tipoVoid, (void *)printf, \"imprima\", &tf[%d], 2);\n", cabecalhoMain, ps->idx); */
funcaoexterna:
    EXTERNA ftipo IDENT '(' lista_tipos ')' ';'  { $$ = opr(EXTERNA, 3, convtn($2), conv($3), $5); }
    ;

lista_funcaoexterna: /* vazio */            { $$ = NULL; }
    | lista_funcaoexterna funcaoexterna     { $$ = opr('l', 2, $1, $2); }
    ;

 /* chamada da funcao */
funcao:
    IDENT '(' ')'                           { $$ = opr(FUNC, 1, conv($1)); }
    | IDENT '(' expr ')'                    { $$ = opr(FUNC, 2, conv($1), $3); }
    | IDENT '(' expr ',' expr ')'           { $$ = opr(FUNC, 3, conv($1), $3, $5); }
    | IDENT '(' expr ',' expr ',' expr ')'  { $$ = opr(FUNC, 4, conv($1), $3, $5, $7); }
/*     IDENT '(' lista_expr ')'              { $$ = opr(FUNC, 2, conv($1), $3); } */
    ;

%%

/* Acha (nao cria) Id pelo seu IDX */
tabelaSimb *achaIdx(int i)
{
//    char *p;
    tabelaSimb *ps;
//    int t1;

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
//    char *p;
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
//    char *p;
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
//    char *p;
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
//    char *p;
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
//    char *p;
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
