//    Compilador PORTUGOL versao 1q
//    Autor: Ruben Carlo Benante
//    Email: benante@gmail.com
//    Data: 23/04/2009

#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 100
#define FUNC_NAME_SIZE 32
#define TEMP_SIZE 100
#define MAX_PARAM 4

struct tabela_call_s //tabela de nomes e enderecos de funcoes para chamar com call
{
    char nome[FUNC_NAME_SIZE]; //nome da funcao
    void (*endereco)();        //ponteiro para a funcao
} tabcall[] = {
                {"imprima", (void *)printf}  //imprima chama printf
              };

enum {imprima}; //enumeracao de funcoes disponiveis

float stack[STACK_SIZE]; //pilha
int stack_idx=0;         //indice da pilha
float temp[TEMP_SIZE];   //variaveis temporarias
float ts[26] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; //tabela de simbolos simplificada

#define jump_f(Q1,NULO,LABEL) if(!Q1) goto LABEL    /* jump to LABEL if Q1==false */
#define jump(NULO1,NULO2,LABEL) goto LABEL          /* jump to LABEL */
void nop(float *nulo1, float *nulo2, float *nulo3); // do nothing
void mov(float q1, float *nulo, float *qres);       // *qres = q1
void uminus(float q1, float *nulo, float *qres);    // *qres = -q1
void add(float q1, float q2, float *qres);          // *qres = q1 + q2
void sub(float q1, float q2, float *qres);          // *qres = q1 - q2
void mult(float q1, float q2, float *qres);         // *qres = q1 * q2
void divi(float q1, float q2, float *qres);         // *qres = q1 / q2
void comp_eq(float q1, float q2, float *qres);      // *qres = (q1 == q2)
void comp_ne(float q1, float q2, float *qres);      // *qres = (q1 != q2)
void comp_gt(float q1, float q2, float *qres);      // *qres = (q1 > q2)
void comp_lt(float q1, float q2, float *qres);      // *qres = (q1 < q2)
void comp_ge(float q1, float q2, float *qres);      // *qres = (q1 >= q2)
void comp_le(float q1, float q2, float *qres);      // *qres = (q1 <= q2)
void rela_an(float q1, float q2, float *qres);      // *qres = (q1 && q2)
void rela_or(float q1, float q2, float *qres);      // *qres = (q1 || q2)
void rela_no(float q1, float *nulo, float *qres);   // *qres = (!q1)
void param(float q1, float *nulo1, float *nulo2);   // push q1 to stak as function parameter
void call(char *q1, int q2, float *qres);           // *qres = f_name(a[1], ..., a[q2]); where q1:f_name, q2:quantity of param

/* ---------------------------------------------------------------------------------------------------------------------- */

/* auxiliar functions */

void _push(float f); // poe na pilha de execucao
float _pop(void);    // tira da pilha de execucao

/* function bodies */

void _push(float f)
{
    stack[stack_idx]=f;
    stack_idx++;
    if(stack_idx>=STACK_SIZE)
    {
        fprintf(stderr,"Erro: pilha cheia.");
        exit(1);
    }
}

float _pop(void)
{
    if(stack_idx<=0)
    {
        fprintf(stderr,"Erro: pilha vazia.");
        exit(1);
    }
    return(stack[--stack_idx]);
}

/* jump operations */
//   jump(NULL,NULL,l2);
//   jump_f(temp[0],NULL,l1);
//---------------------------

//jump_f(tem[13],NULL,l1); // jump if false, i.e., if q1==false jump to label l1
//inline void jump_f(float q1, float *nulo, char *qres) { if(!q1) goto *qres; }
#define jump_f(Q1,NULO,LABEL) if(!Q1) goto LABEL    /* jump to LABEL if Q1==false */
//jump(NULL,NULL,l1); // unconditional jump to label l1
#define jump(NULO1,NULO2,LABEL) goto LABEL          /* jump to LABEL */

/* misc operations */
//nop(NULL,NULL,NULL); // do nothing (just like python keyword pass)
//---------------------------

//nop : //do nothing
void nop(float *nulo1, float *nulo2, float *nulo3) { ; }

/* memory operations */
//  mov(1.00,NULL,&ts[0]);
//  mov(temp[8],NULL,&ts[3]);
//---------------------------

//  mov(temp[8],NULL,&ts[3]); //ts[3]=temp[8];
void mov(float q1, float *nulo, float *qres) { *qres=q1; }

/*mathematical operations */
//   uminus(3.00,NULL,&temp[1]);
//   add(temp[2],4.00,&temp[3]);
//   sub(temp[5],temp[6],&temp[7]);
//   mult(1.00,temp[3],&temp[4]);
//   divi(2.00,temp[1],&temp[2]);
//---------------------------

