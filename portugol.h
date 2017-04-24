/*
    Compilador PORTUGOL v.3q
    Autor: Ruben Carlo Benante
    Email: benante@gmail.com
    Data criação: 23/04/2009
    Data modificação: 25/05/2009
*/

#ifndef _PORTUGOL_H_
#define _PORTUGOL_H_

#define MAX_SIMB 200
#define MAX_SVAL 128
#define MAX_PARAM 3

/* MAX_CABECA = 100 por funcao */
#define MAX_CABECA 2000

/* escopo ----------------------- */

typedef struct esc
{
    int e;                /* este escopo. Zero: invalido. Um: global. */
    struct lesc *lsons;    /* cabeca da lista filhos */
    struct esc *efather;   /* elemento pai */
} escopo;

typedef struct lesc
{
    escopo *eson;            /* dado: este filho */
    struct lesc *lbrother;   /* ponteiro para o proximo irmao, se houver */
} listesc;

extern escopo esco;

/* Tipos de Dados da Tabela de Simbolos */
//char *sTipoDado[18]={"tipoIdUndef", "tipoConInt", "tipoConDouble", "tipoConStr", "tipoIdInt", "tipoIdDouble", "tipoIdStr", "tipoIdPointInt", "tipoIdPointDouble", "tipoIdPointStr", "tipoIdFuncInt", "tipoIdFuncDouble", "tipoIdFuncStr", /*"tipoIdFuncChar", */ "tipoIdFuncVoid", "tipoIdFuncPVoid", "tipoIdFuncPointInt", "tipoIdFuncPointDouble", "tipoIdFuncPointStr"};
typedef enum
{
    tipoIdUndef,

    tipoConInt,
    tipoConDouble,
    tipoConStr,

    tipoIdInt,
    tipoIdDouble,
    tipoIdStr,
    tipoIdPointInt,
    tipoIdPointDouble,
    tipoIdPointStr,

    tipoIdFuncInt,
    //tipoIdFuncFloat,
    tipoIdFuncDouble,
    //tipoIdFuncChar,
    tipoIdFuncStr,
    tipoIdFuncVoid,

    tipoIdFuncPointVoid,
    tipoIdFuncPointInt,
    tipoIdFuncPointDouble,
    tipoIdFuncPointStr

} tipoDado;

/* Tipos de Base */
//char *sTipoBase[8]={"tipoUndef", "tipoInt", "tipoDouble", "tipoStr", "tipoVoid", "tipoPointInt", "tipoPointDouble", "tipoPointStr"};
typedef enum
{
    tipoUndef,
    tipoInt,
    tipoDouble,
    tipoStr,
    tipoVoid,
    tipoPointInt,
    tipoPointDouble,
    tipoPointStr,
} tipoBase;

/* Tipos de Nodos */
typedef enum
{
    tipoSimb,
    tipoOper,
    tipoTipo
} tipoNodo;

/* tabela de simbolos */
typedef struct //uTabela
{
      tipoDado tipoD;       //tipo do dado ou retorno da funcao
      tipoDado tipoRetNovo; //tipo de retorno da funcao portugol caso nao coincida com o tipo definido em C
      int idx;              //ts[idx], tc[idx] ou tf[idx]. Para tf[], se acha o idx em um laco de busca, pelo nome
      int uso;              //verdadeiro se ja usou (ja carregou com load)
      char *idNome;         //nome da variavel ou funcao em Portugol
      char *idFunc;         //nome da funcao em C
      int numPar;           //numero de parametros da funcao
      tipoBase tipoParam[MAX_PARAM]; /* o tipo de cada parametro da funcao (), (t,t) ou (t,t,t) */
      int ival;             //valor da constante inteira
      float dval;           //valor da constante real
      char sval[MAX_SVAL];  //valor da constante texto
      int formatadoSval;    //verdadeiro se sval serve para formato do printf
      int (*ifunc)();       //ponteiro para funcao que retorna inteiro
      //int (*i2func)(const char *, ...);            //bug2------ponteiro para funcao que retorna inteiro
      //float (*ffunc)();     //ponteiro para funcao que retorna float
      double (*dfunc)();      //ponteiro para funcao que retorna double
      char *(*sfunc)();       //ponteiro para funcao que retorna ponteiro para char
      void (*vfunc)();        //ponteiro para a funcao que retorna void
      escopo *pes;             //ponteiro para no da arvore de escopo deste simbolo
} tabelaSimb;

/* operadores */
typedef struct
{
    tipoBase tipoBOper;    /* apos executado, seu tipo de retorno */
    int oper;              /* o operador */
    int nops;              /* numero de operandos */
    struct uNodo *ptn[1];  /* [MAX_OPER]; os operandos (expansivel) tam = sizeof(nodo) + (nops - 1) * sizeof(nodo *); */
} nodoOper;

