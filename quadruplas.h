//    Compilador PORTUGOL versao 3q
//    Autor: Ruben Carlo Benante
//    Email: benante@gmail.com
//    Data: 23/04/2009
//    Modificado: 25/05/2009

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define STACK_SIZE 200
#define FUNC_NAME_SIZE 32
#define MAX_PARAM 3
#define MAX_SVAL 256

#define MAX_TS 100 /* tabela de simbolos */
#define MAX_TC 100 /* tabela de constantes */
#define MAX_TP 100 /* tabela de temporarios */
#define MAX_TF 100 /* tabela de funcoes */

/* Tipos de Base */
typedef enum
{
    tipoUndef,
    tipoInt,
/*    tipoFloat,*/
    tipoDouble,
    tipoStr,
    tipoVoid
} tipoBase;

typedef enum
{
    tipoRetFuncInt,
/*    tipoRetFuncFloat,*/
    tipoRetFuncDouble,
    tipoRetFuncChar,
    tipoRetFuncStr,
    tipoRetFuncVoid,
    tipoRetFuncPVoid
} tipoRetFunc;

/* Super Tipo */
typedef struct
{
      tipoBase tipo;
      int    ival;
      double dval;
      char   sval[MAX_SVAL];
} superTipo;

/* Super Func */
typedef struct
{
      tipoRetFunc tipoRet;
/*      tipoBase tipoParam[MAX_PARAM]; nao precisa, pois estao na pilha com param() */
      int numParam;
      char   *idNome;
      int    (*ifunc)();   //ponteiro para funcao que retorna inteiro
      float  (*ffunc)();   //ponteiro para funcao que retorna float
      double (*dfunc)();   //ponteiro para funcao que retorna double
      char   (*cfunc)();   //ponteiro para funcao que retorna char
      char   *(*sfunc)();  //ponteiro para funcao que retorna ponteiro para char
      void   (*vfunc)();   //ponteiro para a funcao que retorna void
      void   *(*pfunc)();  //ponteiro para a funcao que retorna ponteiro para void
} superFunc;

superTipo eax;                                     //registrador acumulador
//superTipo ebp, eax;                              //registradores de base e acumulador
superTipo gstack[STACK_SIZE];                      //pilha
//superTipo esp={tipoInt, STACK_SIZE, 0.0, '\0'};  //indice da pilha
int gsi = 0;                                       //indice da pilha

superTipo ts[MAX_TS];
superTipo tc[MAX_TC];
superTipo tp[MAX_TP];
superFunc tf[MAX_TF];

#define jump_f(Q1,NUL1,LABEL) if(!(Q1.ival)) goto LABEL    /* jump to LABEL if Q1.ival==false */
#define jump(NUL1,NUL2,LABEL) goto LABEL            /* jump to LABEL */
void nop(superTipo  *nul1, superTipo  *nul2, superTipo  *nul3);    // do nothing
void halt(superTipo  *nul1, superTipo  *nul2, superTipo  *nul3);   // abort with exit(1)

void loadi(int i,   int *nul1,   superTipo *tn);// { tn->tipo=tipoInt; tn->ival=i; }
void loadf(float f, float *nul1, superTipo *tn);// { tn->tipo=tipoFloat; tn->fval=f; }
void loadd(double d, double *nul1, superTipo *tn);// { tn->tipo=tipoDouble; tn->dval=f; }
void loads(char *s, char *nul1,  superTipo *tn);// { tn->tipo=tipoStr; strcpy(tn->sval,s); }
//apenas 0 ou 1 parametro:
//loadfuncd("sqrt", tipoInt,  sqrt);
//void loadfuncd(char *nome, int tipoArg0,  double (*df)());
// completa:
//loadfuncd("sqrt", nPar, tipoPar,  sqrt);
//void loadfunci(char *nome, int tipoArg[MAX_PARAM],  int (*if)());
//void loadfuncp(char *nome, int tipoArg[MAX_PARAM],  void *(*pf)());
//void loadfunc(char *nome, int tipoRet,  void *(*pfunc)());
//{
//   static int idx=-1;
//   idx++;
//   tf[idx].tipo=tipo;
//   if(tipo==tipoIdFuncInt)
//     tf[idx].ifunc=(int)pfunc;
//   else
//     tf[idx].vfptr=(void *)pfunc;
//   tf[idx].nomeId=malloc(strlen(nome)+1);
//   strcpy(tf[idx].idName, nome);
// }

void mov(superTipo q1, superTipo *nul1, superTipo *qres);          //qres=q1;

void uminus(superTipo   q1, superTipo  *nul1, superTipo  *qres);   // *qres = -q1
void add(superTipo      q1, superTipo  q2, superTipo  *qres);      // *qres = q1 + q2
void sub(superTipo      q1, superTipo  q2, superTipo  *qres);      // *qres = q1 - q2
void mult(superTipo     q1, superTipo  q2, superTipo  *qres);      // *qres = q1 * q2
void divi(superTipo     q1, superTipo  q2, superTipo  *qres);      // *qres = q1 / q2
void mod(superTipo      q1, superTipo  q2, superTipo  *qres);      // *qres = q1 % q2
void comp_eq(superTipo  q1, superTipo  q2, superTipo  *qres);      // *qres = (q1 == q2)
void comp_ne(superTipo  q1, superTipo  q2, superTipo  *qres);      // *qres = (q1 != q2)
void comp_gt(superTipo  q1, superTipo  q2, superTipo  *qres);      // *qres = (q1 > q2)
void comp_lt(superTipo  q1, superTipo  q2, superTipo  *qres);      // *qres = (q1 < q2)
void comp_ge(superTipo  q1, superTipo  q2, superTipo  *qres);      // *qres = (q1 >= q2)
void comp_le(superTipo  q1, superTipo  q2, superTipo  *qres);      // *qres = (q1 <= q2)
void rela_an(superTipo  q1, superTipo  q2, superTipo  *qres);      // *qres = (q1 && q2)
void rela_or(superTipo  q1, superTipo  q2, superTipo  *qres);      // *qres = (q1 || q2)
void rela_no(superTipo  q1, superTipo  *nul1, superTipo  *qres);   // *qres = (!q1)
void param(superTipo q1, void *nul1, void *nul2); // push(q1)
void call(char *q1, int q2, superTipo  *qres);    // *qres = f_name(a[1], ..., a[q2]); where q1:f_name, q2:quantity of param

#define call_q1(n) q1(p1, p2, ..., pn)            /* call function */
#define retn       return                         /* return from function */
#define ret(q1)    return(q1)                     /* return from function */

void push(superTipo g); // poe na pilha de execucao
superTipo *pop(void);   // tira da pilha de execucao

/* ------------------------------------------------------------------------------------------------- */

/* auxiliar functions */
//---------------------------
void push(superTipo g) // poe na pilha de execucao geral //push to stack
{
    gstack[gsi]=g; //copia por valor
    //fprintf(stderr, "asm push() gstack[%d]tipo = %d\n", gsi, gstack[gsi].tipo);
    gsi++;
    if(gsi>=STACK_SIZE)
    {
        fprintf(stderr,"ASM Error: stack overflow.\n");
        exit(1);
    }
}

superTipo *pop(void)    // tira da pilha de execucao geral //pop from stack
{
    superTipo *r;
    if(gsi<=0)
    {
        fprintf(stderr,"ASM Error: stack underflow.\n");
        exit(1);
    }
    r=malloc(sizeof(superTipo));
    *r=gstack[--gsi]; //copia por valor
    return(r); //&gstack[--gsi]
}

/* jump operations */
//---------------------------
//see above

