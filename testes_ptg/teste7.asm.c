//    Gerado pelo compilador PORTUGOL versao 1q
//    Autor: Ruben Carlo Benante
//    Email: benante@gmail.com
//    Data: 23/04/2009

#include "quadruplas.h"

int main(void)
{
  mov(1.00,NULL,&ts[0]);
  mov(2.00,NULL,&ts[1]);
  mov(3.00,NULL,&ts[2]);
  comp_ne(ts[0],1.00,&temp[0]);
  jump_f(temp[0],NULL,l1);
  param(ts[0],NULL,NULL);
  call("imprima",1,NULL);
  param(ts[1],NULL,NULL);
  call("imprima",1,NULL);
  jump(NULL,NULL,l2);
l1:
l2:
  param(ts[2],NULL,NULL);
  call("imprima",1,NULL);
}
