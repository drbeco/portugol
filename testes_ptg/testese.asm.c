//    Gerado pelo compilador PORTUGOL versao 1q
//    Autor: Ruben Carlo Benante
//    Email: benante@gmail.com
//    Data: 23/04/2009

#include "quadruplas.h"

int main(void)
{
  mov(1.00,NULL,&ts[0]);
  comp_eq(ts[0],1.00,&temp[0]);
  jump_f(temp[0],NULL,l1);
  param(111.00,NULL,NULL);
  call("imprima",1,NULL);
  jump(NULL,NULL,l2);
l1:
  param(222.00,NULL,NULL);
  call("imprima",1,NULL);
l2:
  param(333.00,NULL,NULL);
  call("imprima",1,NULL);
  param(444.00,NULL,NULL);
  call("imprima",1,NULL);
  param(ts[0],NULL,NULL);
  call("imprima",1,NULL);
}
