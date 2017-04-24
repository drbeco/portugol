/*
    Compilador PORTUGOL v.3q
    Autor: Ruben Carlo Benante
    Email: benante@gmail.com
    Data criação: 23/04/2009
    Data modificação: 25/05/2009
*/

/*Falta: (to do)
      IMPORTE = 273,
      DEFINE = 272,

* indentacao
* funcoes
* estruturas
* gerar codigo em C
* gerar codigo assembly i386, executaveis win32 e linux


*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "portugol.h"
#include "y.tab.h"

#define debug 0

char *sTipoDado[18]={"tipoIdUndef", "tipoConInt", "tipoConDouble", "tipoConStr", "tipoIdInt", "tipoIdDouble", "tipoIdStr", "tipoIdPointInt", "tipoIdPointDouble", "tipoIdPointStr", "tipoIdFuncInt", "tipoIdFuncDouble", "tipoIdFuncStr", /*"tipoIdFuncChar", */ "tipoIdFuncVoid", "tipoIdFuncPVoid", "tipoIdFuncPointInt", "tipoIdFuncPointDouble", "tipoIdFuncPointStr"};
char *sTipoBase[8]={"tipoUndef", "tipoInt", "tipoDouble", "tipoStr", "tipoVoid", "tipoPointInt", "tipoPointDouble", "tipoPointStr"};
extern int debugArvore;
extern int debugTabela;
extern char cabecalhoMain[MAX_CABECA];
extern tipoBase tipoRet;



