/*
    Compilador PORTUGOL v.1q
    Autor: Ruben Carlo Benante
    Email: benante@gmail.com
    Data: 23/04/2009
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "portugol.h"
#include "y.tab.h"

extern FILE* yyout;
char *geratemp(void);
char *geralabel(void);

char *gerac(tipoNodo *p, int n)
{
    char *q1=NULL, *q2=NULL, *q3=NULL, *qres=NULL, qtemp[20]="";

    if(p==NULL)
        return strdup(qtemp);

    switch(p->tipo)
    {
        case tipoConFlutuante:
            sprintf(qtemp,"%.2f",p->fcon.fval);
            break;
        case tipoID:
            sprintf(qtemp,"ts[%d]",p->id.i);
            break;
        case tipoOpr:
            switch(p->opr.oper)
            {
                case INICIO: //INICIO; comandos FIM;
                    if(n==0)
                        fprintf(yyout, "{\n");
                    gerac(p->opr.op[0], n+1);
                    if(n==0)
                        fprintf(yyout, "}\n");
                    break;
                case SE:
                    q1=gerac(p->opr.op[0], n+1); //expr
                    q2=geralabel();//label para o else
                    q3=geralabel();//label para o fim do se
                    fprintf(yyout, "  jump_f(");//pula para label_inicio_senao caso falso
                    fprintf(yyout, "%s,", q1);
                    fprintf(yyout, "%s,", "NULL");
                    fprintf(yyout, "%s);\n", q2);
                    gerac(p->opr.op[1], n+1); //then comandos
                    fprintf(yyout, "  jump(");//pulo incondicional para o fim_se (then pula else)
                    fprintf(yyout, "%s,", "NULL");
                    fprintf(yyout, "%s,", "NULL");
                    fprintf(yyout, "%s);\n", q3);
                    fprintf(yyout, "%s:\n", q2);//label_inicio_senao:
                    if(p->opr.nops>2)
                        gerac(p->opr.op[2], n+1); //else comandos
                    fprintf(yyout, "%s:\n", q3);//label_fim_se:
                    break;
                case IMPRIMA:
                    q1=gerac(p->opr.op[0], n+1);
                    fprintf(yyout, "  param(");
                    fprintf(yyout, "%s,", q1);
                    fprintf(yyout, "%s,", "NULL");
                    fprintf(yyout, "%s);\n", "NULL");

                    fprintf(yyout, "  call(");
                    fprintf(yyout, "%s,", "\"imprima\"");
                    fprintf(yyout, "%s,", "1"); //numero de parametros empilhados para passar para a funcao print
                    fprintf(yyout, "%s);\n", "NULL"); //funcao print nao tem retorno
                    break;
                case ';':
                    fprintf(yyout, "  nop(");
                    fprintf(yyout, "%s,", "NULL");
                    fprintf(yyout, "%s,", "NULL");
                    fprintf(yyout, "%s);\n", "NULL");
                    break;
                case 'l': /* lista de comandos */
                    gerac(p->opr.op[0], n);
                    gerac(p->opr.op[1], n);
                    break;
                case '=':
                    qres=gerac(p->opr.op[0], n+1);
                    q1=gerac(p->opr.op[1], n+1);
                    fprintf(yyout, "  mov(");
                    fprintf(yyout, "%s,", q1);
                    fprintf(yyout, "%s,", "NULL");
                    fprintf(yyout, "&%s);\n", qres);
                    break;
                case UMENOS:
                    q1=gerac(p->opr.op[0], n+1);
                    qres=geratemp();
                    fprintf(yyout, "  uminus(");
                    fprintf(yyout, "%s,", q1);
                    fprintf(yyout, "%s,", "NULL");
                    fprintf(yyout, "&%s);\n", qres);
                    break;
                case '+':
                    q1=gerac(p->opr.op[0], n+1);
                    q2=gerac(p->opr.op[1], n+1);
                    qres=geratemp();
                    fprintf(yyout, "  add(");
                    fprintf(yyout, "%s,", q1);
                    fprintf(yyout, "%s,", q2);
                    fprintf(yyout, "&%s);\n", qres);
                    break;
                case '-':
                    q1=gerac(p->opr.op[0], n+1);
                    q2=gerac(p->opr.op[1], n+1);
                    qres=geratemp();
                    fprintf(yyout, "  sub(");
                    fprintf(yyout, "%s,", q1);
                    fprintf(yyout, "%s,", q2);
                    fprintf(yyout, "&%s);\n", qres);
                    break;
                case '*':
                    q1=gerac(p->opr.op[0], n+1);
                    q2=gerac(p->opr.op[1], n+1);
                    qres=geratemp();
                    fprintf(yyout, "  mult(");
                    fprintf(yyout, "%s,", q1);
                    fprintf(yyout, "%s,", q2);
                    fprintf(yyout, "&%s);\n", qres);
                    break;
                case '/':
                    q1=gerac(p->opr.op[0], n+1);
                    q2=gerac(p->opr.op[1], n+1);
                    qres=geratemp();
                    fprintf(yyout, "  divi(");
                    fprintf(yyout, "%s,", q1);
                    fprintf(yyout, "%s,", q2);
                    fprintf(yyout, "&%s);\n", qres);
                    break;
                case '(':
                    qres=gerac(p->opr.op[0], n+1);
                    break;
                case LT:
                    q1=gerac(p->opr.op[0], n+1);
                    q2=gerac(p->opr.op[1], n+1);
                    qres=geratemp();
                    fprintf(yyout, "  comp_lt(");
                    fprintf(yyout, "%s,", q1);
                    fprintf(yyout, "%s,", q2);
                    fprintf(yyout, "&%s);\n", qres);
                    break;
                case GT:
                    q1=gerac(p->opr.op[0], n+1);
                    q2=gerac(p->opr.op[1], n+1);
                    qres=geratemp();
                    fprintf(yyout, "  comp_gt(");
                    fprintf(yyout, "%s,", q1);
                    fprintf(yyout, "%s,", q2);
                    fprintf(yyout, "&%s);\n", qres);
                    break;
                case GE:
                    q1=gerac(p->opr.op[0], n+1);
                    q2=gerac(p->opr.op[1], n+1);
                    qres=geratemp();
                    fprintf(yyout, "  comp_ge(");
                    fprintf(yyout, "%s,", q1);
                    fprintf(yyout, "%s,", q2);
                    fprintf(yyout, "&%s);\n", qres);
                    break;
                case LE:
                    q1=gerac(p->opr.op[0], n+1);
                    q2=gerac(p->opr.op[1], n+1);
                    qres=geratemp();
                    fprintf(yyout, "  comp_le(");
                    fprintf(yyout, "%s,", q1);
                    fprintf(yyout, "%s,", q2);
                    fprintf(yyout, "&%s);\n", qres);
                    break;
                case NE:
                    q1=gerac(p->opr.op[0], n+1);
                    q2=gerac(p->opr.op[1], n+1);
                    qres=geratemp();
                    fprintf(yyout, "  comp_ne(");
                    fprintf(yyout, "%s,", q1);
                    fprintf(yyout, "%s,", q2);
                    fprintf(yyout, "&%s);\n", qres);
                    break;
                case EQ:
                    q1=gerac(p->opr.op[0], n+1);
                    q2=gerac(p->opr.op[1], n+1);
                    qres=geratemp();
                    fprintf(yyout, "  comp_eq(");
                    fprintf(yyout, "%s,", q1);
                    fprintf(yyout, "%s,", q2);
                    fprintf(yyout, "&%s);\n", qres);
                    break;
                case E:
                    q1=gerac(p->opr.op[0], n+1);
                    q2=gerac(p->opr.op[1], n+1);
                    qres=geratemp();
                    fprintf(yyout, "  rela_an(");
                    fprintf(yyout, "%s,", q1);
                    fprintf(yyout, "%s,", q2);
                    fprintf(yyout, "&%s);\n", qres);
                    break;
                case OU:
                    q1=gerac(p->opr.op[0], n+1);
                    q2=gerac(p->opr.op[1], n+1);
                    qres=geratemp();
                    fprintf(yyout, "  rela_or(");
                    fprintf(yyout, "%s,", q1);
                    fprintf(yyout, "%s,", q2);
                    fprintf(yyout, "&%s);\n", qres);
                    break;
                case NAO:
                    q1=gerac(p->opr.op[0], n+1);
                    qres=geratemp();
                    fprintf(yyout, "  rela_no(");
                    fprintf(yyout, "%s,", q1);
                    fprintf(yyout, "%s,", "NULL");
                    fprintf(yyout, "&%s);\n", qres);
                    break;
            }
    }
    if(qres!=NULL)
        strcpy(qtemp,qres);
    free(q1); free(q2); free(q3); free(qres);
    return strdup(qtemp);
}

char *geratemp(void)
{
    static int t=-1;
    char tmp[20];
    t++;

    sprintf(tmp,"temp[%d]",t);
    return strdup(tmp);
}

char *geralabel(void)
{
    static int l=0;
    char tmp[20];
    l++;

    sprintf(tmp,"l%d",l);
    return strdup(tmp);
}
