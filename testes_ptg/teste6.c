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
  var[1] = -1.30;
  var[2] = 1.00 / ( var[0] * ( var[1] + 3.00 ) - 10.00 );
  printf("%.2f\n", ( var[0] + var[1] - 2.00 * var[2] ));
}