//  uminus  (3.00,NULL,&temp[1]); //temp[1]=-3.0;
void uminus(float q1, float *nulo, float *qres) { *qres=-q1; }
//   add(temp[2],4.00,&temp[3]); //temp[3]=temp[2]+4.0;
void add(float q1, float q2, float *qres) { *qres=q1+q2; }
//   sub(temp[5],temp[6],&temp[7]); //temp[7]=temp[5]-temp[6];
void sub(float q1, float q2, float *qres) { *qres=q1-q2; }
//   mult(1.00,temp[3],&temp[4]); //temp[4]=1.0*temp[3];
void mult(float q1, float q2, float *qres) { *qres=q1*q2; }
//   divi(2.00,temp[1],&temp[2]); //temp[2]=2.0/temp[1];
void divi(float q1, float q2, float *qres) { *qres=q1/q2; }

/* logical operations */
//   comp_eq(ts[1],2.00,&temp[0]);
//   comp_ne(ts[1],2.00,&temp[10]);
//   comp_gt(ts[0],2.00,&temp[15]);
//   comp_lt(ts[1],3.00,&temp[16]);
//   comp_ge(ts[2],3.00,&temp[11]);
//   comp_le(ts[3],0.00,&temp[14]);
//---------------------------

//   comp_eq(ts[1],2.00,&temp[0]); //temp[0]=(ts[1]==2.0);
void comp_eq(float q1, float q2, float *qres) { *qres=(q1==q2); }
//   comp_ne(ts[1],2.00,&temp[10]); //temp[10]=(ts[1]!=2.0);
void comp_ne(float q1, float q2, float *qres) { *qres=(q1!=q2); }
//   comp_gt(ts[0],2.00,&temp[15]); //temp[15]=(ts[0]>2.0);
void comp_gt(float q1, float q2, float *qres) { *qres=(q1>q2); }
//   comp_lt(ts[1],3.00,&temp[16]); //temp[16]=(ts[1]<3.0);
void comp_lt(float q1, float q2, float *qres) { *qres=(q1<q2); }
//   comp_ge(ts[2],3.00,&temp[11]); //temp[11]=(ts[2]>=3.0);
void comp_ge(float q1, float q2, float *qres) { *qres=(q1>=q2); }
//   comp_le(ts[3],0.00,&temp[14]); //temp[14]=(ts[3]<=0.0);
void comp_le(float q1, float q2, float *qres) { *qres=(q1<=q2); }

/* relational operations */
//   rela_an(temp[10],temp[11],&temp[12]);
//   rela_or(temp[9],temp[12],&temp[13]);
//   rela_no(temp[17],NULL,&temp[18]);
//---------------------------

//   rela_an(temp[10],temp[11],&temp[12]); //temp[12]=(temp[10]&&temp[11]);
void rela_an(float q1, float q2, float *qres) { *qres=(q1&&q2); }
//   rela_or(temp[9],temp[12],&temp[13]); //temp[13]=(temp[9]||temp[12]);
void rela_or(float q1, float q2, float *qres) { *qres=(q1||q2); }
//   rela_no(temp[17],NULL,&temp[18]); //temp[18]=!(temp[17]);
void rela_no(float q1, float *nulo, float *qres) { *qres=(!q1); }

/*stack and function operations */
//   param(temp[1],NULL,NULL);
//   call("print",1,&ts[1]);
//---------------------------

//   param(temp[1],NULL,NULL); // put temp[1] into parameter stack
void param(float q1, float *nulo1, float *nulo2) { _push(q1); }
//  call    ("print",1,&ts[0]); //call a function "print" with 1 arg from stack, and return a value to ts[0].
void call(char *q1, int i, float *qres)
{
    //for (i = 0; i < sizeof tabcall / sizeof tabcall[0]; i++)
    int j=0;
    float a[MAX_PARAM];//maximo funcao com 4 argumentos f(a0, a1, a2, a3);

    if(i>MAX_PARAM)
        fprintf(stderr, "error: cant call function with more than %d (MAX_PARAM) parameters.", MAX_PARAM);

    for(j=0; j<i && j<MAX_PARAM; j++)
        a[j]=_pop();    //_pop all parameters

    /* lista de funcoes */
    if(strcmp(q1, tabcall[imprima].nome) == 0) //imprima A;
        tabcall[imprima].endereco("%.2f\n", a[0]); //exemplo: printf("%.2f%.2f",a[0],a[1]);
}
