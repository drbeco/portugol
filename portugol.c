/*
    Compilador PORTUGOL v.2q
    Autor: Ruben Carlo Benante
    Email: benante@gmail.com
    Data criação: 23/04/2009
    Data modificação: 25/05/2009
*/

//Falta: (to do)
//      IMPORTE = 273,
//      DEFINE = 272,

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "portugol.h"
#include "y.tab.h"

char *sTipoDado[14]={"tipoIdIndef", "tipoConInt", "tipoConFloat", "tipoConStr", "tipoIdInt", "tipoIdFloat", "tipoIdStr", "tipoIdFuncInt", "tipoIdFuncFloat", "tipoIdFuncDouble", "tipoIdFuncChar", "tipoIdFuncStr", "tipoIdFuncVoid", "tipoIdFuncPVoid"};
char *sTipoBase[4]={"tipoIndef", "tipoInt", "tipoFloat", "tipoStr"};
extern int debugArvore;
extern int debugTabela;

char *gera_quad(nodo *tn, int n)
{
    char *q1=NULL, *q2=NULL, *q3=NULL, *qres=NULL, qtemp[20]="";
    char msg[128];
    int itemp, t0, t1;

    if(tn==NULL)
        return strdup(qtemp);

    switch(tn->tipoN)
    {
        case tipoSimb:
            switch(tn->pSimb->tipoD)
            {
                case tipoConInt:
                    sprintf(qtemp,"tc[%d]",tn->pSimb->idx); //achaId preenche idx
                    if(!tn->pSimb->uso)
                        fprintf(yyout, "  loadi(%d,%s,&%s);\n", tn->pSimb->ival, "NULL", qtemp);
                    tn->pSimb->uso=1;
                    break;
                case tipoConFloat:
                    sprintf(qtemp,"tc[%d]",tn->pSimb->idx);
                    if(!tn->pSimb->uso)
                        fprintf(yyout, "  loadf(%.2f,%s,&%s);\n", tn->pSimb->fval, "NULL", qtemp);
                    tn->pSimb->uso=1;
                    break;
                case tipoConStr:
                    sprintf(qtemp,"tc[%d]",tn->pSimb->idx);
                    if(!tn->pSimb->uso)
                        fprintf(yyout, "  loads(%s,%s,&%s);\n", tn->pSimb->sval, "NULL", qtemp);
                    tn->pSimb->uso=1;
                    break;
                case tipoIdInt:
                case tipoIdFloat:
                case tipoIdStr:
                    sprintf(qtemp,"ts[%d]",tn->pSimb->idx);
                    break;
                case tipoIdIndef:
                default: //funcao?
                    sprintf(qtemp,"ts[?]");
                    break;
            }
        case tipoOper:
            switch(tn->opr.oper)
            {
                case INICIO: //INICIO; comandos FIM;
                    if(n==0)
                    {
                        if(debugTabela)
                            printTS();
                        if(debugArvore)
                            printNodo(tn,0,"tn");
                    }
                    gera_quad(tn->opr.ptn[0], n+1);
                    if(n==0)
                        fprintf(yyout, "}\n");
                    break;
                case SE:
                    q1=gera_quad(tn->opr.ptn[0], n+1); //expr
                    q2=geraLB(&itemp);//inicio_senao ou fim_se
                    if(tn->opr.nops>2) //tem senao
                        q3=geraLB(&itemp);//fim_se
                    fprintf(yyout, "  jump_f(");//caso falso pula para senao ou para fim_se
                    fprintf(yyout, "%s,", q1);
                    fprintf(yyout, "%s,", "NULL");
                    fprintf(yyout, "%s);\t/* if(F) goto %s */\n", q2, q2); //pula para senao ou para fim_se
                    gera_quad(tn->opr.ptn[1], n+1); //comandos do entao
                    if(tn->opr.nops>2) //tem senao, pula para fim_se
                    {
                        fprintf(yyout, "  jump(");//pulo incondicional para fim_se
                        fprintf(yyout, "%s,", "NULL");
                        fprintf(yyout, "%s,", "NULL");
                        fprintf(yyout, "%s);\n", q3);
                        fprintf(yyout, "%s:\t/* else */\n", q2);//inicio_senao:
                        gera_quad(tn->opr.ptn[2], n+1); //comandos senao
                        fprintf(yyout, "%s:\t/* endif */\n", q3);//fim_se:
                    }
                    else //nao tem senao
                        fprintf(yyout, "%s:\t/* endif */\n", q2);//fim_se:
                    break;
                case IMPRIMA:
                    q1=gera_quad(tn->opr.ptn[0], n+1); //ts, tp ou tc;
                    fprintf(yyout, "  param(%s,NULL,NULL);\n", q1); //string ts[0], tc[0] ou tp[0]
                    fprintf(yyout, "  call(\"imprima\",1,NULL);\n");
                    break;
                case LEIA:
                    qres=gera_quad(tn->opr.ptn[0], n+1);
                    if(tn->opr.ptn[0]->pSimb->tipoD!=tipoIdFloat)
                    {
                        sprintf(msg,"Chamada da funcao leia <tipoIdFloat> com argumento de tipo incorreto. leia <%s>.", nomeTipo(tn->opr.ptn[0]));
                        erroSemantico(msg, tn->linha);
                    }
                    tabelaSimb *ps = achaStr("?");
                    sprintf(qtemp,"tc[%d]",ps->idx);
                    if(!ps->uso)
                        fprintf(yyout, "  loads(\"?\",NULL,&%s);\n", qtemp);
                    ps->uso=1;
                    fprintf(yyout, "  param(%s,NULL,NULL);\n", qtemp);
                    fprintf(yyout, "  call(\"imprima\",1,NULL);\n");
                    fprintf(yyout, "  call(\"leia\",0,&%s);\n", qres);
                    break;
                case ENQUANTO:
                    q1=geraLB(&itemp); // inicio_enquanto
                    q2=geraLB(&itemp); // fim_enquanto
                    fprintf(yyout, "%s:\t/* while */\n", q1); // inicio_enquanto:
                    q3=gera_quad(tn->opr.ptn[0], n+1); // expr condicional
                    fprintf(yyout, "  jump_f(%s,%s,%s);\n",q3,"NULL",q2); // caso falso pula para fim_enquanto
                    gera_quad(tn->opr.ptn[1], n+1); // comandos do laco
                    fprintf(yyout, "  jump(%s,%s,%s);\n","NULL","NULL",q1); // pula para inicio_enquanto
                    fprintf(yyout, "%s:\t/* end_while */\n", q2); // fim_enquanto:
                    break;
                case PARA:
                    q1=geraLB(&itemp); //loop_para:
                    q2=geraLB(&itemp); //fim_para:
                    gera_quad(tn->opr.ptn[0], n+1); //stmt1=inicializacao
                    fprintf(yyout, "%s:\t/* for */\n", q1);//loop_para:
                    q3=gera_quad(tn->opr.ptn[1], n+1); //stmt2=condicao
                    fprintf(yyout, "  jump_f(%s,NULL,%s);\n", q3, q2);//se falso pula para fim_para
                    gera_quad(tn->opr.ptn[3], n+1); //stmt4=comandos do loop
                    gera_quad(tn->opr.ptn[2], n+1); //stmt3=incremento
                    fprintf(yyout, "  jump(NULL,NULL,%s);\n",q1);//pula para loop_para
                    fprintf(yyout, "%s:\t/* end_for */\n", q2);//fim_para:
                    break;
                case FUNC: // | IDENT '(' expr ')'  { $$ = opr(FUNC, 2, $1, $3); }
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    q2=gera_quad(tn->opr.ptn[1], n+1);
                    qres=geraTP(&itemp);
                    t0=pegaTipoBase(tn->opr.ptn[0]); //tipoInt, tipoFloat, tipoStr, tipoIndef
                    t1=pegaTipoBase(tn->opr.ptn[1]); //tipoInt, tipoFloat, tipoStr, tipoIndef
                    if(t1 == tipoIndef)
                    {
                        sprintf(msg,"Operando nao declarado na chamada da funcao <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                        erroSemantico(msg, tn->linha);
                    }
                    if(t1 == tipoStr)
                    {
                        sprintf(msg,"Funcao <%s> com argumento tipoStr nao implementada.", tn->opr.ptn[0]->pSimb->idNome);
                        erroSemantico(msg, tn->linha);
                    }
                    tn->opr.tipoBOper = tipoFloat;//bug: esta fixo! De onde vem o tipo de retorno?
                    fprintf(yyout,"  param(%s, NULL, NULL);\n  call(\"%s\", 1, &%s);\n", q2, tn->opr.ptn[0]->pSimb->idNome, qres);
                    break;
                case ABORTE:
                    fprintf(yyout, "  halt(NULL,NULL,NULL);\n");
                    break;
                case SAIA:
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    fprintf(yyout, "  param(%s,%s,%s);\n",q1,"NULL","NULL");
                    fprintf(yyout, "  call(%s,%s,%s);\n","\"saia\"","1","NULL");
                    break;
                case INT:
                    if(tn->opr.ptn[0]->pSimb->tipoD!=tipoIdIndef)
                    {
                        sprintf(msg,"Redeclaracao da variavel <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                        erroSemantico(msg, tn->linha);
                    }
                    tn->opr.ptn[0]->pSimb->tipoD=tipoIdInt;
                    tn->opr.ptn[0]->pSimb->idx=geraTS();
                    fprintf(yyout,"  loadi(0, NULL, &ts[%d]); /* int %s; */\n", tn->opr.ptn[0]->pSimb->idx, tn->opr.ptn[0]->pSimb->idNome);
                    break;
                case REAL:
                    if(tn->opr.ptn[0]->pSimb->tipoD!=tipoIdIndef)
                    {
                        sprintf(msg,"Redeclaracao da variavel <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                        erroSemantico(msg, tn->linha);
                    }
                    tn->opr.ptn[0]->pSimb->tipoD=tipoIdFloat;
                    tn->opr.ptn[0]->pSimb->idx=geraTS();
                    fprintf(yyout,"  loadf(0.00, NULL, &ts[%d]); /* real %s; */\n", tn->opr.ptn[0]->pSimb->idx, tn->opr.ptn[0]->pSimb->idNome);
                    break;
                case TEXTO:
                    if(tn->opr.ptn[0]->pSimb->tipoD!=tipoIdIndef)
                    {
                        sprintf(msg,"Redeclaracao da variavel <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                        erroSemantico(msg, tn->linha);
                    }
                    tn->opr.ptn[0]->pSimb->tipoD=tipoIdStr;
                    tn->opr.ptn[0]->pSimb->idx=geraTS();
                    fprintf(yyout,"  loads(\"\\0\", NULL, &ts[%d]); /* str %s; */\n", tn->opr.ptn[0]->pSimb->idx, tn->opr.ptn[0]->pSimb->idNome);
                    break;
                case ';':
                    fprintf(yyout, "  nop(NULL,NULL,NULL);\t/* no operation */\n");
                    break;
                case 'l': /* lista de comandos */
                    gera_quad(tn->opr.ptn[0], n);
                    gera_quad(tn->opr.ptn[1], n);
                    break;
                case '=':
                    qres=gera_quad(tn->opr.ptn[0], n+1);
                    q1=gera_quad(tn->opr.ptn[1], n+1);
                    if(tn->opr.ptn[0]->pSimb->tipoD == tipoIdIndef)
                    {
                        sprintf(msg,"Atribuicao invalida a variavel <%s> nao declarada.", tn->opr.ptn[0]->pSimb->idNome);
                        erroSemantico(msg, tn->linha);
                    }
                    if(!variavel(tn->opr.ptn[0])) // tentou func(a)=1;
                    {
                        sprintf(msg,"Atribuicao invalida a uma funcao <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                        erroSemantico(msg, tn->linha);
                    }
                    t0=pegaTipoBase(tn->opr.ptn[0]); //tipoInt, tipoFloat, tipoStr, tipoIndef
                    t1=pegaTipoBase(tn->opr.ptn[1]);
                    if(t0==t1)
                        fprintf(yyout, "  mov(%s,NULL,&%s); /* %s = %s */\n", q1, qres, tn->opr.ptn[0]->pSimb->idNome, q1);
                    else
                    { /* tipos diferentes */
                        sprintf(msg,"Atribuicao de tipos diferentes. <%s, %s> = <%s, %s>.", nomeTipo(tn->opr.ptn[0]), sTipoBase[t0], nomeTipo(tn->opr.ptn[1]), sTipoBase[t1]);
                        erroSemantico(msg, tn->linha);
                    }
                    break;
                case UMENOS:
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    qres=geraTP(&itemp);
                    tn->opr.tipoBOper = pegaTipoBase(tn->opr.ptn[0]);
                    if(tn->opr.tipoBOper  == tipoIndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de menos unario. - <%s>", sTipoBase[tn->opr.tipoBOper]);
                        erroSemantico(msg, tn->linha);
                    }
                    fprintf(yyout, "  uminus(%s,NULL,&%s);\n", q1, qres);
                    break;
                case '+':
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    q2=gera_quad(tn->opr.ptn[1], n+1);
                    qres=geraTP(&itemp);
                    t0=pegaTipoBase(tn->opr.ptn[0]);
                    t1=pegaTipoBase(tn->opr.ptn[1]);
                    if(t0 == tipoIndef || t1 == tipoIndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de soma. <%s> + <%s>", sTipoBase[t0], sTipoBase[t1]);
                        erroSemantico(msg, tn->linha);
                    }
                    if((t0 == tipoStr || t1 == tipoStr) && (t0 != tipoStr || t1 != tipoStr))
                        erroSemantico("Nao posso somar textos com numeros.", tn->linha);
                    if(t0==tipoFloat || t1==tipoFloat)
                        tn->opr.tipoBOper = tipoFloat;
                    else
                        tn->opr.tipoBOper = tipoInt;//t0; //bug:
                    //erroSemantico("Nao posso somar textos com numeros.", tn->linha);
                    //bug: cade a soma de strings? tipoBOPer=tipoStr
                    if(t0 == tipoStr)
                        tn->opr.tipoBOper = tipoStr;
                    fprintf(yyout, "  add(%s,%s,&%s);\n", q1, q2, qres);
                    break;
                case '-':
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    q2=gera_quad(tn->opr.ptn[1], n+1);
                    qres=geraTP(&itemp);
                    t0=pegaTipoBase(tn->opr.ptn[0]);
                    t1=pegaTipoBase(tn->opr.ptn[1]);
                    if(t0 == tipoIndef || t1 == tipoIndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de subtracao. <%s> - <%s>", sTipoBase[t0], sTipoBase[t1]);
                        erroSemantico(msg, tn->linha);
                    }
                    if(t0 == tipoStr || t1 == tipoStr)
                        erroSemantico("Nao posso subtrair textos.", tn->linha);
                    if(t0==tipoFloat || t1==tipoFloat)
                        tn->opr.tipoBOper = tipoFloat;
                    else
                        tn->opr.tipoBOper = tipoInt;
                    fprintf(yyout, "  sub(%s,%s,&%s);\n", q1, q2, qres);
                    break;
                case '*':
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    q2=gera_quad(tn->opr.ptn[1], n+1);
                    qres=geraTP(&itemp);
                    t0=pegaTipoBase(tn->opr.ptn[0]);
                    t1=pegaTipoBase(tn->opr.ptn[1]);
                    if(t0 == tipoIndef || t1 == tipoIndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de multiplicacao. <%s> * <%s>", sTipoBase[t0], sTipoBase[t1]);
                        erroSemantico(msg, tn->linha);
                    }
                    if(t0 == tipoStr || t1 == tipoStr)
                        erroSemantico("Nao posso multiplicar textos.", tn->linha);
                    if(t0==tipoFloat || t1==tipoFloat)
                        tn->opr.tipoBOper = tipoFloat;
                    else
                        tn->opr.tipoBOper = tipoInt;
                    fprintf(yyout, "  mult(%s,%s,&%s);\n", q1, q2, qres);
                    break;
                case '/':
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    q2=gera_quad(tn->opr.ptn[1], n+1);
                    qres=geraTP(&itemp);
                    t0=pegaTipoBase(tn->opr.ptn[0]);
                    t1=pegaTipoBase(tn->opr.ptn[1]);
                    if(t0 == tipoIndef || t1 == tipoIndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de divisao. <%s> / <%s>", sTipoBase[t0], sTipoBase[t1]);
                        erroSemantico(msg, tn->linha);
                    }
                    if(t0 == tipoStr || t1 == tipoStr)
                        erroSemantico("Nao posso dividir textos.", tn->linha);
                    if(t0==tipoFloat || t1==tipoFloat)
                        tn->opr.tipoBOper = tipoFloat;
                    else
                        tn->opr.tipoBOper = tipoInt;
                    fprintf(yyout, "  divi(%s,%s,&%s);\n", q1, q2, qres);
                    break;
                case '%':
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    q2=gera_quad(tn->opr.ptn[1], n+1);
                    qres=geraTP(&itemp);
                    t0=pegaTipoBase(tn->opr.ptn[0]);
                    t1=pegaTipoBase(tn->opr.ptn[1]);
                    if(t0 == tipoIndef || t1 == tipoIndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de modulo. <%s> % <%s>", sTipoBase[t0], sTipoBase[t1]);
                        erroSemantico(msg, tn->linha);
                    }
                    if(t0 == tipoStr || t1 == tipoStr)
                        erroSemantico("Nao posso calcular modulo de textos.", tn->linha);
                    if(t0 == tipoFloat || t1 == tipoFloat)
                        erroSemantico("Nao posso calcular modulo de <tipoFloat>.", tn->linha);
                    tn->opr.tipoBOper = tipoInt;
                    fprintf(yyout, "  mod(%s,%s,&%s);\n", q1, q2, qres);
                    break;
                case '(':
                    qres=gera_quad(tn->opr.ptn[0], n+1);
                    tn->opr.tipoBOper = pegaTipoBase(tn->opr.ptn[0]);
                    if(tn->opr.tipoBOper  == tipoIndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de parenteses. ( <%s> )", sTipoBase[tn->opr.tipoBOper]);
                        erroSemantico(msg, tn->linha);
                    }
                    break;
                case LT: //compara texto com texto ou numero com numero. retorna tipoInt
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    q2=gera_quad(tn->opr.ptn[1], n+1);
                    qres=geraTP(&itemp);
                    t0=pegaTipoBase(tn->opr.ptn[0]);
                    t1=pegaTipoBase(tn->opr.ptn[1]);
                    if(t0 == tipoIndef || t1 == tipoIndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de menor-que. <%s> < <%s>", sTipoBase[t0], sTipoBase[t1]);
                        erroSemantico(msg, tn->linha);
                    }
                    if((t0 == tipoStr || t1 == tipoStr) && (t0 != tipoStr || t1 != tipoStr))
                        erroSemantico("Nao posso comparar (<) textos com numeros.", tn->linha);
                    tn->opr.tipoBOper = tipoInt;
                    fprintf(yyout, "  comp_lt(%s,%s,&%s);\n", q1, q2, qres);
                    break;
                case GT:
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    q2=gera_quad(tn->opr.ptn[1], n+1);
                    qres=geraTP(&itemp);
                    t0=pegaTipoBase(tn->opr.ptn[0]);
                    t1=pegaTipoBase(tn->opr.ptn[1]);
                    if(t0 == tipoIndef || t1 == tipoIndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de maior-que. <%s> > <%s>", sTipoBase[t0], sTipoBase[t1]);
                        erroSemantico(msg, tn->linha);
                    }
                    if((t0 == tipoStr || t1 == tipoStr) && (t0 != tipoStr || t1 != tipoStr))
                        erroSemantico("Nao posso comparar (>) textos com numeros.", tn->linha);
                    tn->opr.tipoBOper = tipoInt;
                    fprintf(yyout, "  comp_gt(%s,%s,&%s);\n", q1, q2, qres);
                    break;
                case GE:
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    q2=gera_quad(tn->opr.ptn[1], n+1);
                    qres=geraTP(&itemp);
                    t0=pegaTipoBase(tn->opr.ptn[0]);
                    t1=pegaTipoBase(tn->opr.ptn[1]);
                    if(t0 == tipoIndef || t1 == tipoIndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de maior-igual. <%s> >= <%s>", sTipoBase[t0], sTipoBase[t1]);
                        erroSemantico(msg, tn->linha);
                    }
                    if((t0 == tipoStr || t1 == tipoStr) && (t0 != tipoStr || t1 != tipoStr))
                        erroSemantico("Nao posso comparar (>=) textos com numeros.", tn->linha);
                    tn->opr.tipoBOper = tipoInt;
                    fprintf(yyout, "  comp_ge(%s,%s,&%s);\n", q1, q2, qres);
                    break;
                case LE:
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    q2=gera_quad(tn->opr.ptn[1], n+1);
                    qres=geraTP(&itemp);
                    t0=pegaTipoBase(tn->opr.ptn[0]);
                    t1=pegaTipoBase(tn->opr.ptn[1]);
                    if(t0 == tipoIndef || t1 == tipoIndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de menor-igual. <%s> <= <%s>", sTipoBase[t0], sTipoBase[t1]);
                        erroSemantico(msg, tn->linha);
                    }
                    if((t0 == tipoStr || t1 == tipoStr) && (t0 != tipoStr || t1 != tipoStr))
                        erroSemantico("Nao posso comparar (<=) textos com numeros.", tn->linha);
                    tn->opr.tipoBOper = tipoInt;
                    fprintf(yyout, "  comp_le(%s,%s,&%s);\n", q1, q2, qres);
                    break;
                case NE:
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    q2=gera_quad(tn->opr.ptn[1], n+1);
                    qres=geraTP(&itemp);
                    t0=pegaTipoBase(tn->opr.ptn[0]);
                    t1=pegaTipoBase(tn->opr.ptn[1]);
                    if(t0 == tipoIndef || t1 == tipoIndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de diferente. <%s> != <%s>", sTipoBase[t0], sTipoBase[t1]);
                        erroSemantico(msg, tn->linha);
                    }
                    if((t0 == tipoStr || t1 == tipoStr) && (t0 != tipoStr || t1 != tipoStr))
                        erroSemantico("Nao posso comparar (!=) textos com numeros.", tn->linha);
                    tn->opr.tipoBOper = tipoInt;
                    fprintf(yyout, "  comp_ne(%s,%s,&%s);\n", q1, q2, qres);
                    break;
                case EQ:
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    q2=gera_quad(tn->opr.ptn[1], n+1);
                    qres=geraTP(&itemp);
                    t0=pegaTipoBase(tn->opr.ptn[0]);
                    t1=pegaTipoBase(tn->opr.ptn[1]);
                    if(t0 == tipoIndef || t1 == tipoIndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de igual. <%s> == <%s>", sTipoBase[t0], sTipoBase[t1]);
                        erroSemantico(msg, tn->linha);
                    }
                    if((t0 == tipoStr || t1 == tipoStr) && (t0 != tipoStr || t1 != tipoStr))
                        erroSemantico("Nao posso comparar (==) textos com numeros.", tn->linha);
                    tn->opr.tipoBOper = tipoInt;
                    fprintf(yyout, "  comp_eq(%s,%s,&%s);\n", q1, q2, qres);
                    break;
                case E:
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    q2=gera_quad(tn->opr.ptn[1], n+1);
                    qres=geraTP(&itemp);
                    t0=pegaTipoBase(tn->opr.ptn[0]);
                    t1=pegaTipoBase(tn->opr.ptn[1]);
                    if(t0 == tipoIndef || t1 == tipoIndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de E logico. <%s> E <%s>", sTipoBase[t0], sTipoBase[t1]);
                        erroSemantico(msg, tn->linha);
                    }
                    if(t0 == tipoStr || t1 == tipoStr)
                        erroSemantico("Nao posso operar (E) em textos.", tn->linha);
                    tn->opr.tipoBOper = tipoInt;
                    fprintf(yyout, "  rela_an(%s,%s,&%s);\n", q1,q2,qres);
                    break;
                case OU:
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    q2=gera_quad(tn->opr.ptn[1], n+1);
                    qres=geraTP(&itemp);
                    t0=pegaTipoBase(tn->opr.ptn[0]);
                    t1=pegaTipoBase(tn->opr.ptn[1]);
                    if(t0 == tipoIndef || t1 == tipoIndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de OU logico. <%s> OU <%s>", sTipoBase[t0], sTipoBase[t1]);
                        erroSemantico(msg, tn->linha);
                    }
                    if(t0 == tipoStr || t1 == tipoStr)
                        erroSemantico("Nao posso operar (OU) em textos.", tn->linha);
                    tn->opr.tipoBOper = tipoInt;
                    fprintf(yyout, "  rela_or(%s,%s,&%s);\n", q1,q2,qres);
                    break;
                case NAO:
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    qres=geraTP(&itemp);
                    t0=pegaTipoBase(tn->opr.ptn[0]);
                    if(t0 == tipoIndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de NAO logico. NAO <%s>", sTipoBase[t0]);
                        erroSemantico(msg, tn->linha);
                    }
                    if(t0 == tipoStr)
                        erroSemantico("Nao posso operar (NAO) em textos.", tn->linha);
                    tn->opr.tipoBOper = tipoInt;
                    fprintf(yyout, "  rela_no(%s,%s,&%s);\n", q1,"NULL",qres);
                    break;
            }
    }
    if(qres!=NULL)
        strcpy(qtemp,qres);
    free(q1); free(q2); free(q3); free(qres);
    return strdup(qtemp);
}

int geraTF(void) //tabela de funcoes
{
    static int itf=-1;
    itf++;
    return itf;
}

int geraTC(void) //tabela de constantes
{
    static int itc=-1;
    itc++;
    return itc;
}

int geraTS(void) //tabela de variaveis
{
    static int its=-1;
    its++;
    return its;
}

char *geraTP(int *i)
{
    static int itp=-1;
    char temp[20];
    itp++;
    *i=itp;
    sprintf(temp,"tp[%d]",itp);
    return strdup(temp);
}

char *geraLB(int *i)
{
    static int l=0;
    char tmp[20];
    l++;
    *i=l;

    sprintf(tmp,"l%d",l);
    return strdup(tmp);
}

void printTS(void)
{
    int n;

    printf("---------------------------- Tabela de Simbolos ----------------------------\n");
    for(n=0; n<MAX_SIMB; n++)
    {
        if(!tabSimb[n].idNome)
            return;
        printf("----------------------------\n");
        printf("tabSimb[%d].tipoD=%s\n", n, sTipoDado[tabSimb[n].tipoD]);
        printf("tabSimb[%d].idx=%d\n", n, tabSimb[n].idx);
        printf("tabSimb[%d].idNome=%s\n", n, tabSimb[n].idNome);
        switch(tabSimb[n].tipoD)
        {
            case tipoConInt:
                printf("tabSimb[%d].uso=%d\n", n, tabSimb[n].uso);
                printf("tabSimb[%d].ival=%d\n", n, tabSimb[n].ival);
                break;
            case tipoConFloat:
                printf("tabSimb[%d].uso=%d\n", n, tabSimb[n].uso);
                printf("tabSimb[%d].fval=%.2f\n", n, tabSimb[n].fval);
                break;
            case tipoConStr:
                printf("tabSimb[%d].uso=%d\n", n, tabSimb[n].uso);
                printf("tabSimb[%d].sval=%s\n", n, tabSimb[n].sval);
                break;
            case tipoIdInt:
            case tipoIdFloat:
            case tipoIdStr:
            case tipoIdIndef:
                break;
            case tipoIdFuncInt:
                printf("tabSimb[%d].idFunc=%s\n", n, tabSimb[n].idFunc);
                printf("tabSimb[%d].ifunc=%u\n", n, tabSimb[n].ifunc);
                break;
            case tipoIdFuncFloat:
                printf("tabSimb[%d].idFunc=%s\n", n, tabSimb[n].idFunc);
                printf("tabSimb[%d].ffunc=%u\n", n, tabSimb[n].ffunc);
                break;
            case tipoIdFuncDouble:
                printf("tabSimb[%d].idFunc=%s\n", n, tabSimb[n].idFunc);
                printf("tabSimb[%d].dfunc=%u\n", n, tabSimb[n].dfunc);
                break;
            case tipoIdFuncChar:
                break;
            case tipoIdFuncStr:
                printf("tabSimb[%d].idFunc=%s\n", n, tabSimb[n].idFunc);
                printf("tabSimb[%d].sfunc=%u\n", n, tabSimb[n].sfunc);
                break;
            case tipoIdFuncVoid:
                printf("tabSimb[%d].idFunc=%s\n", n, tabSimb[n].idFunc);
                printf("tabSimb[%d].vfunc=%u\n", n, tabSimb[n].vfunc);
                break;
        }
    }
}

void printNodo(nodo *tn, int n, char *var)
{
    char *nome;
    int t;

    if(!tn)
        return;

    nome=nomeTipo(tn);

    if(n==0)
        printf("---------------------------- Arvore Sintatica ----------------------------\n");
    if(tn->tipoN==tipoSimb)
    {
        printf("----------------------------\n");
        printf("(%d) %s->pSimb->tipoD=%s\n", n, var, nome);
        printf("(%d) %s->pSimb->idx=%d\n", n, var, tn->pSimb->idx);
        printf("(%d) %s->pSimb->idNome=%s\n", n, var, tn->pSimb->idNome);
        switch(tn->pSimb->tipoD)
        {
            case tipoConInt:
                printf("(%d) %s->pSimb->uso=%d\n", n, var, tn->pSimb->uso);
                printf("(%d) %s->pSimb->ival=%d\n", n, var, tn->pSimb->ival);
                break;
            case tipoConFloat:
                printf("(%d) %s->pSimb->uso=%d\n", n, var, tn->pSimb->uso);
                printf("(%d) %s->pSimb->fval=%.2f\n", n, var, tn->pSimb->fval);
                break;
            case tipoConStr:
                printf("(%d) %s->pSimb->uso=%d\n", n, var, tn->pSimb->uso);
                printf("(%d) %s->pSimb->sval=%s\n", n, var, tn->pSimb->sval);
                break;
            case tipoIdInt:
            case tipoIdFloat:
            case tipoIdStr:
            case tipoIdIndef:
                break;
            case tipoIdFuncInt:
                printf("(%d) %s->pSimb->idFunc=%s\n", n, var, tn->pSimb->idFunc);
                printf("(%d) %s->pSimb->ifunc=%u\n", n, var, tn->pSimb->ifunc);
                break;
            case tipoIdFuncFloat:
                printf("(%d) %s->pSimb->idFunc=%s\n", n, var, tn->pSimb->idFunc);
                printf("(%d) %s->pSimb->ffunc=%u\n", n, var, tn->pSimb->ffunc);
                break;
            case tipoIdFuncDouble:
                printf("(%d) %s->pSimb->idFunc=%s\n", n, var, tn->pSimb->idFunc);
                printf("(%d) %s->pSimb->dfunc=%u\n", n, var, tn->pSimb->dfunc);
                break;
            case tipoIdFuncChar:
                break;
            case tipoIdFuncStr:
                printf("(%d) %s->pSimb->idFunc=%s\n", n, var, tn->pSimb->idFunc);
                printf("(%d) %s->pSimb->sfunc=%u\n", n, var, tn->pSimb->sfunc);
                break;
            case tipoIdFuncVoid:
                printf("(%d) %s->pSimb->idFunc=%s\n", n, var, tn->pSimb->idFunc);
                printf("(%d) %s->pSimb->vfunc=%u\n", n, var, tn->pSimb->vfunc);
                break;
        }
    }
    else //tipoOper
    {
        printf("----------------------------\n");
        printf("(%d) %s->opr.oper=%d", n, var, tn->opr.oper);
        printf(" (%s)\n", token(tn->opr.oper));
        printf("(%d) %s->opr.tipoBOper=%d (%s)\n", n, var, tn->opr.tipoBOper, nome);
        printf("(%d) %s->opr.nops=%d\n", n, var, tn->opr.nops);
        if(tn->opr.nops>0)
            printNodo(tn->opr.ptn[0], n+1, "ptn[0]");
        if(tn->opr.nops>1)
            printNodo(tn->opr.ptn[1], n+1, "ptn[1]");
        if(tn->opr.nops>2)
            printNodo(tn->opr.ptn[2], n+1, "ptn[2]");
        if(tn->opr.nops>3)
            printNodo(tn->opr.ptn[3], n+1, "ptn[3]");
    }
}

int variavel(nodo *p)
{
    if(p->tipoN==tipoOper)
        return 0;

    switch(p->pSimb->tipoD)
    {
        case tipoIdInt:
        case tipoIdFloat:
        case tipoIdStr:
            return 1;
        case tipoIdIndef:  //variavel ou funcao ainda sem tipo
        default:
            return 0;
    }
}

int pegaTipoBase(nodo *p)
{

    if(!p)
        return tipoIndef;

    if(p->tipoN==tipoOper)
        return (p->opr.tipoBOper);

    if(!p->pSimb)
        return tipoIndef;

    switch(p->pSimb->tipoD)
    {
        case tipoConInt:
        case tipoIdInt:
        case tipoIdFuncInt:
            return tipoInt; //------------ tipoInt
        case tipoConFloat:
        case tipoIdFloat:
        case tipoIdFuncFloat:
        case tipoIdFuncDouble:
            return tipoFloat; //------------ tipoFloat
        case tipoConStr:
        case tipoIdStr:
        case tipoIdFuncStr:
            return tipoStr; //------------ tipoStr
        case tipoIdFuncChar:
        case tipoIdFuncVoid:
        case tipoIdFuncPVoid:
        case tipoIdIndef:
        default:
            return tipoIndef; //------------ tipoIndef
    }
}

char *nomeTipo(nodo *p)
{
    if(!p)
        return(strdup("(null)"));
    if(p->tipoN==tipoSimb)
        return(strdup(sTipoDado[p->pSimb->tipoD]));
    else /* tipoOper */
        return(strdup(sTipoBase[p->opr.tipoBOper]));
}

char *token(int tk)
{
    char tmp[2];
    if(tk>32 && tk<127)
    {
        sprintf(tmp, "%c", tk);
        return strdup(tmp);
    }
    switch(tk)
    {
        case SE:
            return(strdup("SE"));
        case ENTAO:
            return(strdup("ENTAO"));
        case SENAO:
            return(strdup("SENAO"));
        case INICIO:
            return(strdup("INICIO"));
        case FIM:
            return(strdup("FIM"));
        case IMPRIMA:
            return(strdup("IMPRIMA"));
        case LEIA:
            return(strdup("LEIA"));
        case ENQUANTO:
            return(strdup("ENQUANTO"));
        case ABORTE:
            return(strdup("ABORTE"));
        case SAIA:
            return(strdup("SAIA"));
        case PARA:
            return(strdup("PARA"));
        case INT:
            return(strdup("INT"));
        case REAL:
            return(strdup("REAL"));
        case TEXTO:
            return(strdup("TEXTO"));
        case DEFINE:
            return(strdup("DEFINE"));
        case IMPORTE:
            return(strdup("IMPORTE"));
        case IDENT:
            return(strdup("IDENT"));
        case INTCON:
            return(strdup("INTCON"));
        case REALCON:
            return(strdup("REALCON"));
        case TEXTOCON:
            return(strdup("TEXTOCON"));
        case OU:
            return(strdup("OU"));
        case E:
            return(strdup("E"));
        case NAO:
            return(strdup("NAO"));
        case LT:
            return(strdup("LT"));
        case GT:
            return(strdup("GT"));
        case NE:
            return(strdup("NE"));
        case EQ:
            return(strdup("EQ"));
        case LE:
            return(strdup("LE"));
        case GE:
            return(strdup("GE"));
        case UMENOS:
            return(strdup("UMENOS"));
        case FUNC:
            return(strdup("FUNC"));
        default:
            return(strdup("default"));
    }
}

void erroSemantico(char *s, int linha)
{
    fprintf(stderr,"//    Linha:%d. Erro semantico: %s\n", linha, s);
    fflush(yyout);
    fclose(yyout);
    exit(1);
}
