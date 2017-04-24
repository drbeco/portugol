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
#include <math.h>
#include "portugol.h"
#include "y.tab.h"
//#include "portugol.tab.h"

#define debug 1

char *sTipoDado[18]={"tipoIdUndef", "tipoConInt", "tipoConDouble", "tipoConStr", "tipoIdInt", "tipoIdDouble", "tipoIdStr",
"tipoIdPointInt", "tipoIdPointDouble", "tipoIdPointStr",
"tipoIdFuncInt", "tipoIdFuncDouble", "tipoIdFuncStr", /*"tipoIdFuncChar", */ "tipoIdFuncVoid",
"tipoIdFuncPointVoid", "tipoIdFuncPointInt", "tipoIdFuncPointDouble", "tipoIdFuncPointStr"};
char *sTipoBase[8]={"tipoUndef", "tipoInt", "tipoDouble", "tipoStr", "tipoVoid", "tipoPointInt", "tipoPointDouble", "tipoPointStr"};
extern int debugArvore;
extern int debugTabela;
extern char cabecalhoMain[MAX_CABECA];
extern tipoBase tipoRet;
escopo esco={1, NULL, NULL}; /* escopo 1: global */

//insere informacoes sobre escopo e indentacao
void pass2(nodo *tn, escopo *pes, int n)
{
    char msg[128];
    tabelaSimb *ps;
    int paramTipo[MAX_PARAM]; /* 3 */
    int npar;

    if (tn==NULL)
        return;

//    if(tabSimb[21].pes)
//        printf("tabSimb[21].pes->e=%d\n", tabSimb[21].pes->e);
//    if(tabSimb[1].pes)
//        printf("tabSimb[1].pes->e=%d\n", tabSimb[1].pes->e);
   // fprintf(stderr, "pass2(tn:%p, pes:%d, n:%d), tn->tipoN:%d\n", tn, pes->e, n, tn->tipoN);
    //printTS();
    //printNodo(tn,n,"tn");
    //printEsc(pes, n);
    switch (tn->tipoN)
    {
    case tipoSimb:
        if(debug==2) fprintf(stderr, "switch tn->pSimb->tipoD= %s ---------------\n", sTipoDado[tn->pSimb->tipoD]);
        switch (tn->pSimb->tipoD)
        {
        case tipoConInt:
        case tipoConDouble:
        case tipoConStr:
            tn->pSimb->pes=achaEsc(&esco, 2); /* retorna o ponteiro para o nodo do escopo 2 PRINCIPAL */
            break;
        case tipoIdUndef:
            if(debug==1) fprintf(stderr, "...tipoIdUndef... tn->pSimb->idNome=%s\n", tn->pSimb->idNome);
            tn->pSimb=achaIdEsc(tn->pSimb->idNome, pes);
            break;
        case tipoIdInt:
        case tipoIdDouble:
        case tipoIdStr:
        case tipoIdPointInt:
        case tipoIdPointDouble:
        case tipoIdPointStr:
            if(debug==2) fprintf(stderr, "...tipoId... tn->pSimb->idNome=%s\n", tn->pSimb->idNome); /* nao deve acontecer nunca! */
//             tn->pSimb=achaIdEsc(tn->pSimb->idNome, pes);
//             break;
        case tipoIdFuncInt:
        case tipoIdFuncDouble:
        case tipoIdFuncStr:
        case tipoIdFuncVoid:
            if(debug==1) fprintf(stderr, "...tipoIdFunc... tn->pSimb->idNome=%s\n", tn->pSimb->idNome);
            /* Tudo seria tipoIdUndef, mas eh necessario por causa das funcoes predefinidas adicionadas com addfunc() */
            tn->pSimb=achaIdEsc(tn->pSimb->idNome, pes);
            break;
        default:
            sprintf(msg,"Operando de tipo desconhecido <%s>.", tn->pSimb->idNome);
            erroSemantico(msg, tn->linha);
            break;
        }
        break;
    case tipoOper:
        if(debug==2) fprintf(stderr, "switch tn->opr.oper= %s ---------------\n", token(tn->opr.oper));
        switch (tn->opr.oper)
        {
        case INICIO: //INICIO; comandos FIM;
            if(debug==2) printf("pass2 -----------------------------\n");
            pass2(tn->opr.ptn[0], pes, n+1);
            pass2(tn->opr.ptn[1], pes, n+1);
            if (n==0)
            {
                printTS();
                printNodo(tn, 0, "tn");
                printEsc(pes, n);
                if(debug==2) printf("pass2 -----------------------------\n");
            }
            break;
        case SE:
            pass2(tn->opr.ptn[0], pes, n+1); //expr
            if(debug==2) printf("insertSon: entao\n");
            pass2(tn->opr.ptn[1], insereEsc(pes, geraES()), n+1); //comandos do entao
            if (tn->opr.nops>2) //tem senao, pula para fim_se
            {
                if(debug==2) printf("insertSon: senao\n");
                pass2(tn->opr.ptn[2], insereEsc(pes, geraES()), n+1); //comandos do senao
            }
            break;
        case ENQUANTO:
            pass2(tn->opr.ptn[0], pes, n+1); //expr condicional
            if(debug==2) printf("insertSon: enquanto\n");
            pass2(tn->opr.ptn[1], insereEsc(pes, geraES()), n+1); //comandos do laco
            break;
        case PARA:
            pass2(tn->opr.ptn[0], pes, n+1); //inicializacao
            pass2(tn->opr.ptn[1], pes, n+1); //condicao
            if(debug==2) printf("insertSon: para\n");
            pass2(tn->opr.ptn[3], insereEsc(pes, geraES()), n+1); //comandos do laco
            pass2(tn->opr.ptn[2], pes, n+1); //incremento
            break;
        case FUNC: /* Aqui a chamada da funcao. Para definicao do prototipo, veja tipos */
            pass2(tn->opr.ptn[0], pes, n+1); //IDENT -> numero idx
            switch (tn->opr.ptn[0]->pSimb->numPar) //ou tn->opr.nops
            {
            case 3:
                pass2(tn->opr.ptn[3], pes, n+1); //arg 3
            case 2:
                pass2(tn->opr.ptn[2], pes, n+1); //arg 2
            case 1:
                pass2(tn->opr.ptn[1], pes, n+1); //arg 1
            }
            break;
        case PRINCIPAL: /* declaraco de main */
            if(debug==2) printf("debug - DECLARACAO - Funcao PRINCIPAL\n");
            if(pes->e!=1) //declaracao de funcao: so no escopo UM (global) eh aceitavel!
            {
                sprintf(msg,"Funcao <principal> so pode ser declarada no escopo global.");
                erroSemantico(msg, tn->linha);
            }
            sprintf(cabecalhoMain, "%s  /* funcoes pre-definidas */\n", cabecalhoMain);
            switch (tn->opr.nops) //quantos parametros: nops==2 para dois param, ou nops=3 para um param.
            {
            case 3: //             INT ptn[0]=PRINCIPAL ( ptn[1]=tipo )  INICIO; ptn[2]=lista_comandos FIM;
                if(debug==2) fprintf(stderr,"insertSon: declaracao de funcao principal, case 3\n");
                tn->opr.ptn[0]->pSimb=addIdEsc("principal", pes);
                paramTipo[0]=tn->opr.ptn[1]->tt; /* tipo do parametro */
                if(paramTipo[0]==tipoVoid)
                    npar=0;
                else
                    if(paramTipo[0]==tipoInt)
                        npar=1;
                    else
                    {
                        sprintf(msg,"Operando de tipo desconhecido: inteiro principal(<tipo>).");
                        erroSemantico(msg, tn->linha);
                    }
                //fprintf(stderr, "addFunc 1\n");
                ps = addFunc("principal", (void *)NULL, "main", npar, tipoIdFuncInt, paramTipo);
                sprintf(cabecalhoMain, "%s  loadfunc(tipoInt, (void *)main, \"principal\", &tf[%d], %d);\n", cabecalhoMain, ps->idx, npar);
                //fprintf(stderr, "case 3: tipo=%d %s\n%s\n", paramTipo[0], sTipoBase[pegaTipoBaseT(paramTipo[0])], cabecalhoMain); //ps->tipoD
                carregaFuncoesPre();
                pass2(tn->opr.ptn[2], insereEsc(pes, 2), n+1); /* processa lista_comandos da funcao principal (escopo 2)*/
                break;
            case 4: //             INT ptn[0]=PRINCIPAL (ptn[1]=INT, ptn[2]=PONTS)  INICIO; ptn[3]=lista_comandos FIM;
                if(debug==2) fprintf(stderr,"insertSon: declaracao de funcao principal, case 2\n");
                //tn->opr.ptn[0]->pSimb=achaFuncEsc(tn->opr.ptn[0]->pSimb->idNome, pes, tipoIdFuncInt);
                tn->opr.ptn[0]->pSimb=addIdEsc(tn->opr.ptn[0]->pSimb->idNome, pes);
                paramTipo[0]=tipoInt;
                paramTipo[1]=tipoPointStr;
                if(tn->opr.ptn[1]->tt!=paramTipo[0] || tn->opr.ptn[2]->tt!=paramTipo[1])
                {
                    sprintf(msg,"Operando de tipo desconhecido: inteiro principal(<tipo, tipo>).");
                    erroSemantico(msg, tn->linha);
                }
                //fprintf(stderr, "addFunc 2\n");
                ps = addFunc("principal", (void *)NULL, "main", 2, tipoIdFuncInt, paramTipo);
                sprintf(cabecalhoMain, "%s  loadfunc(tipoInt, (void *)main, \"principal\", &tf[%d], 2);\n", cabecalhoMain, ps->idx);
                //fprintf(stderr, "case 2:\n%s\n", cabecalhoMain);
                carregaFuncoesPre();
                pass2(tn->opr.ptn[3], insereEsc(pes, 2), n+1);      /* processa lista_comandos */
                break;
            }
            break;
        case INT:       /* declaracoes de funcoes e variaveis */
        case REAL:
        case TEXTO:
        case PONTI:
        case PONTR:
        case PONTS:
        case NADA:
            if(debug==2) printf("//declaracao: nops: %d\n", tn->opr.nops);
            //if(debug) printf("//debug - DECLARACAO - Funcoes\n");
            switch (tn->opr.nops) //quantos parametros: 1, 3, 4 ou 5
            {
            case 1: /* tipo IDENT ; variavel */
                /* declaracao: procurar no escopo atual. Se existir, erro de redeclaracao. Se nao existir declarar */
                //if(debug==2) printf("//debug - DECLARACAO - Variavel\n");
                //tabelaSimb *achaIdEsc(char *nome, escopo *e); /* Procura idNome==nome && escopo<=es->e, retorna o ponteiro para a tabelaSimb */
                //tabelaSimb *addIdEsc(char *nome, escopo *e, tipoDado td); /* Cria/Atualiza ID com escopo e, e tipoDado td, retorna o ponteiro para a tabelaSimb */
                //tn->opr.ptn[0]->pSimb=addIdEsc(tn->opr.ptn[0]->pSimb->idNome, pes, tb2Id(tok2tb(tn->opr.oper)));
                tn->opr.ptn[0]->pSimb=addIdEsc(tn->opr.ptn[0]->pSimb->idNome, pes);
                //pass2(tn->opr.ptn[0], pes, n+1);
                //if(debug) printf("//debug - DECLARACAO - Variavel - declarou!\n");
                if(debug==2) fprintf(stderr, "//debug - DECLARACAO - Variavel - declarou %s escopo %d\n", tn->opr.ptn[0]->pSimb->idNome, tn->opr.ptn[0]->pSimb->pes->e);
                break;
            case 3: //FUNCAO             tipoInt IDENT ( tipo )             INICIO; lista_comandos FIM;
            case 4: //FUNCAO             tipoInt IDENT ( tipo, tipo )       INICIO; lista_comandos FIM;
            case 5: //FUNCAO             tipoInt IDENT ( tipo, tipo, tipo ) INICIO; lista_comandos FIM;
                if(pes->e!=1) //declaracao de funcao: so no escopo UM (global) eh aceitavel!
                {
                    sprintf(msg,"Funcao <%s> so pode ser declarada no escopo global.", tn->opr.ptn[0]->pSimb->idNome);
                    erroSemantico(msg, tn->linha);
                }
                if(debug==2) printf("debug - DECLARACAO - Funcao\n");
                //tn->opr.ptn[0]->pSimb=achaFuncEsc(tn->opr.ptn[0]->pSimb->idNome, pes, tb2Func(tok2tb(tn->opr.oper)));
                tn->opr.ptn[0]->pSimb=addIdEsc(tn->opr.ptn[0]->pSimb->idNome, pes);
                switch (tn->opr.nops) //quantos parametros: 1, 2, 3, 4 ou 5
                {
                case 3: //             tipo IDENT ( tipo )             INICIO; lista_comandos FIM;
                    if(debug==2) printf("insertSon: declaracao de funcao case 3\n");
                    pass2(tn->opr.ptn[2], insereEsc(pes, geraES()), n+1); /* processa lista_comandos */
                    break;
                case 4: //             tipoInt IDENT ( tipo, tipo )       INICIO; lista_comandos FIM;
                    if(debug==2) printf("insertSon: declaracao de funcao case 4\n");
                    pass2(tn->opr.ptn[3], insereEsc(pes, geraES()), n+1); /* processa lista_comandos */
                    break;
                case 5: //             tipoInt IDENT ( tipo, tipo, tipo ) INICIO; lista_comandos FIM;
                    if(debug==2) printf("insertSon: declaracao de funcao case 5\n");
                    pass2(tn->opr.ptn[4], insereEsc(pes, geraES()), n+1); /* processa lista_comandos */
                    break;
                }
                break;
            }
            break;
        case 'l': /* blocos de funcoes, ou lista de comandos */
            pass2(tn->opr.ptn[0], pes, n+1);
            pass2(tn->opr.ptn[1], pes, n+1);
            break;
        case '=':
        case PATTRIB:
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case LT:
        case GT:
        case GE:
        case LE:
        case NE:
        case EQ:
        case E:
        case OU:
            if(debug==2) printf("=, +, -, *, /, %%, LT, GT, GE, LE, NE, EQ, E, OU\n");
            pass2(tn->opr.ptn[0], pes, n+1);
            pass2(tn->opr.ptn[1], pes, n+1);
            break;
        case UMENOS:
        case UPONT:  //i=*q=j;
        case UEND:   //&i; &f;
        case INCPOS: //IDENT INC
        case INCPRE: //INC IDENT
        case DECPOS: //    | IDENT DEC                 { $$ = opr(DECPOS, 1, conv($1)); }
        case DECPRE: /* bug: nao implementado */
        case '(':
        case NAO:
            //printf("UMENOS, UPONT, UEND, INCPOS, INCPRE, DECPOS\n");
            pass2(tn->opr.ptn[0], pes, n+1);
            break;
        case RETORNE:
            //printf("RETORNE\n");
            if(tn->opr.nops!=0)
                pass2(tn->opr.ptn[0], pes, n+1);
            break;
        case ABORTE:
        case ';':
            //printf("ABORTE ';'\n");
            break;
        default:
            sprintf(msg,"Operador desconhecido <%s>", token(tn->opr.oper));
            erroSemantico(msg, tn->linha);
        }
        break;
    case tipoTipo:
        if(debug==2) fprintf(stderr, "switch tn->tt= %s ---------------\n", sTipoBase[tn->tt]);
    default:
            sprintf(msg,"Impossibel gerar quadruplas de tipoNodo tipoN==tipoTipo ou erro desconhecido (switch-default)");
            erroSemantico(msg, tn->linha);
    }
    //fprintf(stderr,"fim do pass2()\n");
    //;
    //if(debug==1) fprintf(stderr,"fim do pass2()\n");
    return;
} //pass2()


