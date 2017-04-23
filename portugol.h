/*
    Compilador PORTUGOL v.1.1
    Autor: Ruben Carlo Benante
    Email: benante@gmail.com
    Data: 23/04/2009
*/

/* Tipos de Nodos */
typedef enum
{
    tipoID,
    tipoOpr,
    tipoConFlutuante,
} nodoEnum;

/* constantes */
typedef struct
{
    nodoEnum tipo;        /* tipo do node */
    float fval;           /* valor da constante real */
} fconTipoNodo;

/* indentificadores */
typedef struct
{
    nodoEnum tipo;      /* tipo do node */
    int i;              /* indice para a tabela de simbolos 0..25 */
} idTipoNodo;

/* operadores */
typedef struct
{
    nodoEnum tipo;                   /* tipo do nodo */
    int oper;                        /* operador */
    int nops;                        /* numero de operandos */
    union etiquetaTipoNodo *op[1];   /* operandos (expansivel) */
} oprTipoNodo;

typedef union etiquetaTipoNodo
{
    nodoEnum tipo;      /* tipo de node */
    fconTipoNodo fcon;  /* constantes numericas reais */
    idTipoNodo id;      /* identificadores */
    oprTipoNodo opr;    /* operadores */
} tipoNodo;
