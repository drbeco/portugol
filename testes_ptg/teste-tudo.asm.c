//    Gerado pelo compilador Portugol versao 2q
//    Autor: Ruben Carlo Benante
//    Email: benante@gmail.com
//    Data: 23/05/2009

#include <math.h>
#include "quadruplas.h"
#include "saida.h"

void filltf(void)
{
  tf[0].tipoRet=tipoRetFuncVoid;
  tf[0].vfunc=(void *)printf;
  tf[0].idNome=malloc(strlen("imprima")+1);
  strcpy(tf[0].idNome,"imprima");

  tf[1].tipoRet=tipoRetFuncVoid;
  tf[1].vfunc=(void *)scanf;
  tf[1].idNome=malloc(strlen("leia")+1);
  strcpy(tf[1].idNome,"leia");

  tf[2].tipoRet=tipoRetFuncVoid;
  tf[2].vfunc=(void *)exit;
  tf[2].idNome=malloc(strlen("saia")+1);
  strcpy(tf[2].idNome,"saia");

  tf[3].tipoRet=tipoRetFuncDouble;
  tf[3].dfunc=sqrt;
  tf[3].idNome=malloc(strlen("raiz")+1);
  strcpy(tf[3].idNome,"raiz");

  tf[4].tipoRet=tipoRetFuncDouble;
  tf[4].dfunc=exp;
  tf[4].idNome=malloc(strlen("exp")+1);
  strcpy(tf[4].idNome,"exp");

}

