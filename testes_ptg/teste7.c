//    Gerado pelo compilador PORTUGOL versao 1.0
//    Autor: Ruben Carlo Benante
//    Email: benante@gmail.com
//    Data: 23/04/2009

#include <stdio.h>
#include <stdlib.h>

float var[26] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

int main(void)
{
  var[0] = 1.00;
  var[1] = 2.00;
  var[2] = 3.00;
  if(var[0] != 1.00)
    {
      printf("%.2f\n", var[0]);
      printf("%.2f\n", var[1]);
    }
  printf("%.2f\n", var[2]);
}
