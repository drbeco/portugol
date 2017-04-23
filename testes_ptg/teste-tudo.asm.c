//    Gerado pelo compilador PORTUGOL versao 1q
//    Autor: Ruben Carlo Benante
//    Email: benante@gmail.com
//    Data: 23/04/2009

#include "quadruplas.h"

int main(void)
{
  mov(1.00,NULL,&ts[0]);
  mov(2.00,NULL,&ts[1]);
  comp_eq(ts[1],2.00,&temp[0]);
  jump_f(temp[0],NULL,l1);
  param(123.00,NULL,NULL);
  call("imprima",1,NULL);
  jump(NULL,NULL,l2);
l1:
l2:
  mov(3.00,NULL,&ts[2]);
  uminus(3.00,NULL,&temp[1]);
  divi(2.00,temp[1],&temp[2]);
  add(temp[2],4.00,&temp[3]);
  mult(1.00,temp[3],&temp[4]);
  add(1.00,temp[4],&temp[5]);
  mult(ts[0],ts[1],&temp[6]);
  sub(temp[5],temp[6],&temp[7]);
  add(temp[7],ts[2],&temp[8]);
  mov(temp[8],NULL,&ts[3]);
  comp_eq(ts[0],1.00,&temp[9]);
  comp_ne(ts[1],2.00,&temp[10]);
  comp_ge(ts[2],3.00,&temp[11]);
  rela_an(temp[10],temp[11],&temp[12]);
  rela_or(temp[9],temp[12],&temp[13]);
  jump_f(temp[13],NULL,l3);
  comp_le(ts[3],0.00,&temp[14]);
  jump_f(temp[14],NULL,l5);
  param(111.10,NULL,NULL);
  call("imprima",1,NULL);
  jump(NULL,NULL,l6);
l5:
  param(ts[2],NULL,NULL);
  call("imprima",1,NULL);
  comp_gt(ts[0],2.00,&temp[15]);
  comp_lt(ts[1],3.00,&temp[16]);
  rela_an(temp[15],temp[16],&temp[17]);
  rela_no(temp[17],NULL,&temp[18]);
  jump_f(temp[18],NULL,l7);
  param(222.20,NULL,NULL);
  call("imprima",1,NULL);
  jump(NULL,NULL,l8);
l7:
l8:
l6:
  jump(NULL,NULL,l4);
l3:
l4:
  nop(NULL,NULL,NULL);
  param(ts[0],NULL,NULL);
  call("imprima",1,NULL);
  param(ts[1],NULL,NULL);
  call("imprima",1,NULL);
  param(ts[2],NULL,NULL);
  call("imprima",1,NULL);
  nop(NULL,NULL,NULL);
  param(ts[3],NULL,NULL);
  call("imprima",1,NULL);
}