/* misc operations */
//---------------------------
void nop(superTipo  *nul1, superTipo  *nul2, superTipo  *nul3) //nop : //do nothing
{
    ;
}

void halt(superTipo  *nul1, superTipo  *nul2, superTipo  *nul3) // abort with exit(1)
{
    exit(1);
}

/* memory operations */
//---------------------------
// put it in the symbol table TS/function table TF
void loadi(int i,   int *nul1,   superTipo *qres)
{
    qres->tipo=tipoInt;
    qres->ival=i;
    qres->dval=0.0;
    qres->sval[0]='\0';
}

// void loadf(float f, float *nul1, superTipo *qres)
// {
//     qres->tipo=tipoFloat;
//     qres->ival=0;
//     qres->fval=f;
//     qres->sval[0]='\0';
// }

void loadd(double d, double *nul1, superTipo *qres)
{
    qres->tipo=tipoDouble;
    qres->ival=0;
    qres->dval=d;
    qres->sval[0]='\0';
}

void loads(char *s, char *nul1,  superTipo *qres)
{
    qres->tipo=tipoStr;
    qres->ival=0;
    qres->dval=0.0;
    strcpy(qres->sval, s);
}

void loadfunc(tipoBase tipoRet, void *pFunc, char *fNome, superFunc *sf, int numpar)
{

  sf->tipoRet=tipoRet;
  sf->numParam=numpar;

  sf->idNome=malloc(strlen(fNome)+1);
  strcpy(sf->idNome,fNome);

  switch(tipoRet)
  {
    case tipoVoid:
      sf->vfunc=pFunc;
      break;
    case tipoInt:
      //sf->ifunc=((int *)())pFunc;
      sf->ifunc=pFunc;
      break;
    case tipoDouble:
      sf->dfunc=pFunc;
      break;
    case tipoStr:
      sf->sfunc=pFunc;
      break;
    default:
      fprintf(stderr,"ASM Error: Unknow return type of function\n");
      exit(1);
  }
}

// move around
void mov(superTipo q1, superTipo *nul1, superTipo *qres)
{
    qres->tipo=q1.tipo;
    if(q1.tipo==tipoInt)
        qres->ival=q1.ival;
    else if(q1.tipo==tipoDouble)
        qres->dval=q1.dval;
    else if(q1.tipo=tipoStr)
        strcpy(qres->sval, q1.sval);
    else
    {
        fprintf(stderr,"ASM Error: invalid mov operation.\n");
        exit(1);
    }
}

/*mathematical operations */
//---------------------------

void uminus(superTipo  q1, superTipo  *nul1, superTipo  *qres)
{
    if(q1.tipo==tipoStr)
    {
        fprintf(stderr,"ASM Error: invalid uminus operation.\n");
        exit(1);
    }
    qres->tipo=q1.tipo;
    if(q1.tipo==tipoInt)
        qres->ival=-q1.ival;
    else
        qres->dval=-q1.dval;
}

void add(superTipo  q1, superTipo  q2, superTipo  *qres)
{

    double arg1, arg2;

    if((q1.tipo == tipoStr || q2.tipo == tipoStr) && (q1.tipo != tipoStr || q2.tipo != tipoStr))
    {
        fprintf(stderr,"ASM Error: invalid add operation.\n");
        exit(1);
    }

    if(q1.tipo == tipoStr) //se um eh, ambos sao
    {
        qres->tipo=tipoStr;
        strcpy(qres->sval, q1.sval);
        strcat(qres->sval, q2.sval);
        return;
    }

    if(q1.tipo == tipoDouble)
        arg1=q1.dval;
    else
        arg1=(double)q1.ival;
    if(q2.tipo == tipoDouble)
        arg2=q2.dval;
    else
        arg2=(double)q2.ival;

    if(q1.tipo == tipoDouble || q2.tipo == tipoDouble)
    {
        qres->dval=arg1 + arg2;
        qres->tipo=tipoDouble;
    }
    else
    {
        qres->ival=(int)(arg1 + arg2);
        qres->tipo=tipoInt;
    }
}

void sub(superTipo  q1, superTipo  q2, superTipo  *qres)
{

    double arg1, arg2;

    if(q1.tipo == tipoStr || q2.tipo == tipoStr)
    {
        fprintf(stderr,"ASM Error: invalid sub operation.\n");
        exit(1);
    }

    if(q1.tipo == tipoDouble)
        arg1=q1.dval;
    else
        arg1=(double)q1.ival;
    if(q2.tipo == tipoDouble)
        arg2=q2.dval;
    else
        arg2=(double)q2.ival;

    if(q1.tipo == tipoDouble || q2.tipo == tipoDouble)
    {
        qres->dval=arg1 - arg2;
        qres->tipo=tipoDouble;
    }
    else
    {
        qres->ival=(int)(arg1 - arg2);
        qres->tipo=tipoInt;
    }
}

void mult(superTipo  q1, superTipo  q2, superTipo  *qres)
{

    double arg1, arg2;

    if(q1.tipo == tipoStr || q2.tipo == tipoStr)
    {
        fprintf(stderr,"ASM Error: invalid mult operation.\n");
        exit(1);
    }

    if(q1.tipo == tipoDouble)
        arg1=q1.dval;
    else
        arg1=(double)q1.ival;
    if(q2.tipo == tipoDouble)
        arg2=q2.dval;
    else
        arg2=(double)q2.ival;

    if(q1.tipo == tipoDouble || q2.tipo == tipoDouble)
    {
        qres->dval=arg1 * arg2;
        qres->tipo=tipoDouble;
    }
    else
    {
        qres->ival=(int)(arg1 * arg2);
        qres->tipo=tipoInt;
    }
}

void divi(superTipo  q1, superTipo  q2, superTipo  *qres)
{

    double arg1, arg2;

    if(q1.tipo == tipoStr || q2.tipo == tipoStr)
    {
        fprintf(stderr,"ASM Error: invalid divi operation.\n");
        exit(1);
    }

    if(q2.tipo == tipoDouble)
        arg2=q2.dval;
    else
        arg2=(double)q2.ival;
    if(arg2==0.0)
    {
        fprintf(stderr,"ASM Error: division by zero.\n");
        exit(1);
    }
    if(q1.tipo == tipoDouble)
        arg1=q1.dval;
    else
        arg1=(double)q1.ival;

    if(q1.tipo == tipoDouble || q2.tipo == tipoDouble)
    {
        qres->dval=arg1 / arg2;
        qres->tipo=tipoDouble;
    }
    else
    {
        qres->ival=(int)(arg1 / arg2);
        qres->tipo=tipoInt;
    }
}

void mod(superTipo  q1, superTipo  q2, superTipo  *qres) // *qres = q1 % q2
{

    int arg1, arg2;

    if(q1.tipo == tipoStr || q2.tipo == tipoStr)
    {
        fprintf(stderr,"ASM Error: invalid mod operation.\n");
        exit(1);
    }

    if(q2.tipo == tipoDouble)
        arg2=(int)q2.dval;
    else
        arg2=q2.ival;
    if(arg2==0)
    {
        fprintf(stderr,"ASM Error: mod division by zero.\n");
        exit(1);
    }
    if(q1.tipo == tipoDouble)
        arg1=(int)q1.dval;
    else
        arg1=q1.ival;

    qres->tipo=tipoInt;
    qres->ival=arg1 % arg2;
}

/* logical operations */
//---------------------------