int main(void)
{
  filltf();

  loads("\0", NULL, &ts[0]); /* str S; */
  loads("\0", NULL, &ts[1]); /* str T; */
  loadi(0, NULL, &ts[2]); /* int variavel_3E; */
  loadi(0, NULL, &ts[3]); /* int A; */
  loadi(0, NULL, &ts[4]); /* int C; */
  loadi(0, NULL, &ts[5]); /* int B; */
  loadf(0.00, NULL, &ts[6]); /* real D; */
  loadf(0.00, NULL, &ts[7]); /* real M; */
  loadf(0.00, NULL, &ts[8]); /* real N; */
  loadf(0.00, NULL, &ts[9]); /* real P; */
  loadf(0.00, NULL, &ts[10]); /* real O; */
  loads("",NULL,&tc[1]);
  mov(tc[1],NULL,&ts[0]); /* S = tc[1] */
  uminus(ts[4],NULL,&tp[0]);
  loadf(0.00,NULL,&tc[2]);
  add(tp[0],tc[2],&tp[1]);
  mov(tp[1],NULL,&ts[7]); /* M = tp[1] */
  loadi(1,NULL,&tc[3]);
  mov(tc[3],NULL,&ts[3]); /* A = tc[3] */
  mov(tc[2],NULL,&ts[6]); /* D = tc[2] */
  loadi(10,NULL,&tc[4]);
  loadi(100,NULL,&tc[5]);
  divi(tc[4],tc[5],&tp[2]);
  mov(tp[2],NULL,&ts[3]); /* A = tp[2] */
  loadi(99,NULL,&tc[6]);
  divi(tc[6],tc[5],&tp[3]);
  mov(tp[3],NULL,&ts[5]); /* B = tp[3] */
  loadf(1.00,NULL,&tc[7]);
  loadi(2,NULL,&tc[8]);
  divi(tc[7],tc[8],&tp[4]);
  mov(tp[4],NULL,&ts[7]); /* M = tp[4] */
  param(ts[3],NULL,NULL);
  call("imprima",1,NULL);
  param(ts[5],NULL,NULL);
  call("imprima",1,NULL);
  param(ts[7],NULL,NULL);
  call("imprima",1,NULL);
  loads("oi",NULL,&tc[9]);
  mov(tc[9],NULL,&ts[0]); /* S = tc[9] */
  mov(tc[3],NULL,&ts[3]); /* A = tc[3] */
  loadf(2.20,NULL,&tc[10]);
  mov(tc[10],NULL,&ts[10]); /* O = tc[10] */
  nop(NULL,NULL,NULL);	/* no operation */
  mov(ts[0],NULL,&ts[1]); /* T = ts[0] */
  mov(ts[3],NULL,&ts[5]); /* B = ts[3] */
  mov(ts[10],NULL,&ts[9]); /* P = ts[10] */
  nop(NULL,NULL,NULL);	/* no operation */
  param(ts[0],NULL,NULL);
  call("imprima",1,NULL);
  param(ts[3],NULL,NULL);
  call("imprima",1,NULL);
  param(ts[10],NULL,NULL);
  call("imprima",1,NULL);
  nop(NULL,NULL,NULL);	/* no operation */
  loadf(1.10,NULL,&tc[11]);
  param(tc[11],NULL,NULL);
  call("imprima",1,NULL);
  param(tc[3],NULL,NULL);
  call("imprima",1,NULL);
  loads("alo #conStr",NULL,&tc[12]);
  param(tc[12],NULL,NULL);
  call("imprima",1,NULL);
  nop(NULL,NULL,NULL);	/* no operation */
  mov(tc[11],NULL,&ts[6]); /* D = tc[11] */
  nop(NULL,NULL,NULL);	/* no operation */
  loadi(3,NULL,&tc[13]);
  uminus(tc[13],NULL,&tp[5]);
  divi(tc[8],tp[5],&tp[6]);
  loadf(4.00,NULL,&tc[14]);
  add(tp[6],tc[14],&tp[7]);
  mult(tc[3],tp[7],&tp[8]);
  add(tc[7],tp[8],&tp[9]);
  mult(ts[3],ts[5],&tp[10]);
  sub(tp[9],tp[10],&tp[11]);
  add(tp[11],ts[4],&tp[12]);
  mov(tp[12],NULL,&ts[6]); /* D = tp[12] */
  comp_eq(ts[3],tc[3],&tp[13]);
  loadf(2.00,NULL,&tc[15]);
  comp_ne(ts[5],tc[15],&tp[14]);
  loadf(3.00,NULL,&tc[16]);
  comp_ge(ts[4],tc[16],&tp[15]);
  rela_an(tp[14],tp[15],&tp[16]);
  rela_or(tp[13],tp[16],&tp[17]);
  jump_f(tp[17],NULL,l1);	/* if(F) goto l1 */
  loadi(0,NULL,&tc[17]);
  comp_le(ts[6],tc[17],&tp[18]);
  jump_f(tp[18],NULL,l2);	/* if(F) goto l2 */
  loadf(111.10,NULL,&tc[18]);
  param(tc[18],NULL,NULL);
  call("imprima",1,NULL);
  add(tc[3],tc[3],&tp[19]);
  param(tp[19],NULL,NULL);
  call("saia",1,NULL);
  jump(NULL,NULL,l3);
l2:	/* else */
  param(ts[4],NULL,NULL);
  call("imprima",1,NULL);
  comp_gt(ts[3],tc[8],&tp[20]);
  comp_lt(ts[5],tc[16],&tp[21]);
  rela_an(tp[20],tp[21],&tp[22]);
  rela_no(tp[22],NULL,&tp[23]);
  jump_f(tp[23],NULL,l4);	/* if(F) goto l4 */
  loadf(222.20,NULL,&tc[19]);
  param(tc[19],NULL,NULL);
  call("imprima",1,NULL);
l4:	/* endif */
l3:	/* endif */
l1:	/* endif */
  nop(NULL,NULL,NULL);	/* no operation */
  param(ts[3],NULL,NULL);
  call("imprima",1,NULL);
  loads("?",NULL,&tc[0]);
  param(tc[0],NULL,NULL);
  call("imprima",1,NULL);
  call("leia",0,&ts[7]);
  comp_eq(ts[7],tc[17],&tp[24]);
  jump_f(tp[24],NULL,l5);	/* if(F) goto l5 */
  halt(NULL,NULL,NULL);
l5:	/* endif */
  nop(NULL,NULL,NULL);	/* no operation */
  param(tc[0],NULL,NULL);
  call("imprima",1,NULL);
  call("leia",0,&ts[8]);
l6:	/* while */
  loadi(5,NULL,&tc[20]);
  comp_lt(ts[7],tc[20],&tp[25]);
  jump_f(tp[25],NULL,l7);
  param(ts[7],NULL,NULL);
  call("imprima",1,NULL);
  add(ts[7],tc[3],&tp[26]);
  mov(tp[26],NULL,&ts[7]); /* M = tp[26] */
  jump(NULL,NULL,l6);
l7:	/* end_while */
  nop(NULL,NULL,NULL);	/* no operation */
  nop(NULL,NULL,NULL);	/* no operation */
  nop(NULL,NULL,NULL);	/* no operation */
  nop(NULL,NULL,NULL);	/* no operation */
  loadf(9.00,NULL,&tc[21]);
  param(tc[21], NULL, NULL);
  call("raiz", 1, &tp[27]);
  mov(tp[27],NULL,&ts[7]); /* M = tp[27] */
  param(tc[7], NULL, NULL);
  call("exp", 1, &tp[28]);
  mov(tp[28],NULL,&ts[8]); /* N = tp[28] */
  loads("raiz(9)=",NULL,&tc[22]);
  param(tc[22],NULL,NULL);
  call("imprima",1,NULL);
  param(ts[7],NULL,NULL);
  call("imprima",1,NULL);
  loads("exp(1) (ou e^1)=",NULL,&tc[23]);
  param(tc[23],NULL,NULL);
  call("imprima",1,NULL);
  param(ts[8],NULL,NULL);
  call("imprima",1,NULL);
  mod(tc[13],tc[8],&tp[29]);
  mov(tp[29],NULL,&ts[2]); /* variavel_3E = tp[29] */
  loads("variavel_3E",NULL,&tc[24]);
  param(tc[24],NULL,NULL);
  call("imprima",1,NULL);
  param(ts[2],NULL,NULL);
  call("imprima",1,NULL);
  nop(NULL,NULL,NULL);	/* no operation */
  loadi(0, NULL, &ts[11]); /* int i; */
  mov(tc[8],NULL,&ts[11]); /* i = tc[8] */
l8:	/* for */
  comp_lt(ts[11],ts[7],&tp[30]);
  jump_f(tp[30],NULL,l9);
  loads("laco:",NULL,&tc[25]);
  param(tc[25],NULL,NULL);
  call("imprima",1,NULL);
  param(ts[11],NULL,NULL);
  call("imprima",1,NULL);
  add(ts[11],tc[3],&tp[31]);
  mov(tp[31],NULL,&ts[11]); /* i = tp[31] */
  jump(NULL,NULL,l8);
l9:	/* end_for */
  param(tc[17],NULL,NULL);
  call("saia",1,NULL);
}
