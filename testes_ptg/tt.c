#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int i=1;
  switch(i)
  {
  case 1:
      printf("dentro ");
      int i=-1;
      i++;
      printf("i=%d\n", i);
      break;
  case 2:
      return 1;
      break;
  default:
      return 2;
  }

  scanf("%d", &i);

  if(i==1)
  {
        int i=-1;
        i++;
        printf("if i==1: i=%d\n", i);
  }
  else
  {
        int i=-1;
        i++;
        printf("else (i!=1): i=%d\n", i);
  }
  printf("fora i=%d\n", i);
}
