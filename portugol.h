/*
    Compilador PORTUGOL v.3q
    Autor: Ruben Carlo Benante
    Email: benante@gmail.com
    Data criação: 23/04/2009
    Data modificação: 25/05/2009
*/

#define MAX_SIMB 200
#define MAX_SVAL 128

/* Tipos de Dados da Tabela de Simbolos */
//char *sTipoDado[14]={"tipoIdIndef", "tipoConInt", "tipoConFloat", "tipoConStr", "tipoIdInt", "tipoIdFloat", "tipoIdStr", "tipoIdFuncInt", "tipoIdFuncFloat", "tipoIdFuncDouble", "tipoIdFuncChar", "tipoIdFuncStr", "tipoIdFuncVoid", "tipoIdFuncPVoid"};
typedef enum
{
    tipoIdUndef,

    tipoConInt,
    tipoConDouble,
    tipoConStr,

    tipoIdInt,
    tipoIdDouble,
    tipoIdStr,
    tipoIdPoint,
    /*tipoIdPointInt,
    tipoIdPointFloat,
    tipoIdPointStr,*/

    tipoIdFuncInt,
    //tipoIdFuncFloat,
    tipoIdFuncDouble,
    //tipoIdFuncChar,
    tipoIdFuncStr,
    tipoIdFuncVoid,
    //tipoIdFuncPVoid,
} tipoDado;

/* Tipos de Base */
//char *sTipoBase[4]={"tipoIndef", "tipoInt", "tipoFloat", "tipoStr"};
typedef enum
{
    tipoUndef,
    tipoInt,
    tipoDouble,
    tipoStr,
    tipoPointInt,
    tipoPointDouble,
    tipoPointStr,
    tipoVoid
} tipoBase;

/* Tipos de Nodos */
typedef enum
{
    tipoSimb,
    tipoOper
} tipoNodo;

/* tabela de simbolos */
typedef struct uTabela
{
      tipoDado tipoD;       //tipo do dado ou retorno da funcao
      tipoDado tipoRetNovo; //tipo de retorno da funcao portugol caso nao coincida com o tipo definido em C
      int idx;              // bug: tf tambem! ts[idx] ou tc[idx]. Para tf[], se acha o idx em um laco de busca, pelo nome
      int uso;              //verdadeiro se ja usou
      char *idNome;         //nome da variavel ou funcao em Portugol
      char *idFunc;         //nome da funcao em C
      int numPar;           //numero de parametros da funcao
      int ival;             //valor da constante inteira
      float dval;           //valor da constante real
      char sval[MAX_SVAL];  //valor da constante texto
      int formatadoSval;    //verdadeiro se sval serve para formato do printf
      int (*ifunc)();       //ponteiro para funcao que retorna inteiro
      //int (*i2func)(const char *, ...);            //bug2------ponteiro para funcao que retorna inteiro
      //float (*ffunc)();     //ponteiro para funcao que retorna double
      double (*dfunc)();    //ponteiro para funcao que retorna double
      char *(*sfunc)();     //ponteiro para funcao que retorna ponteiro para char
      void (*vfunc)();      //ponteiro para a funcao que retorna void
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
    tipoNodo tipoN;         /* tipo de nodo: simb ou oper */
    tabelaSimb *pSimb;      /* ponteiro para tabela de simbolos com identificadores e constantes */
    nodoOper opr;           /* operadores */
} nodo;

tabelaSimb tabSimb[MAX_SIMB];
tabelaSimb *achaIdx(int i);
tabelaSimb *achaId(char *nome);
tabelaSimb *achaInt(int iv);
tabelaSimb *achaDouble(float dv);
tabelaSimb *achaStr(char *sv);
tabelaSimb *achaFuncs(tabelaSimb *ultima);

extern FILE *yyin, *yyout;
extern FILE *fhead;
char *geraLB(int *i);
char *geraTP(int *i);
//int geraTF(void); //tabela de funcoes
int geraTC(void); //tabela de constantes
int geraTS(void); //tabela de variaveis
char *nomeTipo(nodo *p); //retorna o nome do tipoDado ou tipoBase
int variavelT(int t);
int variavel(nodo *p);
int ponteiro(nodo *p);

void addFuncInt(char *id, int (*func)(), char *idF, int nump, int tp);
void addFuncDouble(char *id, double (*func)(), char *idF, int nump, int tiporet); //normalmente tiporet==nome da funcao (FuncDouble)
void addFuncVoid(char *id, void (*func)(), char *idF, int nump, int tiporet); //normalmente tiporet==nome da funcao (FuncVoid)
//void addFuncInt2(char *id, int (*func)(const char *, ...), char *idF, int nump, int tp);
void addConStr(char *s);
void yyerror(char *s);
extern int lineno;

void printNodo(nodo *tn, int n, char *var);
void printTS(void);
int pegaTipoBase(nodo *p);
int pegaTipoBaseT(int t);
void erroSemantico(char *s, int linha);

nodo *opr(int oper, int nops, ...);
nodo *conv(tabelaSimb *ps);
void liberaNodo(nodo *tn);
char *token(int tk);