void comp_eq(superTipo  q1, superTipo  q2, superTipo  *qres)
{

    double arg1, arg2;

    if((q1.tipo == tipoStr || q2.tipo == tipoStr) && (q1.tipo != tipoStr || q2.tipo != tipoStr))
    {
        fprintf(stderr,"ASM Error: invalid comp_eq operation.\n");
        exit(1);
    }

    qres->tipo=tipoInt;
    if(q1.tipo == tipoStr)
    {
        qres->ival = !(strcmp(q1.sval, q2.sval));
        return;
    }

    if(q1.tipo == tipoDouble)
        arg1=q1.dval;
    else
        arg1=(double)q1.ival;
    if(q2.tipo == tipoDouble)
        arg2=q2.dval;
    else
        arg2=(double)q2.ival;

    qres->ival=(int)(arg1 == arg2);
}

void comp_ne(superTipo  q1, superTipo  q2, superTipo  *qres)
{

    double arg1, arg2;

    if((q1.tipo == tipoStr || q2.tipo == tipoStr) && (q1.tipo != tipoStr || q2.tipo != tipoStr))
    {
        fprintf(stderr,"ASM Error: invalid comp_ne operation.\n");
        exit(1);
    }

    qres->tipo=tipoInt;
    if(q1.tipo == tipoStr)
    {
        qres->ival = !!(strcmp(q1.sval, q2.sval));
        return;
    }

    if(q1.tipo == tipoDouble)
        arg1=q1.dval;
    else
        arg1=(double)q1.ival;
    if(q2.tipo == tipoDouble)
        arg2=q2.dval;
    else
        arg2=(double)q2.ival;

    qres->ival=(int)(arg1 != arg2);
}

void comp_gt(superTipo  q1, superTipo  q2, superTipo  *qres)
{

    double arg1, arg2;

    if((q1.tipo == tipoStr || q2.tipo == tipoStr) && (q1.tipo != tipoStr || q2.tipo != tipoStr))
    {
        fprintf(stderr,"ASM Error: invalid comp_gt operation.\n");
        exit(1);
    }

    qres->tipo=tipoInt;
    if(q1.tipo == tipoStr)
    {
        qres->ival = (strcmp(q1.sval, q2.sval)>0);
        return;
    }

    if(q1.tipo == tipoDouble)
        arg1=q1.dval;
    else
        arg1=(double)q1.ival;
    if(q2.tipo == tipoDouble)
        arg2=q2.dval;
    else
        arg2=(double)q2.ival;

    qres->ival=(int)(arg1 > arg2);
}


void comp_lt(superTipo  q1, superTipo  q2, superTipo  *qres)
{
    double arg1, arg2;

    if((q1.tipo == tipoStr || q2.tipo == tipoStr) && (q1.tipo != tipoStr || q2.tipo != tipoStr))
    {
        fprintf(stderr,"ASM Error: invalid comp_lt operation.\n");
        exit(1);
    }

    qres->tipo=tipoInt;
    if(q1.tipo == tipoStr)
    {
        qres->ival = (strcmp(q1.sval, q2.sval)<0);
        return;
    }

    if(q1.tipo == tipoDouble)
        arg1=q1.dval;
    else
        arg1=(double)q1.ival;
    if(q2.tipo == tipoDouble)
        arg2=q2.dval;
    else
        arg2=(double)q2.ival;

    qres->ival=(int)(arg1 < arg2);
}

void comp_ge(superTipo  q1, superTipo  q2, superTipo  *qres)
{
    double arg1, arg2;

    if((q1.tipo == tipoStr || q2.tipo == tipoStr) && (q1.tipo != tipoStr || q2.tipo != tipoStr))
    {
        fprintf(stderr,"ASM Error: invalid comp_ge operation.\n");
        exit(1);
    }

    qres->tipo=tipoInt;
    if(q1.tipo == tipoStr)
    {
        qres->ival = (strcmp(q1.sval, q2.sval)>=0);
        return;
    }

    if(q1.tipo == tipoDouble)
        arg1=q1.dval;
    else
        arg1=(double)q1.ival;
    if(q2.tipo == tipoDouble)
        arg2=q2.dval;
    else
        arg2=(double)q2.ival;

    qres->ival=(int)(arg1 >= arg2);
}

void comp_le(superTipo  q1, superTipo  q2, superTipo  *qres)
{
    double arg1, arg2;

    if((q1.tipo == tipoStr || q2.tipo == tipoStr) && (q1.tipo != tipoStr || q2.tipo != tipoStr))
    {
        fprintf(stderr,"ASM Error: invalid comp_le operation.\n");
        exit(1);
    }

    qres->tipo=tipoInt;
    if(q1.tipo == tipoStr)
    {
        qres->ival = (strcmp(q1.sval, q2.sval)<=0);
        return;
    }

    if(q1.tipo == tipoDouble)
        arg1=q1.dval;
    else
        arg1=(double)q1.ival;
    if(q2.tipo == tipoDouble)
        arg2=q2.dval;
    else
        arg2=(double)q2.ival;

    qres->ival=(int)(arg1 <= arg2);
}

/* relational operations */
//---------------------------

void rela_an(superTipo  q1, superTipo  q2, superTipo  *qres)
{
    double arg1, arg2;

    if(q1.tipo == tipoStr || q2.tipo == tipoStr)
    {
        fprintf(stderr,"ASM Error: invalid rela_an operation.\n");
        exit(1);
    }

    qres->tipo=tipoInt;
    if(q1.tipo == tipoDouble)
        arg1=q1.dval;
    else
        arg1=(double)q1.ival;
    if(q2.tipo == tipoDouble)
        arg2=q2.dval;
    else
        arg2=(double)q2.ival;

    qres->ival=(int)(arg1 && arg2);
}

void rela_or(superTipo  q1, superTipo  q2, superTipo  *qres)
{
    double arg1, arg2;

    if(q1.tipo == tipoStr || q2.tipo == tipoStr)
    {
        fprintf(stderr,"ASM Error: invalid rela_or operation.\n");
        exit(1);
    }

    qres->tipo=tipoInt;
    if(q1.tipo == tipoDouble)
        arg1=q1.dval;
    else
        arg1=(double)q1.ival;
    if(q2.tipo == tipoDouble)
        arg2=q2.dval;
    else
        arg2=(double)q2.ival;

    qres->ival=(int)(arg1 || arg2);
}

void rela_no(superTipo  q1, superTipo  *nul1, superTipo  *qres)
{

    if(q1.tipo == tipoStr)
    {
        fprintf(stderr,"ASM Error: invalid rela_no operation.\n");
        exit(1);
    }

    qres->tipo=tipoInt;
    if(q1.tipo == tipoDouble)
        qres->ival=(int)(!(q1.dval));
    else
        qres->ival=!(q1.ival);
}

/*stack and function operations */
//---------------------------

void param(superTipo q1, void *nul1, void *nul2)
{
    push(q1);
}