char *pass3(nodo *tn, int n)
{
    char *q1=NULL, *q2=NULL, *q3=NULL, *qres=NULL, qtemp[20]="", qtemp2[20];
    char msg[128];
    int itemp, t1, t2, t3, npar;
    int paramTipo[MAX_PARAM]; /* 3 */
    tabelaSimb *ps;

    if (tn==NULL)
        return strdup(qtemp);

    //fprintf(stderr, "pass3(tn:%p, n:%d), tn->tipoN:%d\n", tn, n, tn->tipoN);
    //printTS();
    //printNodo(tn,n,"tn");
    switch (tn->tipoN)
    {
    case tipoSimb:
        switch (tn->pSimb->tipoD)
        {
        case tipoConInt:
            //if(debug) printf("debug tipoConInt\n");
            sprintf(qtemp,"tc[%d]",tn->pSimb->idx); //tc = tabela de constantes
//            if (!tn->pSimb->uso)
//                sprintf(cabecalhoMain, "%s    loadi(%d,NULL,&%s);\n", cabecalhoMain, tn->pSimb->ival, qtemp); //mover para pass2
//                fprintf(yyout, "  loadi(%d,%s,&%s);\n", tn->pSimb->ival, "NULL", qtemp);
//            tn->pSimb->uso=1;
            break;
        case tipoConDouble:
            //if(debug) printf("debug tipoConDouble\n");
            sprintf(qtemp,"tc[%d]",tn->pSimb->idx);
//            if (!tn->pSimb->uso)
//                fprintf(yyout, "  loadd(%.2f,%s,&%s);\n", tn->pSimb->dval, "NULL", qtemp);
//            tn->pSimb->uso=1;
            break;
        case tipoConStr:
            //if(debug) printf("debug tipoConStr\n");
            sprintf(qtemp,"tc[%d]",tn->pSimb->idx);
//            if (!tn->pSimb->uso)
//                fprintf(yyout, "  loads(%s,%s,&%s);\n", tn->pSimb->sval, "NULL", qtemp);
//            tn->pSimb->uso=1;
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
        case tipoIdFuncPointVoid:
            //if(debug) printf("debug tipoIdFunc...\n");
            sprintf(qtemp,"tf[%d]",tn->pSimb->idx);
            break;
        case tipoIdUndef:
        default:
            //if (debug) printf("debug tipoIdUndef default...\n");
            sprintf(qtemp,"ts[?]");
            //if(debug) printf("debug tipoIdUndef default, qtemp: %s\n", qtemp);
            sprintf(msg,"Operando <%s> usado antes de ser declarado.", tn->pSimb->idNome);
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
            pass3(tn->opr.ptn[0], n+1);
            ps=achaIdEsc("principal", &esco); //funcao, escopo
            if(ps->numPar==0)
                fprintf(yyout,"int main(void) /* principal */\n{\n");
            else
                if(ps->numPar==1)
                    fprintf(yyout,"int main(int argc) /* principal */\n{\n");
                else
                    fprintf(yyout,"int main(int argc, char **argv) /* principal */\n{\n");

            carregaConstantes();
            fprintf(yyout,"%s", cabecalhoMain);
            //fprintf(yyout,"  loadfunc(tipoInt,   (void *)%s, \"%s\", &tf[%d], %d); /* definicao de funcao */\n", /*so feito dentro do main*/ ps->idFunc, ps->idNome, ps->idx, ps->numPar);
            tipoRet=tipoInt;
            pass3(tn->opr.ptn[1], n+1);
            //printf("debug - INICIO - pass3(ptn[1]) ok! \n");
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
            q1=pass3(tn->opr.ptn[0], n+1); //expr
            q2=geraLB(&itemp);//inicio_senao ou fim_se
            if (tn->opr.nops>2) //tem senao
                q3=geraLB(&itemp);//fim_se
            fprintf(yyout, "  jump_f(");//caso falso pula para senao ou para fim_se
            fprintf(yyout, "%s,", q1);
            fprintf(yyout, "%s,", "NULL");
            fprintf(yyout, "%s);\t/* if(F) goto %s */\n", q2, q2); //pula para senao ou para fim_se
            pass3(tn->opr.ptn[1], n+1); //comandos do entao
            if (tn->opr.nops>2) //tem senao, pula para fim_se
            {
                fprintf(yyout, "  jump(");//pulo incondicional para fim_se
                fprintf(yyout, "%s,", "NULL");
                fprintf(yyout, "%s,", "NULL");
                fprintf(yyout, "%s);\n", q3);
                fprintf(yyout, "%s:\t/* else */\n", q2);//inicio_senao:
                pass3(tn->opr.ptn[2], n+1); //comandos senao
                fprintf(yyout, "%s:\t/* endif */\n", q3);//fim_se:
            }
            else //nao tem senao
                fprintf(yyout, "%s:\t/* endif */\n", q2);//fim_se:
            break;
        case ENQUANTO:
            q1=geraLB(&itemp); // inicio_enquanto
            q2=geraLB(&itemp); // fim_enquanto
            fprintf(yyout, "%s:\t/* while */\n", q1); // inicio_enquanto:
            q3=pass3(tn->opr.ptn[0], n+1); // expr condicional
            fprintf(yyout, "  jump_f(%s,%s,%s);\n",q3,"NULL",q2); // caso falso pula para fim_enquanto
            pass3(tn->opr.ptn[1], n+1); // comandos do laco
            fprintf(yyout, "  jump(%s,%s,%s);\n","NULL","NULL",q1); // pula para inicio_enquanto
            fprintf(yyout, "%s:\t/* end_while */\n", q2); // fim_enquanto:
            break;
        case PARA:
            q1=geraLB(&itemp); //loop_para:
            q2=geraLB(&itemp); //fim_para:
            pass3(tn->opr.ptn[0], n+1); //stmt1=inicializacao
            fprintf(yyout, "%s:\t/* for */\n", q1);//loop_para:
            q3=pass3(tn->opr.ptn[1], n+1); //stmt2=condicao
            fprintf(yyout, "  jump_f(%s,NULL,%s);\n", q3, q2);//se falso pula para fim_para
            pass3(tn->opr.ptn[3], n+1); //stmt4=comandos do loop
            pass3(tn->opr.ptn[2], n+1); //stmt3=incremento
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
            q1=pass3(tn->opr.ptn[0], n+1); //IDENT ts[?]
            //if(debug) printf("debug FUNC q1 ok.\n");
            qres=geraTP(&itemp);//retorno da funcao em um temporario
            if (tn->opr.ptn[0]->pSimb->numPar != tn->opr.nops-1)
            {
                sprintf(msg,"Numero de parametros declarados (%d) nao coincide com usados (%d) na chamada da funcao <%s>.", tn->opr.ptn[0]->pSimb->numPar, tn->opr.nops-1, tn->opr.ptn[0]->pSimb->idNome);
                erroSemantico(msg, tn->linha);
            }
            switch (tn->opr.ptn[0]->pSimb->numPar) //ou tn->opr.nops
            {
            case 2: /* func(tipo,tipo) */
                if (!strcmp(tn->opr.ptn[0]->pSimb->idNome,"imprima")) //se imprima
                    if (!tn->opr.ptn[1]->pSimb->formatadoSval)
                    {
                        sprintf(msg,"Formato incorreto para a funcao imprima(\"formato\", expr).");
                        erroSemantico(msg, tn->linha);
                    }
                q3=pass3(tn->opr.ptn[2], n+1); //arg2 == $5
                t3=pegaTipoBase(tn->opr.ptn[2]); //tipo do arg2: tipoInt, tipoDouble, tipoStr, tipoUndef
                fprintf(yyout,"  param(%s, NULL, NULL); /* arg2 */\n", q3);
                if (t3 == tipoUndef)
                {
                    sprintf(msg,"Argumento 2 nao declarado na chamada da funcao <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                    erroSemantico(msg, tn->linha);
                }
                /*                            if(t3 == tipoStr)
                                            {
                                                sprintf(msg,"Funcao <%s> com argumento tipoStr nao implementada.", tn->opr.ptn[0]->pSimb->idNome);
                                                erroSemantico(msg, tn->linha);
                                            }*/
            case 1: /* func(tipo) */
                q2=pass3(tn->opr.ptn[1], n+1); //arg1 == $3
                t2=pegaTipoBase(tn->opr.ptn[1]); //tipo do arg1: tipoInt, tipoDouble, tipoStr, tipoUndef
                fprintf(yyout,"  param(%s, NULL, NULL); /* arg1 */\n", q2);
                if (t2 == tipoUndef)
                {
                    sprintf(msg,"Argumento 1 nao declarado na chamada da funcao <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                    erroSemantico(msg, tn->linha);
                }
                /*                            if(t2 == tipoStr)
                                            {
                                                sprintf(msg,"Funcao <%s> com argumento tipoStr nao implementada.", tn->opr.ptn[0]->pSimb->idNome);
                                                erroSemantico(msg, tn->linha);
                                            }*/
            case 0: /* func() */
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
        case PRINCIPAL:
            if(debug==2) printf("debug - DECLARACAO - Funcao PRINCIPAL - pass3\n");
            tipoRet=tipoInt;
            switch (tn->opr.nops) //quantos parametros: 2 ou 3
            {
            case 3: //             INT ptn[0]=PRINCIPAL ( ptn[1]=tipo )  INICIO; ptn[2]=lista_comandos FIM;
                if(debug==2) fprintf(stderr,"declaracao de funcao principal, case 3 (tipo)\n");
//adicionado em pass2                ps = addFunc("principal", (void *)NULL, "main", npar, tipoIdFuncInt, paramTipo);
//                sprintf(cabecalhoMain, "%s  loadfunc(%s, (void *)%s, \"%s\", &tf[%d], %d); /* definicao de funcao */\n", cabecalhoMain, sTipoBase[pegaTipoBaseT(ps->tipoD)], ps->idFunc, ps->idNome, ps->idx, ps->numPar);
                pass3(tn->opr.ptn[2], n+1); /* processa lista_comandos da funcao principal */
                break;
            case 4: //             INT ptn[0]=PRINCIPAL (ptn[1]=INT, ptn[2]=PONTS)  INICIO; ptn[3]=lista_comandos FIM;
                if(debug==2) fprintf(stderr,"declaracao de funcao principal, case 2 (INT, PONTS)\n");
//adicionado em pass2                ps = addFunc("principal", (void *)NULL, "main", 2, tipoIdFuncInt, paramTipo);
//                sprintf(cabecalhoMain, "%s  loadfunc(%s, (void *)%s, \"%s\", &tf[%d], %d); /* definicao de funcao */\n", cabecalhoMain, sTipoBase[pegaTipoBaseT(ps->tipoD)], ps->idFunc, ps->idNome, ps->idx, ps->numPar);
                pass3(tn->opr.ptn[3], n+1);      /* processa lista_comandos */
                break;
            }
            fprintf(yyout, "  nop(NULL,NULL,NULL);\t/* no operation */\n} /* close main */\n\n"); /* fecha chave do main */
            break;
        case NADA:
            if(debug) printf("debug - NADA\n");
            if (tn->opr.ptn[0]->pSimb->tipoD!=tipoIdUndef)
            {
                sprintf(msg,"Redeclaracao do identificador <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                erroSemantico(msg, tn->linha);
            }
            switch (tn->opr.nops) //quantos parametros: 1, 3, 4 ou 5
            {
            case 1: /* NADA IDENT */
                sprintf(msg,"Nao posso declarar variavel <%s> do tipo <tipoVoid>.", tn->opr.ptn[0]->pSimb->idNome);
                erroSemantico(msg, tn->linha);
                break;
            case 3: /* NADA funcID (tipo) */
//             tipo IDENT '(' tipo ')' INICIO ';' lista_comandos FIM ';'
//                                      $$ = opr($1, 3, conv($2), convtn($4), $8);
                paramTipo[0]=tn->opr.ptn[1]->tt; /* tipo do parametro */
                if(paramTipo[0]==tipoVoid)
                    npar=0;
                else
                    npar=1;
                ps = addFunc(tn->opr.ptn[0]->pSimb->idNome, (void *)NULL, tn->opr.ptn[0]->pSimb->idNome, npar, tipoIdFuncDouble , paramTipo);
                sprintf(cabecalhoMain, "%s  loadfunc(%s, (void *)%s, \"%s\", &tf[%d], %d);\n", cabecalhoMain, sTipoBase[pegaTipoBaseT(ps->tipoD)], ps->idFunc, ps->idNome, ps->idx, ps->numPar);
                fprintf(yyout, "void %s(%s)\n{\n", tn->opr.ptn[0]->pSimb->idNome, tb2c(paramTipo[0]));
                //if (debug)  printf("//    Linha:%d. \n", tn->linha);
                tipoRet=tipoDouble;
                pass3(tn->opr.ptn[2], n+1); /* processa lista_comandos */
                fprintf(yyout, "  nop(NULL,NULL,NULL);\t/* no operation */\n} /* close function */\n\n"); /* fecha chave do main */
                break;
            case 4: /* bug implementar */
//             | tipo IDENT '(' tipo ',' tipo ')' INICIO ';' lista_comandos FIM ';'
//                                      $$ = opr($1, 4, conv($2), convtn($4), convtn($6), $10);
                pass3(tn->opr.ptn[3], n); /* processa lista_comandos */
                break;
            case 5:
//             | tipo IDENT '(' tipo ',' tipo ',' tipo ')' INICIO ';' lista_comandos FIM ';'
//                                      $$ = opr($1, 5, conv($2), convtn($4), convtn($6), convtn($8), $12);
                pass3(tn->opr.ptn[4], n); /* processa lista_comandos */
                break;
            default:
                sprintf(msg,"Numero de parametros declarados (%d) na funcao <%s> excede o limite permitido.", tn->opr.ptn[0]->pSimb->numPar, tn->opr.ptn[0]->pSimb->idNome);
                erroSemantico(msg, tn->linha); /* exit(1) */
            }
            break;
        case INT:
            if(debug) printf("debug - INT\n");
            if(tn->opr.ptn[0]->tipoN!=tipoTipo) /* bug? tipoN==tipoPsimb senao ERRO */
                if (tn->opr.ptn[0]->pSimb->tipoD!=tipoIdUndef)
                {
                    sprintf(msg,"Redeclaracao da variavel <%s>.", tn->opr.ptn[0]->pSimb->idNome);
                    erroSemantico(msg, tn->linha);
                }
            switch (tn->opr.nops) //quantos parametros: 1, 3, 4 ou 5
            {
            case 1: /* INT IDENT ; */
                tn->opr.ptn[0]->pSimb->tipoD=tipoIdInt;
                tn->opr.ptn[0]->pSimb->idx=geraTS();
                fprintf(yyout,"  loadi(0, NULL, &ts[%d]); /* int %s; */\n", tn->opr.ptn[0]->pSimb->idx, tn->opr.ptn[0]->pSimb->idNome);
//                sprintf(cabecalhoMain, "%s    loadi(%d,NULL,&%s);\n", cabecalhoMain, tn->pSimb->ival, qtemp);
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
                fprintf(stderr, "addFunc 3\n");
                ps = addFunc(tn->opr.ptn[0]->pSimb->idNome, (void *)NULL, tn->opr.ptn[0]->pSimb->idNome, npar, tipoIdFuncInt, paramTipo);
                sprintf(cabecalhoMain, "%s  loadfunc(%s, (void *)%s, \"%s\", &tf[%d], %d);\n", cabecalhoMain, sTipoBase[pegaTipoBaseT(ps->tipoD)], ps->idFunc, ps->idNome, ps->idx, ps->numPar);
                fprintf(yyout, "int %s(%s)\n{\n", tn->opr.ptn[0]->pSimb->idNome, tb2c(paramTipo[0]));
                //if (debug)  printf("//    Linha:%d. \n", tn->linha);
                tipoRet=tipoInt;
                pass3(tn->opr.ptn[2], n+1); /* processa lista_comandos */
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
                if(paramTipo[0]==tipoVoid)
                    npar=0;
                else
                    npar=1;
                /* bug: idNome == idFunc sempre! */
                //addFunc("saia", (void *)exit, "exit" , 1 numParam, tipoIdFuncInt /*tipo de retorno e na TS*/, tipoParam[] /*tipo dos arg*/);
                fprintf(stderr, "addFunc 4\n");
                ps = addFunc(tn->opr.ptn[0]->pSimb->idNome, (void *)NULL, tn->opr.ptn[0]->pSimb->idNome, npar, tipoIdFuncDouble , paramTipo);
                sprintf(cabecalhoMain, "%s  loadfunc(%s, (void *)%s, \"%s\", &tf[%d], %d);\n", cabecalhoMain, sTipoBase[pegaTipoBaseT(ps->tipoD)], ps->idFunc, ps->idNome, ps->idx, ps->numPar); /*so feito dentro do main*/
                //fprintf(yyout,"  loadfunc(%s,   (void *)%s,\"%s\", &tf[%d], %d); /* definicao de funcao */\n", sTipoBase[pegaTipoBaseT(ps->tipoD)], ps->idFunc, ps->idNome, ps->idx, ps->numPar); /*so feito dentro do main*/
                fprintf(yyout, "double %s(%s)\n{\n", tn->opr.ptn[0]->pSimb->idNome, tb2c(paramTipo[0]));
                //if (debug)  printf("//    Linha:%d. \n", tn->linha);
                tipoRet=tipoDouble;
                pass3(tn->opr.ptn[2], n+1); /* processa lista_comandos */
                fprintf(yyout, "  nop(NULL,NULL,NULL);\t/* no operation */\n} /* close function */\n\n"); /* fecha chave do main */
                break;
            case 4: /* bug implementar */
//             | tipo IDENT '(' tipo ',' tipo ')' INICIO ';' lista_comandos FIM ';'
//                                      $$ = opr($1, 4, conv($2), convtn($4), convtn($6), $10);
                pass3(tn->opr.ptn[3], n); /* processa lista_comandos */
                break;
            case 5:
//             | tipo IDENT '(' tipo ',' tipo ',' tipo ')' INICIO ';' lista_comandos FIM ';'
//                                      $$ = opr($1, 5, conv($2), convtn($4), convtn($6), convtn($8), $12);
                pass3(tn->opr.ptn[4], n); /* processa lista_comandos */
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
        case 'l': /* INICIO; lista de comandos FIM; */
            pass3(tn->opr.ptn[0], n);
            pass3(tn->opr.ptn[1], n);
            break;
        case '=': //p=&l; ATTRIB
//            if (debug) printf("debug =\n");
//            printNodo(tn->opr.ptn[0], 0, "tn->opr.ptn[0]");
            qres=pass3(tn->opr.ptn[0], n+1);
//            if (debug) printf("debug =2\n");
            q1=pass3(tn->opr.ptn[1], n+1);
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
            qres=pass3(tn->opr.ptn[0], n+1);
            q1=pass3(tn->opr.ptn[1], n+1);
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
            q1=pass3(tn->opr.ptn[0], n+1);
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
            q1=pass3(tn->opr.ptn[0], n+1);
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
            q1=pass3(tn->opr.ptn[0], n+1);
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
            q1=pass3(tn->opr.ptn[0], n+1); // mov(q1, null, qres)
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
            qres=pass3(tn->opr.ptn[0], n+1); // add(qres, 1, q1)
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
            q1=pass3(tn->opr.ptn[0], n+1); // mov(q1, null, qres)
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
        case DECPRE: //    | DEC IDENT                 { $$ = opr(DECPRE, 1, conv($2)); }
            break; /*bug: implementar */
        case '+':
            q1=pass3(tn->opr.ptn[0], n+1);
            q2=pass3(tn->opr.ptn[1], n+1);
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
            q1=pass3(tn->opr.ptn[0], n+1);
            q2=pass3(tn->opr.ptn[1], n+1);
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
            q1=pass3(tn->opr.ptn[0], n+1);
            q2=pass3(tn->opr.ptn[1], n+1);
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
            q1=pass3(tn->opr.ptn[0], n+1);
            q2=pass3(tn->opr.ptn[1], n+1);
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
            q1=pass3(tn->opr.ptn[0], n+1);
            q2=pass3(tn->opr.ptn[1], n+1);
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
            qres=pass3(tn->opr.ptn[0], n+1);
            tn->opr.tipoBOper = pegaTipoBase(tn->opr.ptn[0]);
            if (tn->opr.tipoBOper  == tipoUndef)
            {
                sprintf(msg,"Operando nao declarado na operacao de parenteses. ( <%s> )", sTipoBase[tn->opr.tipoBOper]);
                erroSemantico(msg, tn->linha);
            }
            break;
        case LT: //compara texto com texto ou numero com numero. retorna tipoInt
            q1=pass3(tn->opr.ptn[0], n+1);
            q2=pass3(tn->opr.ptn[1], n+1);
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
            q1=pass3(tn->opr.ptn[0], n+1);
            q2=pass3(tn->opr.ptn[1], n+1);
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
            q1=pass3(tn->opr.ptn[0], n+1);
            q2=pass3(tn->opr.ptn[1], n+1);
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
            q1=pass3(tn->opr.ptn[0], n+1);
            q2=pass3(tn->opr.ptn[1], n+1);
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
            q1=pass3(tn->opr.ptn[0], n+1);
            q2=pass3(tn->opr.ptn[1], n+1);
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
            q1=pass3(tn->opr.ptn[0], n+1);
            q2=pass3(tn->opr.ptn[1], n+1);
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
            q1=pass3(tn->opr.ptn[0], n+1);
            q2=pass3(tn->opr.ptn[1], n+1);
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
            q1=pass3(tn->opr.ptn[0], n+1);
            q2=pass3(tn->opr.ptn[1], n+1);
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
            q1=pass3(tn->opr.ptn[0], n+1);
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
                q1=pass3(tn->opr.ptn[0], n+1);
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
} //pass3

int geraTF(void) //tabela de funcoes
{
    static int itf=-1; /* ja tem predefinido printf, scanf, exit, sqrt */
    itf++;
//    fprintf(stderr, "GeraTF()==%d\n", itf);
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

int geraES(void) //tabela de escopos
{
    static int ite=2; /* UM eh o pai de todos, DOIS eh a funcao principal */
    ite++;
    return ite;
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
    listesc *lp;

    printf("---------------------------- Tabela de Simbolos ----------------------------\n");
    for (n=0; n<MAX_SIMB; n++)
    {
        if (!tabSimb[n].idNome)
        {
            //printf("Fim da tabela de simbolos\n");
            return;
        }
        printf("----------------------------\n");
        printf("%p->tabSimb[%d]\n", &tabSimb[n], n);
        printf("tabSimb[%d].tipoD=%s\n", n, sTipoDado[tabSimb[n].tipoD]);
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
            printf("tabSimb[%d].tipoRetNovo=%s\n", n, sTipoDado[tabSimb[n].tipoRetNovo]);
            printf("tabSimb[%d].idFunc=%s\n", n, tabSimb[n].idFunc);
            printf("tabSimb[%d].ifunc=%p\n", n, tabSimb[n].ifunc);
            break;
            /*            case tipoIdFuncDouble:
                            printf("tabSimb[%d].tipoRetNovo=%d (%s)\n", n, tabSimb[n].tipoRetNovo, sTipoDado[tabSimb[n].tipoRetNovo]);
                            printf("tabSimb[%d].idFunc=%s\n", n, tabSimb[n].idFunc);
                            printf("tabSimb[%d].ffunc=%p\n", n, tabSimb[n].ffunc);
                            break;*/
        case tipoIdFuncDouble:
            printf("tabSimb[%d].tipoRetNovo=%s\n", n, sTipoDado[tabSimb[n].tipoRetNovo]);
            printf("tabSimb[%d].idFunc=%s\n", n, tabSimb[n].idFunc);
            printf("tabSimb[%d].dfunc=%p\n", n, tabSimb[n].dfunc);
            break;
            /*            case tipoIdFuncChar:
                            break;*/
        case tipoIdFuncStr:
            printf("tabSimb[%d].tipoRetNovo=%s\n", n, sTipoDado[tabSimb[n].tipoRetNovo]);
            printf("tabSimb[%d].idFunc=%s\n", n, tabSimb[n].idFunc);
            printf("tabSimb[%d].sfunc=%p\n", n, tabSimb[n].sfunc);
            break;
        case tipoIdFuncVoid:
            printf("tabSimb[%d].tipoRetNovo=%s\n", n, sTipoDado[tabSimb[n].tipoRetNovo]);
            printf("tabSimb[%d].idFunc=%s\n", n, tabSimb[n].idFunc);
            printf("tabSimb[%d].vfunc=%p\n", n, tabSimb[n].vfunc);
            break;
        default:
            printf("default switch\n");
        }
        if(tabSimb[n].pes!=NULL)
        {
            printf("tabSimb[%d].pes->e=%d\n", n, tabSimb[n].pes->e);
            if(tabSimb[n].pes->efather!=NULL)
                printf("tabSimb[%d].pes->efather->e=%d\n", n, tabSimb[n].pes->efather->e);
            else
                printf("tabSimb[%d].pes->efather->e=NULL\n", n);
            if(tabSimb[n].pes->lsons==NULL)
                printf("tabSimb[%d].pes->lsons==NULL\n", n);
            else
            {
                lp=tabSimb[n].pes->lsons;
                if(lp!=NULL)
                    printf("tabSimb[%d].pes->lsons->eson->e = ", n);
                else
                    printf("tabSimb[%d].pes->lsons=NULL", n);
                while(lp!=NULL)
                {
                    if(lp->eson!=NULL)
                        printf("%d, ", lp->eson->e);
                    lp=lp->lbrother;
                }
                printf("\n");
            }
        }
        else
            printf("tabSimb[%d].pes==NULL\n", n);

    }
//    printf("fim tabela\n");
}

void printEsc(escopo *es, int n)
{
    listesc *s;
    if(!es)
        return;
    if (n==0)
        printf("---------------------------- Arvore de Escopo ----------------------------\n");

    printf("----------------------------\n");
    //printf("(%d) es:%p=(e:%d, efather:%p, lsons:%p", n, es, es->e, es->efather, es->lsons);
    printf("(%d) e = %d\n", n, es->e);
    printf("(%d) father = %d\n", n, (es->efather)?es->efather->e:0);
    if(es->lsons)
        printf("(%d) sons = ", n);
    s=es->lsons;
    while(s)
    {
        printf("%d", s->eson->e);
        if(s->eson->lsons)
            printf(" (sons), ");
        else
            printf(", ");
        s=s->lbrother;
    }
    if(es->lsons)
        printf("\n");
    s=es->lsons;
    while(s)
    {
//        printf("(lbrother:%p, e:%d, efather:%p, lsons:%p)\n", s, s->eson->e, s->eson->efather, s->eson->lsons);
        printEsc(s->eson, n+1);
        s=s->lbrother;
    }
//    printf("printEsc fim?\n");
}

void printNodo(nodo *tn, int n, char *var)
{
    char *nome;
    int t;
    listesc *lp;

    if (!tn)
        return;

    nome=nomeTipo(tn);

    if (n==0)
        printf("---------------------------- Arvore Sintatica ----------------------------\n");
    if (tn->tipoN==tipoSimb)
    {
        printf("----------------------------\n");
        printf("(%d) %s->tipoN=tipoSimb\n", n, var);
        printf("(%d) %s->linha=%d\n", n, var, tn->linha);
        printf("(%d) %s->pSimb->tipoD=%s\n", n, var, nome);
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
            printf("(%d) %s->pSimb->tipoRetNovo=%s\n", n, var, sTipoDado[tn->pSimb->tipoRetNovo]);
            printf("(%d) %s->pSimb->idFunc=%s\n", n, var, tn->pSimb->idFunc);
            printf("(%d) %s->pSimb->ifunc=%p\n", n, var, tn->pSimb->ifunc);
            break;
            /*            case tipoIdFuncDouble:
                            printf("(%d) %s->pSimb->tipoRetNovo=%d (%s)\n", n, var, tn->pSimb->tipoRetNovo, sTipoDado[tn->pSimb->tipoRetNovo]);
                            printf("(%d) %s->pSimb->idFunc=%s\n", n, var, tn->pSimb->idFunc);
                            printf("(%d) %s->pSimb->ffunc=%p\n", n, var, tn->pSimb->dfunc);
                            break;*/
        case tipoIdFuncDouble:
            printf("(%d) %s->pSimb->tipoRetNovo=%s\n", n, var, sTipoDado[tn->pSimb->tipoRetNovo]);
            printf("(%d) %s->pSimb->idFunc=%s\n", n, var, tn->pSimb->idFunc);
            printf("(%d) %s->pSimb->dfunc=%p\n", n, var, tn->pSimb->dfunc);
            break;
            /*            case tipoIdFuncChar:
                            break;*/
        case tipoIdFuncStr:
            printf("(%d) %s->pSimb->tipoRetNovo=%s\n", n, var, sTipoDado[tn->pSimb->tipoRetNovo]);
            printf("(%d) %s->pSimb->idFunc=%s\n", n, var, tn->pSimb->idFunc);
            printf("(%d) %s->pSimb->sfunc=%p\n", n, var, tn->pSimb->sfunc);
            break;
        case tipoIdFuncVoid:
            printf("(%d) %s->pSimb->tipoRetNovo=%s\n", n, var, sTipoDado[tn->pSimb->tipoRetNovo]);
            printf("(%d) %s->pSimb->idFunc=%s\n", n, var, tn->pSimb->idFunc);
            printf("(%d) %s->pSimb->vfunc=%p\n", n, var, tn->pSimb->vfunc);
            break;
        default:
            printf("switch default!\n");
        }
        if(tn->pSimb->pes!=NULL)
        {
            printf("(%d) %s->pSimb->pes->e=%d\n", n, var, tn->pSimb->pes->e);
            if(tn->pSimb->pes->efather!=NULL)
                printf("(%d) %s->pSimb->pes->efather->e=%d\n", n, var, tn->pSimb->pes->efather->e);
            else
                printf("(%d) %s->pSimb->pes->efather->e=NULL\n", n, var);
            if(tn->pSimb->pes->lsons==NULL)
                printf("(%d) %s->pSimb->pes->lsons=NULL\n", n, var);
            else
            {
                lp=tn->pSimb->pes->lsons;
                if(lp!=NULL)
                    printf("(%d) %s->pSimb->pes->lsons->eson->e= ", n, var);
                else
                    printf("(%d) %s->pSimb->pes->lsons->eson->e=NULL ", n, var);
                while(lp!=NULL)
                {
                    if(lp->eson!=NULL)
                        printf("%d, ", lp->eson->e);
                    lp=lp->lbrother;
                }
                printf("\n");
            }
        }
        else
            printf("(%d) %s->pSimb->pes==NULL\n", n, var);
    }
    else
        if (tn->tipoN==tipoOper) //tipoOper
        {
//             if (tn->opr.oper!='l')
            {
                printf("----------------------------\n");
                printf("(%d) %s->tipoN=tipoOper\n", n, var);
                printf("(%d) %s->linha=%d\n", n, var, tn->linha);
                printf("(%d) %s->opr.oper='%s'\n", n, var, token(tn->opr.oper));
                printf("(%d) %s->opr.tipoBOper=%s\n", n, var, nome);
                printf("(%d) %s->opr.nops=%d\n", n, var, tn->opr.nops);
            }
            if (tn->opr.nops>0)
                printNodo(tn->opr.ptn[0], n+1, "ptn[0]");
            if (tn->opr.nops>1)
                printNodo(tn->opr.ptn[1], n+1, "ptn[1]");
            if (tn->opr.nops>2)
            {
                //printf("tentando nops>2\n");
                printNodo(tn->opr.ptn[2], n+1, "ptn[2]");
            }
            if (tn->opr.nops>3)
                printNodo(tn->opr.ptn[3], n+1, "ptn[3]");

        }
        else //tipoTipo
        {
            printf("----------------------------\n");
            printf("(%d) %s->tipoN=tipoTipo\n", n, var);
            printf("(%d) %s->linha=%d\n", n, var, tn->linha);
            printf("(%d) %s->tt=%s\n", n, var, sTipoBase[tn->tt]);
        }
//        printf("ret\n");
}

/* retorna verdadeiro se um tipo t eh uma variavel */
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

/* retorna verdadeiro se um nodo p se refere a uma variavel */
int variavel(nodo *p)
{
    if (p->tipoN==tipoOper || p->tipoN==tipoTipo)
        return 0;
    variavelT(p->pSimb->tipoD);
}

/* retorna verdadeiro se um nodo p se refere a um ponteiro */
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

/* retorna o tipo base do tipo de dado t */
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
    case tipoIdFuncPointVoid:
    case tipoIdUndef:
    default:
        return tipoUndef; //------------ tipoUndef
    }
}

/* retorna o tipo base do tipo contido no nodo p */
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

/* retorna o nome do tipo de dado contido no nodo p que pode ser Simbolo, Operador ou Tipo */
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

/* converte um tipo base tb em seu cast em c */
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
//"tipoIdFuncInt", "tipoIdFuncDouble", "tipoIdFuncStr", "tipoIdFuncVoid", "tipoIdFuncPointVoid", "tipoIdFuncPointInt", "tipoIdFuncPointDouble", "tipoIdFuncPointStr"};
//int tok2td(int tk) {;}

/* converte um tipo base em um tipo de Dado retorno de funcao */
int tb2Func(int tb)
{
    switch (tb)
    {
    case tipoInt:
        return tipoIdFuncInt;
    case tipoDouble:
        return tipoIdFuncDouble;
    case tipoStr:
        return tipoIdFuncStr;
    case tipoVoid:
        return tipoIdFuncVoid;
    case tipoPointInt:
        return tipoIdFuncPointInt;
    case tipoPointDouble:
        return tipoIdFuncPointDouble;
    case tipoPointStr:
        return tipoIdFuncPointStr;
/*    case tipoPointVoid:
        return tipoIdFuncPointVoid;*/
    default:
        return tipoIdUndef;
    }
}

/* converte um tipo base em um tipo de Dado identificador */
int tb2Id(int tb)
{
    switch (tb)
    {
    case tipoInt:
        return tipoIdInt;
    case tipoDouble:
        return tipoIdDouble;
    case tipoStr:
        return tipoIdStr;
    case tipoVoid:          /* nao existe variavel sem tipo */
        return tipoIdUndef;
    case tipoPointInt:
        return tipoIdPointInt;
    case tipoPointDouble:
        return tipoIdPointDouble;
    case tipoPointStr:
        return tipoIdPointStr;
    default:
        return tipoIdUndef;
    }
}

//char *sTipoBase[8]={"tipoUndef", "tipoInt", "tipoDouble", "tipoStr", "tipoVoid", "tipoPointInt", "tipoPointDouble", "tipoPointStr"};
/* converte um valor de token em um tipo base */
int tok2tb(int tk)
{
    switch (tk)
    {
    case INT:
        return tipoInt;
    case REAL:
        return tipoDouble;
    case TEXTO:
        return tipoStr;
    case NADA:
        return tipoVoid;
    case PONTI:
        return tipoPointInt;
    case PONTR:
        return tipoPointDouble;
    case PONTS:
        return tipoPointStr;
    default:
        return tipoUndef;
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

escopo *insereEsc(escopo *pe, int d)
{
    listesc *lant, *lprox;
    lant=NULL; /* irmao anterior */
    if(pe==NULL)
    {
        fprintf(stderr, "Erro: pai nulo no escopo\n");
        exit(1);
    }
    lprox=pe->lsons;
    while(lprox!=NULL)
    {
        lant=lprox;
        lprox=lprox->lbrother;
    }
    lprox = malloc(sizeof(listesc)); /* novo irmao na lista */
    if(lprox == NULL)
    {
        fprintf(stderr, "Erro: alocacao lprox\n");
        exit(1);
    }
    lprox->lbrother=NULL; /* o ultimo continua NULL */
    if(lant != NULL)
        lant->lbrother=lprox; /* liga a lista irmao anterior com o novo */
    lprox->eson = malloc(sizeof(escopo)); /* dados deste irmao */
    if(lprox->eson == NULL)
    {
        fprintf(stderr, "Erro: alocacao lprox->eson \n");
        exit(1);
    }
    lprox->eson->e=d;          /* o dado */
    lprox->eson->efather = pe; /* o filho tem pai */
    lprox->eson->lsons=NULL;   /* filhos deste irmao  */
    if(pe->lsons==NULL)        /* se primeiro filho */
        pe->lsons=lprox;           /* o pai tem filho */
    return lprox->eson;        /* retorna o filho inserido */
} //insereEsc

/* Procura idNome==nome && escopo<=es->e, retorna o ponteiro para a tabelaSimb. Se escopo nulo, atualiza e retorna ele */
//tabessslaSimb *achaIdEsc(char *nome, escopo *e);
tabelaSimb *achaIdEsc(char *nome, escopo *pe)
{
    char *p;
    tabelaSimb *ps;
    escopo *pesc;

    if(!pe)
        return NULL;
    pesc=pe;
    do
    {
        //fprintf(stderr, "tentando pesc->e: %d para %s\n", pesc->e, nome);
        for(ps=tabSimb; ps < &tabSimb[MAX_SIMB]; ps++)
            if(ps->idNome && !strcmp(ps->idNome, nome)) /* encontrou o nome ? */
                if(ps->pes)
                    if(ps->pes->e==pesc->e)           /* mesmo escopo ? */
                        return ps;
        pesc=pesc->efather; /* nao achou, procura escopo ascendente ate raiz */
    }while(pesc);

    //printTS();
    //fprintf(stderr, "nome %s, escopo %d\n", nome, pe->e);
    yyerror("Nao achou simbolo (funcao achaIdEsc).\n"); /* caso contrario */
    exit(1);
}

/* declaracao: procurar na TS idnome + escopo atual.
Se existir nome e escopo, erro de redeclaracao.
Se existir nome com um escopo invalido, atualiza escopo
Se existir nome, com escopo diferente, incluir nova declaracao com outro escopo
Se nao existir nome, declarar (?)
Retorna o ponteiro para a tabelaSimb */
//tabelaSimb *addIdEsc(char *nome, escopo *pe, tipoDado td)
tabelaSimb *addIdEsc(char *nome, escopo *pe)
{
    char *p;
    tabelaSimb *ps;
    char msg[128];

    for(ps=tabSimb; ps < &tabSimb[MAX_SIMB]; ps++)
    {
        if(ps->idNome && !strcmp(ps->idNome, nome)) /* encontrou o nome ? */
            if(ps->pes)
            {
                if(ps->pes->e==pe->e)           /* mesmo escopo ? */
                {
                    sprintf(msg, "Escopo: %d. Redeclaracao do identificador <%s>.", pe->e, nome);
                    yyerror(msg);
                    //erroSemantico(msg, tn->linha);
                    exit(1);
                    //return ps;
                }
            }
            else /* achou com escopo nulo, atualiza */
            {
                //ps->idx=geraTS();
                //ps->tipoD = td;
                ps->pes=pe;
                return ps;
            }
        if(!ps->idNome)  //nao achou ou achou com escopo diferente, (sempre acha idNome, pois .l cadastrou)
        {
            //ps->idx=geraTS();
            //ps->tipoD = td;
            ps->idNome = strdup(nome);
            ps->pes=pe;
            return ps;
        }
    } /* for: nao eh o fim, procura mais */
    yyerror("Tabela de simbolos: nao achou simbolo %%s!"); /* caso contrario */
    exit(1);
}

/* Acha com mesmo escopo ou cria ID+escopo e retorna o ponteiro para a tabelaSimb */
tabelaSimb *achaFuncEsc(char *nome, escopo *pe, tipoDado td)
{
    char *p;
    tabelaSimb *ps;

    for(ps=tabSimb; ps < &tabSimb[MAX_SIMB]; ps++)
    {
        if(ps->idNome && !strcmp(ps->idNome, nome)) /* encontrou o nome ? */
            if(ps->pes)
            {
                if(ps->pes->e==pe->e)           /* mesmo escopo ? */
                {
                    printf("Escopo: %d. Redeclaracao da funcao <%s>.", pe->e, nome);
                    exit(1);
                }
            }
            else /* achou com escopo nulo, atualiza */
            {
                //ps->idx=geraTF();  //feito pelo pass3 addFunc
                //ps->tipoD = td;   //feito pelo pass3 addFunc
                ps->pes=pe;
                //printf("saiu, achou escopo nulo e atualizou, achaIdFuncEsc\n");
                //printf("ps:%p, ps->tipoD:%s\n", ps, sTipoDado[ps->tipoD]);
                return ps;
            }

        /* nao achou, ou achou com escopo diferente: veja se chegou no fim da tabela e insere */
        if(!ps->idNome)  //apenas escopo diferente, pois sempre acha
        {
            //ps->idx=geraTF();   //feito pelo pass3 addFunc
            //ps->tipoD = td;     //feito pelo pass3 addFunc
            ps->idNome = strdup(nome);
            ps->pes=pe;
            //printf("saiu, nao achou ou escopo diferente, achaIdFuncEsc\n");
            //printf("ps:%p, ps->tipoD:%s\n", ps, sTipoDado[ps->tipoD]);
            return ps;
        }
        /* nao eh o fim, procura mais */
    }
    yyerror("Tabela de simbolos: nao achou simbolo identificador!"); /* caso contrario */
    exit(1);
}

/* Acha/cria ConInt e retorna o ponteiro para a TS */
tabelaSimb *achaIntEsc(int iv, escopo *pe)
{
    char *p;
    tabelaSimb *ps;
    int i;

    for(ps=tabSimb; ps < &tabSimb[MAX_SIMB]; ps++)
    {
        if(ps->idNome && ps->ival==iv && ps->tipoD==tipoConInt) /* encontrou ? */
            if(ps->pes)
            {
                if(ps->pes->e==pe->e)           /* mesmo escopo ? */
                    return ps; /* sim ! nao tem erro de redeclaracao para constantes numericas */
            }
            else /* achou com escopo nulo, atualiza */
            {
                ps->pes=pe;
                return ps;
            }
        if(!ps->idNome) // escopo diferente
        {
            i=geraTC();
            ps->tipoD = tipoConInt;
            ps->idNome = strdup("#ConInt");
            ps->ival = iv;
            ps->idx = i;
            ps->pes=pe;
            return ps;
        }
    }
    yyerror("Tabela de simbolos: nao achou %%d!"); /* caso contrario */
    exit(1);
}

/* Acha/cria ConFloat e retorna o ponteiro para a TS */
tabelaSimb *achaDoubleEsc(float dv, escopo *pe)
{
    char *p;
    tabelaSimb *ps;
    int i;

    for(ps=tabSimb; ps < &tabSimb[MAX_SIMB]; ps++)
    {
        if(ps->idNome && ps->dval==dv && ps->tipoD==tipoConDouble) /* encontrou ? */
            if(ps->pes)
            {
                if(ps->pes->e==pe->e)           /* mesmo escopo ? */
                    return ps; /* sim ! */
            }
            else /* achou com escopo nulo, atualiza */
            {
                ps->pes=pe;
                return ps;
            }
        if(!ps->idNome) /* ponteiro livre ? escopo diferente! */
        {
            i=geraTC();
            ps->tipoD = tipoConDouble;
            ps->idNome = strdup("#ConDouble");
            ps->dval = dv;
            ps->idx = i;
            ps->pes=pe;
            return ps;
        }
    }
    yyerror("Tabela de simbolos: nao achou %%f!"); /* caso contrario */
    exit(1);
}

/* Acha/cria ConStr e retorna o ponteiro para a TS */
tabelaSimb *achaStrEsc(char *sv, escopo *pe)
{
    char *p;
    tabelaSimb *ps;
    int i;

    for(ps=tabSimb; ps < &tabSimb[MAX_SIMB]; ps++)
    {
        if(ps->idNome && !strcmp(ps->sval, sv)) /* encontrou ? */
            if(ps->pes)
            {
                if(ps->pes->e==pe->e)           /* mesmo escopo ? */
                    return ps; /* sim ! */
            }
            else /* achou com escopo nulo, atualiza */
            {
                ps->pes=pe;
                return ps;
            }
        if(!ps->idNome) /* ponteiro livre ? escopo diferente! */
        {
            i=geraTC();
            ps->tipoD = tipoConStr;
            ps->idNome = strdup("#ConStr");
            strcpy(ps->sval,sv);
            ps->idx = i;
            ps->pes=pe;
            return ps;
        }
    }
    yyerror("Tabela de simbolos: nao achou %%s!"); /* caso contrario */
    exit(1);
}

//tn->pSimb->pes=achaEsc(2);
escopo *achaEsc(escopo *es, int e)
{
    escopo *ret=NULL;
    listesc *s;

    if(!es)
        return NULL;

    if(es->e==e)
        return es;

    s=es->lsons;
    while(s && !ret)
    {
        ret = achaEsc(s->eson, e);
        s=s->lbrother;
    }
    return ret;

}

void carregaFuncoesPre(void)
{
    tabelaSimb *ps;

    ps=achaIdEsc("imprima", &esco);
    sprintf(cabecalhoMain, "%s  loadfunc(tipoVoid, (void *)printf, \"imprima\", &tf[%d], 2);\n", cabecalhoMain, ps->idx);
    ps=achaIdEsc("leia", &esco);
    sprintf(cabecalhoMain, "%s  loadfunc(tipoVoid, (void *)scanf, \"leia\", &tf[%d], 2);\n", cabecalhoMain, ps->idx);
    ps=achaIdEsc("saia", &esco);
    sprintf(cabecalhoMain, "%s  loadfunc(tipoVoid, (void *)exit, \"saia\", &tf[%d], 1);\n", cabecalhoMain, ps->idx);
    ps=achaIdEsc("raiz", &esco);
    sprintf(cabecalhoMain, "%s  loadfunc(tipoDouble, (void *)sqrt, \"raiz\", &tf[%d], 1);\n", cabecalhoMain, ps->idx);
    sprintf(cabecalhoMain, "%s  /* funcoes definidas pelo usuario */\n", cabecalhoMain);
}

/* carrega no cabecalho todas as constantes da TS */
void carregaConstantes(void)
{
    tabelaSimb *ps;

    sprintf(cabecalhoMain, "%s  /* tabela de constantes */\n", cabecalhoMain);
    for(ps=tabSimb; ps < &tabSimb[MAX_SIMB]; ps++)
    {
        if(ps->idNome)
        {
            if(ps->tipoD==tipoConInt)    /* encontrou int */
                sprintf(cabecalhoMain, "%s  loadi(%d,NULL,&tc[%d]);\n", cabecalhoMain, ps->ival, ps->idx);
            else if(ps->tipoD==tipoConDouble) /* encontrou double */
                    sprintf(cabecalhoMain, "%s  loadd(%.2f,NULL,&tc[%d]);\n", cabecalhoMain, ps->dval, ps->idx);
                else if(ps->tipoD==tipoConStr)    /* encontrou string */
                    sprintf(cabecalhoMain, "%s  loads(%s,NULL,&tc[%d]);\n", cabecalhoMain, ps->sval, ps->idx);
        }
    }
    sprintf(cabecalhoMain, "%s\n  /* codigo do programa */\n", cabecalhoMain);
}
