/*
    Compilador PORTUGOL v.1.0
    Autor: Ruben Carlo Benante
    Email: benante@gmail.com
    Data: 23/04/2009
*/

#include <stdio.h>
#include <string.h>
#include "portugol.h"
#include "y.tab.h"

void gerac(tipoNodo *p, int n)
{
    char espaco[81]="                                                                                "; //80 espacos
    espaco[(((2*n)<81)?2*n:80)]='\0';

    if(p==NULL)
        return;

    switch(p->tipo)
    {
        case tipoConFlutuante:
            printf("%.2f",p->fcon.fval);
            break;
        case tipoID:
            printf("var[%d]",p->id.i);
            break;
        case tipoOpr:
            switch(p->opr.oper)
            {
                case INICIO:
                    printf("%s{\n",espaco);
                    gerac(p->opr.op[0], n+1);
                    printf("%s}\n",espaco);
                    break;
                case SE:
                    printf("%sif(",espaco);
                    gerac(p->opr.op[0], n+1);
                    printf(")\n");
                    gerac(p->opr.op[1], n+1);
                    if(p->opr.nops>2)
                    {
                        printf("%selse\n",espaco);
                        gerac(p->opr.op[2], n+1);
                    }
                    break;
                case IMPRIMA:
                    if(p->opr.op[0]->tipo==tipoID)
                    {
                        printf("%sprintf(\"%%.2f\\n\", ",espaco);
                        gerac(p->opr.op[0], n+1);
                        printf(");\n");
                    }
                    else
                        if(p->opr.op[0]->tipo==tipoConFlutuante)
                        {
                            printf("%sprintf(\"",espaco);
                            gerac(p->opr.op[0], n+1);
                            printf("\\n\");\n");
                        }
                        else /* tipoOpr */
                        {
                            printf("%sprintf(\"%%.2f\\n\", ( ",espaco);
                            gerac(p->opr.op[0], n+1);
                            printf(" ));\n");
                        }
                    break;
                case ';':
                    printf("%s;\n",espaco);
                    break;
                case 'l': /* lista de comandos */
                    gerac(p->opr.op[0], n);
                    gerac(p->opr.op[1], n);
                    break;
                case '=':
                    printf("%s",espaco);
                    gerac(p->opr.op[0], n+1);
                    printf(" = ");
                    gerac(p->opr.op[1], n+1);
                    printf(";\n");
                    break;
                case UMENOS:
                    printf("-");
                    gerac(p->opr.op[0], n+1);
                    break;
                case '+':
                    gerac(p->opr.op[0], n+1);
                    printf(" + ");
                    gerac(p->opr.op[1], n+1);
                    break;
                case '-':
                    gerac(p->opr.op[0], n+1);
                    printf(" - ");
                    gerac(p->opr.op[1], n+1);
                    break;
                case '*':
                    gerac(p->opr.op[0], n+1);
                    printf(" * ");
                    gerac(p->opr.op[1], n+1);
                    break;
                case '/':
                    gerac(p->opr.op[0], n+1);
                    printf(" / ");
                    gerac(p->opr.op[1], n+1);
                    break;
                case '(':
                    printf("( ");
                    gerac(p->opr.op[0], n+1);
                    printf(" )");
                    break;
                case LT:
                    gerac(p->opr.op[0], n+1);
                    printf(" < ");
                    gerac(p->opr.op[1], n+1);
                    break;
                case GT:
                    gerac(p->opr.op[0], n+1);
                    printf(" > ");
                    gerac(p->opr.op[1], n+1);
                    break;
                case GE:
                    gerac(p->opr.op[0], n+1);
                    printf(" >= ");
                    gerac(p->opr.op[1], n+1);
                    break;
                case LE:
                    gerac(p->opr.op[0], n+1);
                    printf(" <= ");
                    gerac(p->opr.op[1], n+1);
                    break;
                case NE:
                    gerac(p->opr.op[0], n+1);
                    printf(" != ");
                    gerac(p->opr.op[1], n+1);
                    break;
                case EQ:
                    gerac(p->opr.op[0], n+1);
                    printf(" == ");
                    gerac(p->opr.op[1], n+1);
                    break;
                case E:
                    gerac(p->opr.op[0], n+1);
                    printf(" && ");
                    gerac(p->opr.op[1], n+1);
                    break;
                case OU:
                    gerac(p->opr.op[0], n+1);
                    printf(" || ");
                    gerac(p->opr.op[1], n+1);
                    break;
                case NAO:
                    printf("!");
                    gerac(p->opr.op[0], n+1);
                    break;
            }
    }
     return;
}