// void call(char *q1, int i, superTipo  *qres)
// {
//     int j=0, idx;
//     superTipo *g[MAX_PARAM];//maximo funcao com 4 argumentos f(a0, a1, a2, a3);
//
//     if(i>MAX_PARAM)
//     {
//         fprintf(stderr, "ASM Error: cant call function with more than %d (MAX_PARAM) parameters.\n", MAX_PARAM);
//         exit(1);
//     }
//
//     for(j=0; j<i && j<MAX_PARAM; j++)
//         g[j]=pop();    //pop all parameters
//
//     /* lista de funcoes */
//     for(idx=0; idx<MAX_TF; idx++)
//         if(strcmp(tf[idx].idNome, q1) == 0) //found!
//             break;
//     if(idx==MAX_TF)
//     {
//         fprintf(stderr, "ASM Error: function not in tf[] table (loop exausted).\n");
//         exit(1);
//     }
//
//     /*strcmp(ts[idx].idNome, "scanf");
//     strcmp(ts[idx].idNome, "printf");*/
//
//     /* switch(i) //numero de parametros */
//     /* switch(i) //tipo de retorno */
//     /* (*tf[idx].vfunc)(g[0]->sval, g[1]->sval); //printf("%s\n",sval); */
//     /*
//     1- int f(int)
//     2- int f(double)
//     3- int f(str)
//     4- double f(int)
//     5- double f(double)
//     6- double f(str)
//     7- str f(int)
//     8- str f(double)
//     9- str f(str)
//     10- int,int
//     11- int,double
//     12- int,str
//     13- double,int
//     14- double,double
//     15- double,str
//     16- str,int
//     17- str,double
//     18- str,str
//     */
//
//     switch(idx)
//     {
//         case 0: //printf
//             if(g[0]->tipo!=tipoStr)
//             {
//                 fprintf(stderr, "ASM Error: function printf needs tipoStr as first arg.\n");
//                 exit(1);
//             }
//             if(g[1]->tipo==tipoStr)
//                 (*tf[idx].vfunc)(g[0]->sval, g[1]->sval); //printf("%s\n",sval);
//             else if(g[1]->tipo==tipoInt)
//                 (*tf[idx].vfunc)(g[0]->sval, g[1]->ival); //printf("%d\n",ival);
//             else // tipoDouble
//                 (*tf[idx].vfunc)(g[0]->sval, g[1]->dval); //printf("%.2f\n",dval);
//             break;
//         case 1: //scanf
//             if(i!=0)
//             {
//                 fprintf(stderr, "ASM Error: function scanf cannot take any args.\n");
//                 exit(1);
//             }
//             (*tf[idx].vfunc)("%f", &qres->dval); //scanf("%f",&ts[1]);
//             qres->tipo=tipoDouble;
//             break;
//         case 2: //exit
//             if(g[0]->tipo==tipoStr)
//             {
//                 fprintf(stderr, "ASM Error: function exit cannot take <tipoStr> as arg.\n");
//                 exit(1);
//             }
//             else if(g[0]->tipo==tipoInt)
//                 (*tf[idx].vfunc)(g[0]->ival); //exit(ival)
//             else /* tipoDouble */
//                 (*tf[idx].vfunc)((int)g[0]->dval); //exit(ival)
//             break;
//         case 3: //sqrt
//             if(g[0]->tipo==tipoStr)
//             {
//                 fprintf(stderr, "ASM Error: function sqrt cannot take <tipoStr> as arg.\n");
//                 exit(1);
//             }
//             else if(g[0]->tipo==tipoInt)
//                 qres->dval=(*tf[idx].dfunc)((double)g[0]->ival); //sqrt((double)ival)
//             else /* tipoDouble */
//                 qres->dval=(*tf[idx].dfunc)(g[0]->dval); //sqrt(dval)
//             qres->tipo=tipoDouble;
//             break;
//         case 4: //exp
//             if(g[0]->tipo==tipoStr)
//             {
//                 fprintf(stderr, "ASM Error: function exp cannot take <tipoStr> as arg.\n");
//                 exit(1);
//             }
//             else if(g[0]->tipo==tipoInt)
//                 qres->dval=(*tf[idx].dfunc)((double)g[0]->ival); //exp((double)ival)
//             else /* tipoDouble */
//                 qres->dval=(*tf[idx].dfunc)(g[0]->dval); //exp(dval)
//             qres->tipo=tipoDouble;
//             break;
//         case 5: //pow
//             if(g[0]->tipo==tipoStr || g[1]->tipo==tipoStr)
//             {
//                 fprintf(stderr, "ASM Error: function pow cannot take <tipoStr> as arg.\n");
//                 exit(1);
//             }
//             qres->tipo=tipoDouble;
//             if(g[0]->tipo==tipoInt)
//                 if(g[1]->tipo==tipoInt)
//                     qres->dval=(*tf[idx].dfunc)((double)g[0]->ival, (double)g[1]->ival); //exp((double)ival)
//                 else /* g[1]==tipoDouble */
//                     qres->dval=(*tf[idx].dfunc)((double)g[0]->ival, g[1]->dval); //exp((double)ival)
//             else /* g[0]==tipoDouble */
//                 if(g[1]->tipo==tipoInt)
//                     qres->dval=(*tf[idx].dfunc)(g[0]->dval, (double)g[1]->ival); //exp((double)ival)
//                 else /* g[1]==tipoDouble */
//                     qres->dval=(*tf[idx].dfunc)(g[0]->dval, g[1]->dval); //exp((double)ival)
//             break;
//         default:
//             fprintf(stderr, "ASM Error: function %s not in tf[] table. (default switch)\n", q1);
//             exit(1);
//     }
// }

