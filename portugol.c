/*
    Compilador PORTUGOL v.1.1
    Autor: Ruben Carlo Benante
    Email: benante@gmail.com
    Data: 23/04/2009
*/

#include <stdio.h>
#include <string.h>
#include "portugol.h"
#include "y.tab.h"
extern FILE* yyout;

void gerac(tipoNodo *p, int n)
{
    char espaco[81]="                                                                                "; //80 espacos
    espaco[(((2*n)<81)?2*n:80)]='\0';

    if(p==NULL)
        return;

    switch(p->tipo)
    {
        case tipoConFlutuante:
            fprintf(yyout, "%.2f",p->fcon.fval);
            break;
        case tipoID:
            fprintf(yyout, "var[%d]",p->id.i);
            break;
        case tipoOpr:
            switch(p->opr.oper)
            {
                case INICIO:
                    fprintf(yyout, "%s{\n",espaco);
                    gerac(p->opr.op[0], n+1);
                    fprintf(yyout, "%s}\n",espaco);
                    break;
                case SE:
                    fprintf(yyout, "%sif(",espaco);
                    gerac(p->opr.op[0], n+1);
                    fprintf(yyout, ")\n");
                    gerac(p->opr.op[1], n+1);
                    if(p->opr.nops>2)
                    {
                        fprintf(yyout, "%selse\n",espaco);
                        gerac(p->opr.op[2], n+1);
                    }
                    break;
                case IMPRIMA:
                    if(p->opr.op[0]->tipo==tipoID)
                    {
                        fprintf(yyout, "%sprintf(\"%%.2f\\n\", ",espaco);
                        gerac(p->opr.op[0], n+1);
                        fprintf(yyout, ");\n");
                    }
                    else
                        if(p->opr.op[0]->tipo==tipoConFlutuante)
                        {
                            fprintf(yyout, "%sprintf(\"",espaco);
                            gerac(p->opr.op[0], n+1);
                            fprintf(yyout, "\\n\");\n");
                        }
                        else /* tipoOpr */
                        {
                            fprintf(yyout, "%sprintf(\"%%.2f\\n\", ( ",espaco);
                            gerac(p->opr.op[0], n+1);
                            fprintf(yyout, " ));\n");
                        }
                    break;
                case ';':
                    fprintf(yyout, "%s;\n",espaco);
                    break;
                case 'l': /* lista de comandos */
                    gerac(p->opr.op[0], n);
                    gerac(p->opr.op[1], n);
                    break;
                case '=':
                    fprintf(yyout, "%s",espaco);
                    gerac(p->opr.op[0], n+1);
                    fprintf(yyout, " = ");
                    gerac(p->opr.op[1], n+1);
                    fprintf(yyout, ";\n");
                    break;
                case UMENOS:
                    fprintf(yyout, "-");
                    gerac(p->opr.op[0], n+1);
                    break;
                case '+':
                    gerac(p->opr.op[0], n+1);
                    fprintf(yyout, " + ");
                    gerac(p->opr.op[1], n+1);
                    break;
                case '-':
                    gerac(p->opr.op[0], n+1);
                    fprintf(yyout, " - ");
                    gerac(p->opr.op[1], n+1);
                    break;
                case '*':
                    gerac(p->opr.op[0], n+1);
                    fprintf(yyout, " * ");
                    gerac(p->opr.op[1], n+1);
                    break;
                case '/':
                    gerac(p->opr.op[0], n+1);
                    fprintf(yyout, " / ");
                    gerac(p->opr.op[1], n+1);
                    break;
                case '(':
                    fprintf(yyout, "( ");
                    gerac(p->opr.op[0], n+1);
                    fprintf(yyout, " )");
                    break;
                case LT:
                    gerac(p->opr.op[0], n+1);
                    fprintf(yyout, " < ");
                    gerac(p->opr.op[1], n+1);
                    break;
                case GT:
                    gerac(p->opr.op[0], n+1);
                    fprintf(yyout, " > ");
                    gerac(p->opr.op[1], n+1);
                    break;
                case GE:
                    gerac(p->opr.op[0], n+1);
                    fprintf(yyout, " >= ");
                    gerac(p->opr.op[1], n+1);
                    break;
                case LE:
                    gerac(p->opr.op[0], n+1);
                    fprintf(yyout, " <= ");
                    gerac(p->opr.op[1], n+1);
                    break;
                case NE:
                    gerac(p->opr.op[0], n+1);
                    fprintf(yyout, " != ");
                    gerac(p->opr.op[1], n+1);
                    break;
                case EQ:
                    gerac(p->opr.op[0], n+1);
                    fprintf(yyout, " == ");
                    gerac(p->opr.op[1], n+1);
                    break;
                case E:
                    gerac(p->opr.op[0], n+1);
                    fprintf(yyout, " && ");
                    gerac(p->opr.op[1], n+1);
                    break;
                case OU:
                    gerac(p->opr.op[0], n+1);
                    fprintf(yyout, " || ");
                    gerac(p->opr.op[1], n+1);
                    break;
                case NAO:
                    fprintf(yyout, "!");
                    gerac(p->opr.op[0], n+1);
                    break;
            }
    }
     return;
}