/* Nodo */
typedef struct uNodo
{
    int linha;              /* linha da criacao */
    tipoNodo tipoN;         /* tipo de nodo: tipoSimb, tipoOper ou tipoTipo */
    tabelaSimb *pSimb;      /* se tipoSimb: ponteiro para tabela de simbolos com identificadores e constantes */
    nodoOper opr;           /* se tipoOper: operadores */
    tipoDado tt;            /* se tipoTipo: tt */
} nodo;

tabelaSimb tabSimb[MAX_SIMB];
tabelaSimb *achaIdx(int i);         /* so acha pelo indicie, nao cria (pode ter idx repetido! TS e TF testa: variavelT()*/
tabelaSimb *achaId(char *nome);     /* acha ou cria ID (variavel ou funcao) tipoIdUndef */
tabelaSimb *achaInt(int iv);        /* acha ou cria tipoConInt */
tabelaSimb *achaDouble(float dv);   /* acha ou cria tipoConDouble */
tabelaSimb *achaStr(char *sv);      /* acha ou cria tipoConStr */
//void addFunc(char *id, void (*func)(), char *idF /*similar em c*/, int nump, int tret /*tipo retorno e TS*/, int ta /*tipo arg*/);

tabelaSimb *achaIdEsc(char *nome, escopo *e); /* Procura idNome==nome && escopo<=es->e, retorna o ponteiro para a tabelaSimb */
//tabelaSimb *addIdEsc(char *nome, escopo *e, tipoDado td); /* Cria/Atualiza ID com escopo e, e tipoDado td, retorna o ponteiro para a tabelaSimb */
tabelaSimb *addIdEsc(char *nome, escopo *e); /* Cria/Atualiza ID com escopo e, retorna o ponteiro para a tabelaSimb. Da erro de redeclaracao */
tabelaSimb *achaFuncEsc(char *nome, escopo *pe, tipoDado td);
//tabelaSimb *achaIntEsc(int iv, escopo *e); /* Acha/cria ConInt com escopo e, e retorna o ponteiro para a TS */
//tabelaSimb *achaDoubleEsc(float dv, escopo *e); /* Acha/cria ConFloat com escopo e, e retorna o ponteiro para a TS */
//tabelaSimb *achaStrEsc(char *sv, escopo *e); /* Acha/cria ConStr com escopo e, e retorna o ponteiro para a TS */

tabelaSimb *addFunc(char *id, void *func, char *idF /*similar em c*/, int nump, int tret, int *ta /*tipo args*/); /* Acha ou cria funcao */
tabelaSimb *achaFuncs(tabelaSimb *ultima); /* laco para achar TODAS funcoes. So acha, nao cria */

extern FILE *yyin, *yyout;
extern FILE *fhead;

char *geraLB(int *i);
char *geraTP(int *i);
int geraTF(void); //tabela de funcoes
int geraTC(void); //tabela de constantes
int geraTS(void); //tabela de variaveis
int geraES(void); //tabela de escopos
char *nomeTipo(nodo *p); //retorna o nome do tipoDado ou tipoBase
int variavelT(int t);
int variavel(nodo *p);
int ponteiro(nodo *p);
char cabecalhoMain[MAX_CABECA];
tipoBase tipoRet;
int indente;

void yyerror(char *s);
extern int lineno;

void printNodo(nodo *tn, int n, char *var);
void printTS(void);
int pegaTipoBase(nodo *p);
int pegaTipoBaseT(int t);
void erroSemantico(char *s, int linha);

nodo *opr(int oper, int nops, ...);     /* converte operador em nodo */
nodo *conv(tabelaSimb *ps);             /* converte ID ou Constante da tabela de Simbolos em nodo */
nodo *convtn(int tipo);                 /* converte tipo em nodo */
void liberaNodo(nodo *tn);
char *token(int tk);
int tok2tb(int tk);
char *tb2c(int tb);
escopo *insereEsc(escopo *pe, int d); /*escopo*/
void printEsc(escopo *es, int n);     /*escopo*/
escopo *achaEsc(escopo *es, int e);
void carregaFuncoesPre(void);   /* carrega funcoes predefinidas no cabecalhoMain: imprima, leia, saia, sqrt e raiz */
void carregaFuncoesPreTS(void); /* carrega funcoes predefinidas na TS: imprima, leia, saia, sqrt e raiz */
void carregaConstantes(void);   /* carrega constantes no cabecalhoMain */

extern int debugArvore;
extern int debugTabela;
extern char cabecalhoMain[MAX_CABECA];
extern tipoBase tipoRet;

#endif
