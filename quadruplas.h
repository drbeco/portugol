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
#define MAX_PARAM 4
#define MAX_SVAL 256

/* Tipos de Base */
typedef enum
{
    tipoIndef,
    tipoInt,
    tipoFloat,
    tipoStr,
    tipoVoid
} tipoBase;

typedef enum
{
    tipoRetFuncInt,
    tipoRetFuncFloat,
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
      float  fval;
      char   sval[MAX_SVAL];
} superTipo;

/* Super Func */
typedef struct
{
      tipoRetFunc tipoRet;
      tipoBase tipoParam[MAX_PARAM];
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

#include "saida.h"

superTipo gstack[STACK_SIZE];   //pilha
int gsi=0;                      //indice da pilha geral

#define jump_f(Q1,NUL1,LABEL) if(!(Q1.ival)) goto LABEL    /* jump to LABEL if Q1.ival==false */
#define jump(NUL1,NUL2,LABEL) goto LABEL            /* jump to LABEL */
void nop(superTipo  *nul1, superTipo  *nul2, superTipo  *nul3);    // do nothing
void halt(superTipo  *nul1, superTipo  *nul2, superTipo  *nul3);   // abort with exit(1)

void loadi(int i,   int *nul1,   superTipo *tn);// { tn->tipo=tipoIntInt; tn->ival=i; }
void loadf(float f, float *nul1, superTipo *tn);// { tn->tipo=tipoIntFloat; tn->fval=f; }
void loads(char *s, char *nul1,  superTipo *tn);// { tn->tipo=tipoIntStr; strcpy(tn->sval,s); }
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

void mov(superTipo q1, superTipo *nul1, superTipo *qres);               //qres=q1;

void uminus(superTipo  q1, superTipo  *nul1, superTipo  *qres);    // *qres = -q1
void add(superTipo  q1, superTipo  q2, superTipo  *qres);          // *qres = q1 + q2
void sub(superTipo  q1, superTipo  q2, superTipo  *qres);          // *qres = q1 - q2
void mult(superTipo  q1, superTipo  q2, superTipo  *qres);         // *qres = q1 * q2
void divi(superTipo  q1, superTipo  q2, superTipo  *qres);         // *qres = q1 / q2
void mod(superTipo  q1, superTipo  q2, superTipo  *qres);          // *qres = q1 % q2
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

void push(superTipo g); // poe na pilha de execucao
superTipo *pop(void);   // tira da pilha de execucao

/* ------------------------------------------------------------------------------------------------- */

/* auxiliar functions */
//---------------------------
void push(superTipo g) // poe na pilha de execucao geral //push to stack
{
    gstack[gsi]=g; //copia por valor
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
void loadi(int i,   int *nul1,   superTipo *qres)
{
    qres->tipo=tipoInt;
    qres->ival=i;
    qres->fval=0.0;
    qres->sval[0]='\0';
}

void loadf(float f, float *nul1, superTipo *qres)
{
    qres->tipo=tipoFloat;
    qres->ival=0;
    qres->fval=f;
    qres->sval[0]='\0';
}

void loads(char *s, char *nul1,  superTipo *qres)
{
    qres->tipo=tipoStr;
    qres->ival=0;
    qres->fval=0.0;
    strcpy(qres->sval, s);
}

void mov(superTipo q1, superTipo *nul1, superTipo *qres)
{
    qres->tipo=q1.tipo;
    if(q1.tipo==tipoInt)
        qres->ival=q1.ival;
    else if(q1.tipo==tipoFloat)
        qres->fval=q1.fval;
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
        qres->fval=-q1.fval;
}

void add(superTipo  q1, superTipo  q2, superTipo  *qres)
{

    float arg1, arg2;

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

    if(q1.tipo == tipoFloat)
        arg1=q1.fval;
    else
        arg1=(float)q1.ival;
    if(q2.tipo == tipoFloat)
        arg2=q2.fval;
    else
        arg2=(float)q2.ival;

    if(q1.tipo == tipoFloat || q2.tipo == tipoFloat)
    {
        qres->fval=arg1 + arg2;
        qres->tipo=tipoFloat;
    }
    else
    {
        qres->ival=(int)(arg1 + arg2);
        qres->tipo=tipoInt;
    }
}

void sub(superTipo  q1, superTipo  q2, superTipo  *qres)
{

    float arg1, arg2;

    if(q1.tipo == tipoStr || q2.tipo == tipoStr)
    {
        fprintf(stderr,"ASM Error: invalid sub operation.\n");
        exit(1);
    }

    if(q1.tipo == tipoFloat)
        arg1=q1.fval;
    else
        arg1=(float)q1.ival;
    if(q2.tipo == tipoFloat)
        arg2=q2.fval;
    else
        arg2=(float)q2.ival;

    if(q1.tipo == tipoFloat || q2.tipo == tipoFloat)
    {
        qres->fval=arg1 - arg2;
        qres->tipo=tipoFloat;
    }
    else
    {
        qres->ival=(int)(arg1 - arg2);
        qres->tipo=tipoInt;
    }
}

void mult(superTipo  q1, superTipo  q2, superTipo  *qres)
{

    float arg1, arg2;

    if(q1.tipo == tipoStr || q2.tipo == tipoStr)
    {
        fprintf(stderr,"ASM Error: invalid mult operation.\n");
        exit(1);
    }

    if(q1.tipo == tipoFloat)
        arg1=q1.fval;
    else
        arg1=(float)q1.ival;
    if(q2.tipo == tipoFloat)
        arg2=q2.fval;
    else
        arg2=(float)q2.ival;

    if(q1.tipo == tipoFloat || q2.tipo == tipoFloat)
    {
        qres->fval=arg1 * arg2;
        qres->tipo=tipoFloat;
    }
    else
    {
        qres->ival=(int)(arg1 * arg2);
        qres->tipo=tipoInt;
    }
}

void divi(superTipo  q1, superTipo  q2, superTipo  *qres)
{

    float arg1, arg2;

    if(q1.tipo == tipoStr || q2.tipo == tipoStr)
    {
        fprintf(stderr,"ASM Error: invalid divi operation.\n");
        exit(1);
    }

    if(q2.tipo == tipoFloat)
        arg2=q2.fval;
    else
        arg2=(float)q2.ival;
    if(arg2==0.0)
    {
        fprintf(stderr,"ASM Error: division by zero.\n");
        exit(1);
    }
    if(q1.tipo == tipoFloat)
        arg1=q1.fval;
    else
        arg1=(float)q1.ival;

    if(q1.tipo == tipoFloat || q2.tipo == tipoFloat)
    {
        qres->fval=arg1 / arg2;
        qres->tipo=tipoFloat;
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

    if(q2.tipo == tipoFloat)
        arg2=(int)q2.fval;
    else
        arg2=q2.ival;
    if(arg2==0)
    {
        fprintf(stderr,"ASM Error: mod division by zero.\n");
        exit(1);
    }
    if(q1.tipo == tipoFloat)
        arg1=(int)q1.fval;
    else
        arg1=q1.ival;

    qres->tipo=tipoInt;
    qres->ival=arg1 % arg2;
}

/* logical operations */
//---------------------------

void comp_eq(superTipo  q1, superTipo  q2, superTipo  *qres)
{

    float arg1, arg2;

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

    if(q1.tipo == tipoFloat)
        arg1=q1.fval;
    else
        arg1=(float)q1.ival;
    if(q2.tipo == tipoFloat)
        arg2=q2.fval;
    else
        arg2=(float)q2.ival;

    qres->ival=(int)(arg1 == arg2);
}

void comp_ne(superTipo  q1, superTipo  q2, superTipo  *qres)
{

    float arg1, arg2;

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

    if(q1.tipo == tipoFloat)
        arg1=q1.fval;
    else
        arg1=(float)q1.ival;
    if(q2.tipo == tipoFloat)
        arg2=q2.fval;
    else
        arg2=(float)q2.ival;

    qres->ival=(int)(arg1 != arg2);
}

void comp_gt(superTipo  q1, superTipo  q2, superTipo  *qres)
{

    float arg1, arg2;

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

    if(q1.tipo == tipoFloat)
        arg1=q1.fval;
    else
        arg1=(float)q1.ival;
    if(q2.tipo == tipoFloat)
        arg2=q2.fval;
    else
        arg2=(float)q2.ival;

    qres->ival=(int)(arg1 > arg2);
}


void comp_lt(superTipo  q1, superTipo  q2, superTipo  *qres)
{
    float arg1, arg2;

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

    if(q1.tipo == tipoFloat)
        arg1=q1.fval;
    else
        arg1=(float)q1.ival;
    if(q2.tipo == tipoFloat)
        arg2=q2.fval;
    else
        arg2=(float)q2.ival;

    qres->ival=(int)(arg1 < arg2);
}

void comp_ge(superTipo  q1, superTipo  q2, superTipo  *qres)
{
    float arg1, arg2;

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

    if(q1.tipo == tipoFloat)
        arg1=q1.fval;
    else
        arg1=(float)q1.ival;
    if(q2.tipo == tipoFloat)
        arg2=q2.fval;
    else
        arg2=(float)q2.ival;

    qres->ival=(int)(arg1 >= arg2);
}

void comp_le(superTipo  q1, superTipo  q2, superTipo  *qres)
{
    float arg1, arg2;

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

    if(q1.tipo == tipoFloat)
        arg1=q1.fval;
    else
        arg1=(float)q1.ival;
    if(q2.tipo == tipoFloat)
        arg2=q2.fval;
    else
        arg2=(float)q2.ival;

    qres->ival=(int)(arg1 <= arg2);
}

/* relational operations */
//---------------------------

void rela_an(superTipo  q1, superTipo  q2, superTipo  *qres)
{
    float arg1, arg2;

    if(q1.tipo == tipoStr || q2.tipo == tipoStr)
    {
        fprintf(stderr,"ASM Error: invalid rela_an operation.\n");
        exit(1);
    }

    qres->tipo=tipoInt;
    if(q1.tipo == tipoFloat)
        arg1=q1.fval;
    else
        arg1=(float)q1.ival;
    if(q2.tipo == tipoFloat)
        arg2=q2.fval;
    else
        arg2=(float)q2.ival;

    qres->ival=(int)(arg1 && arg2);
}

void rela_or(superTipo  q1, superTipo  q2, superTipo  *qres)
{
    float arg1, arg2;

    if(q1.tipo == tipoStr || q2.tipo == tipoStr)
    {
        fprintf(stderr,"ASM Error: invalid rela_or operation.\n");
        exit(1);
    }

    qres->tipo=tipoInt;
    if(q1.tipo == tipoFloat)
        arg1=q1.fval;
    else
        arg1=(float)q1.ival;
    if(q2.tipo == tipoFloat)
        arg2=q2.fval;
    else
        arg2=(float)q2.ival;

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
    if(q1.tipo == tipoFloat)
        qres->ival=(int)(!(q1.fval));
    else
        qres->ival=!(q1.ival);
}

/*stack and function operations */
//---------------------------

void param(superTipo q1, void *nul1, void *nul2)
{
    push(q1);
}

void call(char *q1, int i, superTipo  *qres)
{
    int j=0, idx;
    superTipo *g[MAX_PARAM];//maximo funcao com 4 argumentos f(a0, a1, a2, a3);

    if(i>MAX_PARAM)
    {
        fprintf(stderr, "ASM Error: cant call function with more than %d (MAX_PARAM) parameters.\n", MAX_PARAM);
        exit(1);
    }

    for(j=0; j<i && j<MAX_PARAM; j++)
        g[j]=pop();    //pop all parameters

    /* lista de funcoes */
    for(idx=0; idx<MAX_TF; idx++)
        if(strcmp(tf[idx].idNome, q1) == 0) //found!
            break;
    if(idx==MAX_TF)
    {
        fprintf(stderr, "ASM Error: function not in tf[] table (loop exausted).\n");
        exit(1);
    }

    switch(idx)
    {
        case 0: //printf
            if(g[0]->tipo!=tipoStr)
            {
                fprintf(stderr, "ASM Error: function printf needs tipoStr as first arg.\n");
                exit(1);
            }
            if(g[1]->tipo==tipoStr)
                (*tf[idx].vfunc)(g[0]->sval, g[1]->sval); //printf("%s\n",sval);
            else if(g[1]->tipo==tipoInt)
                (*tf[idx].vfunc)(g[0]->sval, g[1]->ival); //printf("%d\n",ival);
            else // tipoFloat
                (*tf[idx].vfunc)(g[0]->sval, g[1]->fval); //printf("%.2f\n",fval);
            break;
        case 1: //scanf
            if(i!=0)
            {
                fprintf(stderr, "ASM Error: function scanf cannot take any args.\n");
                exit(1);
            }
            (*tf[idx].vfunc)("%f", &qres->fval); //scanf("%f",&ts[1]);
            qres->tipo=tipoFloat;
            break;
        case 2: //exit
            if(g[0]->tipo==tipoStr)
            {
                fprintf(stderr, "ASM Error: function exit cannot take <tipoStr> as arg.\n");
                exit(1);
            }
            else if(g[0]->tipo==tipoInt)
                (*tf[idx].vfunc)(g[0]->ival); //exit(ival)
            else /* tipoFloat */
                (*tf[idx].vfunc)((int)g[0]->fval); //exit(ival)
            break;
        case 3: //sqrt
            if(g[0]->tipo==tipoStr)
            {
                fprintf(stderr, "ASM Error: function sqrt cannot take <tipoStr> as arg.\n");
                exit(1);
            }
            else if(g[0]->tipo==tipoInt)
                qres->fval=(*tf[idx].dfunc)((float)g[0]->ival); //sqrt((float)ival)
            else /* tipoFloat */
                qres->fval=(*tf[idx].dfunc)(g[0]->fval); //sqrt(fval)
            qres->tipo=tipoFloat;
            break;
        case 4: //exp
            if(g[0]->tipo==tipoStr)
            {
                fprintf(stderr, "ASM Error: function exp cannot take <tipoStr> as arg.\n");
                exit(1);
            }
            else if(g[0]->tipo==tipoInt)
                qres->fval=(*tf[idx].dfunc)((float)g[0]->ival); //exp((float)ival)
            else /* tipoFloat */
                qres->fval=(*tf[idx].dfunc)(g[0]->fval); //exp(fval)
            qres->tipo=tipoFloat;
            break;
        case 5: //pow
            if(g[0]->tipo==tipoStr || g[1]->tipo==tipoStr)
            {
                fprintf(stderr, "ASM Error: function pow cannot take <tipoStr> as arg.\n");
                exit(1);
            }
            qres->tipo=tipoFloat;
            if(g[0]->tipo==tipoInt)
                if(g[1]->tipo==tipoInt)
                    qres->fval=(*tf[idx].dfunc)((float)g[0]->ival, (float)g[1]->ival); //exp((float)ival)
                else /* g[1]==tipoFloat */
                    qres->fval=(*tf[idx].dfunc)((float)g[0]->ival, g[1]->fval); //exp((float)ival)
            else /* g[0]==tipoFloat */
                if(g[1]->tipo==tipoInt)
                    qres->fval=(*tf[idx].dfunc)(g[0]->fval, (float)g[1]->ival); //exp((float)ival)
                else /* g[1]==tipoFloat */
                    qres->fval=(*tf[idx].dfunc)(g[0]->fval, g[1]->fval); //exp((float)ival)
            break;
        default:
            fprintf(stderr, "ASM Error: function %s not in tf[] table. (default switch)\n", q1);
            exit(1);
    }
}