void pass1(nodo *tn, int n)
{
    char *q1=NULL, *q2=NULL, *q3=NULL, *qres=NULL, qtemp[20]="", qtemp2[20];
    char msg[128];
    int itemp, t1, t2, t3, npar;
    int paramTipo[MAX_PARAM]; /* 3 */
    tabelaSimb *ps;

    if (tn==NULL)
        return strdup(qtemp);

    //fprintf(stderr, "gera_quad(tn:%p, n:%d), tn->tipoN:%d\n", tn, n, tn->tipoN);
    //printTS();
    //printNodo(tn,n,"tn");
    switch (tn->tipoN)
    {
    case tipoSimb:
        switch (tn->pSimb->tipoD)
        {
        case tipoConInt:
            //if(debug) printf("debug tipoConInt\n");
            sprintf(qtemp,"tc[%d]",tn->pSimb->idx); //achaId preenche idx
            if (!tn->pSimb->uso)
                fprintf(yyout, "  loadi(%d,%s,&%s);\n", tn->pSimb->ival, "NULL", qtemp);
            tn->pSimb->uso=1;
            break;
        case tipoConDouble:
            //if(debug) printf("debug tipoConDouble\n");
            sprintf(qtemp,"tc[%d]",tn->pSimb->idx);
            if (!tn->pSimb->uso)
                fprintf(yyout, "  loadd(%.2f,%s,&%s);\n", tn->pSimb->dval, "NULL", qtemp);
            tn->pSimb->uso=1;
            break;
        case tipoConStr:
            //if(debug) printf("debug tipoConStr\n");
            sprintf(qtemp,"tc[%d]",tn->pSimb->idx);
            if (!tn->pSimb->uso)
                fprintf(yyout, "  loads(%s,%s,&%s);\n", tn->pSimb->sval, "NULL", qtemp);
            tn->pSimb->uso=1;
            break;
        case tipoIdInt:
        case tipoIdDouble:
        case tipoIdStr:
        case tipoIdPointInt:
        case tipoIdPointDouble:
        case tipoIdPointStr:
            //if(debug) printf("debug tipoId...\n");
            sprintf(qtemp,"ts[%d]",tn->pSimb->idx);
            //if(debug) printf("debug tipoId... ok\n");
            break;
        case tipoIdFuncInt:
            //case tipoIdFuncFloat:
        case tipoIdFuncDouble:
            //case tipoIdFuncChar:
        case tipoIdFuncStr:
        case tipoIdFuncVoid:
        case tipoIdFuncPVoid:
            //if(debug) printf("debug tipoIdFunc...\n");
            sprintf(qtemp,"tf[%d]",tn->pSimb->idx);
            break;
        case tipoIdUndef:
        default:
            //if (debug) printf("debug tipoIdUndef default...\n");
            sprintf(qtemp,"ts[?]");
            //if(debug) printf("debug tipoIdUndef default, qtemp: %s\n", qtemp);
            sprintf(msg,"Operando nao declarado na chamada da funcao <%s>.", tn->pSimb->idNome);
            erroSemantico(msg, tn->linha);
            break;
        }
        break;
    case tipoOper:
        switch (tn->opr.oper)
        {
        case INICIO: //INICIO; comandos FIM;
            //preprocs blocos principio             { $$ = opr(INICIO, 2, $2, $3); }
            //if (debug) printf("debug tipoOper INICIO (%d)\n", tn->opr.nops);
            fprintf(yyout, "//    Gerado pelo compilador Portugol versao 3r\n");
            fprintf(yyout, "//    Autor: Ruben Carlo Benante\n");
            fprintf(yyout, "//    Email: rcb@beco.cc\n");
            fprintf(yyout, "//    Data: 23/05/2009, 10/03/2011\n");
            fprintf(yyout, "//    Compilado em: %s as %s\n\n", __DATE__, __TIME__);
            fprintf(yyout, "#include <stdio.h>\n");
            fprintf(yyout, "#include <stdlib.h>\n");
            fprintf(yyout, "#include <math.h>\n");
            fprintf(yyout, "#include \"quadruplas.h\"\n\n");
//            fprintf(yyout, "#define MAX_TS 100 /* tabela de simbolos */\n");
//            fprintf(yyout, "#define MAX_TC 100 /* tabela de constantes */\n");
//            fprintf(yyout, "#define MAX_TP 100 /* tabela de temporarios */\n");
//            fprintf(yyout, "#define MAX_TF 100 /* tabela de funcoes */\n\n");
//            fprintf(yyout, "superTipo ts[MAX_TS];\n");
//            fprintf(yyout, "superTipo tc[MAX_TC];\n");
//            fprintf(yyout, "superTipo tp[MAX_TP];\n");
//            fprintf(yyout, "superFunc tf[MAX_TF];\n\n");
            gera_quad(tn->opr.ptn[0], n+1);
            fprintf(yyout,"int main(void) /* principal */\n{\n");
            fprintf(yyout,"%s\n", cabecalhoMain);
            //fprintf(yyout,"  loadfunc(tipoInt,   (void *)%s, \"%s\", &tf[%d], %d); /* definicao de funcao */\n", /*so feito dentro do main*/ ps->idFunc, ps->idNome, ps->idx, ps->numPar);
            tipoRet=tipoInt;
            gera_quad(tn->opr.ptn[1], n+1);
            //printf("debug - INICIO - gera_quad(ptn[1]) ok! \n");
            if (n==0)
            {
                if (debugTabela)
                    printTS();
                if (debugArvore)
                    printNodo(tn,0,"tn");
                //fprintf(yyout, "  nop(NULL,NULL,NULL);\t/* no operation */\n} /* close main */\n"); /* fecha chave do main */
            }
            break;
        case SE:
            q1=gera_quad(tn->opr.ptn[0], n+1); //expr
            q2=geraLB(&itemp);//inicio_senao ou fim_se
            if (tn->opr.nops>2) //tem senao
                q3=geraLB(&itemp);//fim_se
            fprintf(yyout, "  jump_f(");//caso falso pula para senao ou para fim_se
            fprintf(yyout, "%s,", q1);
            fprintf(yyout, "%s,", "NULL");
            fprintf(yyout, "%s);\t/* if(F) goto %s */\n", q2, q2); //pula para senao ou para fim_se
            gera_quad(tn->opr.ptn[1], n+1); //comandos do entao
            if (tn->opr.nops>2) //tem senao, pula para fim_se
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
        case FUNC: /* Aqui a chamada da funcao. Para definicao do prototipo, veja tipos */
            if (debug) printf("debug FUNC\n");
            //    IDENT '(' ')'                       { $$ = opr(FUNC, 1, conv($1)); }
            //    | IDENT '(' expr ')'                { $$ = opr(FUNC, 2, conv($1), $3); }
            //    | IDENT '(' expr ',' expr ')'       { $$ = opr(FUNC, 3, conv($1), $3, $5); }
            //printf("tn->opr.ptn[0]=%p\n", tn->opr.ptn[0]);
            //fprintf(stderr,"debug Numero de parametros declarados (%d). Usados (%d). Funcao <%s>. Operador oper:%d\n", tn->opr.ptn[0]->pSimb->numPar, tn->opr.nops-1, tn->opr.ptn[0]->pSimb->idNome, tn->opr.oper);
            //printf("tn->opr.ptn[0]= ok!\n");
            q1=gera_quad(tn->opr.ptn[0], n+1); //IDENT ts[?]
            //if(debug) printf("debug FUNC q1 ok.\n");
            qres=geraTP(&itemp);//retorno da funcao em um temporario
            if (tn->opr.ptn[0]->pSimb->numPar != tn->opr.nops-1)
            {
                sprintf(msg,"Numero de parametros declarados (%d) nao coincide com usados (%d) na chamada da funcao <%s>.", tn->opr.ptn[0]->pSimb->numPar, tn->opr.nops-1, tn->opr.ptn[0]->pSimb->idNome);
                erroSemantico(msg, tn->linha);
            }
            switch (tn->opr.ptn[0]->pSimb->numPar) //ou tn->opr.nops
            {
            case 2:
                if (!strcmp(tn->opr.ptn[0]->pSimb->idNome,"imprima")) //se imprima
                    if (!tn->opr.ptn[1]->pSimb->formatadoSval)
                    {
                        sprintf(msg,"Formato incorreto para a funcao imprima(\"formato\", expr).");
                        erroSemantico(msg, tn->linha);
                    }
                q3=gera_quad(tn->opr.ptn[2], n+1); //arg2 == $5
                t3=pegaTipoBase(tn->opr.ptn[2]); //tipo do arg2: tipoInt, tipoDouble, tipoStr, tipoUndef
                fprintf(yyout,"  param(%s, NULL, NULL); /* arg2 */\n", q3);
                if (t3 == tipoUndef)
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
                if (t2 == tipoUndef)
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
                sprintf(msg,"Funcao <%s> possui argumentos demais.", tn->opr.ptn[0]->pSimb->idNome);
                erroSemantico(msg, tn->linha);
            }
            tn->opr.tipoBOper = pegaTipoBaseT(tn->opr.ptn[0]->pSimb->tipoRetNovo);//bug: esta fixo! De onde vem o tipo
            fprintf(yyout,"  call(\"%s\", %d, NULL);\n", tn->opr.ptn[0]->pSimb->idNome, tn->opr.ptn[0]->pSimb->numPar);
            fprintf(yyout,"  mov(eax, NULL, &%s);\n", qres);

            if(!strcmp("leia", tn->opr.ptn[0]->pSimb->idNome)) //fucao leia, receba o valor
                fprintf(yyout, "  mov(%s,NULL,&%s); /* %s = %s */\n", qres, q3, q3, qres);
            // funcao leia(strformatado, pont);
            //  param(ts[2], NULL, NULL);//  arg2
            //  loads("%f",NULL,&tc[3]);
            //  param(tc[3], NULL, NULL);//  arg1
            //  call("leia", 2, NULL);
            //  mov(eax, NULL, &tp[2]);
            // *pont=eax
            break;
        case ABORTE:
            fprintf(yyout, "  halt(NULL,NULL,NULL);\n");
            break;
        case INT:
            if(debug) printf("debug - INT\n");
            if(tn->opr.ptn[0]->tipoN!=tipoTipo)
                if (tn->opr.ptn[0]->pSimb->tipoD!=tipoIdUndef)
                {
                    sprintf(msg,"Redeclaracao da variavel <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                    erroSemantico(msg, tn->linha);
                }
            switch (tn->opr.nops) //quantos parametros: 1, 2, 3, 4 ou 5
            {
            case 1: /* INT IDENT ; */
                tn->opr.ptn[0]->pSimb->tipoD=tipoIdInt;
                tn->opr.ptn[0]->pSimb->idx=geraTS();
                fprintf(yyout,"  loadi(0, NULL, &ts[%d]); /* int %s; */\n", tn->opr.ptn[0]->pSimb->idx, tn->opr.ptn[0]->pSimb->idNome);
                break;
            case 2:
//             INT PRINCIPAL '(' tipo ')' INICIO ';' lista_comandos FIM ';'
//                        $$ = opr(INT, 2, convtn($4), $8);
                paramTipo[0]=tn->opr.ptn[0]->tt; /* tipo do parametro */
                if(paramTipo[0]!=tipoVoid)
                    erroSemantico("Programa principal nao deve ter argumentos: inteiro principal(nada)", tn->linha);

                //addFunc("saia", (void *)exit, "exit" , 1 numParam, tipoIdFuncInt /*tipo de retorno e na TS*/, tipoParam[] /*tipo dos arg*/);
                //ps = addFunc(tn->opr.ptn[0]->pSimb->idNome, (void *)NULL, tn->opr.ptn[0]->pSimb->idNome, npar, tipoIdFuncInt, paramTipo);
                //sprintf(cabecalhoMain, "%s  loadfunc(%s, (void *)%s, \"%s\", &tf[%d], %d); /* definicao de funcao */\n", cabecalhoMain, sTipoBase[pegaTipoBaseT(ps->tipoD)], ps->idFunc, ps->idNome, ps->idx, ps->numPar);
                //fprintf(yyout, "int %s(%s)\n{\n", tn->opr.ptn[0]->pSimb->idNome, tb2c(paramTipo[0]));
                //if (debug)  printf("//    Linha:%d. \n", tn->linha);
                tipoRet=tipoInt;
                gera_quad(tn->opr.ptn[1], n+1); /* processa lista_comandos */
                fprintf(yyout, "  nop(NULL,NULL,NULL);\t/* no operation */\n} /* close main */\n\n"); /* fecha chave do main */
                break;
            case 3: /* sera que aqui casa inteiro principal(nada) {;} ? */
//             tipo IDENT '(' tipo ')' INICIO ';' lista_comandos FIM ';'
//                                      $$ = opr($1, 3, conv($2), convtn($4), $8);
                paramTipo[0]=tn->opr.ptn[1]->tt; /* tipo do parametro */
                if(paramTipo[0]==tipoVoid)
                    npar=0;
                else
                    npar=1;
                //addFunc("saia", (void *)exit, "exit" , 1 numParam, tipoIdFuncInt /*tipo de retorno e na TS*/, tipoParam[] /*tipo dos arg*/);
                ps = addFunc(tn->opr.ptn[0]->pSimb->idNome, (void *)NULL, tn->opr.ptn[0]->pSimb->idNome, npar, tipoIdFuncInt, paramTipo);
                sprintf(cabecalhoMain, "%s  loadfunc(%s, (void *)%s, \"%s\", &tf[%d], %d); /* definicao de funcao */\n", cabecalhoMain, sTipoBase[pegaTipoBaseT(ps->tipoD)], ps->idFunc, ps->idNome, ps->idx, ps->numPar);
                fprintf(yyout, "int %s(%s)\n{\n", tn->opr.ptn[0]->pSimb->idNome, tb2c(paramTipo[0]));
                //if (debug)  printf("//    Linha:%d. \n", tn->linha);
                tipoRet=tipoInt;
                gera_quad(tn->opr.ptn[2], n+1); /* processa lista_comandos */
                fprintf(yyout, "  nop(NULL,NULL,NULL);\t/* no operation */\n} /* close function */\n\n"); /* fecha chave do main */
                break;
            }
            break;
        case REAL: /* Definicao de variaveis e funcoes */
            /* falta cuidar de: */
//              | tipo IDENT ';'        $$ = opr($1, 1, conv($2)); }
//             tipo IDENT '(' tipo ')' INICIO ';' lista_comandos FIM ';'
//                                      $$ = opr($1, 3, conv($2), convtn($4), $8);
//             | tipo IDENT '(' tipo ',' tipo ')' INICIO ';' lista_comandos FIM ';'
//                                      $$ = opr($1, 4, conv($2), convtn($4), convtn($6), $10);
//             | tipo IDENT '(' tipo ',' tipo ',' tipo ')' INICIO ';' lista_comandos FIM ';'
//                                      $$ = opr($1, 5, conv($2), convtn($4), convtn($6), convtn($8), $12);

            if (tn->opr.ptn[0]->pSimb->tipoD!=tipoIdUndef)
            {
                sprintf(msg,"Redeclaracao do identificador <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                erroSemantico(msg, tn->linha);
            }
            switch (tn->opr.nops) //quantos parametros: 1, 3, 4 ou 5
            {
            case 1: /* REAL IDENT */
                //if (debug) printf("debug declaracao de VARIAVEL\n");
                tn->opr.ptn[0]->pSimb->tipoD=tipoIdDouble;
                tn->opr.ptn[0]->pSimb->idx=geraTS();
                fprintf(yyout,"  loadd(0.00, NULL, &ts[%d]); /* real %s; */\n", tn->opr.ptn[0]->pSimb->idx, tn->opr.ptn[0]->pSimb->idNome);
                break;
            case 3: /* tipo funcID (tipo) */
//             tipo IDENT '(' tipo ')' INICIO ';' lista_comandos FIM ';'
//                                      $$ = opr($1, 3, conv($2), convtn($4), $8);
                paramTipo[0]=tn->opr.ptn[1]->tt; /* tipo do parametro */
                /* bug: no .l, dar addfunc em leia, imprima, e algumas matematicas basicas */
                if(paramTipo[0]==tipoVoid)
                    npar=0;
                else
                    npar=1;
                /* bug: idNome == idFunc sempre! */
                //addFunc("saia", (void *)exit, "exit" , 1 numParam, tipoIdFuncInt /*tipo de retorno e na TS*/, tipoParam[] /*tipo dos arg*/);
                ps = addFunc(tn->opr.ptn[0]->pSimb->idNome, (void *)NULL, tn->opr.ptn[0]->pSimb->idNome, npar, tipoIdFuncDouble , paramTipo);
                sprintf(cabecalhoMain, "%s  loadfunc(%s, (void *)%s, \"%s\", &tf[%d], %d); /* definicao de funcao */\n",\
                                cabecalhoMain, sTipoBase[pegaTipoBaseT(ps->tipoD)], ps->idFunc, ps->idNome, ps->idx, ps->numPar); /*so feito dentro do main*/
                //fprintf(yyout,"  loadfunc(%s,   (void *)%s,\"%s\", &tf[%d], %d); /* definicao de funcao */\n", sTipoBase[pegaTipoBaseT(ps->tipoD)], ps->idFunc, ps->idNome, ps->idx, ps->numPar); /*so feito dentro do main*/
                fprintf(yyout, "double %s(%s)\n{\n", tn->opr.ptn[0]->pSimb->idNome, tb2c(paramTipo[0]));
                //if (debug)  printf("//    Linha:%d. \n", tn->linha);
                tipoRet=tipoDouble;
                gera_quad(tn->opr.ptn[2], n+1); /* processa lista_comandos */
                fprintf(yyout, "  nop(NULL,NULL,NULL);\t/* no operation */\n} /* close function */\n\n"); /* fecha chave do main */
                break;
            case 4:
//             | tipo IDENT '(' tipo ',' tipo ')' INICIO ';' lista_comandos FIM ';'
//                                      $$ = opr($1, 4, conv($2), convtn($4), convtn($6), $10);
                gera_quad(tn->opr.ptn[3], n); /* processa lista_comandos */
                break;
            case 5:
//             | tipo IDENT '(' tipo ',' tipo ',' tipo ')' INICIO ';' lista_comandos FIM ';'
//                                      $$ = opr($1, 5, conv($2), convtn($4), convtn($6), convtn($8), $12);
                gera_quad(tn->opr.ptn[4], n); /* processa lista_comandos */
                break;
            default:
                sprintf(msg,"Numero de parametros declarados (%d) na funcao <%s> excede o limite permitido.", tn->opr.ptn[0]->pSimb->numPar, tn->opr.ptn[0]->pSimb->idNome);
                erroSemantico(msg, tn->linha); /* exit(1) */
            }
            break;
        case TEXTO:
            if (tn->opr.ptn[0]->pSimb->tipoD!=tipoIdUndef)
            {
                sprintf(msg,"Redeclaracao da variavel <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                erroSemantico(msg, tn->linha);
            }
            tn->opr.ptn[0]->pSimb->tipoD=tipoIdStr;
            tn->opr.ptn[0]->pSimb->idx=geraTS();
            fprintf(yyout,"  loads(\"\\0\", NULL, &ts[%d]); /* texto %s; */\n", tn->opr.ptn[0]->pSimb->idx, tn->opr.ptn[0]->pSimb->idNome);
            break;
        case PONTI:
            if (debug) printf("debug PONTI\n");
            if (tn->opr.ptn[0]->pSimb->tipoD!=tipoIdUndef)
            {
                sprintf(msg,"Redeclaracao da variavel <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                erroSemantico(msg, tn->linha);
            }
            tn->opr.ptn[0]->pSimb->tipoD=tipoIdPointInt;
            tn->opr.ptn[0]->pSimb->idx=geraTS();
            fprintf(yyout,"  loadi(-1, NULL, &ts[%d]); /* ponteiro int %s; */\n", tn->opr.ptn[0]->pSimb->idx, tn->opr.ptn[0]->pSimb->idNome);
            break;
        case PONTR:
            if (debug) printf("debug PONTR\n");
            if (tn->opr.ptn[0]->pSimb->tipoD!=tipoIdUndef)
            {
                sprintf(msg,"Redeclaracao da variavel <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                erroSemantico(msg, tn->linha);
            }
            tn->opr.ptn[0]->pSimb->tipoD=tipoIdPointDouble;
            tn->opr.ptn[0]->pSimb->idx=geraTS();
            fprintf(yyout,"  loadi(-1, NULL, &ts[%d]); /* ponteiro real %s; */\n", tn->opr.ptn[0]->pSimb->idx, tn->opr.ptn[0]->pSimb->idNome);
            break;
        case PONTS:
            if (debug) printf("debug PONTS\n");
            if (tn->opr.ptn[0]->pSimb->tipoD!=tipoIdUndef)
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
//                     fprintf(yyout,"  loadd(0.00, NULL, &ts[%d]); /* real %s; */\n", tn->opr.ptn[0]->pSimb->idx, tn->opr.ptn[0]->pSimb->idNome);
//                    tn->opr.tipoBOper = pegaTipoBase(tn->pSimb-tipoD);
        case ';':
            fprintf(yyout, "  nop(NULL,NULL,NULL);\t/* no operation */\n");
            break;
        case 'l': /* lista de comandos */
            gera_quad(tn->opr.ptn[0], n);
            gera_quad(tn->opr.ptn[1], n);
            break;
        case '=': //p=&l; ATTRIB
//            if (debug) printf("debug =\n");
//            printNodo(tn->opr.ptn[0], 0, "tn->opr.ptn[0]");
            qres=gera_quad(tn->opr.ptn[0], n+1);
//            if (debug) printf("debug =2\n");
            q1=gera_quad(tn->opr.ptn[1], n+1);
            if (tn->opr.ptn[0]->pSimb->tipoD == tipoIdUndef)
            {
                sprintf(msg,"Atribuicao invalida a variavel <%s> nao declarada.", tn->opr.ptn[0]->pSimb->idNome);
                erroSemantico(msg, tn->linha);
            }
            if (!variavel(tn->opr.ptn[0])) // tentou func(a)=1;
            {
                sprintf(msg,"Atribuicao invalida a uma funcao <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                erroSemantico(msg, tn->linha);
            }
            t1=pegaTipoBase(tn->opr.ptn[0]); //tipoUndef, tipoInt, tipoDouble, tipoStr, nao tipoPoint
            t2=pegaTipoBase(tn->opr.ptn[1]);
            if (ponteiro(tn->opr.ptn[0]) && t2!=tipoInt)
            {
                sprintf(msg,"Atribuicao incompativel com ponteiros. <%s> = <%s>.", nomeTipo(tn->opr.ptn[0]), nomeTipo(tn->opr.ptn[1]));
                erroSemantico(msg, tn->linha);
            }
            if (t1==t2 || (ponteiro(tn->opr.ptn[0]) && t2==tipoInt))
            {
                tn->opr.tipoBOper = t2;
                fprintf(yyout, "  mov(%s,NULL,&%s); /* %s = %s */\n", q1, qres, tn->opr.ptn[0]->pSimb->idNome, q1);
            }
            else
            { /* tipos diferentes */
                if (debug) printf("debug = else\n");
                //printf("Atribuicao de tipos diferentes. <%p> = <%p>.", tn->opr.ptn[0], tn->opr.ptn[1]);
                //sprintf(msg,"Atribuicao de tipos diferentes. <%d> = <%d>.", tn->opr.ptn[0]->pSimb->tipoD, tn->opr.ptn[1]->opr.tipoBOper);
                sprintf(msg,"Atribuicao de tipos diferentes. <%s> = <%s>.", nomeTipo(tn->opr.ptn[0]), nomeTipo(tn->opr.ptn[1]));
                erroSemantico(msg, tn->linha);
            }
            //if(debug) printf("debug =fim\n");
            break;
        case PATTRIB: //    | '*' IDENT '=' expr        { $$ = opr(PATTRIB, 2, conv($2), $4); }
            if (debug) printf("debug PATTRIB\n");
            qres=gera_quad(tn->opr.ptn[0], n+1);
            q1=gera_quad(tn->opr.ptn[1], n+1);
            if (!ponteiro(tn->opr.ptn[0]))
            {
                sprintf(msg,"Atribuicao invalida a variavel <%s> nao-ponteiro.", tn->opr.ptn[0]->pSimb->idNome);
                erroSemantico(msg, tn->linha);
            }
            t1=pegaTipoBase(tn->opr.ptn[0]);//tipoUndef tipoInt tipoDouble tipoStr tipoPointInt tipoPointDouble tipoPointStr
            t2=pegaTipoBase(tn->opr.ptn[1]);
            if (t1==t2)
            {
                tn->opr.tipoBOper = t2;
                fprintf(yyout, "  mov_pb(%s,NULL,(&%s)); /* * %s = %s */\n", q1, qres, tn->opr.ptn[0]->pSimb->idNome, q1);
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
            if (tn->opr.tipoBOper  == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de menos unario. - <%s>", sTipoBase[tn->opr.tipoBOper]);
                erroSemantico(msg, tn->linha);
            }
            fprintf(yyout, "  uminus(%s,NULL,&%s);\n", q1, qres);
            break;
        case UPONT: //i=*q=j;
            if (debug) printf("debug UPONT\n");
            q1=gera_quad(tn->opr.ptn[0], n+1);
            qres=geraTP(&itemp);
            if (!ponteiro(tn->opr.ptn[0]))
            {
                sprintf(msg,"Tentativa de apontar valor em variavel nao-ponteiro. * <%s>", sTipoBase[t1]);
                erroSemantico(msg, tn->linha);
            }
            fprintf(yyout, "  mov_pa((%s),NULL,&%s); /* %s = * %s */\n", q1, qres, qres, q1);
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
            if (debug) printf("debug UEND\n");
            q1=gera_quad(tn->opr.ptn[0], n+1);
            t1 = pegaTipoBase(tn->opr.ptn[0]);
            //tn->opr.tipoBOper = tipoInt;
            //bug: erro! esta permitindo um 'ponteiro real p' apontar para um int i;
            //ponteiro int p; real f; p=&f;
            //solucao: retorna tipoPointInt/tipoPointDouble ou tipoEndInt tipoEndDouble
            //o que eh p? tipoPointInt. *p? tipoInt. i? tipoInt. &i? tipoPointInt *i=erro. &q? tipoPointInt
            // ponteiro ponteiro r; r? tipoPointPointInt. *r? tipoPointInt. **r? tipoInt
            if (t1 == tipoInt)
                tn->opr.tipoBOper = tipoPointInt; //operador & retorna tipoPointInt
            else if (t1 == tipoDouble)
                tn->opr.tipoBOper = tipoPointDouble; //operador & retorna tipoPointDouble
            else if (t1 == tipoStr)
                tn->opr.tipoBOper = tipoPointStr; //operador & retorna tipoPointStr*/
//                    else
            if (!variavel(tn->opr.ptn[0]))
            {
                sprintf(msg,"Operador endereco nao aceita variavel deste tipo. & <%s>", sTipoBase[t1]);
                erroSemantico(msg, tn->linha);
            }

            ps = achaInt(tn->opr.ptn[0]->pSimb->idx);
            sprintf(qtemp,"tc[%d]",ps->idx); //constante com indice
            if (!ps->uso)
            {
                fprintf(yyout, "  loadi(%d,NULL,&%s); /* %s = %d */\n", tn->opr.ptn[0]->pSimb->idx, qtemp, qtemp, tn->opr.ptn[0]->pSimb->idx); //tc[1]=ptn->idx
                ps->uso=1;
            }
            break;
        case INCPOS: //IDENT INC
            if (debug) printf("debug INCPOS\n");
            q1=gera_quad(tn->opr.ptn[0], n+1); // mov(q1, null, qres)
            qres=geraTP(&itemp); //tp[0] == ret
            t1 = pegaTipoBase(tn->opr.ptn[0]);
            if (t1 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de incremento pos-fixado. <%s>++", sTipoBase[tn->opr.tipoBOper]);
                erroSemantico(msg, tn->linha);
            }
            if (t1 == tipoStr)
                erroSemantico("Nao posso incrementar textos.", tn->linha);
            tn->opr.tipoBOper = t1;
            fprintf(yyout, "  mov(%s,NULL,&%s); /* %s = %s */\n", q1, qres, qres, tn->opr.ptn[0]->pSimb->idNome);
            ps = achaInt(1);
            sprintf(qtemp,"tc[%d]",ps->idx); //constante 1
            if (!ps->uso)
            {
                fprintf(yyout, "  loadi(1,NULL,&%s); /* %s = 1 */\n", qtemp, qtemp); //tp[1]=1
                ps->uso=1;
            }
            q3=geraTP(&itemp); //tp[3]
            fprintf(yyout, "  add(%s,%s,&%s);\n", q1, qtemp, q3);
            fprintf(yyout, "  mov(%s,NULL,&%s); /* %s = %s */\n", q3, q1, tn->opr.ptn[0]->pSimb->idNome, q3);
            //printf("debug 3\n");
            break;
        case INCPRE: //INC IDENT
            if (debug) printf("debug INCPRE\n");
            qres=gera_quad(tn->opr.ptn[0], n+1); // add(qres, 1, q1)
            q1=geraTP(&itemp);
            t1 = pegaTipoBase(tn->opr.ptn[0]);
            if (t1 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de incremento pre-fixado. ++<%s>", sTipoBase[tn->opr.tipoBOper]);
                erroSemantico(msg, tn->linha);
            }
            if (t1 == tipoStr)
                erroSemantico("Nao posso incrementar textos.", tn->linha);
            tn->opr.tipoBOper = t1;
            ps = achaInt(1);
            sprintf(qtemp,"tc[%d]",ps->idx); //constante 1
            if (!ps->uso)
            {
                fprintf(yyout, "  loadi(1,NULL,&%s); /* %s = 1 */\n", qtemp, qtemp); //tp[1]=1
                ps->uso=1;
            }
            fprintf(yyout, "  add(%s,%s,&%s);\n", qres, qtemp, q1); //A+1 -> q1
            fprintf(yyout, "  mov(%s,NULL,&%s); /* %s = %s */\n", q1, qres, tn->opr.ptn[0]->pSimb->idNome, q1);
            //printf("debug 4\n");
            break;
        case DECPOS: //    | IDENT DEC                 { $$ = opr(DECPOS, 1, conv($1)); }
            //if(debug) printf("debug DECPOS\n");
            q1=gera_quad(tn->opr.ptn[0], n+1); // mov(q1, null, qres)
            qres=geraTP(&itemp); //tp[0] == ret
            t1 = pegaTipoBase(tn->opr.ptn[0]);
            if (t1 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de incremento pos-fixado. <%s>++", sTipoBase[tn->opr.tipoBOper]);
                erroSemantico(msg, tn->linha);
            }
            if (t1 == tipoStr)
                erroSemantico("Nao posso incrementar textos.", tn->linha);
            tn->opr.tipoBOper = t1;
            fprintf(yyout, "  mov(%s,NULL,&%s); /* %s = %s */\n", q1, qres, qres, tn->opr.ptn[0]->pSimb->idNome);
            ps = achaInt(1);
            sprintf(qtemp,"tc[%d]",ps->idx); //constante 1
            if (!ps->uso)
            {
                fprintf(yyout, "  loadi(1,NULL,&%s); /* %s = 1 */\n", qtemp, qtemp); //tp[1]=1
                ps->uso=1;
            }
            q3=geraTP(&itemp); //tp[3]
            fprintf(yyout, "  sub(%s,%s,&%s);\n", q1, qtemp, q3);
            fprintf(yyout, "  mov(%s,NULL,&%s); /* %s = %s */\n", q3, q1, tn->opr.ptn[0]->pSimb->idNome, q3);
            //printf("debug 3\n");
            break;
//    | DEC IDENT                 { $$ = opr(DECPRE, 1, conv($2)); }
        case '+':
            q1=gera_quad(tn->opr.ptn[0], n+1);
            q2=gera_quad(tn->opr.ptn[1], n+1);
            qres=geraTP(&itemp);
            t1=pegaTipoBase(tn->opr.ptn[0]);
            t2=pegaTipoBase(tn->opr.ptn[1]);
            if (t1 == tipoUndef || t2 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de soma. <%s> + <%s>", sTipoBase[t1], sTipoBase[t2]);
                erroSemantico(msg, tn->linha);
            }
            if ((t1 == tipoStr || t2 == tipoStr) && (t1 != tipoStr || t2 != tipoStr))
                erroSemantico("Nao posso somar textos com numeros.", tn->linha);
            if (ponteiro(tn->opr.ptn[0]) || ponteiro(tn->opr.ptn[1]))
                erroSemantico("Nao posso somar ponteiros.", tn->linha);
            if (t1==tipoDouble || t2==tipoDouble)
                tn->opr.tipoBOper = tipoDouble;
            else
                tn->opr.tipoBOper = t1;
            if (t1 == tipoStr)
                tn->opr.tipoBOper = tipoStr;
            fprintf(yyout, "  add(%s,%s,&%s);\n", q1, q2, qres);
            break;
        case '-':
            q1=gera_quad(tn->opr.ptn[0], n+1);
            q2=gera_quad(tn->opr.ptn[1], n+1);
            qres=geraTP(&itemp);
            t1=pegaTipoBase(tn->opr.ptn[0]);
            t2=pegaTipoBase(tn->opr.ptn[1]);
            if (t1 == tipoUndef || t2 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de subtracao. <%s> - <%s>", sTipoBase[t1], sTipoBase[t2]);
                erroSemantico(msg, tn->linha);
            }
            if (t1 == tipoStr || t2 == tipoStr)
                erroSemantico("Nao posso subtrair textos.", tn->linha);
            if (ponteiro(tn->opr.ptn[0]) || ponteiro(tn->opr.ptn[1]))
                erroSemantico("Nao posso subtrair ponteiros.", tn->linha);
            if (t1==tipoDouble || t2==tipoDouble)
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
            if (t1 == tipoUndef || t2 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de multiplicacao. <%s> * <%s>", sTipoBase[t1], sTipoBase[t2]);
                erroSemantico(msg, tn->linha);
            }
            if (t1 == tipoStr || t2 == tipoStr)
                erroSemantico("Nao posso multiplicar textos.", tn->linha);
            if (ponteiro(tn->opr.ptn[0]) || ponteiro(tn->opr.ptn[1]))
                erroSemantico("Nao posso multiplicar ponteiros.", tn->linha);
            if (t1==tipoDouble || t2==tipoDouble)
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
            if (t1 == tipoUndef || t2 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de divisao. <%s> / <%s>", sTipoBase[t1], sTipoBase[t2]);
                erroSemantico(msg, tn->linha);
            }
            if (t1 == tipoStr || t2 == tipoStr)
                erroSemantico("Nao posso dividir textos.", tn->linha);
            if (ponteiro(tn->opr.ptn[0]) || ponteiro(tn->opr.ptn[1]))
                erroSemantico("Nao posso dividir ponteiros.", tn->linha);
            if (t1==tipoDouble || t2==tipoDouble)
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
            if (t1 == tipoUndef || t2 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de modulo. <%s> %% <%s>", sTipoBase[t1], sTipoBase[t2]);
                erroSemantico(msg, tn->linha);
            }
            if (t1 == tipoStr || t2 == tipoStr)
                erroSemantico("Nao posso calcular modulo de textos.", tn->linha);
            if (ponteiro(tn->opr.ptn[0]) || ponteiro(tn->opr.ptn[1]))
                erroSemantico("Nao posso calcular modulo de ponteiros.", tn->linha);
            if (t1 == tipoDouble || t2 == tipoDouble)
                erroSemantico("Nao posso calcular modulo de <tipoDouble>.", tn->linha);
            tn->opr.tipoBOper = tipoInt;
            fprintf(yyout, "  mod(%s,%s,&%s);\n", q1, q2, qres);
            break;
        case '(':
            qres=gera_quad(tn->opr.ptn[0], n+1);
            tn->opr.tipoBOper = pegaTipoBase(tn->opr.ptn[0]);
            if (tn->opr.tipoBOper  == tipoUndef)
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
            if (t1 == tipoUndef || t2 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de menor-que. <%s> < <%s>", sTipoBase[t1], sTipoBase[t2]);
                erroSemantico(msg, tn->linha);
            }
            if ((t1 == tipoStr || t2 == tipoStr) && (t1 != tipoStr || t2 != tipoStr))
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
            if (t1 == tipoUndef || t2 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de maior-que. <%s> > <%s>", sTipoBase[t1], sTipoBase[t2]);
                erroSemantico(msg, tn->linha);
            }
            if ((t1 == tipoStr || t2 == tipoStr) && (t1 != tipoStr || t2 != tipoStr))
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
            if (t1 == tipoUndef || t2 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de maior-igual. <%s> >= <%s>", sTipoBase[t1], sTipoBase[t2]);
                erroSemantico(msg, tn->linha);
            }
            if ((t1 == tipoStr || t2 == tipoStr) && (t1 != tipoStr || t2 != tipoStr))
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
            if (t1 == tipoUndef || t2 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de menor-igual. <%s> <= <%s>", sTipoBase[t1], sTipoBase[t2]);
                erroSemantico(msg, tn->linha);
            }
            if ((t1 == tipoStr || t2 == tipoStr) && (t1 != tipoStr || t2 != tipoStr))
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
            if (t1 == tipoUndef || t2 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de diferente. <%s> != <%s>", sTipoBase[t1], sTipoBase[t2]);
                erroSemantico(msg, tn->linha);
            }
            if ((t1 == tipoStr || t2 == tipoStr) && (t1 != tipoStr || t2 != tipoStr))
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
            if (t1 == tipoUndef || t2 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de igual. <%s> == <%s>", sTipoBase[t1], sTipoBase[t2]);
                erroSemantico(msg, tn->linha);
            }
            if ((t1 == tipoStr || t2 == tipoStr) && (t1 != tipoStr || t2 != tipoStr))
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
            if (t1 == tipoUndef || t2 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de E logico. <%s> E <%s>", sTipoBase[t1], sTipoBase[t2]);
                erroSemantico(msg, tn->linha);
            }
            if (t1 == tipoStr || t2 == tipoStr)
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
            if (t1 == tipoUndef || t2 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de OU logico. <%s> OU <%s>", sTipoBase[t1], sTipoBase[t2]);
                erroSemantico(msg, tn->linha);
            }
            if (t1 == tipoStr || t2 == tipoStr)
                erroSemantico("Nao posso operar (OU) em textos.", tn->linha);
            tn->opr.tipoBOper = tipoInt;
            fprintf(yyout, "  rela_or(%s,%s,&%s);\n", q1,q2,qres);
            break;
        case NAO:
            q1=gera_quad(tn->opr.ptn[0], n+1);
            qres=geraTP(&itemp);
            t1=pegaTipoBase(tn->opr.ptn[0]);
            if (t1 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de NAO logico. NAO <%s>", sTipoBase[t1]);
                erroSemantico(msg, tn->linha);
            }
            if (t1 == tipoStr)
                erroSemantico("Nao posso operar (NAO) em textos.", tn->linha);
            tn->opr.tipoBOper = tipoInt;
            fprintf(yyout, "  rela_no(%s,%s,&%s);\n", q1,"NULL",qres);
            break;
        case RETORNE:
            if(tipoRet==tipoUndef)
                erroSemantico("Tipo de retorno indefinido.", tn->linha);
            if(tn->opr.nops==0)
            {
                tn->opr.tipoBOper = tipoVoid;
                fprintf(yyout,"  retn;\n");
                if(tipoRet!=tipoVoid)
                {
                    sprintf(msg, "Retorno <tipoVoid> na funcao de <%s>.", sTipoBase[tipoRet]);
                    erroSemantico(msg, tn->linha);
                }
            }
            else
            {
                q1=gera_quad(tn->opr.ptn[0], n+1);
                t1=pegaTipoBase(tn->opr.ptn[0]);
                if (t1 == tipoUndef)
                {
                    sprintf(msg,"Operando nao declarado na operacao de RETORNE(<%s>)", sTipoBase[t1]);
                    erroSemantico(msg, tn->linha);
                }
/*                if (t1 == tipoStr)
                    erroSemantico("Nao posso retornar textos.", tn->linha);*/
                if (ponteiro(tn->opr.ptn[0]))
                    erroSemantico("Nao posso retornar ponteiros.", tn->linha);
                if(tipoRet!=t1)
                {
                    sprintf(msg, "Retorno <%s> na funcao de <%s>.", sTipoBase[t1], sTipoBase[tipoRet]);
                    erroSemantico(msg, tn->linha);
                }
                tn->opr.tipoBOper = t1;
                switch(t1)
                {
                    case tipoInt:
                        fprintf(yyout,"  ret(%s.ival);\n", q1);
                        break;
                    case tipoDouble:
                        fprintf(yyout,"  ret(%s.dval);\n", q1);
                        break;
                    case tipoStr:
                        fprintf(yyout,"  ret(%s.sval);\n", q1);
                        break;
                    default:
                        fprintf(yyout,"  ret(%s.ival);\n", q1);
                        break;
                }
            }
            break;
        default:
            sprintf(msg,"Operador desconhecido <%s>", token(tn->opr.oper));
            erroSemantico(msg, tn->linha);
        }
        break;
    case tipoTipo:
    default:
            sprintf(msg,"Impossibel gerar quadruplas de tipoNodo tipoN==tipoTipo ou erro desconhecido (switch-default)");
            erroSemantico(msg, tn->linha);
    }
    if (qres!=NULL) //retorna na ordem de prioridade: qres ou qtemp
        strcpy(qtemp,qres);
    free(q1);
    free(q2);
    free(q3);
    free(qres);
    return strdup(qtemp);
} //passo-1




char *gera_quad(nodo *tn, int n)
{
    char *q1=NULL, *q2=NULL, *q3=NULL, *qres=NULL, qtemp[20]="", qtemp2[20];
    char msg[128];
    int itemp, t1, t2, t3, npar;
    int paramTipo[MAX_PARAM]; /* 3 */
    tabelaSimb *ps;

    if (tn==NULL)
        return strdup(qtemp);

    //fprintf(stderr, "gera_quad(tn:%p, n:%d), tn->tipoN:%d\n", tn, n, tn->tipoN);
    //printTS();
    //printNodo(tn,n,"tn");
    switch (tn->tipoN)
    {
    case tipoSimb:
        switch (tn->pSimb->tipoD)
        {
        case tipoConInt:
            //if(debug) printf("debug tipoConInt\n");
            sprintf(qtemp,"tc[%d]",tn->pSimb->idx); //achaId preenche idx
            if (!tn->pSimb->uso)
                fprintf(yyout, "  loadi(%d,%s,&%s);\n", tn->pSimb->ival, "NULL", qtemp);
            tn->pSimb->uso=1;
            break;
        case tipoConDouble:
            //if(debug) printf("debug tipoConDouble\n");
            sprintf(qtemp,"tc[%d]",tn->pSimb->idx);
            if (!tn->pSimb->uso)
                fprintf(yyout, "  loadd(%.2f,%s,&%s);\n", tn->pSimb->dval, "NULL", qtemp);
            tn->pSimb->uso=1;
            break;
        case tipoConStr:
            //if(debug) printf("debug tipoConStr\n");
            sprintf(qtemp,"tc[%d]",tn->pSimb->idx);
            if (!tn->pSimb->uso)
                fprintf(yyout, "  loads(%s,%s,&%s);\n", tn->pSimb->sval, "NULL", qtemp);
            tn->pSimb->uso=1;
            break;
        case tipoIdInt:
        case tipoIdDouble:
        case tipoIdStr:
        case tipoIdPointInt:
        case tipoIdPointDouble:
        case tipoIdPointStr:
            //if(debug) printf("debug tipoId...\n");
            sprintf(qtemp,"ts[%d]",tn->pSimb->idx);
            //if(debug) printf("debug tipoId... ok\n");
            break;
        case tipoIdFuncInt:
            //case tipoIdFuncFloat:
        case tipoIdFuncDouble:
            //case tipoIdFuncChar:
        case tipoIdFuncStr:
        case tipoIdFuncVoid:
        case tipoIdFuncPVoid:
            //if(debug) printf("debug tipoIdFunc...\n");
            sprintf(qtemp,"tf[%d]",tn->pSimb->idx);
            break;
        case tipoIdUndef:
        default:
            //if (debug) printf("debug tipoIdUndef default...\n");
            sprintf(qtemp,"ts[?]");
            //if(debug) printf("debug tipoIdUndef default, qtemp: %s\n", qtemp);
            sprintf(msg,"Operando nao declarado na chamada da funcao <%s>.", tn->pSimb->idNome);
            erroSemantico(msg, tn->linha);
            break;
        }
        break;
    case tipoOper:
        switch (tn->opr.oper)
        {
        case INICIO: //INICIO; comandos FIM;
            //preprocs blocos principio             { $$ = opr(INICIO, 2, $2, $3); }
            //if (debug) printf("debug tipoOper INICIO (%d)\n", tn->opr.nops);
            fprintf(yyout, "//    Gerado pelo compilador Portugol versao 3r\n");
            fprintf(yyout, "//    Autor: Ruben Carlo Benante\n");
            fprintf(yyout, "//    Email: rcb@beco.cc\n");
            fprintf(yyout, "//    Data: 23/05/2009, 10/03/2011\n");
            fprintf(yyout, "//    Compilado em: %s as %s\n\n", __DATE__, __TIME__);
            fprintf(yyout, "#include <stdio.h>\n");
            fprintf(yyout, "#include <stdlib.h>\n");
            fprintf(yyout, "#include <math.h>\n");
            fprintf(yyout, "#include \"quadruplas.h\"\n\n");
//            fprintf(yyout, "#define MAX_TS 100 /* tabela de simbolos */\n");
//            fprintf(yyout, "#define MAX_TC 100 /* tabela de constantes */\n");
//            fprintf(yyout, "#define MAX_TP 100 /* tabela de temporarios */\n");
//            fprintf(yyout, "#define MAX_TF 100 /* tabela de funcoes */\n\n");
//            fprintf(yyout, "superTipo ts[MAX_TS];\n");
//            fprintf(yyout, "superTipo tc[MAX_TC];\n");
//            fprintf(yyout, "superTipo tp[MAX_TP];\n");
//            fprintf(yyout, "superFunc tf[MAX_TF];\n\n");
            gera_quad(tn->opr.ptn[0], n+1);
            fprintf(yyout,"int main(void) /* principal */\n{\n");
            fprintf(yyout,"%s\n", cabecalhoMain);
            //fprintf(yyout,"  loadfunc(tipoInt,   (void *)%s, \"%s\", &tf[%d], %d); /* definicao de funcao */\n", /*so feito dentro do main*/ ps->idFunc, ps->idNome, ps->idx, ps->numPar);
            tipoRet=tipoInt;
            gera_quad(tn->opr.ptn[1], n+1);
            //printf("debug - INICIO - gera_quad(ptn[1]) ok! \n");
            if (n==0)
            {
                if (debugTabela)
                    printTS();
                if (debugArvore)
                    printNodo(tn,0,"tn");
                //fprintf(yyout, "  nop(NULL,NULL,NULL);\t/* no operation */\n} /* close main */\n"); /* fecha chave do main */
            }
            break;
        case SE:
            q1=gera_quad(tn->opr.ptn[0], n+1); //expr
            q2=geraLB(&itemp);//inicio_senao ou fim_se
            if (tn->opr.nops>2) //tem senao
                q3=geraLB(&itemp);//fim_se
            fprintf(yyout, "  jump_f(");//caso falso pula para senao ou para fim_se
            fprintf(yyout, "%s,", q1);
            fprintf(yyout, "%s,", "NULL");
            fprintf(yyout, "%s);\t/* if(F) goto %s */\n", q2, q2); //pula para senao ou para fim_se
            gera_quad(tn->opr.ptn[1], n+1); //comandos do entao
            if (tn->opr.nops>2) //tem senao, pula para fim_se
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
        case FUNC: /* Aqui a chamada da funcao. Para definicao do prototipo, veja tipos */
            if (debug) printf("debug FUNC\n");
            //    IDENT '(' ')'                       { $$ = opr(FUNC, 1, conv($1)); }
            //    | IDENT '(' expr ')'                { $$ = opr(FUNC, 2, conv($1), $3); }
            //    | IDENT '(' expr ',' expr ')'       { $$ = opr(FUNC, 3, conv($1), $3, $5); }
            //printf("tn->opr.ptn[0]=%p\n", tn->opr.ptn[0]);
            //fprintf(stderr,"debug Numero de parametros declarados (%d). Usados (%d). Funcao <%s>. Operador oper:%d\n", tn->opr.ptn[0]->pSimb->numPar, tn->opr.nops-1, tn->opr.ptn[0]->pSimb->idNome, tn->opr.oper);
            //printf("tn->opr.ptn[0]= ok!\n");
            q1=gera_quad(tn->opr.ptn[0], n+1); //IDENT ts[?]
            //if(debug) printf("debug FUNC q1 ok.\n");
            qres=geraTP(&itemp);//retorno da funcao em um temporario
            if (tn->opr.ptn[0]->pSimb->numPar != tn->opr.nops-1)
            {
                sprintf(msg,"Numero de parametros declarados (%d) nao coincide com usados (%d) na chamada da funcao <%s>.", tn->opr.ptn[0]->pSimb->numPar, tn->opr.nops-1, tn->opr.ptn[0]->pSimb->idNome);
                erroSemantico(msg, tn->linha);
            }
            switch (tn->opr.ptn[0]->pSimb->numPar) //ou tn->opr.nops
            {
            case 2:
                if (!strcmp(tn->opr.ptn[0]->pSimb->idNome,"imprima")) //se imprima
                    if (!tn->opr.ptn[1]->pSimb->formatadoSval)
                    {
                        sprintf(msg,"Formato incorreto para a funcao imprima(\"formato\", expr).");
                        erroSemantico(msg, tn->linha);
                    }
                q3=gera_quad(tn->opr.ptn[2], n+1); //arg2 == $5
                t3=pegaTipoBase(tn->opr.ptn[2]); //tipo do arg2: tipoInt, tipoDouble, tipoStr, tipoUndef
                fprintf(yyout,"  param(%s, NULL, NULL); /* arg2 */\n", q3);
                if (t3 == tipoUndef)
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
                if (t2 == tipoUndef)
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
                sprintf(msg,"Funcao <%s> possui argumentos demais.", tn->opr.ptn[0]->pSimb->idNome);
                erroSemantico(msg, tn->linha);
            }
            tn->opr.tipoBOper = pegaTipoBaseT(tn->opr.ptn[0]->pSimb->tipoRetNovo);//bug: esta fixo! De onde vem o tipo
            fprintf(yyout,"  call(\"%s\", %d, NULL);\n", tn->opr.ptn[0]->pSimb->idNome, tn->opr.ptn[0]->pSimb->numPar);
            fprintf(yyout,"  mov(eax, NULL, &%s);\n", qres);

            if(!strcmp("leia", tn->opr.ptn[0]->pSimb->idNome)) //fucao leia, receba o valor
                fprintf(yyout, "  mov(%s,NULL,&%s); /* %s = %s */\n", qres, q3, q3, qres);
            // funcao leia(strformatado, pont);
            //  param(ts[2], NULL, NULL);//  arg2
            //  loads("%f",NULL,&tc[3]);
            //  param(tc[3], NULL, NULL);//  arg1
            //  call("leia", 2, NULL);
            //  mov(eax, NULL, &tp[2]);
            // *pont=eax
            break;
        case ABORTE:
            fprintf(yyout, "  halt(NULL,NULL,NULL);\n");
            break;
        case INT:
            if(debug) printf("debug - INT\n");
            if(tn->opr.ptn[0]->tipoN!=tipoTipo)
                if (tn->opr.ptn[0]->pSimb->tipoD!=tipoIdUndef)
                {
                    sprintf(msg,"Redeclaracao da variavel <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                    erroSemantico(msg, tn->linha);
                }
            switch (tn->opr.nops) //quantos parametros: 1, 2, 3, 4 ou 5
            {
            case 1: /* INT IDENT ; */
                tn->opr.ptn[0]->pSimb->tipoD=tipoIdInt;
                tn->opr.ptn[0]->pSimb->idx=geraTS();
                fprintf(yyout,"  loadi(0, NULL, &ts[%d]); /* int %s; */\n", tn->opr.ptn[0]->pSimb->idx, tn->opr.ptn[0]->pSimb->idNome);
                break;
            case 2:
//             INT PRINCIPAL '(' tipo ')' INICIO ';' lista_comandos FIM ';'
//                        $$ = opr(INT, 2, convtn($4), $8);
                paramTipo[0]=tn->opr.ptn[0]->tt; /* tipo do parametro */
                if(paramTipo[0]!=tipoVoid)
                    erroSemantico("Programa principal nao deve ter argumentos: inteiro principal(nada)", tn->linha);

                //addFunc("saia", (void *)exit, "exit" , 1 numParam, tipoIdFuncInt /*tipo de retorno e na TS*/, tipoParam[] /*tipo dos arg*/);
                //ps = addFunc(tn->opr.ptn[0]->pSimb->idNome, (void *)NULL, tn->opr.ptn[0]->pSimb->idNome, npar, tipoIdFuncInt, paramTipo);
                //sprintf(cabecalhoMain, "%s  loadfunc(%s, (void *)%s, \"%s\", &tf[%d], %d); /* definicao de funcao */\n", cabecalhoMain, sTipoBase[pegaTipoBaseT(ps->tipoD)], ps->idFunc, ps->idNome, ps->idx, ps->numPar);
                //fprintf(yyout, "int %s(%s)\n{\n", tn->opr.ptn[0]->pSimb->idNome, tb2c(paramTipo[0]));
                //if (debug)  printf("//    Linha:%d. \n", tn->linha);
                tipoRet=tipoInt;
                gera_quad(tn->opr.ptn[1], n+1); /* processa lista_comandos */
                fprintf(yyout, "  nop(NULL,NULL,NULL);\t/* no operation */\n} /* close main */\n\n"); /* fecha chave do main */
                break;
            case 3: /* sera que aqui casa inteiro principal(nada) {;} ? */
//             tipo IDENT '(' tipo ')' INICIO ';' lista_comandos FIM ';'
//                                      $$ = opr($1, 3, conv($2), convtn($4), $8);
                paramTipo[0]=tn->opr.ptn[1]->tt; /* tipo do parametro */
                if(paramTipo[0]==tipoVoid)
                    npar=0;
                else
                    npar=1;
                //addFunc("saia", (void *)exit, "exit" , 1 numParam, tipoIdFuncInt /*tipo de retorno e na TS*/, tipoParam[] /*tipo dos arg*/);
                ps = addFunc(tn->opr.ptn[0]->pSimb->idNome, (void *)NULL, tn->opr.ptn[0]->pSimb->idNome, npar, tipoIdFuncInt, paramTipo);
                sprintf(cabecalhoMain, "%s  loadfunc(%s, (void *)%s, \"%s\", &tf[%d], %d); /* definicao de funcao */\n", cabecalhoMain, sTipoBase[pegaTipoBaseT(ps->tipoD)], ps->idFunc, ps->idNome, ps->idx, ps->numPar);
                fprintf(yyout, "int %s(%s)\n{\n", tn->opr.ptn[0]->pSimb->idNome, tb2c(paramTipo[0]));
                //if (debug)  printf("//    Linha:%d. \n", tn->linha);
                tipoRet=tipoInt;
                gera_quad(tn->opr.ptn[2], n+1); /* processa lista_comandos */
                fprintf(yyout, "  nop(NULL,NULL,NULL);\t/* no operation */\n} /* close function */\n\n"); /* fecha chave do main */
                break;
            }
            break;
        case REAL: /* Definicao de variaveis e funcoes */
            /* falta cuidar de: */
//              | tipo IDENT ';'        $$ = opr($1, 1, conv($2)); }
//             tipo IDENT '(' tipo ')' INICIO ';' lista_comandos FIM ';'
//                                      $$ = opr($1, 3, conv($2), convtn($4), $8);
//             | tipo IDENT '(' tipo ',' tipo ')' INICIO ';' lista_comandos FIM ';'
//                                      $$ = opr($1, 4, conv($2), convtn($4), convtn($6), $10);
//             | tipo IDENT '(' tipo ',' tipo ',' tipo ')' INICIO ';' lista_comandos FIM ';'
//                                      $$ = opr($1, 5, conv($2), convtn($4), convtn($6), convtn($8), $12);

            if (tn->opr.ptn[0]->pSimb->tipoD!=tipoIdUndef)
            {
                sprintf(msg,"Redeclaracao do identificador <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                erroSemantico(msg, tn->linha);
            }
            switch (tn->opr.nops) //quantos parametros: 1, 3, 4 ou 5
            {
            case 1: /* REAL IDENT */
                //if (debug) printf("debug declaracao de VARIAVEL\n");
                tn->opr.ptn[0]->pSimb->tipoD=tipoIdDouble;
                tn->opr.ptn[0]->pSimb->idx=geraTS();
                fprintf(yyout,"  loadd(0.00, NULL, &ts[%d]); /* real %s; */\n", tn->opr.ptn[0]->pSimb->idx, tn->opr.ptn[0]->pSimb->idNome);
                break;
            case 3: /* tipo funcID (tipo) */
//             tipo IDENT '(' tipo ')' INICIO ';' lista_comandos FIM ';'
//                                      $$ = opr($1, 3, conv($2), convtn($4), $8);
                paramTipo[0]=tn->opr.ptn[1]->tt; /* tipo do parametro */
                /* bug: no .l, dar addfunc em leia, imprima, e algumas matematicas basicas */
                if(paramTipo[0]==tipoVoid)
                    npar=0;
                else
                    npar=1;
                /* bug: idNome == idFunc sempre! */
                //addFunc("saia", (void *)exit, "exit" , 1 numParam, tipoIdFuncInt /*tipo de retorno e na TS*/, tipoParam[] /*tipo dos arg*/);
                ps = addFunc(tn->opr.ptn[0]->pSimb->idNome, (void *)NULL, tn->opr.ptn[0]->pSimb->idNome, npar, tipoIdFuncDouble , paramTipo);
                sprintf(cabecalhoMain, "%s  loadfunc(%s, (void *)%s, \"%s\", &tf[%d], %d); /* definicao de funcao */\n",\
                                cabecalhoMain, sTipoBase[pegaTipoBaseT(ps->tipoD)], ps->idFunc, ps->idNome, ps->idx, ps->numPar); /*so feito dentro do main*/
                //fprintf(yyout,"  loadfunc(%s,   (void *)%s,\"%s\", &tf[%d], %d); /* definicao de funcao */\n", sTipoBase[pegaTipoBaseT(ps->tipoD)], ps->idFunc, ps->idNome, ps->idx, ps->numPar); /*so feito dentro do main*/
                fprintf(yyout, "double %s(%s)\n{\n", tn->opr.ptn[0]->pSimb->idNome, tb2c(paramTipo[0]));
                //if (debug)  printf("//    Linha:%d. \n", tn->linha);
                tipoRet=tipoDouble;
                gera_quad(tn->opr.ptn[2], n+1); /* processa lista_comandos */
                fprintf(yyout, "  nop(NULL,NULL,NULL);\t/* no operation */\n} /* close function */\n\n"); /* fecha chave do main */
                break;
            case 4:
//             | tipo IDENT '(' tipo ',' tipo ')' INICIO ';' lista_comandos FIM ';'
//                                      $$ = opr($1, 4, conv($2), convtn($4), convtn($6), $10);
                gera_quad(tn->opr.ptn[3], n); /* processa lista_comandos */
                break;
            case 5:
//             | tipo IDENT '(' tipo ',' tipo ',' tipo ')' INICIO ';' lista_comandos FIM ';'
//                                      $$ = opr($1, 5, conv($2), convtn($4), convtn($6), convtn($8), $12);
                gera_quad(tn->opr.ptn[4], n); /* processa lista_comandos */
                break;
            default:
                sprintf(msg,"Numero de parametros declarados (%d) na funcao <%s> excede o limite permitido.", tn->opr.ptn[0]->pSimb->numPar, tn->opr.ptn[0]->pSimb->idNome);
                erroSemantico(msg, tn->linha); /* exit(1) */
            }
            break;
        case TEXTO:
            if (tn->opr.ptn[0]->pSimb->tipoD!=tipoIdUndef)
            {
                sprintf(msg,"Redeclaracao da variavel <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                erroSemantico(msg, tn->linha);
            }
            tn->opr.ptn[0]->pSimb->tipoD=tipoIdStr;
            tn->opr.ptn[0]->pSimb->idx=geraTS();
            fprintf(yyout,"  loads(\"\\0\", NULL, &ts[%d]); /* texto %s; */\n", tn->opr.ptn[0]->pSimb->idx, tn->opr.ptn[0]->pSimb->idNome);
            break;
        case PONTI:
            if (debug) printf("debug PONTI\n");
            if (tn->opr.ptn[0]->pSimb->tipoD!=tipoIdUndef)
            {
                sprintf(msg,"Redeclaracao da variavel <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                erroSemantico(msg, tn->linha);
            }
            tn->opr.ptn[0]->pSimb->tipoD=tipoIdPointInt;
            tn->opr.ptn[0]->pSimb->idx=geraTS();
            fprintf(yyout,"  loadi(-1, NULL, &ts[%d]); /* ponteiro int %s; */\n", tn->opr.ptn[0]->pSimb->idx, tn->opr.ptn[0]->pSimb->idNome);
            break;
        case PONTR:
            if (debug) printf("debug PONTR\n");
            if (tn->opr.ptn[0]->pSimb->tipoD!=tipoIdUndef)
            {
                sprintf(msg,"Redeclaracao da variavel <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                erroSemantico(msg, tn->linha);
            }
            tn->opr.ptn[0]->pSimb->tipoD=tipoIdPointDouble;
            tn->opr.ptn[0]->pSimb->idx=geraTS();
            fprintf(yyout,"  loadi(-1, NULL, &ts[%d]); /* ponteiro real %s; */\n", tn->opr.ptn[0]->pSimb->idx, tn->opr.ptn[0]->pSimb->idNome);
            break;
        case PONTS:
            if (debug) printf("debug PONTS\n");
            if (tn->opr.ptn[0]->pSimb->tipoD!=tipoIdUndef)
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
//                     fprintf(yyout,"  loadd(0.00, NULL, &ts[%d]); /* real %s; */\n", tn->opr.ptn[0]->pSimb->idx, tn->opr.ptn[0]->pSimb->idNome);
//                    tn->opr.tipoBOper = pegaTipoBase(tn->pSimb-tipoD);
        case ';':
            fprintf(yyout, "  nop(NULL,NULL,NULL);\t/* no operation */\n");
            break;
        case 'l': /* lista de comandos */
            gera_quad(tn->opr.ptn[0], n);
            gera_quad(tn->opr.ptn[1], n);
            break;
        case '=': //p=&l; ATTRIB
//            if (debug) printf("debug =\n");
//            printNodo(tn->opr.ptn[0], 0, "tn->opr.ptn[0]");
            qres=gera_quad(tn->opr.ptn[0], n+1);
//            if (debug) printf("debug =2\n");
            q1=gera_quad(tn->opr.ptn[1], n+1);
            if (tn->opr.ptn[0]->pSimb->tipoD == tipoIdUndef)
            {
                sprintf(msg,"Atribuicao invalida a variavel <%s> nao declarada.", tn->opr.ptn[0]->pSimb->idNome);
                erroSemantico(msg, tn->linha);
            }
            if (!variavel(tn->opr.ptn[0])) // tentou func(a)=1;
            {
                sprintf(msg,"Atribuicao invalida a uma funcao <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                erroSemantico(msg, tn->linha);
            }
            t1=pegaTipoBase(tn->opr.ptn[0]); //tipoUndef, tipoInt, tipoDouble, tipoStr, nao tipoPoint
            t2=pegaTipoBase(tn->opr.ptn[1]);
            if (ponteiro(tn->opr.ptn[0]) && t2!=tipoInt)
            {
                sprintf(msg,"Atribuicao incompativel com ponteiros. <%s> = <%s>.", nomeTipo(tn->opr.ptn[0]), nomeTipo(tn->opr.ptn[1]));
                erroSemantico(msg, tn->linha);
            }
            if (t1==t2 || (ponteiro(tn->opr.ptn[0]) && t2==tipoInt))
            {
                tn->opr.tipoBOper = t2;
                fprintf(yyout, "  mov(%s,NULL,&%s); /* %s = %s */\n", q1, qres, tn->opr.ptn[0]->pSimb->idNome, q1);
            }
            else
            { /* tipos diferentes */
                if (debug) printf("debug = else\n");
                //printf("Atribuicao de tipos diferentes. <%p> = <%p>.", tn->opr.ptn[0], tn->opr.ptn[1]);
                //sprintf(msg,"Atribuicao de tipos diferentes. <%d> = <%d>.", tn->opr.ptn[0]->pSimb->tipoD, tn->opr.ptn[1]->opr.tipoBOper);
                sprintf(msg,"Atribuicao de tipos diferentes. <%s> = <%s>.", nomeTipo(tn->opr.ptn[0]), nomeTipo(tn->opr.ptn[1]));
                erroSemantico(msg, tn->linha);
            }
            //if(debug) printf("debug =fim\n");
            break;
        case PATTRIB: //    | '*' IDENT '=' expr        { $$ = opr(PATTRIB, 2, conv($2), $4); }
            if (debug) printf("debug PATTRIB\n");
            qres=gera_quad(tn->opr.ptn[0], n+1);
            q1=gera_quad(tn->opr.ptn[1], n+1);
            if (!ponteiro(tn->opr.ptn[0]))
            {
                sprintf(msg,"Atribuicao invalida a variavel <%s> nao-ponteiro.", tn->opr.ptn[0]->pSimb->idNome);
                erroSemantico(msg, tn->linha);
            }
            t1=pegaTipoBase(tn->opr.ptn[0]);//tipoUndef tipoInt tipoDouble tipoStr tipoPointInt tipoPointDouble tipoPointStr
            t2=pegaTipoBase(tn->opr.ptn[1]);
            if (t1==t2)
            {
                tn->opr.tipoBOper = t2;
                fprintf(yyout, "  mov_pb(%s,NULL,(&%s)); /* * %s = %s */\n", q1, qres, tn->opr.ptn[0]->pSimb->idNome, q1);
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
            if (tn->opr.tipoBOper  == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de menos unario. - <%s>", sTipoBase[tn->opr.tipoBOper]);
                erroSemantico(msg, tn->linha);
            }
            fprintf(yyout, "  uminus(%s,NULL,&%s);\n", q1, qres);
            break;
        case UPONT: //i=*q=j;
            if (debug) printf("debug UPONT\n");
            q1=gera_quad(tn->opr.ptn[0], n+1);
            qres=geraTP(&itemp);
            if (!ponteiro(tn->opr.ptn[0]))
            {
                sprintf(msg,"Tentativa de apontar valor em variavel nao-ponteiro. * <%s>", sTipoBase[t1]);
                erroSemantico(msg, tn->linha);
            }
            fprintf(yyout, "  mov_pa((%s),NULL,&%s); /* %s = * %s */\n", q1, qres, qres, q1);
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
            if (debug) printf("debug UEND\n");
            q1=gera_quad(tn->opr.ptn[0], n+1);
            t1 = pegaTipoBase(tn->opr.ptn[0]);
            //tn->opr.tipoBOper = tipoInt;
            //bug: erro! esta permitindo um 'ponteiro real p' apontar para um int i;
            //ponteiro int p; real f; p=&f;
            //solucao: retorna tipoPointInt/tipoPointDouble ou tipoEndInt tipoEndDouble
            //o que eh p? tipoPointInt. *p? tipoInt. i? tipoInt. &i? tipoPointInt *i=erro. &q? tipoPointInt
            // ponteiro ponteiro r; r? tipoPointPointInt. *r? tipoPointInt. **r? tipoInt
            if (t1 == tipoInt)
                tn->opr.tipoBOper = tipoPointInt; //operador & retorna tipoPointInt
            else if (t1 == tipoDouble)
                tn->opr.tipoBOper = tipoPointDouble; //operador & retorna tipoPointDouble
            else if (t1 == tipoStr)
                tn->opr.tipoBOper = tipoPointStr; //operador & retorna tipoPointStr*/
//                    else
            if (!variavel(tn->opr.ptn[0]))
            {
                sprintf(msg,"Operador endereco nao aceita variavel deste tipo. & <%s>", sTipoBase[t1]);
                erroSemantico(msg, tn->linha);
            }

            ps = achaInt(tn->opr.ptn[0]->pSimb->idx);
            sprintf(qtemp,"tc[%d]",ps->idx); //constante com indice
            if (!ps->uso)
            {
                fprintf(yyout, "  loadi(%d,NULL,&%s); /* %s = %d */\n", tn->opr.ptn[0]->pSimb->idx, qtemp, qtemp, tn->opr.ptn[0]->pSimb->idx); //tc[1]=ptn->idx
                ps->uso=1;
            }
            break;
        case INCPOS: //IDENT INC
            if (debug) printf("debug INCPOS\n");
            q1=gera_quad(tn->opr.ptn[0], n+1); // mov(q1, null, qres)
            qres=geraTP(&itemp); //tp[0] == ret
            t1 = pegaTipoBase(tn->opr.ptn[0]);
            if (t1 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de incremento pos-fixado. <%s>++", sTipoBase[tn->opr.tipoBOper]);
                erroSemantico(msg, tn->linha);
            }
            if (t1 == tipoStr)
                erroSemantico("Nao posso incrementar textos.", tn->linha);
            tn->opr.tipoBOper = t1;
            fprintf(yyout, "  mov(%s,NULL,&%s); /* %s = %s */\n", q1, qres, qres, tn->opr.ptn[0]->pSimb->idNome);
            ps = achaInt(1);
            sprintf(qtemp,"tc[%d]",ps->idx); //constante 1
            if (!ps->uso)
            {
                fprintf(yyout, "  loadi(1,NULL,&%s); /* %s = 1 */\n", qtemp, qtemp); //tp[1]=1
                ps->uso=1;
            }
            q3=geraTP(&itemp); //tp[3]
            fprintf(yyout, "  add(%s,%s,&%s);\n", q1, qtemp, q3);
            fprintf(yyout, "  mov(%s,NULL,&%s); /* %s = %s */\n", q3, q1, tn->opr.ptn[0]->pSimb->idNome, q3);
            //printf("debug 3\n");
            break;
        case INCPRE: //INC IDENT
            if (debug) printf("debug INCPRE\n");
            qres=gera_quad(tn->opr.ptn[0], n+1); // add(qres, 1, q1)
            q1=geraTP(&itemp);
            t1 = pegaTipoBase(tn->opr.ptn[0]);
            if (t1 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de incremento pre-fixado. ++<%s>", sTipoBase[tn->opr.tipoBOper]);
                erroSemantico(msg, tn->linha);
            }
            if (t1 == tipoStr)
                erroSemantico("Nao posso incrementar textos.", tn->linha);
            tn->opr.tipoBOper = t1;
            ps = achaInt(1);
            sprintf(qtemp,"tc[%d]",ps->idx); //constante 1
            if (!ps->uso)
            {
                fprintf(yyout, "  loadi(1,NULL,&%s); /* %s = 1 */\n", qtemp, qtemp); //tp[1]=1
                ps->uso=1;
            }
            fprintf(yyout, "  add(%s,%s,&%s);\n", qres, qtemp, q1); //A+1 -> q1
            fprintf(yyout, "  mov(%s,NULL,&%s); /* %s = %s */\n", q1, qres, tn->opr.ptn[0]->pSimb->idNome, q1);
            //printf("debug 4\n");
            break;
        case DECPOS: //    | IDENT DEC                 { $$ = opr(DECPOS, 1, conv($1)); }
            //if(debug) printf("debug DECPOS\n");
            q1=gera_quad(tn->opr.ptn[0], n+1); // mov(q1, null, qres)
            qres=geraTP(&itemp); //tp[0] == ret
            t1 = pegaTipoBase(tn->opr.ptn[0]);
            if (t1 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de incremento pos-fixado. <%s>++", sTipoBase[tn->opr.tipoBOper]);
                erroSemantico(msg, tn->linha);
            }
            if (t1 == tipoStr)
                erroSemantico("Nao posso incrementar textos.", tn->linha);
            tn->opr.tipoBOper = t1;
            fprintf(yyout, "  mov(%s,NULL,&%s); /* %s = %s */\n", q1, qres, qres, tn->opr.ptn[0]->pSimb->idNome);
            ps = achaInt(1);
            sprintf(qtemp,"tc[%d]",ps->idx); //constante 1
            if (!ps->uso)
            {
                fprintf(yyout, "  loadi(1,NULL,&%s); /* %s = 1 */\n", qtemp, qtemp); //tp[1]=1
                ps->uso=1;
            }
            q3=geraTP(&itemp); //tp[3]
            fprintf(yyout, "  sub(%s,%s,&%s);\n", q1, qtemp, q3);
            fprintf(yyout, "  mov(%s,NULL,&%s); /* %s = %s */\n", q3, q1, tn->opr.ptn[0]->pSimb->idNome, q3);
            //printf("debug 3\n");
            break;
//    | DEC IDENT                 { $$ = opr(DECPRE, 1, conv($2)); }
        case '+':
            q1=gera_quad(tn->opr.ptn[0], n+1);
            q2=gera_quad(tn->opr.ptn[1], n+1);
            qres=geraTP(&itemp);
            t1=pegaTipoBase(tn->opr.ptn[0]);
            t2=pegaTipoBase(tn->opr.ptn[1]);
            if (t1 == tipoUndef || t2 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de soma. <%s> + <%s>", sTipoBase[t1], sTipoBase[t2]);
                erroSemantico(msg, tn->linha);
            }
            if ((t1 == tipoStr || t2 == tipoStr) && (t1 != tipoStr || t2 != tipoStr))
                erroSemantico("Nao posso somar textos com numeros.", tn->linha);
            if (ponteiro(tn->opr.ptn[0]) || ponteiro(tn->opr.ptn[1]))
                erroSemantico("Nao posso somar ponteiros.", tn->linha);
            if (t1==tipoDouble || t2==tipoDouble)
                tn->opr.tipoBOper = tipoDouble;
            else
                tn->opr.tipoBOper = t1;
            if (t1 == tipoStr)
                tn->opr.tipoBOper = tipoStr;
            fprintf(yyout, "  add(%s,%s,&%s);\n", q1, q2, qres);
            break;
        case '-':
            q1=gera_quad(tn->opr.ptn[0], n+1);
            q2=gera_quad(tn->opr.ptn[1], n+1);
            qres=geraTP(&itemp);
            t1=pegaTipoBase(tn->opr.ptn[0]);
            t2=pegaTipoBase(tn->opr.ptn[1]);
            if (t1 == tipoUndef || t2 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de subtracao. <%s> - <%s>", sTipoBase[t1], sTipoBase[t2]);
                erroSemantico(msg, tn->linha);
            }
            if (t1 == tipoStr || t2 == tipoStr)
                erroSemantico("Nao posso subtrair textos.", tn->linha);
            if (ponteiro(tn->opr.ptn[0]) || ponteiro(tn->opr.ptn[1]))
                erroSemantico("Nao posso subtrair ponteiros.", tn->linha);
            if (t1==tipoDouble || t2==tipoDouble)
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
            if (t1 == tipoUndef || t2 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de multiplicacao. <%s> * <%s>", sTipoBase[t1], sTipoBase[t2]);
                erroSemantico(msg, tn->linha);
            }
            if (t1 == tipoStr || t2 == tipoStr)
                erroSemantico("Nao posso multiplicar textos.", tn->linha);
            if (ponteiro(tn->opr.ptn[0]) || ponteiro(tn->opr.ptn[1]))
                erroSemantico("Nao posso multiplicar ponteiros.", tn->linha);
            if (t1==tipoDouble || t2==tipoDouble)
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
            if (t1 == tipoUndef || t2 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de divisao. <%s> / <%s>", sTipoBase[t1], sTipoBase[t2]);
                erroSemantico(msg, tn->linha);
            }
            if (t1 == tipoStr || t2 == tipoStr)
                erroSemantico("Nao posso dividir textos.", tn->linha);
            if (ponteiro(tn->opr.ptn[0]) || ponteiro(tn->opr.ptn[1]))
                erroSemantico("Nao posso dividir ponteiros.", tn->linha);
            if (t1==tipoDouble || t2==tipoDouble)
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
            if (t1 == tipoUndef || t2 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de modulo. <%s> %% <%s>", sTipoBase[t1], sTipoBase[t2]);
                erroSemantico(msg, tn->linha);
            }
            if (t1 == tipoStr || t2 == tipoStr)
                erroSemantico("Nao posso calcular modulo de textos.", tn->linha);
            if (ponteiro(tn->opr.ptn[0]) || ponteiro(tn->opr.ptn[1]))
                erroSemantico("Nao posso calcular modulo de ponteiros.", tn->linha);
            if (t1 == tipoDouble || t2 == tipoDouble)
                erroSemantico("Nao posso calcular modulo de <tipoDouble>.", tn->linha);
            tn->opr.tipoBOper = tipoInt;
            fprintf(yyout, "  mod(%s,%s,&%s);\n", q1, q2, qres);
            break;
        case '(':
            qres=gera_quad(tn->opr.ptn[0], n+1);
            tn->opr.tipoBOper = pegaTipoBase(tn->opr.ptn[0]);
            if (tn->opr.tipoBOper  == tipoUndef)
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
            if (t1 == tipoUndef || t2 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de menor-que. <%s> < <%s>", sTipoBase[t1], sTipoBase[t2]);
                erroSemantico(msg, tn->linha);
            }
            if ((t1 == tipoStr || t2 == tipoStr) && (t1 != tipoStr || t2 != tipoStr))
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
            if (t1 == tipoUndef || t2 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de maior-que. <%s> > <%s>", sTipoBase[t1], sTipoBase[t2]);
                erroSemantico(msg, tn->linha);
            }
            if ((t1 == tipoStr || t2 == tipoStr) && (t1 != tipoStr || t2 != tipoStr))
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
            if (t1 == tipoUndef || t2 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de maior-igual. <%s> >= <%s>", sTipoBase[t1], sTipoBase[t2]);
                erroSemantico(msg, tn->linha);
            }
            if ((t1 == tipoStr || t2 == tipoStr) && (t1 != tipoStr || t2 != tipoStr))
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
            if (t1 == tipoUndef || t2 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de menor-igual. <%s> <= <%s>", sTipoBase[t1], sTipoBase[t2]);
                erroSemantico(msg, tn->linha);
            }
            if ((t1 == tipoStr || t2 == tipoStr) && (t1 != tipoStr || t2 != tipoStr))
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
            if (t1 == tipoUndef || t2 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de diferente. <%s> != <%s>", sTipoBase[t1], sTipoBase[t2]);
                erroSemantico(msg, tn->linha);
            }
            if ((t1 == tipoStr || t2 == tipoStr) && (t1 != tipoStr || t2 != tipoStr))
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
            if (t1 == tipoUndef || t2 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de igual. <%s> == <%s>", sTipoBase[t1], sTipoBase[t2]);
                erroSemantico(msg, tn->linha);
            }
            if ((t1 == tipoStr || t2 == tipoStr) && (t1 != tipoStr || t2 != tipoStr))
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
            if (t1 == tipoUndef || t2 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de E logico. <%s> E <%s>", sTipoBase[t1], sTipoBase[t2]);
                erroSemantico(msg, tn->linha);
            }
            if (t1 == tipoStr || t2 == tipoStr)
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
            if (t1 == tipoUndef || t2 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de OU logico. <%s> OU <%s>", sTipoBase[t1], sTipoBase[t2]);
                erroSemantico(msg, tn->linha);
            }
            if (t1 == tipoStr || t2 == tipoStr)
                erroSemantico("Nao posso operar (OU) em textos.", tn->linha);
            tn->opr.tipoBOper = tipoInt;
            fprintf(yyout, "  rela_or(%s,%s,&%s);\n", q1,q2,qres);
            break;
        case NAO:
            q1=gera_quad(tn->opr.ptn[0], n+1);
            qres=geraTP(&itemp);
            t1=pegaTipoBase(tn->opr.ptn[0]);
            if (t1 == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de NAO logico. NAO <%s>", sTipoBase[t1]);
                erroSemantico(msg, tn->linha);
            }
            if (t1 == tipoStr)
                erroSemantico("Nao posso operar (NAO) em textos.", tn->linha);
            tn->opr.tipoBOper = tipoInt;
            fprintf(yyout, "  rela_no(%s,%s,&%s);\n", q1,"NULL",qres);
            break;
        case RETORNE:
            if(tipoRet==tipoUndef)
                erroSemantico("Tipo de retorno indefinido.", tn->linha);
            if(tn->opr.nops==0)
            {
                tn->opr.tipoBOper = tipoVoid;
                fprintf(yyout,"  retn;\n");
                if(tipoRet!=tipoVoid)
                {
                    sprintf(msg, "Retorno <tipoVoid> na funcao de <%s>.", sTipoBase[tipoRet]);
                    erroSemantico(msg, tn->linha);
                }
            }
            else
            {
                q1=gera_quad(tn->opr.ptn[0], n+1);
                t1=pegaTipoBase(tn->opr.ptn[0]);
                if (t1 == tipoUndef)
                {
                    sprintf(msg,"Operando nao declarado na operacao de RETORNE(<%s>)", sTipoBase[t1]);
                    erroSemantico(msg, tn->linha);
                }
/*                if (t1 == tipoStr)
                    erroSemantico("Nao posso retornar textos.", tn->linha);*/
                if (ponteiro(tn->opr.ptn[0]))
                    erroSemantico("Nao posso retornar ponteiros.", tn->linha);
                if(tipoRet!=t1)
                {
                    sprintf(msg, "Retorno <%s> na funcao de <%s>.", sTipoBase[t1], sTipoBase[tipoRet]);
                    erroSemantico(msg, tn->linha);
                }
                tn->opr.tipoBOper = t1;
                switch(t1)
                {
                    case tipoInt:
                        fprintf(yyout,"  ret(%s.ival);\n", q1);
                        break;
                    case tipoDouble:
                        fprintf(yyout,"  ret(%s.dval);\n", q1);
                        break;
                    case tipoStr:
                        fprintf(yyout,"  ret(%s.sval);\n", q1);
                        break;
                    default:
                        fprintf(yyout,"  ret(%s.ival);\n", q1);
                        break;
                }
            }
            break;
        default:
            sprintf(msg,"Operador desconhecido <%s>", token(tn->opr.oper));
            erroSemantico(msg, tn->linha);
        }
        break;
    case tipoTipo:
    default:
            sprintf(msg,"Impossibel gerar quadruplas de tipoNodo tipoN==tipoTipo ou erro desconhecido (switch-default)");
            erroSemantico(msg, tn->linha);
    }
    if (qres!=NULL) //retorna na ordem de prioridade: qres ou qtemp
        strcpy(qtemp,qres);
    free(q1);
    free(q2);
    free(q3);
    free(qres);
    return strdup(qtemp);
} //gera_quad

int geraTF(void) //tabela de funcoes
{
    static int itf=3; /* comeca no 4, pois ja tem predefinido printf, scanf, exit, sqrt */
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
    for (n=0; n<MAX_SIMB; n++)
    {
        if (!tabSimb[n].idNome)
            return;
        printf("----------------------------\n");
        printf("tabSimb[%d].tipoD=%d (%s)\n", n, tabSimb[n].tipoD, sTipoDado[tabSimb[n].tipoD]);
        printf("tabSimb[%d].idx=%d\n", n, tabSimb[n].idx);
        printf("tabSimb[%d].idNome=%s\n", n, tabSimb[n].idNome);
        switch (tabSimb[n].tipoD)
        {
        case tipoConInt:
            printf("tabSimb[%d].uso=%d\n", n, tabSimb[n].uso);
            printf("tabSimb[%d].ival=%d\n", n, tabSimb[n].ival);
            break;
        case tipoConDouble:
            printf("tabSimb[%d].uso=%d\n", n, tabSimb[n].uso);
            printf("tabSimb[%d].fval=%.2f\n", n, tabSimb[n].dval);
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
            printf("tabSimb[%d].ifunc=%p\n", n, tabSimb[n].ifunc);
            break;
            /*            case tipoIdFuncDouble:
                            printf("tabSimb[%d].tipoRetNovo=%d (%s)\n", n, tabSimb[n].tipoRetNovo, sTipoDado[tabSimb[n].tipoRetNovo]);
                            printf("tabSimb[%d].idFunc=%s\n", n, tabSimb[n].idFunc);
                            printf("tabSimb[%d].ffunc=%p\n", n, tabSimb[n].ffunc);
                            break;*/
        case tipoIdFuncDouble:
            printf("tabSimb[%d].tipoRetNovo=%d (%s)\n", n, tabSimb[n].tipoRetNovo, sTipoDado[tabSimb[n].tipoRetNovo]);
            printf("tabSimb[%d].idFunc=%s\n", n, tabSimb[n].idFunc);
            printf("tabSimb[%d].dfunc=%p\n", n, tabSimb[n].dfunc);
            break;
            /*            case tipoIdFuncChar:
                            break;*/
        case tipoIdFuncStr:
            printf("tabSimb[%d].tipoRetNovo=%d (%s)\n", n, tabSimb[n].tipoRetNovo, sTipoDado[tabSimb[n].tipoRetNovo]);
            printf("tabSimb[%d].idFunc=%s\n", n, tabSimb[n].idFunc);
            printf("tabSimb[%d].sfunc=%p\n", n, tabSimb[n].sfunc);
            break;
        case tipoIdFuncVoid:
            printf("tabSimb[%d].tipoRetNovo=%d (%s)\n", n, tabSimb[n].tipoRetNovo, sTipoDado[tabSimb[n].tipoRetNovo]);
            printf("tabSimb[%d].idFunc=%s\n", n, tabSimb[n].idFunc);
            printf("tabSimb[%d].vfunc=%p\n", n, tabSimb[n].vfunc);
            break;
        }
    }
}

void printNodo(nodo *tn, int n, char *var)
{
    char *nome;
    int t;

    if (!tn)
        return;

    nome=nomeTipo(tn);

    if (n==0)
        printf("---------------------------- Arvore Sintatica ----------------------------\n");
    if (tn->tipoN==tipoSimb)
    {
        printf("----------------------------\n");
        printf("(%d) %s->pSimb->tipoD=%d (%s)\n", n, var, tn->pSimb->tipoD, nome);
        printf("(%d) %s->pSimb->idx=%d\n", n, var, tn->pSimb->idx);
        printf("(%d) %s->pSimb->idNome=%s\n", n, var, tn->pSimb->idNome);
        switch (tn->pSimb->tipoD)
        {
        case tipoConInt:
            printf("(%d) %s->pSimb->uso=%d\n", n, var, tn->pSimb->uso);
            printf("(%d) %s->pSimb->ival=%d\n", n, var, tn->pSimb->ival);
            break;
        case tipoConDouble:
            printf("(%d) %s->pSimb->uso=%d\n", n, var, tn->pSimb->uso);
            printf("(%d) %s->pSimb->fval=%.2f\n", n, var, tn->pSimb->dval);
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
            printf("(%d) %s->pSimb->ifunc=%p\n", n, var, tn->pSimb->ifunc);
            break;
            /*            case tipoIdFuncDouble:
                            printf("(%d) %s->pSimb->tipoRetNovo=%d (%s)\n", n, var, tn->pSimb->tipoRetNovo, sTipoDado[tn->pSimb->tipoRetNovo]);
                            printf("(%d) %s->pSimb->idFunc=%s\n", n, var, tn->pSimb->idFunc);
                            printf("(%d) %s->pSimb->ffunc=%p\n", n, var, tn->pSimb->dfunc);
                            break;*/
        case tipoIdFuncDouble:
            printf("(%d) %s->pSimb->tipoRetNovo=%d (%s)\n", n, var, tn->pSimb->tipoRetNovo, sTipoDado[tn->pSimb->tipoRetNovo]);
            printf("(%d) %s->pSimb->idFunc=%s\n", n, var, tn->pSimb->idFunc);
            printf("(%d) %s->pSimb->dfunc=%p\n", n, var, tn->pSimb->dfunc);
            break;
            /*            case tipoIdFuncChar:
                            break;*/
        case tipoIdFuncStr:
            printf("(%d) %s->pSimb->tipoRetNovo=%d (%s)\n", n, var, tn->pSimb->tipoRetNovo, sTipoDado[tn->pSimb->tipoRetNovo]);
            printf("(%d) %s->pSimb->idFunc=%s\n", n, var, tn->pSimb->idFunc);
            printf("(%d) %s->pSimb->sfunc=%p\n", n, var, tn->pSimb->sfunc);
            break;
        case tipoIdFuncVoid:
            printf("(%d) %s->pSimb->tipoRetNovo=%d (%s)\n", n, var, tn->pSimb->tipoRetNovo, sTipoDado[tn->pSimb->tipoRetNovo]);
            printf("(%d) %s->pSimb->idFunc=%s\n", n, var, tn->pSimb->idFunc);
            printf("(%d) %s->pSimb->vfunc=%p\n", n, var, tn->pSimb->vfunc);
            break;
        }
    }
    else
        if (tn->tipoN==tipoOper) //tipoOper
        {
            if (tn->opr.oper!='l')
            {
                printf("----------------------------\n");
                printf("(%d) %s->opr.oper=%d", n, var, tn->opr.oper);
                printf(" (%s)\n", token(tn->opr.oper));
                printf("(%d) %s->opr.tipoBOper=%d (%s)\n", n, var, tn->opr.tipoBOper, nome);
                printf("(%d) %s->opr.nops=%d\n", n, var, tn->opr.nops);
            }
            if (tn->opr.nops>0)
                printNodo(tn->opr.ptn[0], n+1, "ptn[0]");
            if (tn->opr.nops>1)
                printNodo(tn->opr.ptn[1], n+1, "ptn[1]");
            if (tn->opr.nops>2)
                printNodo(tn->opr.ptn[2], n+1, "ptn[2]");
            if (tn->opr.nops>3)
                printNodo(tn->opr.ptn[3], n+1, "ptn[3]");

        }
        else //tipoTipo
            printf("(%d) %s->opr.tt=%s\n", n, var, sTipoDado[tn->tt]);
}

int variavelT(int t)
{
    switch (t)
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
    if (p->tipoN==tipoOper || p->tipoN==tipoTipo)
        return 0;
    variavelT(p->pSimb->tipoD);
}

int ponteiro(nodo *p)
{
    if (p->tipoN==tipoOper || p->tipoN==tipoTipo)
        return 0;

    switch (p->pSimb->tipoD)
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
    switch (t)
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
//         case tipoIdFuncChar:
    case tipoIdFuncPVoid:
    case tipoIdUndef:
    default:
        return tipoUndef; //------------ tipoUndef
    }
}

int pegaTipoBase(nodo *p)
{

    if (!p)
        return tipoUndef;

    if (p->tipoN==tipoOper)
        return (p->opr.tipoBOper);
    else
        if(p->tipoN==tipoSimb)
            if (!p->pSimb)
                return tipoUndef;
            else
                return (pegaTipoBaseT(p->pSimb->tipoD));
        else /* tipoTipo */
            return (p->tt);
}

char *nomeTipo(nodo *p)
{
    if (!p)
        return(strdup("(null)"));
    if (p->tipoN==tipoSimb)
    {
        //if(debug) printf("debug nodoTipo tipoD=%d\n",p->pSimb->tipoD);
        return(strdup(sTipoDado[p->pSimb->tipoD]));
        //if(debug) printf("debug nodoTipo tipoD=%d depois\n",p->pSimb->tipoD);
    }
    else
        if (p->tipoN==tipoOper) /* tipoOper */
        {
            //if(debug) printf("debug nodoTipo tipoBOper=%d\n",p->opr.tipoBOper);
            return(strdup(sTipoBase[p->opr.tipoBOper]));
            //if(debug) printf("debug nodoTipo tipoBOper=%d depois\n",p->opr.tipoBOper);
        }
        else /* tipoTipo */
            return(strdup(sTipoBase[p->tt]));

}

char *tb2c(int tb)
{
    switch(tb)
    {
        case tipoInt:
            return(strdup("int"));
        case tipoDouble:
            return(strdup("double"));
        case tipoStr:
            return(strdup("char *"));
        case tipoVoid:
            return(strdup("void"));
        case tipoPointInt:
            return(strdup("int *"));
        case tipoPointDouble:
            return(strdup("double *"));
        case tipoPointStr:
            return(strdup("char **"));
        case tipoUndef:
        default:
            return(strdup("void *"));
    }
}

//char *sTipoDado[18]={"tipoIdUndef", "tipoConInt", "tipoConDouble", "tipoConStr",
//"tipoIdInt", "tipoIdDouble", "tipoIdStr", "tipoIdPointInt", "tipoIdPointDouble", "tipoIdPointStr",
//"tipoIdFuncInt", "tipoIdFuncDouble", "tipoIdFuncStr", "tipoIdFuncVoid", "tipoIdFuncPVoid", "tipoIdFuncPointInt", "tipoIdFuncPointDouble", "tipoIdFuncPointStr"};
//int tok2td(int tk) {;}

//char *sTipoBase[8]={"tipoUndef", "tipoInt", "tipoDouble", "tipoStr", "tipoVoid", "tipoPointInt", "tipoPointDouble", "tipoPointStr"};
int tok2tb(int tk)
{
    switch (tk)
    {
    case INT:
        return 1;
    case REAL:
        return 2;
    case TEXTO:
        return 3;
    case NADA:
        return 4;
    case PONTI:
        return 5;
    case PONTR:
        return 6;
    case PONTS:
        return 7;
    default:
        return 0;
    }
}


char *token(int tk)
{
    char tmp[2];
    if (tk>32 && tk<127)
    {
        sprintf(tmp, "%c", tk);
        return strdup(tmp);
    }
    switch (tk)
    {
    case PRINCIPAL:
        return(strdup("PRINCIPAL"));
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
    case NADA:
        return(strdup("NADA"));
    case FUNCAO:
        return(strdup("FUNCAO"));
    case EXTERNA:
        return(strdup("EXTERNA"));
    case FUNC:
        return(strdup("FUNC"));
    case DEFINE:
        return(strdup("DEFINE"));
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
    case RETORNE:
        return(strdup("RETORNE"));
        /*        case IMPORTE:
                    return(strdup("IMPORTE")); */
    default:
        return(strdup("default"));
        /* INC DEC DECPOS DECPRE PATTRIB PONTI PONTR PONTS */
    }
}

void erroSemantico(char *s, int linha)
{
    fprintf(stderr,"//    Linha:%d. Erro semantico: %s\n", linha, s);
    fflush(yyout);
    fclose(yyout);
    exit(1);
}