void call(char *q1, int i, superTipo  *nul2)
{
    int j=0, idx;
    superTipo *g[MAX_PARAM];//maximo funcao com 4 argumentos f(a0, a1, a2, a3);
    //superTipo npar;

    //loadi(i, NULL, &npar);

    if (i>MAX_PARAM)
    {
        fprintf(stderr, "ASM Error: cant call function with more than %d (MAX_PARAM) parameters.\n", MAX_PARAM);
        exit(1);
    }

    /* colocar na pilha na ordem inversa */
    //param(i, NULL, NULL);
    //param(s, NULL, NULL);
    //call("printf", 2, &r);
    for (j=0; j<i && j<MAX_PARAM; j++)
    {
        g[j]=pop();    //pop all parameters
//        printf("tipo[%d]=%d\n", j, g[j]->tipo);
    }
        //pop(&g[j]);    //pop all parameters
    //sub(esp, npar, &esp); //do not really pop those items

    /* lista de funcoes */
    for (idx=0; idx<MAX_TF; idx++)
    {
        if(tf[idx].idNome==NULL)
            continue;
        if (strcmp(tf[idx].idNome, q1) == 0) //found!
            break;
    }
    //printf("idx:%d MAX_TF:%d\n", idx, MAX_TF);
    if (idx==MAX_TF)
    {
        fprintf(stderr, "ASM Error: function not in tf[] table (loop exausted).\n");
        exit(1);
    }

//         case 1: //scanf
//             if(i!=0)
//             {
//                 fprintf(stderr, "ASM Error: function scanf cannot take any args.\n");
//                 exit(1);
//             }
//             (*tf[idx].vfunc)("%f", &qres->dval); //scanf("%f",&ts[1]);
//             qres->tipo=tipoDouble;
//             break;
    //param(i/d/s?, NULL, NULL);
    //param(s, NULL, NULL);
    //call("printf", 2, &r);
//    fprintf(stderr, "asm: idx %d\n", idx);
    if(idx==1) //scanf hard-coded
    {
        //fprintf(stderr, "asm: scanf!\n");
        //char *strstr(const char *s1, const char *s2) -- locates the first occurrence of the string s2 in string s1. Null if not
        if(strstr(g[0]->sval, "%d")) // pediu int
        {
            eax.tipo=tipoInt;
            //(*tf[idx].vfunc)(g[0]->sval, &eax.ival);
            (*tf[idx].vfunc)("%d", &eax.ival);
        }
        else
            if(strstr(g[0]->sval, "%f")) // pediu double
            {
                eax.tipo=tipoDouble;
                //(*tf[idx].vfunc)(g[0]->sval, &(eax.dval));
                (*tf[idx].vfunc)("%lf", &(eax.dval));
            }
            else
                if(strstr(g[0]->sval, "%s")) // pediu string
                {
                    eax.tipo=tipoStr;
                    //(*tf[idx].vfunc)(g[0]->sval, eax.sval);
                    (*tf[idx].vfunc)("%s", eax.sval);
                }
                else // erro
                {
                    fprintf(stderr, "ASM Error: <tipoRet>=leia(<tipoStr>) only accept %%d, %%f or %%s in the formated string.\n");
                    exit(1);
                }
        return;
    }

    if (i==0) /* func_?fv */
        switch (tf[idx].tipoRet)
        {
        case tipoVoid: // func_vfv
            eax.tipo=tipoUndef;
            (*tf[idx].vfunc)();
            break;
        case tipoInt: // func_ifv
            eax.tipo=tipoInt;
            eax.ival=(*tf[idx].ifunc)();
            break;
        case tipoDouble: // func_dfv
            eax.tipo=tipoDouble;
            eax.dval=(*tf[idx].dfunc)();
            break;
        case tipoStr: // func_sfv
            eax.tipo=tipoStr;
            strcpy(eax.sval, (*tf[idx].sfunc)());
            break;
        default:
            fprintf(stderr, "ASM Error: Unknow return type\n");
            exit(1);
        }
    if (i==1) /* func_?f? */
        switch (tf[idx].tipoRet)
        {
        case tipoVoid: // func_vf?
            eax.tipo=tipoUndef;
            switch (g[0]->tipo)
            {
            case tipoInt:  // func_vfi
                (*tf[idx].vfunc)(g[0]->ival);
                break;
            case tipoDouble: // func_vfd
                (*tf[idx].vfunc)(g[0]->dval);
                break;
            case tipoStr: // func_vfs
                (*tf[idx].vfunc)(g[0]->sval);
                break;
            default:
                fprintf(stderr, "ASM Error: Unknow type of arg 1\n");
                exit(1);
            }
            break;
        case tipoInt: // func_if?
            eax.tipo=tipoInt;
            switch (g[0]->tipo)
            {
            case tipoInt: // func_ifi
                eax.ival=(*tf[idx].ifunc)(g[0]->ival);
                break;
            case tipoDouble: // func_ifd
                eax.ival=(*tf[idx].ifunc)(g[0]->dval);
                break;
            case tipoStr: // func_ifs
                eax.ival=(*tf[idx].ifunc)(g[0]->sval);
                break;
            default:
                fprintf(stderr, "ASM Error: Unknow type of arg 1\n");
                exit(1);
            }
            break;
        case tipoDouble: // func_df?
            eax.tipo=tipoDouble;
            switch (g[0]->tipo)
            {
            case tipoInt: // func_dfi
                eax.dval=(*tf[idx].dfunc)(g[0]->ival);
                break;
            case tipoDouble: // func_dfd
                eax.dval=(*tf[idx].dfunc)(g[0]->dval);
                break;
            case tipoStr: // func_dfs
                eax.dval=(*tf[idx].dfunc)(g[0]->sval);
                break;
            default:
                fprintf(stderr, "ASM Error: Unknow type of arg 1\n");
                exit(1);
            }
            break;
        case tipoStr: // func_sf?
            eax.tipo=tipoStr;
            switch (g[0]->tipo)
            {
            case tipoInt: // func_sfi
                strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->ival));
                break;
            case tipoDouble: // func_sfd
                strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->dval));
                break;
            case tipoStr: // func_sfs
                strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->sval));
                break;
            default:
                fprintf(stderr, "ASM Error: Unknow type of arg 1\n");
                exit(1);
            }
            break;
        default:
            fprintf(stderr, "ASM Error: Unknow return type\n");
            exit(1);
        }

    if (i==2) /* func_?f?? */
        switch (tf[idx].tipoRet)
        {
        case tipoVoid: // func_vf??
            eax.tipo=tipoUndef;
            switch (g[0]->tipo)
            {
            case tipoInt: // func_vfi?
                switch (g[1]->tipo)
                {
                case tipoInt: // func_vfii
                    (*tf[idx].vfunc)(g[0]->ival, g[1]->ival);
                    break;
                case tipoDouble: // func_vfid
                    (*tf[idx].vfunc)(g[0]->ival, g[1]->dval);
                    break;
                case tipoStr: // func_vfis
                    (*tf[idx].vfunc)(g[0]->ival, g[1]->sval);
                    break;
                default:
                    fprintf(stderr, "ASM Error: Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoDouble: // func_vfd?
                switch (g[1]->tipo)
                {
                case tipoInt: // func_vfdi
                    (*tf[idx].vfunc)(g[0]->dval, g[1]->ival);
                    break;
                case tipoDouble: // func_vfdd
                    (*tf[idx].vfunc)(g[0]->dval, g[1]->dval);
                    break;
                case tipoStr: // func_vfds
                    (*tf[idx].vfunc)(g[0]->dval, g[1]->sval);
                    break;
                default:
                    fprintf(stderr, "ASM Error: Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoStr: //func_vfs?
                switch (g[1]->tipo)
                {
                case tipoInt: // func_vfsi
                    (*tf[idx].vfunc)(g[0]->sval, g[1]->ival);
                    break;
                case tipoDouble: // func_vfsd
                    (*tf[idx].vfunc)(g[0]->sval, g[1]->dval);
                    break;
                case tipoStr: // func_vfss
                    (*tf[idx].vfunc)(g[0]->sval, g[1]->sval);
                    break;
                default:
                    fprintf(stderr, "ASM Error: Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            default:
                fprintf(stderr, "ASM Error: Unknow type of arg 1\n");
                exit(1);
            } //void switch g[0]
            break;

        case tipoInt: // func_if??
            eax.tipo=tipoInt;
            switch (g[0]->tipo)
            {
            case tipoInt: // func_ifi?
                switch (g[1]->tipo)
                {
                case tipoInt: // func_ifii
                    eax.ival=(*tf[idx].ifunc)(g[0]->ival, g[1]->ival);
                    break;
                case tipoDouble: // func_ifid
                    eax.ival=(*tf[idx].ifunc)(g[0]->ival, g[1]->dval);
                    break;
                case tipoStr: // func_ifis
                    eax.ival=(*tf[idx].ifunc)(g[0]->ival, g[1]->sval);
                    break;
                default:
                    fprintf(stderr, "ASM Error: Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoDouble: // func_ifd?
                switch (g[1]->tipo)
                {
                case tipoInt: // func_ifdi
                    eax.ival=(*tf[idx].ifunc)(g[0]->dval, g[1]->ival);
                    break;
                case tipoDouble: // func_ifdd
                    eax.ival=(*tf[idx].ifunc)(g[0]->dval, g[1]->dval);
                    break;
                case tipoStr: // func_ifds
                    eax.ival=(*tf[idx].ifunc)(g[0]->dval, g[1]->sval);
                    break;
                default:
                    fprintf(stderr, "ASM Error: Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoStr: //func_ifs?
                switch (g[1]->tipo)
                {
                case tipoInt: // func_ifsi
                    eax.ival=(*tf[idx].ifunc)(g[0]->sval, g[1]->ival);
                    break;
                case tipoDouble: // func_ifsd
                    eax.ival=(*tf[idx].ifunc)(g[0]->sval, g[1]->dval);
                    break;
                case tipoStr: // func_ifss
                    eax.ival=(*tf[idx].ifunc)(g[0]->sval, g[1]->sval);
                    break;
                default:
                    fprintf(stderr, "ASM Error: Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            default:
                fprintf(stderr, "ASM Error: Unknow type of arg 1\n");
                exit(1);
            } //int switch g[0]
            break;

        case tipoDouble: // func_df??
            eax.tipo=tipoDouble;
            switch (g[0]->tipo)
            {
            case tipoInt: // func_dfi?
                switch (g[1]->tipo)
                {
                case tipoInt: // func_dfii
                    eax.dval=(*tf[idx].dfunc)(g[0]->ival, g[1]->ival);
                    break;
                case tipoDouble: // func_dfid
                    eax.dval=(*tf[idx].dfunc)(g[0]->ival, g[1]->dval);
                    break;
                case tipoStr: // func_dfis
                    eax.dval=(*tf[idx].dfunc)(g[0]->ival, g[1]->sval);
                    break;
                default:
                    fprintf(stderr, "ASM Error: Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoDouble: // func_dfd?
                switch (g[1]->tipo)
                {
                case tipoInt: // func_dfdi
                    eax.dval=(*tf[idx].dfunc)(g[0]->dval, g[1]->ival);
                    break;
                case tipoDouble: // func_dfdd
                    eax.dval=(*tf[idx].dfunc)(g[0]->dval, g[1]->dval);
                    break;
                case tipoStr: // func_dfds
                    eax.dval=(*tf[idx].dfunc)(g[0]->dval, g[1]->sval);
                    break;
                default:
                    fprintf(stderr, "ASM Error: Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoStr: //func_dfs?
                switch (g[1]->tipo)
                {
                case tipoInt: // func_dfsi
                    eax.dval=(*tf[idx].dfunc)(g[0]->sval, g[1]->ival);
                    break;
                case tipoDouble: // func_dfsd
                    eax.dval=(*tf[idx].dfunc)(g[0]->sval, g[1]->dval);
                    break;
                case tipoStr: // func_dfss
                    eax.dval=(*tf[idx].dfunc)(g[0]->sval, g[1]->sval);
                    break;
                default:
                    fprintf(stderr, "ASM Error: Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            default:
                fprintf(stderr, "ASM Error: Unknow type of arg 1\n");
                exit(1);
            } //double switch g[0]
            break;

        case tipoStr: // func_sf??
            eax.tipo=tipoStr;
            switch (g[0]->tipo)
            {
            case tipoInt: // func_sfi?
                switch (g[1]->tipo)
                {
                case tipoInt: // func_sfii
                    strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->ival, g[1]->ival));
                    break;
                case tipoDouble: // func_sfid
                    strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->ival, g[1]->dval));
                    break;
                case tipoStr: // func_sfis
                    strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->ival, g[1]->sval));
                    break;
                default:
                    fprintf(stderr, "ASM Error: Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoDouble: // func_sfd?
                switch (g[1]->tipo)
                {
                case tipoInt: // func_sfdi
                    strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->dval, g[1]->ival));
                    break;
                case tipoDouble: // func_sfdd
                    strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->dval, g[1]->dval));
                    break;
                case tipoStr: // func_sfds
                    strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->dval, g[1]->sval));
                    break;
                default:
                    fprintf(stderr, "ASM Error: Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoStr: //func_sfs?
                switch (g[1]->tipo)
                {
                case tipoInt: // func_sfsi
                    strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->sval, g[1]->ival));
                    break;
                case tipoDouble: // func_sfsd
                    strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->sval, g[1]->dval));
                    break;
                case tipoStr: // func_sfss
                    strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->sval, g[1]->sval));
                    break;
                default:
                    fprintf(stderr, "ASM Error: Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            default:
                fprintf(stderr, "ASM Error: Unknow type of arg 1\n");
                exit(1);
            } //str switch g[0]
            break;
        default:
            fprintf(stderr, "ASM Error: Unknow return type\n");
            exit(1);
        } //switch tipoRet

    /* ---------------- tres argumentos ---------------- */

    if (i==3) /* func_?f??? */
        switch (tf[idx].tipoRet)
        {
        case tipoVoid: // func_vf???
            eax.tipo=tipoUndef;
            switch (g[0]->tipo)
            {
            case tipoInt: // func_vfi??
                switch (g[1]->tipo)
                {
                case tipoInt: // func_vfii?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_vfiii
                        (*tf[idx].vfunc)(g[0]->ival, g[1]->ival, g[2]->ival);
                        break;
                    case tipoDouble: // func_vfiid
                        (*tf[idx].vfunc)(g[0]->ival, g[1]->ival, g[2]->dval);
                        break;
                    case tipoStr: // func_vfiis
                        (*tf[idx].vfunc)(g[0]->ival, g[1]->ival, g[2]->sval);
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoDouble: // func_vfid?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_vfidi
                        (*tf[idx].vfunc)(g[0]->ival, g[1]->dval, g[2]->ival);
                        break;
                    case tipoDouble: // func_vfidd
                        (*tf[idx].vfunc)(g[0]->ival, g[1]->dval, g[2]->dval);
                        break;
                    case tipoStr: // func_vfids
                        (*tf[idx].vfunc)(g[0]->ival, g[1]->dval, g[2]->sval);
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoStr: // func_vfis?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_vfisi
                        (*tf[idx].vfunc)(g[0]->ival, g[1]->sval, g[2]->ival);
                        break;
                    case tipoDouble: // func_vfisd
                        (*tf[idx].vfunc)(g[0]->ival, g[1]->sval, g[2]->dval);
                        break;
                    case tipoStr: // func_vfiss
                        (*tf[idx].vfunc)(g[0]->ival, g[1]->sval, g[2]->sval);
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                default:
                    fprintf(stderr, "ASM Error: Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoDouble: // func_vfd??
                switch (g[1]->tipo)
                {
                case tipoInt: // func_vfdi?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_vfdii
                        (*tf[idx].vfunc)(g[0]->dval, g[1]->ival, g[2]->ival);
                        break;
                    case tipoDouble: // func_vfdid
                        (*tf[idx].vfunc)(g[0]->dval, g[1]->ival, g[2]->dval);
                        break;
                    case tipoStr: // func_vfdis
                        (*tf[idx].vfunc)(g[0]->dval, g[1]->ival, g[2]->sval);
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoDouble: // func_vfdd?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_vfddi
                        (*tf[idx].vfunc)(g[0]->dval, g[1]->dval, g[2]->ival);
                        break;
                    case tipoDouble: // func_vfddd
                        (*tf[idx].vfunc)(g[0]->dval, g[1]->dval, g[2]->dval);
                        break;
                    case tipoStr: // func_vfdds
                        (*tf[idx].vfunc)(g[0]->dval, g[1]->dval, g[2]->sval);
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoStr: // func_vfds?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_vfdsi
                        (*tf[idx].vfunc)(g[0]->dval, g[1]->sval, g[2]->ival);
                        break;
                    case tipoDouble: // func_vfdsd
                        (*tf[idx].vfunc)(g[0]->dval, g[1]->sval, g[2]->dval);
                        break;
                    case tipoStr: // func_vfdss
                        (*tf[idx].vfunc)(g[0]->dval, g[1]->sval, g[2]->sval);
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                default:
                    fprintf(stderr, "ASM Error: Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoStr: //func_vfs??
                switch (g[1]->tipo)
                {
                case tipoInt: // func_vfsi?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_vfsii
                        (*tf[idx].vfunc)(g[0]->sval, g[1]->ival, g[2]->ival);
                        break;
                    case tipoDouble: // func_vfsid
                        (*tf[idx].vfunc)(g[0]->sval, g[1]->ival, g[2]->dval);
                        break;
                    case tipoStr: // func_vfsis
                        (*tf[idx].vfunc)(g[0]->sval, g[1]->ival, g[2]->sval);
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoDouble: // func_vfsd?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_vfsdi
                        (*tf[idx].vfunc)(g[0]->sval, g[1]->dval, g[2]->ival);
                        break;
                    case tipoDouble: // func_vfsdd
                        (*tf[idx].vfunc)(g[0]->sval, g[1]->dval, g[2]->dval);
                        break;
                    case tipoStr: // func_vfsds
                        (*tf[idx].vfunc)(g[0]->sval, g[1]->dval, g[2]->sval);
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoStr: // func_vfss?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_vfssi
                        (*tf[idx].vfunc)(g[0]->sval, g[1]->sval, g[2]->ival);
                        break;
                    case tipoDouble: // func_vfssd
                        (*tf[idx].vfunc)(g[0]->sval, g[1]->sval, g[2]->dval);
                        break;
                    case tipoStr: // func_vfsss
                        (*tf[idx].vfunc)(g[0]->sval, g[1]->sval, g[2]->sval);
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                default:
                    fprintf(stderr, "ASM Error: Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            default:
                fprintf(stderr, "ASM Error: Unknow type of arg 1\n");
                exit(1);
            } //void switch g[0]
            break;

        case tipoInt: // func_if???
            eax.tipo=tipoInt;
            switch (g[0]->tipo)
            {
            case tipoInt: // func_ifi??
                switch (g[1]->tipo)
                {
                case tipoInt: // func_ifii?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_ifiii
                        eax.ival=(*tf[idx].ifunc)(g[0]->ival, g[1]->ival, g[2]->ival);
                        break;
                    case tipoDouble: // func_ifiid
                        eax.ival=(*tf[idx].ifunc)(g[0]->ival, g[1]->ival, g[2]->dval);
                        break;
                    case tipoStr: // func_ifiis
                        eax.ival=(*tf[idx].ifunc)(g[0]->ival, g[1]->ival, g[2]->sval);
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoDouble: // func_ifid?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_ifidi
                        eax.ival=(*tf[idx].ifunc)(g[0]->ival, g[1]->dval, g[2]->ival);
                        break;
                    case tipoDouble: // func_ifidd
                        eax.ival=(*tf[idx].ifunc)(g[0]->ival, g[1]->dval, g[2]->dval);
                        break;
                    case tipoStr: // func_ifids
                        eax.ival=(*tf[idx].ifunc)(g[0]->ival, g[1]->dval, g[2]->sval);
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoStr: // func_ifis?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_ifisi
                        eax.ival=(*tf[idx].ifunc)(g[0]->ival, g[1]->sval, g[2]->ival);
                        break;
                    case tipoDouble: // func_ifisd
                        eax.ival=(*tf[idx].ifunc)(g[0]->ival, g[1]->sval, g[2]->dval);
                        break;
                    case tipoStr: // func_ifiss
                        eax.ival=(*tf[idx].ifunc)(g[0]->ival, g[1]->sval, g[2]->sval);
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                default:
                    fprintf(stderr, "ASM Error: Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoDouble: // func_ifd??
                switch (g[1]->tipo)
                {
                case tipoInt: // func_ifdi?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_ifdii
                        eax.ival=(*tf[idx].ifunc)(g[0]->dval, g[1]->ival, g[2]->ival);
                        break;
                    case tipoDouble: // func_ifdid
                        eax.ival=(*tf[idx].ifunc)(g[0]->dval, g[1]->ival, g[2]->dval);
                        break;
                    case tipoStr: // func_ifdis
                        eax.ival=(*tf[idx].ifunc)(g[0]->dval, g[1]->ival, g[2]->sval);
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoDouble: // func_ifdd?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_ifddi
                        eax.ival=(*tf[idx].ifunc)(g[0]->dval, g[1]->dval, g[2]->ival);
                        break;
                    case tipoDouble: // func_ifddd
                        eax.ival=(*tf[idx].ifunc)(g[0]->dval, g[1]->dval, g[2]->dval);
                        break;
                    case tipoStr: // func_ifdds
                        eax.ival=(*tf[idx].ifunc)(g[0]->dval, g[1]->dval, g[2]->sval);
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                case tipoStr: // func_ifds?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_ifdsi
                        eax.ival=(*tf[idx].ifunc)(g[0]->dval, g[1]->sval, g[2]->ival);
                        break;
                    case tipoDouble: // func_ifdsd
                        eax.ival=(*tf[idx].ifunc)(g[0]->dval, g[1]->sval, g[2]->dval);
                        break;
                    case tipoStr: // func_ifdss
                        eax.ival=(*tf[idx].ifunc)(g[0]->dval, g[1]->sval, g[2]->sval);
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                default:
                    fprintf(stderr, "ASM Error: Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoStr: //func_ifs??
                switch (g[1]->tipo)
                {
                case tipoInt: // func_ifsi?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_ifsii
                        eax.ival=(*tf[idx].ifunc)(g[0]->sval, g[1]->ival, g[2]->ival);
                        break;
                    case tipoDouble: // func_ifsid
                        eax.ival=(*tf[idx].ifunc)(g[0]->sval, g[1]->ival, g[2]->dval);
                        break;
                    case tipoStr: // func_ifsis
                        eax.ival=(*tf[idx].ifunc)(g[0]->sval, g[1]->ival, g[2]->sval);
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoDouble: // func_ifsd?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_ifsdi
                        eax.ival=(*tf[idx].ifunc)(g[0]->sval, g[1]->dval, g[2]->ival);
                        break;
                    case tipoDouble: // func_ifsdd
                        eax.ival=(*tf[idx].ifunc)(g[0]->sval, g[1]->dval, g[2]->dval);
                        break;
                    case tipoStr: // func_ifsds
                        eax.ival=(*tf[idx].ifunc)(g[0]->sval, g[1]->dval, g[2]->sval);
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoStr: // func_ifss?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_ifssi
                        eax.ival=(*tf[idx].ifunc)(g[0]->sval, g[1]->sval, g[2]->ival);
                        break;
                    case tipoDouble: // func_ifssd
                        eax.ival=(*tf[idx].ifunc)(g[0]->sval, g[1]->sval, g[2]->dval);
                        break;
                    case tipoStr: // func_ifsss
                        eax.ival=(*tf[idx].ifunc)(g[0]->sval, g[1]->sval, g[2]->sval);
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                default:
                    fprintf(stderr, "ASM Error: Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            default:
                fprintf(stderr, "ASM Error: Unknow type of arg 1\n");
                exit(1);
            } // int switch g[0]
            break;

        case tipoDouble: // func_df???
            eax.tipo=tipoDouble;
            switch (g[0]->tipo)
            {
            case tipoInt: // func_dfi??
                switch (g[1]->tipo)
                {
                case tipoInt: // func_dfii?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_dfiii
                        eax.dval=(*tf[idx].dfunc)(g[0]->ival, g[1]->ival, g[2]->ival);
                        break;
                    case tipoDouble: // func_dfiid
                        eax.dval=(*tf[idx].dfunc)(g[0]->ival, g[1]->ival, g[2]->dval);
                        break;
                    case tipoStr: // func_dfiis
                        eax.dval=(*tf[idx].dfunc)(g[0]->ival, g[1]->ival, g[2]->sval);
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoDouble: // func_dfid?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_dfidi
                        eax.dval=(*tf[idx].dfunc)(g[0]->ival, g[1]->dval, g[2]->ival);
                        break;
                    case tipoDouble: // func_dfidd
                        eax.dval=(*tf[idx].dfunc)(g[0]->ival, g[1]->dval, g[2]->dval);
                        break;
                    case tipoStr: // func_dfids
                        eax.dval=(*tf[idx].dfunc)(g[0]->ival, g[1]->dval, g[2]->sval);
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoStr: // func_dfis?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_dfisi
                        eax.dval=(*tf[idx].dfunc)(g[0]->ival, g[1]->sval, g[2]->ival);
                        break;
                    case tipoDouble: // func_dfisd
                        eax.dval=(*tf[idx].dfunc)(g[0]->ival, g[1]->sval, g[2]->dval);
                        break;
                    case tipoStr: // func_dfiss
                        eax.dval=(*tf[idx].dfunc)(g[0]->ival, g[1]->sval, g[2]->sval);
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                default:
                    fprintf(stderr, "ASM Error: Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoDouble: // func_dfd??
                switch (g[1]->tipo)
                {
                case tipoInt: // func_dfdi?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_dfdii
                        eax.dval=(*tf[idx].dfunc)(g[0]->dval, g[1]->ival, g[2]->ival);
                        break;
                    case tipoDouble: // func_dfdid
                        eax.dval=(*tf[idx].dfunc)(g[0]->dval, g[1]->ival, g[2]->dval);
                        break;
                    case tipoStr: // func_dfdis
                        eax.dval=(*tf[idx].dfunc)(g[0]->dval, g[1]->ival, g[2]->sval);
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoDouble: // func_dfdd?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_dfddi
                        eax.dval=(*tf[idx].dfunc)(g[0]->dval, g[1]->dval, g[2]->ival);
                        break;
                    case tipoDouble: // func_dfddd
                        eax.dval=(*tf[idx].dfunc)(g[0]->dval, g[1]->dval, g[2]->dval);
                        break;
                    case tipoStr: // func_dfdds
                        eax.dval=(*tf[idx].dfunc)(g[0]->dval, g[1]->dval, g[2]->sval);
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoStr: // func_dfds?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_dfdsi
                        eax.dval=(*tf[idx].dfunc)(g[0]->dval, g[1]->sval, g[2]->ival);
                        break;
                    case tipoDouble: // func_dfdsd
                        eax.dval=(*tf[idx].dfunc)(g[0]->dval, g[1]->sval, g[2]->dval);
                        break;
                    case tipoStr: // func_dfdss
                        eax.dval=(*tf[idx].dfunc)(g[0]->dval, g[1]->sval, g[2]->sval);
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                default:
                    fprintf(stderr, "ASM Error: Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoStr: //func_dfs??
                switch (g[1]->tipo)
                {
                case tipoInt: // func_dfsi?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_dfsii
                        eax.dval=(*tf[idx].dfunc)(g[0]->sval, g[1]->ival, g[2]->ival);
                        break;
                    case tipoDouble: // func_dfsid
                        eax.dval=(*tf[idx].dfunc)(g[0]->sval, g[1]->ival, g[2]->dval);
                        break;
                    case tipoStr: // func_dfsis
                        eax.dval=(*tf[idx].dfunc)(g[0]->sval, g[1]->ival, g[2]->sval);
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoDouble: // func_dfsd?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_dfsdi
                        eax.dval=(*tf[idx].dfunc)(g[0]->sval, g[1]->dval, g[2]->ival);
                        break;
                    case tipoDouble: // func_dfsdd
                        eax.dval=(*tf[idx].dfunc)(g[0]->sval, g[1]->dval, g[2]->dval);
                        break;
                    case tipoStr: // func_dfsds
                        eax.dval=(*tf[idx].dfunc)(g[0]->sval, g[1]->dval, g[2]->sval);
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoStr: // func_dfss?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_dfssi
                        eax.dval=(*tf[idx].dfunc)(g[0]->sval, g[1]->sval, g[2]->ival);
                        break;
                    case tipoDouble: // func_dfssd
                        eax.dval=(*tf[idx].dfunc)(g[0]->sval, g[1]->sval, g[2]->dval);
                        break;
                    case tipoStr: // func_dfsss
                        eax.dval=(*tf[idx].dfunc)(g[0]->sval, g[1]->sval, g[2]->sval);
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                default:
                    fprintf(stderr, "ASM Error: Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            default:
                fprintf(stderr, "ASM Error: Unknow type of arg 1\n");
                exit(1);
            } //double switch g[0]
            break;

        case tipoStr: // func_sf???
            eax.tipo=tipoStr;
            switch (g[0]->tipo)
            {
            case tipoInt: // func_sfi??
                switch (g[1]->tipo)
                {
                case tipoInt: // func_sfii?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_sfiii
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->ival, g[1]->ival, g[2]->ival));
                        break;
                    case tipoDouble: // func_sfiid
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->ival, g[1]->ival, g[2]->dval));
                        break;
                    case tipoStr: // func_sfiis
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->ival, g[1]->ival, g[2]->sval));
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoDouble: // func_sfid?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_sfidi
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->ival, g[1]->dval, g[2]->ival));
                        break;
                    case tipoDouble: // func_sfidd
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->ival, g[1]->dval, g[2]->dval));
                        break;
                    case tipoStr: // func_sfids
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->ival, g[1]->dval, g[2]->sval));
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoStr: // func_sfis?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_sfisi
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->ival, g[1]->sval, g[2]->ival));
                        break;
                    case tipoDouble: // func_sfisd
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->ival, g[1]->sval, g[2]->dval));
                        break;
                    case tipoStr: // func_sfiss
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->ival, g[1]->sval, g[2]->sval));
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                default:
                    fprintf(stderr, "ASM Error: Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoDouble: // func_sfd??
                switch (g[1]->tipo)
                {
                case tipoInt: // func_sfdi?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_sfdii
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->dval, g[1]->ival, g[2]->ival));
                        break;
                    case tipoDouble: // func_sfdid
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->dval, g[1]->ival, g[2]->dval));
                        break;
                    case tipoStr: // func_sfdis
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->dval, g[1]->ival, g[2]->sval));
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoDouble: // func_sfdd?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_sfddi
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->dval, g[1]->dval, g[2]->ival));
                        break;
                    case tipoDouble: // func_sfddd
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->dval, g[1]->dval, g[2]->dval));
                        break;
                    case tipoStr: // func_sfdds
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->dval, g[1]->dval, g[2]->sval));
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoStr: // func_sfds?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_sfddi
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->dval, g[1]->sval, g[2]->ival));
                        break;
                    case tipoDouble: // func_sfddd
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->dval, g[1]->sval, g[2]->dval));
                        break;
                    case tipoStr: // func_sfdds
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->dval, g[1]->sval, g[2]->sval));
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                default:
                    fprintf(stderr, "ASM Error: Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoStr: //func_sfs??
                switch (g[1]->tipo)
                {
                case tipoInt: // func_sfsi?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_sfsii
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->sval, g[1]->ival, g[2]->ival));
                        break;
                    case tipoDouble: // func_sfsid
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->sval, g[1]->ival, g[2]->dval));
                        break;
                    case tipoStr: // func_sfsis
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->sval, g[1]->ival, g[2]->sval));
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoDouble: // func_sfsd?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_sfsdi
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->sval, g[1]->dval, g[2]->ival));
                        break;
                    case tipoDouble: // func_sfsdd
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->sval, g[1]->dval, g[2]->dval));
                        break;
                    case tipoStr: // func_sfsds
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->sval, g[1]->dval, g[2]->sval));
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoStr: // func_sfss?
                    switch (g[2]->tipo)
                    {
                    case tipoInt: // func_sfssi
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->sval, g[1]->sval, g[2]->ival));
                        break;
                    case tipoDouble: // func_sfssd
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->sval, g[1]->sval, g[2]->dval));
                        break;
                    case tipoStr: // func_sfsss
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0]->sval, g[1]->sval, g[2]->sval));
                        break;
                    default:
                        fprintf(stderr, "ASM Error: Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                default:
                    fprintf(stderr, "ASM Error: Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            default:
                fprintf(stderr, "ASM Error: Unknow type of arg 1\n");
                exit(1);
            } //string switch g[0]
            break;
        default:
            fprintf(stderr, "ASM Error: Unknow return type\n");
            exit(1);
        } //switch tipoRet
        //printf("retornando de call\n");
}
