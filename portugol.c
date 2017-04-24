/*
    Compilador PORTUGOL v.3q
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

#define debug 0

char *sTipoDado[17]={"tipoIdUndef", "tipoConInt", "tipoConDouble", "tipoConStr", "tipoIdInt", "tipoIdDouble", "tipoIdStr", "tipoIdPointInt", "tipoIdPointDouble", "tipoIdPointStr", "tipoIdFuncInt", "tipoIdFuncDouble", "tipoIdFuncDouble", "tipoIdFuncChar", "tipoIdFuncStr", "tipoIdFuncVoid", "tipoIdFuncPVoid"};
//char *sTipoBase[8]={"tipoUndef", "tipoInt", "tipoDouble", "tipoStr", "tipoPointInt", "tipoPointDouble", "tipoPointStr", "tipoVoid"};
char *sTipoBase[5]={"tipoUndef", "tipoInt", "tipoDouble", "tipoStr", "tipoVoid"};
extern int debugArvore;
extern int debugTabela;

char *gera_quad(nodo *tn, int n)
{
    char *q1=NULL, *q2=NULL, *q3=NULL, *qres=NULL, qtemp[20]="", qtemp2[20];
    char msg[128];
    int itemp, t1, t2, t3;
    tabelaSimb *ps;

    if(tn==NULL)
        return strdup(qtemp);

    switch(tn->tipoN)
    {
        case tipoSimb:
            switch(tn->pSimb->tipoD)
            {
                case tipoConInt:
                    //if(debug) printf("debug tipoConInt\n");
                    sprintf(qtemp,"tc[%d]",tn->pSimb->idx); //achaId preenche idx
                    if(!tn->pSimb->uso)
                        fprintf(yyout, "  loadi(%d,%s,&%s);\n", tn->pSimb->ival, "NULL", qtemp);
                    tn->pSimb->uso=1;
                    break;
                case tipoConDouble:
                    //if(debug) printf("debug tipoConDouble\n");
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
                case tipoIdDouble:
                case tipoIdStr:
                case tipoIdPointInt:
                case tipoIdPointDouble:
                case tipoIdPointStr:
                    sprintf(qtemp,"ts[%d]",tn->pSimb->idx);
                    break;
                case tipoIdFuncInt:
                //case tipoIdFuncFloat:
                case tipoIdFuncDouble:
                case tipoIdFuncChar:
                case tipoIdFuncStr:
                case tipoIdFuncVoid:
                case tipoIdFuncPVoid:
                    sprintf(qtemp,"tf[%d]",tn->pSimb->idx);
                    break;
                case tipoIdUndef:
                default:
                    sprintf(qtemp,"ts[?]");
                    sprintf(msg,"Operando nao declarado na chamada da funcao <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                    erroSemantico(msg, tn->linha);
                    break;
            }
        case tipoOper:
            switch(tn->opr.oper)
            {
                case INICIO: //INICIO; comandos FIM;
                    gera_quad(tn->opr.ptn[0], n+1);
                    if(n==0)
                    {
                        if(debugTabela)
                            printTS();
                        if(debugArvore)
                            printNodo(tn,0,"tn");
                        fprintf(yyout, "  nop(NULL,NULL,NULL);\t/* no operation */\n}\n");
                    }
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
                case FUNC:
                    //if(debug) printf("debug FUNC\n");
                    //    IDENT '(' ')'                       { $$ = opr(FUNC, 1, conv($1)); }
                    //    | IDENT '(' expr ')'                { $$ = opr(FUNC, 2, conv($1), $3); }
                    //    | IDENT '(' expr ',' expr ')'       { $$ = opr(FUNC, 3, conv($1), $3, $5); }
                    q1=gera_quad(tn->opr.ptn[0], n+1); //IDENT ts[?]
                    qres=geraTP(&itemp);//retorno da funcao em um temporario
                    if(tn->opr.ptn[0]->pSimb->numPar != tn->opr.nops-1)
                    {
                        sprintf(msg,"Numero de parametros declarados (%d) nao coincide com usados (%d) na chamada da funcao <%s>.", tn->opr.ptn[0]->pSimb->numPar, tn->opr.nops-1, tn->opr.ptn[0]->pSimb->idNome);
                        erroSemantico(msg, tn->linha);
                    }
                    switch(tn->opr.ptn[0]->pSimb->numPar) //ou tn->opr.nops
                    {
                        case 2:
                            if(!strcmp(tn->opr.ptn[0]->pSimb->idNome,"imprima")) //se imprima
                                if(!tn->opr.ptn[1]->pSimb->formatadoSval)
                                {
                                    sprintf(msg,"Formato incorreto para a funcao imprima(\"formato\", expr).");
                                    erroSemantico(msg, tn->linha);
                                }
                            q3=gera_quad(tn->opr.ptn[2], n+1); //arg2 == $5
                            t3=pegaTipoBase(tn->opr.ptn[2]); //tipo do arg2: tipoInt, tipoDouble, tipoStr, tipoUndef
                            fprintf(yyout,"  param(%s, NULL, NULL); /* arg2 */\n", q3);
                            if(t3 == tipoUndef)
                            {
                                sprintf(msg,"Operando nao declarado na chamada da funcao <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                                erroSemantico(msg, tn->linha);
                            }
/*                            if(t3 == tipoStr)
                            {
                                sprintf(msg,"Funcao <%s> com argumento tipoStr nao implementada.", tn->opr.ptn[0]->pSimb->idNome);
                                erroSemantico(msg, tn->linha);
                            }*/
                        case 1:
                            q2=gera_quad(tn->opr.ptn[1], n+1); //arg1 == $3
                            t2=pegaTipoBase(tn->opr.ptn[1]); //tipo do arg1: tipoInt, tipoDouble, tipoStr, tipoUndef
                            fprintf(yyout,"  param(%s, NULL, NULL); /* arg1 */\n", q2);
                            if(t2 == tipoUndef)
                            {
                                sprintf(msg,"Operando nao declarado na chamada da funcao <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                                erroSemantico(msg, tn->linha);
                            }
/*                            if(t2 == tipoStr)
                            {
                                sprintf(msg,"Funcao <%s> com argumento tipoStr nao implementada.", tn->opr.ptn[0]->pSimb->idNome);
                                erroSemantico(msg, tn->linha);
                            }*/
                        case 0:
                            break;
                        default:
                        {
                            sprintf(msg,"Funcao <%s> possui argumentos demais.", tn->opr.ptn[0]->pSimb->idNome);
                            erroSemantico(msg, tn->linha);
                        }
                    }
                    tn->opr.tipoBOper = pegaTipoBaseT(tn->opr.ptn[0]->pSimb->tipoRetNovo);//bug: esta fixo! De onde vem o tipo
                    fprintf(yyout,"  call(\"%s\", %d, &%s);\n", tn->opr.ptn[0]->pSimb->idNome, tn->opr.ptn[0]->pSimb->numPar, qres);
                    break;
                case ABORTE:
                    fprintf(yyout, "  halt(NULL,NULL,NULL);\n");
                    break;
                case INT:
                    if(tn->opr.ptn[0]->pSimb->tipoD!=tipoIdUndef)
                    {
                        sprintf(msg,"Redeclaracao da variavel <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                        erroSemantico(msg, tn->linha);
                    }
                    tn->opr.ptn[0]->pSimb->tipoD=tipoIdInt;
                    tn->opr.ptn[0]->pSimb->idx=geraTS();
                    fprintf(yyout,"  loadi(0, NULL, &ts[%d]); /* int %s; */\n", tn->opr.ptn[0]->pSimb->idx, tn->opr.ptn[0]->pSimb->idNome);
                    break;
                case REAL:
                    if(tn->opr.ptn[0]->pSimb->tipoD!=tipoIdUndef)
                    {
                        sprintf(msg,"Redeclaracao da variavel <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                        erroSemantico(msg, tn->linha);
                    }
                    tn->opr.ptn[0]->pSimb->tipoD=tipoIdDouble;
                    tn->opr.ptn[0]->pSimb->idx=geraTS();
                    fprintf(yyout,"  loadf(0.00, NULL, &ts[%d]); /* real %s; */\n", tn->opr.ptn[0]->pSimb->idx, tn->opr.ptn[0]->pSimb->idNome);
                    break;
                case TEXTO:
                    if(tn->opr.ptn[0]->pSimb->tipoD!=tipoIdUndef)
                    {
                        sprintf(msg,"Redeclaracao da variavel <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                        erroSemantico(msg, tn->linha);
                    }
                    tn->opr.ptn[0]->pSimb->tipoD=tipoIdStr;
                    tn->opr.ptn[0]->pSimb->idx=geraTS();
                    fprintf(yyout,"  loads(\"\\0\", NULL, &ts[%d]); /* texto %s; */\n", tn->opr.ptn[0]->pSimb->idx, tn->opr.ptn[0]->pSimb->idNome);
                    break;
                case PONTI:
                    if(debug) printf("debug PONTI\n");
                    if(tn->opr.ptn[0]->pSimb->tipoD!=tipoIdUndef)
                    {
                        sprintf(msg,"Redeclaracao da variavel <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                        erroSemantico(msg, tn->linha);
                    }
                    tn->opr.ptn[0]->pSimb->tipoD=tipoIdPointInt;
                    tn->opr.ptn[0]->pSimb->idx=geraTS();
                    fprintf(yyout,"  loadi(-1, NULL, &ts[%d]); /* ponteiro int %s; */\n", tn->opr.ptn[0]->pSimb->idx, tn->opr.ptn[0]->pSimb->idNome);
                    break;
                case PONTR:
                    if(debug) printf("debug PONTR\n");
                    if(tn->opr.ptn[0]->pSimb->tipoD!=tipoIdUndef)
                    {
                        sprintf(msg,"Redeclaracao da variavel <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                        erroSemantico(msg, tn->linha);
                    }
                    tn->opr.ptn[0]->pSimb->tipoD=tipoIdPointDouble;
                    tn->opr.ptn[0]->pSimb->idx=geraTS();
                    fprintf(yyout,"  loadi(-1, NULL, &ts[%d]); /* ponteiro real %s; */\n", tn->opr.ptn[0]->pSimb->idx, tn->opr.ptn[0]->pSimb->idNome);
                    break;
                case PONTS:
                    if(debug) printf("debug PONTS\n");
                    if(tn->opr.ptn[0]->pSimb->tipoD!=tipoIdUndef)
                    {
                        sprintf(msg,"Redeclaracao da variavel <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                        erroSemantico(msg, tn->linha);
                    }
                    tn->opr.ptn[0]->pSimb->tipoD=tipoIdPointStr;
                    tn->opr.ptn[0]->pSimb->idx=geraTS();
                    fprintf(yyout,"  loadi(-1, NULL, &ts[%d]); /* ponteiro texto %s; */\n", tn->opr.ptn[0]->pSimb->idx, tn->opr.ptn[0]->pSimb->idNome);
                    break;
//                 case IMPORTE: //IMPORTE REAL IDENT '(' REAL ')' ';'
//                     if(tn->opr.ptn[0]->pSimb->tipoD!=tipoIdUndef)
//                     {
//                         sprintf(msg,"Redeclaracao da variavel <%s>.", tn->opr.ptn[0]->pSimb->idNome);
//                         erroSemantico(msg, tn->linha);
//                     }
//                     tn->opr.ptn[0]->pSimb->tipoD=tipoIdDouble;
//                     tn->opr.ptn[0]->pSimb->idx=geraTS();
//                     fprintf(yyout,"  loadf(0.00, NULL, &ts[%d]); /* real %s; */\n", tn->opr.ptn[0]->pSimb->idx, tn->opr.ptn[0]->pSimb->idNome);
//                    tn->opr.tipoBOper = pegaTipoBase(tn->pSimb-tipoD);
                case ';':
                    fprintf(yyout, "  nop(NULL,NULL,NULL);\t/* no operation */\n");
                    break;
                case 'l': /* lista de comandos */
                    gera_quad(tn->opr.ptn[0], n);
                    gera_quad(tn->opr.ptn[1], n);
                    break;
                case '=': //p=&l;
                    if(debug) printf("debug =\n");
                    qres=gera_quad(tn->opr.ptn[0], n+1);
                    q1=gera_quad(tn->opr.ptn[1], n+1);
                    if(tn->opr.ptn[0]->pSimb->tipoD == tipoIdUndef)
                    {
                        sprintf(msg,"Atribuicao invalida a variavel <%s> nao declarada.", tn->opr.ptn[0]->pSimb->idNome);
                        erroSemantico(msg, tn->linha);
                    }
                    if(!variavel(tn->opr.ptn[0])) // tentou func(a)=1;
                    {
                        sprintf(msg,"Atribuicao invalida a uma funcao <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                        erroSemantico(msg, tn->linha);
                    }
                    t1=pegaTipoBase(tn->opr.ptn[0]); //tipoUndef, tipoInt, tipoDouble, tipoStr, nao tipoPoint
                    t2=pegaTipoBase(tn->opr.ptn[1]);
                    if(ponteiro(tn->opr.ptn[0]) && t2!=tipoInt)
                    {
                        sprintf(msg,"Atribuicao incompativel com ponteiros. <%s> = <%s>.", nomeTipo(tn->opr.ptn[0]), nomeTipo(tn->opr.ptn[1]));
                        erroSemantico(msg, tn->linha);
                    }
                    if(t1==t2 || (ponteiro(tn->opr.ptn[0]) && t2==tipoInt))
                    {
                        tn->opr.tipoBOper = t2;
                        fprintf(yyout, "  move(%s,NULL,&%s); /* %s = %s */\n", q1, qres, tn->opr.ptn[0]->pSimb->idNome, q1);
                    }
                    else
                    { /* tipos diferentes */
                        //if(debug) printf("debug =4\n");
                        //printf("Atribuicao de tipos diferentes. <%u> = <%u>.", tn->opr.ptn[0], tn->opr.ptn[1]);
                        //sprintf(msg,"Atribuicao de tipos diferentes. <%d> = <%d>.", tn->opr.ptn[0]->pSimb->tipoD, tn->opr.ptn[1]->opr.tipoBOper);
                        sprintf(msg,"Atribuicao de tipos diferentes. <%s> = <%s>.", nomeTipo(tn->opr.ptn[0]), nomeTipo(tn->opr.ptn[1]));
                        erroSemantico(msg, tn->linha);
                    }
                    //if(debug) printf("debug =fim\n");
                    break;
                case PATTRIB: //    | '*' IDENT '=' expr        { $$ = opr(PATTRIB, 2, conv($2), $4); }
                    //if(debug) printf("debug =\n");
                    qres=gera_quad(tn->opr.ptn[0], n+1);
                    q1=gera_quad(tn->opr.ptn[1], n+1);
                    if(!ponteiro(tn->opr.ptn[0]))
                    {
                        sprintf(msg,"Atribuicao invalida a variavel <%s> nao-ponteiro.", tn->opr.ptn[0]->pSimb->idNome);
                        erroSemantico(msg, tn->linha);
                    }
                    t1=pegaTipoBase(tn->opr.ptn[0]);//tipoUndef tipoInt tipoDouble tipoStr tipoPointInt tipoPointDouble tipoPointStr
                    t2=pegaTipoBase(tn->opr.ptn[1]);
                    if(t1==t2)
                    {
                        tn->opr.tipoBOper = t2;
                        fprintf(yyout, "  move_pb(%s,NULL,(&%s)); /* * %s = %s */\n", q1, qres, tn->opr.ptn[0]->pSimb->idNome, q1);
                    }
                    else
                    { /* tipos diferentes */
                        sprintf(msg,"Atribuicao de tipos diferentes. * <%s> = <%s>.", nomeTipo(tn->opr.ptn[0]), nomeTipo(tn->opr.ptn[1]));
                        erroSemantico(msg, tn->linha);
                    }
                    break;
                case UMENOS:
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    qres=geraTP(&itemp);
                    tn->opr.tipoBOper = pegaTipoBase(tn->opr.ptn[0]);
                    if(tn->opr.tipoBOper  == tipoUndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de menos unario. - <%s>", sTipoBase[tn->opr.tipoBOper]);
                        erroSemantico(msg, tn->linha);
                    }
                    fprintf(yyout, "  uminus(%s,NULL,&%s);\n", q1, qres);
                    break;
                case UPONT: //i=*q=j;
                    if(debug) printf("debug UPONT\n");
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    qres=geraTP(&itemp);
                    if(!ponteiro(tn->opr.ptn[0]))
                    {
                        sprintf(msg,"Tentativa de apontar valor em variavel nao-ponteiro. * <%s>", sTipoBase[t1]);
                        erroSemantico(msg, tn->linha);
                    }
                    fprintf(yyout, "  move_pa((%s),NULL,&%s); /* %s = * %s */\n", q1, qres, qres, q1);
                    tn->opr.tipoBOper = pegaTipoBase(tn->opr.ptn[0]); //por causa dessa linha, precisa ser 'ponteiro -int- p;'
//                    t1 = pegaTipoBase(tn->opr.ptn[0]);
//                    tn->opr.tipoBOper = t1;
/*                    if(t1 == tipoPointInt)
                        tn->opr.tipoBOper = tipoInt;
                    else if(t1 == tipoPointDouble)
                        tn->opr.tipoBOper = tipoDouble;
                    else if(t1 == tipoPointStr)
                        tn->opr.tipoBOper = tipoStr;*/
                    break;
                case UEND: //&i; &f;
                    if(debug) printf("debug UEND\n");
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    t1 = pegaTipoBase(tn->opr.ptn[0]);
                    //tn->opr.tipoBOper = tipoInt;
                    //bug: erro! esta permitindo um 'ponteiro real p' apontar para um int i;
                    //ponteiro int p; real f; p=&f;
                    //solucao: retorna tipoPointInt/tipoPointDouble ou tipoEndInt tipoEndDouble
                    //o que eh p? tipoPointInt. *p? tipoInt. i? tipoInt. &i? tipoPointInt *i=erro. &q? tipoPointInt
                    // ponteiro ponteiro r; r? tipoPointPointInt. *r? tipoPointInt. **r? tipoInt
                    if(t1 == tipoInt)
                        tn->opr.tipoBOper = tipoPointInt; //operador & retorna tipoPointInt
                    else if(t1 == tipoDouble)
                        tn->opr.tipoBOper = tipoPointDouble; //operador & retorna tipoPointDouble
                    else if(t1 == tipoStr)
                        tn->opr.tipoBOper = tipoPointStr; //operador & retorna tipoPointStr*/
//                    else
                    if(!variavel(tn->opr.ptn[0]))
                    {
                        sprintf(msg,"Operador endereco nao aceita variavel deste tipo. & <%s>", sTipoBase[t1]);
                        erroSemantico(msg, tn->linha);
                    }

                    ps = achaInt(tn->opr.ptn[0]->pSimb->idx);
                    sprintf(qtemp,"tc[%d]",ps->idx); //constante com indice
                    if(!ps->uso)
                    {
                        fprintf(yyout, "  loadi(%d,NULL,&%s); /* %s = %d */\n", tn->opr.ptn[0]->pSimb->idx, qtemp, qtemp, tn->opr.ptn[0]->pSimb->idx); //tc[1]=ptn->idx
                        ps->uso=1;
                    }
                    break;
                case INCPOS: //IDENT INC
                    if(debug) printf("debug INCPOS\n");
                    q1=gera_quad(tn->opr.ptn[0], n+1); // move(q1, null, qres)
                    qres=geraTP(&itemp); //tp[0] == ret
                    t1 = pegaTipoBase(tn->opr.ptn[0]);
                    if(t1 == tipoUndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de incremento pos-fixado. <%s>++", sTipoBase[tn->opr.tipoBOper]);
                        erroSemantico(msg, tn->linha);
                    }
                    if(t1 == tipoStr)
                        erroSemantico("Nao posso incrementar textos.", tn->linha);
                    tn->opr.tipoBOper = t1;
                    fprintf(yyout, "  move(%s,NULL,&%s); /* %s = %s */\n", q1, qres, qres, tn->opr.ptn[0]->pSimb->idNome);
                    ps = achaInt(1);
                    sprintf(qtemp,"tc[%d]",ps->idx); //constante 1
                    if(!ps->uso)
                    {
                        fprintf(yyout, "  loadi(1,NULL,&%s); /* %s = 1 */\n", qtemp, qtemp); //tp[1]=1
                        ps->uso=1;
                    }
                    q3=geraTP(&itemp); //tp[3]
                    fprintf(yyout, "  add(%s,%s,&%s);\n", q1, qtemp, q3);
                    fprintf(yyout, "  move(%s,NULL,&%s); /* %s = %s */\n", q3, q1, tn->opr.ptn[0]->pSimb->idNome, q3);
                    //printf("debug 3\n");
                    break;
                case INCPRE: //INC IDENT
                    if(debug) printf("debug INCPRE\n");
                    qres=gera_quad(tn->opr.ptn[0], n+1); // add(qres, 1, q1)
                    q1=geraTP(&itemp);
                    t1 = pegaTipoBase(tn->opr.ptn[0]);
                    if(t1 == tipoUndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de incremento pre-fixado. ++<%s>", sTipoBase[tn->opr.tipoBOper]);
                        erroSemantico(msg, tn->linha);
                    }
                    if(t1 == tipoStr)
                        erroSemantico("Nao posso incrementar textos.", tn->linha);
                    tn->opr.tipoBOper = t1;
                    ps = achaInt(1);
                    sprintf(qtemp,"tc[%d]",ps->idx); //constante 1
                    if(!ps->uso)
                    {
                        fprintf(yyout, "  loadi(1,NULL,&%s); /* %s = 1 */\n", qtemp, qtemp); //tp[1]=1
                        ps->uso=1;
                    }
                    fprintf(yyout, "  add(%s,%s,&%s);\n", qres, qtemp, q1); //A+1 -> q1
                    fprintf(yyout, "  move(%s,NULL,&%s); /* %s = %s */\n", q1, qres, tn->opr.ptn[0]->pSimb->idNome, q1);
                    //printf("debug 4\n");
                    break;
                case DECPOS: //    | IDENT DEC                 { $$ = opr(DECPOS, 1, conv($1)); }
                    //if(debug) printf("debug DECPOS\n");
                    q1=gera_quad(tn->opr.ptn[0], n+1); // move(q1, null, qres)
                    qres=geraTP(&itemp); //tp[0] == ret
                    t1 = pegaTipoBase(tn->opr.ptn[0]);
                    if(t1 == tipoUndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de incremento pos-fixado. <%s>++", sTipoBase[tn->opr.tipoBOper]);
                        erroSemantico(msg, tn->linha);
                    }
                    if(t1 == tipoStr)
                        erroSemantico("Nao posso incrementar textos.", tn->linha);
                    tn->opr.tipoBOper = t1;
                    fprintf(yyout, "  move(%s,NULL,&%s); /* %s = %s */\n", q1, qres, qres, tn->opr.ptn[0]->pSimb->idNome);
                    ps = achaInt(1);
                    sprintf(qtemp,"tc[%d]",ps->idx); //constante 1
                    if(!ps->uso)
                    {
                        fprintf(yyout, "  loadi(1,NULL,&%s); /* %s = 1 */\n", qtemp, qtemp); //tp[1]=1
                        ps->uso=1;
                    }
                    q3=geraTP(&itemp); //tp[3]
                    fprintf(yyout, "  sub(%s,%s,&%s);\n", q1, qtemp, q3);
                    fprintf(yyout, "  move(%s,NULL,&%s); /* %s = %s */\n", q3, q1, tn->opr.ptn[0]->pSimb->idNome, q3);
                    //printf("debug 3\n");
                    break;
//    | DEC IDENT                 { $$ = opr(DECPRE, 1, conv($2)); }
                case '+':
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    q2=gera_quad(tn->opr.ptn[1], n+1);
                    qres=geraTP(&itemp);
                    t1=pegaTipoBase(tn->opr.ptn[0]);
                    t2=pegaTipoBase(tn->opr.ptn[1]);
                    if(t1 == tipoUndef || t2 == tipoUndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de soma. <%s> + <%s>", sTipoBase[t1], sTipoBase[t2]);
                        erroSemantico(msg, tn->linha);
                    }
                    if((t1 == tipoStr || t2 == tipoStr) && (t1 != tipoStr || t2 != tipoStr))
                        erroSemantico("Nao posso somar textos com numeros.", tn->linha);
                    if(ponteiro(tn->opr.ptn[0]) || ponteiro(tn->opr.ptn[1]))
                        erroSemantico("Nao posso somar ponteiros.", tn->linha);
                    if(t1==tipoDouble || t2==tipoDouble)
                        tn->opr.tipoBOper = tipoDouble;
                    else
                        tn->opr.tipoBOper = t1;
                    if(t1 == tipoStr)
                        tn->opr.tipoBOper = tipoStr;
                    fprintf(yyout, "  add(%s,%s,&%s);\n", q1, q2, qres);
                    break;
                case '-':
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    q2=gera_quad(tn->opr.ptn[1], n+1);
                    qres=geraTP(&itemp);
                    t1=pegaTipoBase(tn->opr.ptn[0]);
                    t2=pegaTipoBase(tn->opr.ptn[1]);
                    if(t1 == tipoUndef || t2 == tipoUndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de subtracao. <%s> - <%s>", sTipoBase[t1], sTipoBase[t2]);
                        erroSemantico(msg, tn->linha);
                    }
                    if(t1 == tipoStr || t2 == tipoStr)
                        erroSemantico("Nao posso subtrair textos.", tn->linha);
                    if(ponteiro(tn->opr.ptn[0]) || ponteiro(tn->opr.ptn[1]))
                        erroSemantico("Nao posso subtrair ponteiros.", tn->linha);
                    if(t1==tipoDouble || t2==tipoDouble)
                        tn->opr.tipoBOper = tipoDouble;
                    else
                        tn->opr.tipoBOper = tipoInt;
                    fprintf(yyout, "  sub(%s,%s,&%s);\n", q1, q2, qres);
                    break;
                case '*':
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    q2=gera_quad(tn->opr.ptn[1], n+1);
                    qres=geraTP(&itemp);
                    t1=pegaTipoBase(tn->opr.ptn[0]);
                    t2=pegaTipoBase(tn->opr.ptn[1]);
                    if(t1 == tipoUndef || t2 == tipoUndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de multiplicacao. <%s> * <%s>", sTipoBase[t1], sTipoBase[t2]);
                        erroSemantico(msg, tn->linha);
                    }
                    if(t1 == tipoStr || t2 == tipoStr)
                        erroSemantico("Nao posso multiplicar textos.", tn->linha);
                    if(ponteiro(tn->opr.ptn[0]) || ponteiro(tn->opr.ptn[1]))
                        erroSemantico("Nao posso multiplicar ponteiros.", tn->linha);
                    if(t1==tipoDouble || t2==tipoDouble)
                        tn->opr.tipoBOper = tipoDouble;
                    else
                        tn->opr.tipoBOper = tipoInt;
                    fprintf(yyout, "  mult(%s,%s,&%s);\n", q1, q2, qres);
                    break;
                case '/':
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    q2=gera_quad(tn->opr.ptn[1], n+1);
                    qres=geraTP(&itemp);
                    t1=pegaTipoBase(tn->opr.ptn[0]);
                    t2=pegaTipoBase(tn->opr.ptn[1]);
                    if(t1 == tipoUndef || t2 == tipoUndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de divisao. <%s> / <%s>", sTipoBase[t1], sTipoBase[t2]);
                        erroSemantico(msg, tn->linha);
                    }
                    if(t1 == tipoStr || t2 == tipoStr)
                        erroSemantico("Nao posso dividir textos.", tn->linha);
                    if(ponteiro(tn->opr.ptn[0]) || ponteiro(tn->opr.ptn[1]))
                        erroSemantico("Nao posso dividir ponteiros.", tn->linha);
                    if(t1==tipoDouble || t2==tipoDouble)
                        tn->opr.tipoBOper = tipoDouble;
                    else
                        tn->opr.tipoBOper = tipoInt;
                    fprintf(yyout, "  divi(%s,%s,&%s);\n", q1, q2, qres);
                    break;
                case '%':
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    q2=gera_quad(tn->opr.ptn[1], n+1);
                    qres=geraTP(&itemp);
                    t1=pegaTipoBase(tn->opr.ptn[0]);
                    t2=pegaTipoBase(tn->opr.ptn[1]);
                    if(t1 == tipoUndef || t2 == tipoUndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de modulo. <%s> % <%s>", sTipoBase[t1], sTipoBase[t2]);
                        erroSemantico(msg, tn->linha);
                    }
                    if(t1 == tipoStr || t2 == tipoStr)
                        erroSemantico("Nao posso calcular modulo de textos.", tn->linha);
                    if(ponteiro(tn->opr.ptn[0]) || ponteiro(tn->opr.ptn[1]))
                        erroSemantico("Nao posso calcular modulo de ponteiros.", tn->linha);
                    if(t1 == tipoDouble || t2 == tipoDouble)
                        erroSemantico("Nao posso calcular modulo de <tipoDouble>.", tn->linha);
                    tn->opr.tipoBOper = tipoInt;
                    fprintf(yyout, "  mod(%s,%s,&%s);\n", q1, q2, qres);
                    break;
                case '(':
                    qres=gera_quad(tn->opr.ptn[0], n+1);
                    tn->opr.tipoBOper = pegaTipoBase(tn->opr.ptn[0]);
                    if(tn->opr.tipoBOper  == tipoUndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de parenteses. ( <%s> )", sTipoBase[tn->opr.tipoBOper]);
                        erroSemantico(msg, tn->linha);
                    }
                    break;
                case LT: //compara texto com texto ou numero com numero. retorna tipoInt
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    q2=gera_quad(tn->opr.ptn[1], n+1);
                    qres=geraTP(&itemp);
                    t1=pegaTipoBase(tn->opr.ptn[0]);
                    t2=pegaTipoBase(tn->opr.ptn[1]);
                    if(t1 == tipoUndef || t2 == tipoUndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de menor-que. <%s> < <%s>", sTipoBase[t1], sTipoBase[t2]);
                        erroSemantico(msg, tn->linha);
                    }
                    if((t1 == tipoStr || t2 == tipoStr) && (t1 != tipoStr || t2 != tipoStr))
                        erroSemantico("Nao posso comparar (<) textos com numeros.", tn->linha);
                    tn->opr.tipoBOper = tipoInt;
                    fprintf(yyout, "  comp_lt(%s,%s,&%s);\n", q1, q2, qres);
                    break;
                case GT:
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    q2=gera_quad(tn->opr.ptn[1], n+1);
                    qres=geraTP(&itemp);
                    t1=pegaTipoBase(tn->opr.ptn[0]);
                    t2=pegaTipoBase(tn->opr.ptn[1]);
                    if(t1 == tipoUndef || t2 == tipoUndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de maior-que. <%s> > <%s>", sTipoBase[t1], sTipoBase[t2]);
                        erroSemantico(msg, tn->linha);
                    }
                    if((t1 == tipoStr || t2 == tipoStr) && (t1 != tipoStr || t2 != tipoStr))
                        erroSemantico("Nao posso comparar (>) textos com numeros.", tn->linha);
                    tn->opr.tipoBOper = tipoInt;
                    fprintf(yyout, "  comp_gt(%s,%s,&%s);\n", q1, q2, qres);
                    break;
                case GE:
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    q2=gera_quad(tn->opr.ptn[1], n+1);
                    qres=geraTP(&itemp);
                    t1=pegaTipoBase(tn->opr.ptn[0]);
                    t2=pegaTipoBase(tn->opr.ptn[1]);
                    if(t1 == tipoUndef || t2 == tipoUndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de maior-igual. <%s> >= <%s>", sTipoBase[t1], sTipoBase[t2]);
                        erroSemantico(msg, tn->linha);
                    }
                    if((t1 == tipoStr || t2 == tipoStr) && (t1 != tipoStr || t2 != tipoStr))
                        erroSemantico("Nao posso comparar (>=) textos com numeros.", tn->linha);
                    tn->opr.tipoBOper = tipoInt;
                    fprintf(yyout, "  comp_ge(%s,%s,&%s);\n", q1, q2, qres);
                    break;
                case LE:
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    q2=gera_quad(tn->opr.ptn[1], n+1);
                    qres=geraTP(&itemp);
                    t1=pegaTipoBase(tn->opr.ptn[0]);
                    t2=pegaTipoBase(tn->opr.ptn[1]);
                    if(t1 == tipoUndef || t2 == tipoUndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de menor-igual. <%s> <= <%s>", sTipoBase[t1], sTipoBase[t2]);
                        erroSemantico(msg, tn->linha);
                    }
                    if((t1 == tipoStr || t2 == tipoStr) && (t1 != tipoStr || t2 != tipoStr))
                        erroSemantico("Nao posso comparar (<=) textos com numeros.", tn->linha);
                    tn->opr.tipoBOper = tipoInt;
                    fprintf(yyout, "  comp_le(%s,%s,&%s);\n", q1, q2, qres);
                    break;
                case NE:
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    q2=gera_quad(tn->opr.ptn[1], n+1);
                    qres=geraTP(&itemp);
                    t1=pegaTipoBase(tn->opr.ptn[0]);
                    t2=pegaTipoBase(tn->opr.ptn[1]);
                    if(t1 == tipoUndef || t2 == tipoUndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de diferente. <%s> != <%s>", sTipoBase[t1], sTipoBase[t2]);
                        erroSemantico(msg, tn->linha);
                    }
                    if((t1 == tipoStr || t2 == tipoStr) && (t1 != tipoStr || t2 != tipoStr))
                        erroSemantico("Nao posso comparar (!=) textos com numeros.", tn->linha);
                    tn->opr.tipoBOper = tipoInt;
                    fprintf(yyout, "  comp_ne(%s,%s,&%s);\n", q1, q2, qres);
                    break;
                case EQ:
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    q2=gera_quad(tn->opr.ptn[1], n+1);
                    qres=geraTP(&itemp);
                    t1=pegaTipoBase(tn->opr.ptn[0]);
                    t2=pegaTipoBase(tn->opr.ptn[1]);
                    if(t1 == tipoUndef || t2 == tipoUndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de igual. <%s> == <%s>", sTipoBase[t1], sTipoBase[t2]);
                        erroSemantico(msg, tn->linha);
                    }
                    if((t1 == tipoStr || t2 == tipoStr) && (t1 != tipoStr || t2 != tipoStr))
                        erroSemantico("Nao posso comparar (==) textos com numeros.", tn->linha);
                    tn->opr.tipoBOper = tipoInt;
                    fprintf(yyout, "  comp_eq(%s,%s,&%s);\n", q1, q2, qres);
                    break;
                case E:
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    q2=gera_quad(tn->opr.ptn[1], n+1);
                    qres=geraTP(&itemp);
                    t1=pegaTipoBase(tn->opr.ptn[0]);
                    t2=pegaTipoBase(tn->opr.ptn[1]);
                    if(t1 == tipoUndef || t2 == tipoUndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de E logico. <%s> E <%s>", sTipoBase[t1], sTipoBase[t2]);
                        erroSemantico(msg, tn->linha);
                    }
                    if(t1 == tipoStr || t2 == tipoStr)
                        erroSemantico("Nao posso operar (E) em textos.", tn->linha);
                    tn->opr.tipoBOper = tipoInt;
                    fprintf(yyout, "  rela_an(%s,%s,&%s);\n", q1,q2,qres);
                    break;
                case OU:
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    q2=gera_quad(tn->opr.ptn[1], n+1);
                    qres=geraTP(&itemp);
                    t1=pegaTipoBase(tn->opr.ptn[0]);
                    t2=pegaTipoBase(tn->opr.ptn[1]);
                    if(t1 == tipoUndef || t2 == tipoUndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de OU logico. <%s> OU <%s>", sTipoBase[t1], sTipoBase[t2]);
                        erroSemantico(msg, tn->linha);
                    }
                    if(t1 == tipoStr || t2 == tipoStr)
                        erroSemantico("Nao posso operar (OU) em textos.", tn->linha);
                    tn->opr.tipoBOper = tipoInt;
                    fprintf(yyout, "  rela_or(%s,%s,&%s);\n", q1,q2,qres);
                    break;
                case NAO:
                    q1=gera_quad(tn->opr.ptn[0], n+1);
                    qres=geraTP(&itemp);
                    t1=pegaTipoBase(tn->opr.ptn[0]);
                    if(t1 == tipoUndef)
                    {
                        sprintf(msg,"Operando nao declarado na operacao de NAO logico. NAO <%s>", sTipoBase[t1]);
                        erroSemantico(msg, tn->linha);
                    }
                    if(t1 == tipoStr)
                        erroSemantico("Nao posso operar (NAO) em textos.", tn->linha);
                    tn->opr.tipoBOper = tipoInt;
                    fprintf(yyout, "  rela_no(%s,%s,&%s);\n", q1,"NULL",qres);
                    break;
            }
    }
    if(qres!=NULL) //retorna na ordem de prioridade: qres ou qtemp
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
        printf("tabSimb[%d].tipoD=%d (%s)\n", n, tabSimb[n].tipoD, sTipoDado[tabSimb[n].tipoD]);
        printf("tabSimb[%d].idx=%d\n", n, tabSimb[n].idx);
        printf("tabSimb[%d].idNome=%s\n", n, tabSimb[n].idNome);
        switch(tabSimb[n].tipoD)
        {
            case tipoConInt:
                printf("tabSimb[%d].uso=%d\n", n, tabSimb[n].uso);
                printf("tabSimb[%d].ival=%d\n", n, tabSimb[n].ival);
                break;
            case tipoConDouble:
                printf("tabSimb[%d].uso=%d\n", n, tabSimb[n].uso);
                printf("tabSimb[%d].fval=%.2f\n", n, tabSimb[n].fval);
                break;
            case tipoConStr:
                printf("tabSimb[%d].uso=%d\n", n, tabSimb[n].uso);
                printf("tabSimb[%d].sval=%s\n", n, tabSimb[n].sval);
                break;
            case tipoIdInt:
            case tipoIdDouble:
            case tipoIdStr:
            case tipoIdUndef:
                break;
            case tipoIdPointInt:
            case tipoIdPointDouble:
            case tipoIdPointStr:
                //printf("tabSimb[%d].pval=%d\n", n, tabSimb[n].pval);
                break;
            case tipoIdFuncInt:
                printf("tabSimb[%d].tipoRetNovo=%d (%s)\n", n, tabSimb[n].tipoRetNovo, sTipoDado[tabSimb[n].tipoRetNovo]);
                printf("tabSimb[%d].idFunc=%s\n", n, tabSimb[n].idFunc);
                printf("tabSimb[%d].ifunc=%u\n", n, tabSimb[n].ifunc);
                break;
            case tipoIdFuncDouble:
                printf("tabSimb[%d].tipoRetNovo=%d (%s)\n", n, tabSimb[n].tipoRetNovo, sTipoDado[tabSimb[n].tipoRetNovo]);
                printf("tabSimb[%d].idFunc=%s\n", n, tabSimb[n].idFunc);
                printf("tabSimb[%d].ffunc=%u\n", n, tabSimb[n].ffunc);
                break;
            case tipoIdFuncDouble:
                printf("tabSimb[%d].tipoRetNovo=%d (%s)\n", n, tabSimb[n].tipoRetNovo, sTipoDado[tabSimb[n].tipoRetNovo]);
                printf("tabSimb[%d].idFunc=%s\n", n, tabSimb[n].idFunc);
                printf("tabSimb[%d].dfunc=%u\n", n, tabSimb[n].dfunc);
                break;
            case tipoIdFuncChar:
                break;
            case tipoIdFuncStr:
                printf("tabSimb[%d].tipoRetNovo=%d (%s)\n", n, tabSimb[n].tipoRetNovo, sTipoDado[tabSimb[n].tipoRetNovo]);
                printf("tabSimb[%d].idFunc=%s\n", n, tabSimb[n].idFunc);
                printf("tabSimb[%d].sfunc=%u\n", n, tabSimb[n].sfunc);
                break;
            case tipoIdFuncVoid:
                printf("tabSimb[%d].tipoRetNovo=%d (%s)\n", n, tabSimb[n].tipoRetNovo, sTipoDado[tabSimb[n].tipoRetNovo]);
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
        printf("(%d) %s->pSimb->tipoD=%d (%s)\n", n, var, tn->pSimb->tipoD, nome);
        printf("(%d) %s->pSimb->idx=%d\n", n, var, tn->pSimb->idx);
        printf("(%d) %s->pSimb->idNome=%s\n", n, var, tn->pSimb->idNome);
        switch(tn->pSimb->tipoD)
        {
            case tipoConInt:
                printf("(%d) %s->pSimb->uso=%d\n", n, var, tn->pSimb->uso);
                printf("(%d) %s->pSimb->ival=%d\n", n, var, tn->pSimb->ival);
                break;
            case tipoConDouble:
                printf("(%d) %s->pSimb->uso=%d\n", n, var, tn->pSimb->uso);
                printf("(%d) %s->pSimb->fval=%.2f\n", n, var, tn->pSimb->fval);
                break;
            case tipoConStr:
                printf("(%d) %s->pSimb->uso=%d\n", n, var, tn->pSimb->uso);
                printf("(%d) %s->pSimb->sval=%s\n", n, var, tn->pSimb->sval);
                break;
            case tipoIdInt:
            case tipoIdDouble:
            case tipoIdStr:
            case tipoIdPointInt:
            case tipoIdPointDouble:
            case tipoIdPointStr:
            case tipoIdUndef:
                break;
            case tipoIdFuncInt:
                printf("(%d) %s->pSimb->tipoRetNovo=%d (%s)\n", n, var, tn->pSimb->tipoRetNovo, sTipoDado[tn->pSimb->tipoRetNovo]);
                printf("(%d) %s->pSimb->idFunc=%s\n", n, var, tn->pSimb->idFunc);
                printf("(%d) %s->pSimb->ifunc=%u\n", n, var, tn->pSimb->ifunc);
                break;
            case tipoIdFuncDouble:
                printf("(%d) %s->pSimb->tipoRetNovo=%d (%s)\n", n, var, tn->pSimb->tipoRetNovo, sTipoDado[tn->pSimb->tipoRetNovo]);
                printf("(%d) %s->pSimb->idFunc=%s\n", n, var, tn->pSimb->idFunc);
                printf("(%d) %s->pSimb->ffunc=%u\n", n, var, tn->pSimb->ffunc);
                break;
            case tipoIdFuncDouble:
                printf("(%d) %s->pSimb->tipoRetNovo=%d (%s)\n", n, var, tn->pSimb->tipoRetNovo, sTipoDado[tn->pSimb->tipoRetNovo]);
                printf("(%d) %s->pSimb->idFunc=%s\n", n, var, tn->pSimb->idFunc);
                printf("(%d) %s->pSimb->dfunc=%u\n", n, var, tn->pSimb->dfunc);
                break;
            case tipoIdFuncChar:
                break;
            case tipoIdFuncStr:
                printf("(%d) %s->pSimb->tipoRetNovo=%d (%s)\n", n, var, tn->pSimb->tipoRetNovo, sTipoDado[tn->pSimb->tipoRetNovo]);
                printf("(%d) %s->pSimb->idFunc=%s\n", n, var, tn->pSimb->idFunc);
                printf("(%d) %s->pSimb->sfunc=%u\n", n, var, tn->pSimb->sfunc);
                break;
            case tipoIdFuncVoid:
                printf("(%d) %s->pSimb->tipoRetNovo=%d (%s)\n", n, var, tn->pSimb->tipoRetNovo, sTipoDado[tn->pSimb->tipoRetNovo]);
                printf("(%d) %s->pSimb->idFunc=%s\n", n, var, tn->pSimb->idFunc);
                printf("(%d) %s->pSimb->vfunc=%u\n", n, var, tn->pSimb->vfunc);
                break;
        }
    }
    else //tipoOper
    {
        if(tn->opr.oper!='l')
        {
            printf("----------------------------\n");
            printf("(%d) %s->opr.oper=%d", n, var, tn->opr.oper);
            printf(" (%s)\n", token(tn->opr.oper));
            printf("(%d) %s->opr.tipoBOper=%d (%s)\n", n, var, tn->opr.tipoBOper, nome);
            printf("(%d) %s->opr.nops=%d\n", n, var, tn->opr.nops);
        }
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

int variavelT(int t)
{
    switch(t)
    {
        case tipoIdInt:
        case tipoIdDouble:
        case tipoIdStr:
        case tipoIdPointInt:
        case tipoIdPointDouble:
        case tipoIdPointStr:
            return 1;
        case tipoIdUndef:  //variavel ou funcao ainda sem tipo
        default:
            return 0;
    }
}

int variavel(nodo *p)
{
    if(p->tipoN==tipoOper)
        return 0;
    variavelT(p->pSimb->tipoD);
}

int ponteiro(nodo *p)
{
    if(p->tipoN==tipoOper)
        return 0;

    switch(p->pSimb->tipoD)
    {
        case tipoIdPointInt:
        case tipoIdPointDouble:
        case tipoIdPointStr:
            return 1;
        case tipoIdUndef:
        default:
            return 0;
    }
}

int pegaTipoBaseT(int t)
{
    switch(t)
    {
        case tipoConInt:
        case tipoIdInt:
        case tipoIdFuncInt:
        case tipoIdPointInt:
            return tipoInt; //------------ tipoInt
        case tipoConDouble:
        case tipoIdDouble:
        case tipoIdFuncDouble:
      //  case tipoIdFuncDouble:
        case tipoIdPointDouble:
            return tipoDouble; //---------- tipoDouble
        case tipoConStr:
        case tipoIdStr:
        case tipoIdFuncStr:
        case tipoIdPointStr:
            return tipoStr; //------------ tipoStr
/*        case tipoIdPointInt:
            return tipoPointInt; //---------- tipoPointInt
        case tipoIdPointDouble:
            return tipoPointDouble; //---------- tipoPointDouble
        case tipoIdPointStr:
            return tipoPointStr; //---------- tipoPointStr*/
        case tipoIdFuncVoid:
            return tipoVoid; //----------- tipoVoid
        case tipoIdFuncChar:
        case tipoIdFuncPVoid:
        case tipoIdUndef:
        default:
            return tipoUndef; //------------ tipoUndef
    }
}

int pegaTipoBase(nodo *p)
{

    if(!p)
        return tipoUndef;

    if(p->tipoN==tipoOper)
        return (p->opr.tipoBOper);

    if(!p->pSimb)
        return tipoUndef;

    return (pegaTipoBaseT(p->pSimb->tipoD));
}

char *nomeTipo(nodo *p)
{
    if(!p)
        return(strdup("(null)"));
    if(p->tipoN==tipoSimb)
    {
        //if(debug) printf("debug nodoTipo tipoD=%d\n",p->pSimb->tipoD);
        return(strdup(sTipoDado[p->pSimb->tipoD]));
        //if(debug) printf("debug nodoTipo tipoD=%d depois\n",p->pSimb->tipoD);
    }
    else /* tipoOper */
    {
        //if(debug) printf("debug nodoTipo tipoBOper=%d\n",p->opr.tipoBOper);
        return(strdup(sTipoBase[p->opr.tipoBOper]));
        //if(debug) printf("debug nodoTipo tipoBOper=%d depois\n",p->opr.tipoBOper);
    }
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
        case ENQUANTO:
            return(strdup("ENQUANTO"));
        case ABORTE:
            return(strdup("ABORTE"));
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
        case PONT:
            return(strdup("PONT"));
        case UPONT:
            return(strdup("UPONT"));
        case UEND:
            return(strdup("UEND"));
        case INCPRE:
            return(strdup("INCPRE"));
        case INCPOS:
            return(strdup("INCPOS"));
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
