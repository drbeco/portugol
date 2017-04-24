#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SVAL 256
#define MAX_PARAM 2
#define STACK_SIZE 200
#define MAX_TS 6  /* tabela de variaveis */
#define MAX_TC 6  /* tabela de constantes */
#define MAX_TP 6  /* tabela de temporarios */
#define MAX_TF 52 /* tabela de funcoes */

/* Tipos de Base */
typedef enum
{
    tipoUndef,
    tipoVoid,
    tipoInt,
    tipoDouble,
    tipoStr
} tipoBase;

/* Super Tipo */
typedef struct
{
    tipoBase tipo;
    int    ival;
    double dval;
    char   sval[MAX_SVAL];
} superTipo;


/* Super Func */
typedef struct
{
    tipoBase tipoRet;
    int numParam;
    char   *idNome;
    int    (*ifunc)();   //ponteiro para funcao que retorna inteiro
    double (*dfunc)();   //ponteiro para funcao que retorna double
    char   *(*sfunc)();  //ponteiro para funcao que retorna ponteiro para char
    void   (*vfunc)();   //ponteiro para a funcao que retorna void
} superFunc;

superTipo gstack[STACK_SIZE];   //pilha
superTipo esp={tipoInt, STACK_SIZE, 0.0, '\0'};
//int gsi=STACK_SIZE-1;           //indice da pilha geral

superTipo ts[MAX_TS]={0};
superTipo tc[MAX_TC]={0};
superTipo tp[MAX_TP]={0};
superFunc tf[MAX_TF]={0};

#define retn      return                         /* return from function */
#define ret(q1)   return(q1)                     /* return from function */

superTipo ebp, eax;


void loadfunc(tipoBase tipoRet, void *pFunc, char *fNome, superFunc *sf, int numpar)
{

    sf->tipoRet=tipoRet;
    sf->numParam=numpar;

    sf->idNome=malloc(strlen(fNome)+1);
    strcpy(sf->idNome,fNome);

    switch (tipoRet)
    {
    case tipoVoid:
        sf->vfunc=pFunc;
        break;
    case tipoInt:
        //sf->ifunc=((int *)())pFunc;
        sf->ifunc=pFunc;
        break;
    case tipoDouble:
        sf->dfunc=pFunc;
        break;
    case tipoStr:
        sf->sfunc=pFunc;
        break;
    default:
        fprintf(stderr,"ASM Error: Unknow return type\n");
        exit(1);
    }
}

void loadi(int i,   int *nul1,   superTipo *qres)
{
    qres->tipo=tipoInt;
    qres->ival=i;
    qres->dval=0.0;
    qres->sval[0]='\0';
}

void loadd(double d, double *nul1, superTipo *qres)
{
    qres->tipo=tipoDouble;
    qres->ival=0;
    qres->dval=d;
    qres->sval[0]='\0';
}

void loads(char *s, char *nul1,  superTipo *qres)
{
    qres->tipo=tipoStr;
    qres->ival=0;
    qres->dval=0.0;
    strcpy(qres->sval, s);
}


void add(superTipo  q1, superTipo  q2, superTipo  *qres)
{

    double arg1, arg2;

    if ((q1.tipo == tipoStr || q2.tipo == tipoStr) && (q1.tipo != tipoStr || q2.tipo != tipoStr))
    {
        fprintf(stderr,"ASM Error: invalid add operation.\n");
        exit(1);
    }

    if (q1.tipo == tipoStr) //se um eh, ambos sao
    {
        qres->tipo=tipoStr;
        strcpy(qres->sval, q1.sval);
        strcat(qres->sval, q2.sval);
        return;
    }

    if (q1.tipo == tipoDouble)
        arg1=q1.dval;
    else
        arg1=(double)q1.ival;
    if (q2.tipo == tipoDouble)
        arg2=q2.dval;
    else
        arg2=(double)q2.ival;

    if (q1.tipo == tipoDouble || q2.tipo == tipoDouble)
    {
        qres->dval=arg1 + arg2;
        qres->tipo=tipoDouble;
    }
    else
    {
        qres->ival=(int)(arg1 + arg2);
        qres->tipo=tipoInt;
    }
}

void sub(superTipo  q1, superTipo  q2, superTipo  *qres)
{

    double arg1, arg2;

    if (q1.tipo == tipoStr || q2.tipo == tipoStr)
    {
        fprintf(stderr,"ASM Error: invalid sub operation.\n");
        exit(1);
    }

    if (q1.tipo == tipoDouble)
        arg1=q1.dval;
    else
        arg1=(double)q1.ival;
    if (q2.tipo == tipoDouble)
        arg2=q2.dval;
    else
        arg2=(double)q2.ival;

    if (q1.tipo == tipoDouble || q2.tipo == tipoDouble)
    {
        qres->dval=arg1 - arg2;
        qres->tipo=tipoDouble;
    }
    else
    {
        qres->ival=(int)(arg1 - arg2);
        qres->tipo=tipoInt;
    }
}

void push(superTipo g) // poe na pilha de execucao geral //push to stack
{
    if (esp.ival<1)
    {
        fprintf(stderr,"ASM Error: stack overflow.\n");
        exit(1);
    }
    esp.ival--;
    gstack[esp.ival]=g; //copia por valor
}

// superTipo *pop(void)    // tira da pilha de execucao geral //pop from stack
// {
//     superTipo *r;
//     if(gsi<=0)
//     {
//         fprintf(stderr,"ASM Error: stack underflow.\n");
//         exit(1);
//     }
//     r=malloc(sizeof(superTipo));
//     *r=gstack[--gsi]; //copia por valor
//     return(r); //&gstack[--gsi]
// }

void pop(superTipo *qres)    // tira da pilha de execucao geral //pop from stack
{
    if (esp.ival>=STACK_SIZE)
    {
        fprintf(stderr,"ASM Error: stack underflow.\n");
        exit(1);
    }
    qres->tipo=gstack[esp.ival].tipo;
    qres->ival=gstack[esp.ival].ival;
    qres->dval=gstack[esp.ival].dval;
    strcpy(qres->sval, gstack[esp.ival].sval);
    esp.ival++;
    return;
}


void param(superTipo q1, void *nul1, void *nul2)
{
    push(q1);
}



// move around
void mov(superTipo q1, superTipo *nul1, superTipo *qres)
{
    qres->tipo=q1.tipo;
    if (q1.tipo==tipoInt)
        qres->ival=q1.ival;
    else if (q1.tipo==tipoDouble)
        qres->dval=q1.dval;
    else if (q1.tipo=tipoStr)
        strcpy(qres->sval, q1.sval);
    else
    {
        fprintf(stderr,"ASM Error: invalid mov operation.\n");
        exit(1);
    }
}


void func_vfv(void)
{
    push(ebp);
    mov(esp, NULL, &ebp);
    loadi(2, NULL, &tp[0]); /* one local variable */
    sub(esp, tp[0], &esp); /* stack pointer */

    printf("func_vfv\n");

    mov(ebp, NULL, &esp);
    pop(&ebp);
    retn; /* return value in eax */
}
void func_vfi(int i)
{
    printf("func_vfi\n");
    return ;
}
void func_vfd(double d)
{
    printf("func_vfd\n");
    return ;
}
void func_vfs(char *s)
{
    printf("func_vfs\n");
    return ;
}
int func_ifv(void)
{
    printf("func_ifv\n");
    return 1;
}
int func_ifi(int i)
{
    printf("func_ifi\n");
    ret(1);
}
int func_ifd(double d)
{
    printf("func_ifd\n");
    return 1;
}
int func_ifs(char *s)
{
    printf("func_ifs\n");
    return 1;
}
double func_dfv(void)
{
    printf("func_dfv\n");
    return 1.1;
}
double func_dfi(int i)
{
    printf("func_dfi\n");
    return 1.1;
}
double func_dfd(double d)
{
    printf("func_dfd\n");
    return 1.1;
}
double func_dfs(char *s)
{
    printf("func_dfs\n");
    return 1.1;
}
char *func_sfv(void)
{
//  char tmp[MAX_SVAL]="pchar\n";
    printf("func_sfv\n");
    return strdup("pchar\n");
}
char *func_sfi(int i)
{
    printf("func_sfi\n");
    return strdup("pchar\n");
}
char *func_sfd(double d)
{
    printf("func_sfd\n");
    return strdup("pchar\n");
}
char *func_sfs(char *s)
{
    printf("func_sfs\n");
    return strdup("pchar\n");
}


/* dois argumentos, segundo int */

void func_vfii(int i, int j)
{
    printf("func_vfii\n");
    return ;
}
void func_vfdi(double d, int i)
{
    printf("func_vfdi\n");
    return ;
}
void func_vfsi(char *s, int i)
{
    printf("func_vfsi\n");
    return ;
}
int func_ifii(int i, int j)
{
    printf("func_ifii\n");
    return 1;
}
int func_ifdi(double d, int i)
{
    printf("func_ifdi\n");
    return 1;
}
int func_ifsi(char *s, int i)
{
    printf("func_ifsi\n");
    return 1;
}
double func_dfii(int i, int j)
{
    printf("func_dfii\n");
    return 1.1;
}
double func_dfdi(double d, int i)
{
    printf("func_dfdi\n");
    return 1.1;
}
double func_dfsi(char *s, int i)
{
    printf("func_dfsi\n");
    return 1.1;
}
char *func_sfii(int i, int j)
{
    printf("func_sfii\n");
    return strdup("pchar\n");
}
char *func_sfdi(double d, int i)
{
    printf("func_sfdi\n");
    return strdup("pchar\n");
}
char *func_sfsi(char *s, int i)
{
    printf("func_sfsi\n");
    return strdup("pchar\n");
}


/* dois argumentos, segundo double */

void func_vfid(int i, double d)
{
    printf("func_vfid\n");
    return ;
}
void func_vfdd(double d, double e)
{
    printf("func_vfdd\n");
    return ;
}
void func_vfsd(char *s, double d)
{
    printf("func_vfsd\n");
    return ;
}
int func_ifid(int i, double d)
{
    printf("func_ifid\n");
    return 1;
}
int func_ifdd(double d, double e)
{
    printf("func_ifdd\n");
    return 1;
}
int func_ifsd(char *s, double d)
{
    printf("func_ifsd\n");
    return 1;
}
double func_dfid(int i, double d)
{
    printf("func_dfid\n");
    return 1.1;
}
double func_dfdd(double d, double e)
{
    printf("func_dfdd\n");
    return 1.1;
}
double func_dfsd(char *s, double d)
{
    printf("func_dfsd\n");
    return 1.1;
}
char *func_sfid(int i, double d)
{
    printf("func_sfid\n");
    return strdup("pchar\n");
}
char *func_sfdd(double d, double e)
{
    printf("func_sfdd\n");
    return strdup("pchar\n");
}
char *func_sfsd(char *s, double d)
{
    printf("func_sfsd\n");
    return strdup("pchar\n");
}


/* dois argumentos, segundo char * */

void func_vfis(int i, char *s)
{
    printf("func_vfis\n");
    return ;
}
void func_vfds(double d, char *s)
{
    printf("func_vfds\n");
    return ;
}
void func_vfss(char *s, char *t)
{
    printf("func_vfss\n");
    return ;
}
int func_ifis(int i, char *s)
{
    printf("func_ifis\n");
    return ;
}
int func_ifds(double d, char *s)
{
    printf("func_ifds\n");
    return ;
}
int func_ifss(char *s, char *t)
{
    printf("func_ifss\n");
    return ;
}
double func_dfis(int i, char *s)
{
    printf("func_dfis\n");
    return ;
}
double func_dfds(double d, char *s)
{
    printf("func_dfds\n");
    return ;
}
double func_dfss(char *s, char *t)
{
    printf("func_dfss\n");
    return ;
}
char *func_sfis(int i, char *s)
{
    printf("func_sfis\n");
    return strdup("pchar\n");
}
char *func_sfds(double d, char *s)
{
    printf("func_sfds\n");
    return strdup("pchar\n");
}
char *func_sfss(char *s, char *t)
{
    printf("func_sfss\n");
    return strdup("pchar\n");
}

//void call(char *q1, int i, superTipo  *qres)
void call(char *q1, int i, superTipo  *nul2)
{
    int j=0, idx;
    superTipo g[MAX_PARAM];//maximo funcao com 4 argumentos f(a0, a1, a2, a3);
    superTipo npar;

    loadi(i, NULL, &npar);

    if (i>MAX_PARAM)
    {
        fprintf(stderr, "ASM Error: cant call function with more than %d (MAX_PARAM) parameters.\n", MAX_PARAM);
        exit(1);
    }

    /* colocar na pilha na ordem inversa */
    //param(i, NULL, NULL);
    //param(s, NULL, NULL);
    //call("printf", 2, &r);
    for (j=0; j<i && j<MAX_PARAM; j++)
        pop(&g[j]);    //pop all parameters
    sub(esp, npar, &esp); //do not really pop those items

    /* lista de funcoes */
    for (idx=0; idx<MAX_TF; idx++)
    {
        if(tf[idx].idNome==NULL)
            continue;
        if (strcmp(tf[idx].idNome, q1) == 0) //found!
            break;
    }
    printf("idx:%d MAX_TF:%d\n", idx, MAX_TF);
    if (idx==MAX_TF)
    {
        fprintf(stderr, "ASM Error: function not in tf[] table (loop exausted).\n");
        exit(1);
    }

    if (i==0) /* func_?fv */
        switch (tf[idx].tipoRet)
        {
        case tipoVoid: // func_vfv
            eax.tipo=tipoUndef;
            (*tf[idx].vfunc)();
            break;
        case tipoInt: // func_ifv
            eax.tipo=tipoInt;
            eax.ival=(*tf[idx].ifunc)();
            break;
        case tipoDouble: // func_dfv
            eax.tipo=tipoDouble;
            eax.dval=(*tf[idx].dfunc)();
            break;
        case tipoStr: // func_sfv
            eax.tipo=tipoStr;
            strcpy(eax.sval, (*tf[idx].sfunc)());
            break;
        default:
            fprintf(stderr,"Unknow return type\n");
            exit(1);
        }
    if (i==1) /* func_?f? */
        switch (tf[idx].tipoRet)
        {
        case tipoVoid: // func_vf?
            eax.tipo=tipoUndef;
            switch (g[0].tipo)
            {
            case tipoInt:  // func_vfi
                (*tf[idx].vfunc)(g[0].ival);
                break;
            case tipoDouble: // func_vfd
                (*tf[idx].vfunc)(g[0].dval);
                break;
            case tipoStr: // func_vfs
                (*tf[idx].vfunc)(g[0].sval);
                break;
            default:
                fprintf(stderr,"Unknow type of arg 1\n");
                exit(1);
            }
            break;
        case tipoInt: // func_if?
            eax.tipo=tipoInt;
            switch (g[0].tipo)
            {
            case tipoInt: // func_ifi
                eax.ival=(*tf[idx].ifunc)(g[0].ival);
                break;
            case tipoDouble: // func_ifd
                eax.ival=(*tf[idx].ifunc)(g[0].dval);
                break;
            case tipoStr: // func_ifs
                eax.ival=(*tf[idx].ifunc)(g[0].sval);
                break;
            default:
                fprintf(stderr,"Unknow type of arg 1\n");
                exit(1);
            }
            break;
        case tipoDouble: // func_df?
            eax.tipo=tipoDouble;
            switch (g[0].tipo)
            {
            case tipoInt: // func_dfi
                eax.dval=(*tf[idx].dfunc)(g[0].ival);
                break;
            case tipoDouble: // func_dfd
                eax.dval=(*tf[idx].dfunc)(g[0].dval);
                break;
            case tipoStr: // func_dfs
                eax.dval=(*tf[idx].dfunc)(g[0].sval);
                break;
            default:
                fprintf(stderr,"Unknow type of arg 1\n");
                exit(1);
            }
            break;
        case tipoStr: // func_sf?
            eax.tipo=tipoStr;
            switch (g[0].tipo)
            {
            case tipoInt: // func_sfi
                strcpy(eax.sval, (*tf[idx].sfunc)(g[0].ival));
                break;
            case tipoDouble: // func_sfd
                strcpy(eax.sval, (*tf[idx].sfunc)(g[0].dval));
                break;
            case tipoStr: // func_sfs
                strcpy(eax.sval, (*tf[idx].sfunc)(g[0].sval));
                break;
            default:
                fprintf(stderr,"Unknow type of arg 1\n");
                exit(1);
            }
            break;
        default:
            fprintf(stderr,"Unknow return type\n");
            exit(1);
        }

    if (i==2) /* func_?f?? */
        switch (tf[idx].tipoRet)
        {
        case tipoVoid: // func_vf??
            eax.tipo=tipoUndef;
            switch (g[0].tipo)
            {
            case tipoInt: // func_vfi?
                switch (g[1].tipo)
                {
                case tipoInt: // func_vfii
                    (*tf[idx].vfunc)(g[0].ival, g[1].ival);
                    break;
                case tipoDouble: // func_vfid
                    (*tf[idx].vfunc)(g[0].ival, g[1].dval);
                    break;
                case tipoStr: // func_vfis
                    (*tf[idx].vfunc)(g[0].ival, g[1].sval);
                    break;
                default:
                    fprintf(stderr,"Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoDouble: // func_vfd?
                switch (g[1].tipo)
                {
                case tipoInt: // func_vfdi
                    (*tf[idx].vfunc)(g[0].dval, g[1].ival);
                    break;
                case tipoDouble: // func_vfdd
                    (*tf[idx].vfunc)(g[0].dval, g[1].dval);
                    break;
                case tipoStr: // func_vfds
                    (*tf[idx].vfunc)(g[0].dval, g[1].sval);
                    break;
                default:
                    fprintf(stderr,"Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoStr: //func_vfs?
                switch (g[1].tipo)
                {
                case tipoInt: // func_vfsi
                    (*tf[idx].vfunc)(g[0].sval, g[1].ival);
                    break;
                case tipoDouble: // func_vfsd
                    (*tf[idx].vfunc)(g[0].sval, g[1].dval);
                    break;
                case tipoStr: // func_vfss
                    (*tf[idx].vfunc)(g[0].sval, g[1].sval);
                    break;
                default:
                    fprintf(stderr,"Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            default:
                fprintf(stderr,"Unknow type of arg 1\n");
                exit(1);
            } //void switch g[0]
            break;

        case tipoInt: // func_if??
            eax.tipo=tipoInt;
            switch (g[0].tipo)
            {
            case tipoInt: // func_ifi?
                switch (g[1].tipo)
                {
                case tipoInt: // func_ifii
                    eax.ival=(*tf[idx].ifunc)(g[0].ival, g[1].ival);
                    break;
                case tipoDouble: // func_ifid
                    eax.ival=(*tf[idx].ifunc)(g[0].ival, g[1].dval);
                    break;
                case tipoStr: // func_ifis
                    eax.ival=(*tf[idx].ifunc)(g[0].ival, g[1].sval);
                    break;
                default:
                    fprintf(stderr,"Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoDouble: // func_ifd?
                switch (g[1].tipo)
                {
                case tipoInt: // func_ifdi
                    eax.ival=(*tf[idx].ifunc)(g[0].dval, g[1].ival);
                    break;
                case tipoDouble: // func_ifdd
                    eax.ival=(*tf[idx].ifunc)(g[0].dval, g[1].dval);
                    break;
                case tipoStr: // func_ifds
                    eax.ival=(*tf[idx].ifunc)(g[0].dval, g[1].sval);
                    break;
                default:
                    fprintf(stderr,"Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoStr: //func_ifs?
                switch (g[1].tipo)
                {
                case tipoInt: // func_ifsi
                    eax.ival=(*tf[idx].ifunc)(g[0].sval, g[1].ival);
                    break;
                case tipoDouble: // func_ifsd
                    eax.ival=(*tf[idx].ifunc)(g[0].sval, g[1].dval);
                    break;
                case tipoStr: // func_ifss
                    eax.ival=(*tf[idx].ifunc)(g[0].sval, g[1].sval);
                    break;
                default:
                    fprintf(stderr,"Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            default:
                fprintf(stderr,"Unknow type of arg 1\n");
                exit(1);
            } //int switch g[0]
            break;

        case tipoDouble: // func_df??
            eax.tipo=tipoDouble;
            switch (g[0].tipo)
            {
            case tipoInt: // func_dfi?
                switch (g[1].tipo)
                {
                case tipoInt: // func_dfii
                    eax.dval=(*tf[idx].dfunc)(g[0].ival, g[1].ival);
                    break;
                case tipoDouble: // func_dfid
                    eax.dval=(*tf[idx].dfunc)(g[0].ival, g[1].dval);
                    break;
                case tipoStr: // func_dfis
                    eax.dval=(*tf[idx].dfunc)(g[0].ival, g[1].sval);
                    break;
                default:
                    fprintf(stderr,"Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoDouble: // func_dfd?
                switch (g[1].tipo)
                {
                case tipoInt: // func_dfdi
                    eax.dval=(*tf[idx].dfunc)(g[0].dval, g[1].ival);
                    break;
                case tipoDouble: // func_dfdd
                    eax.dval=(*tf[idx].dfunc)(g[0].dval, g[1].dval);
                    break;
                case tipoStr: // func_dfds
                    eax.dval=(*tf[idx].dfunc)(g[0].dval, g[1].sval);
                    break;
                default:
                    fprintf(stderr,"Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoStr: //func_dfs?
                switch (g[1].tipo)
                {
                case tipoInt: // func_dfsi
                    eax.dval=(*tf[idx].dfunc)(g[0].sval, g[1].ival);
                    break;
                case tipoDouble: // func_dfsd
                    eax.dval=(*tf[idx].dfunc)(g[0].sval, g[1].dval);
                    break;
                case tipoStr: // func_dfss
                    eax.dval=(*tf[idx].dfunc)(g[0].sval, g[1].sval);
                    break;
                default:
                    fprintf(stderr,"Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            default:
                fprintf(stderr,"Unknow type of arg 1\n");
                exit(1);
            } //double switch g[0]
            break;

        case tipoStr: // func_sf??
            eax.tipo=tipoStr;
            switch (g[0].tipo)
            {
            case tipoInt: // func_sfi?
                switch (g[1].tipo)
                {
                case tipoInt: // func_sfii
                    strcpy(eax.sval, (*tf[idx].sfunc)(g[0].ival, g[1].ival));
                    break;
                case tipoDouble: // func_sfid
                    strcpy(eax.sval, (*tf[idx].sfunc)(g[0].ival, g[1].dval));
                    break;
                case tipoStr: // func_sfis
                    strcpy(eax.sval, (*tf[idx].sfunc)(g[0].ival, g[1].sval));
                    break;
                default:
                    fprintf(stderr,"Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoDouble: // func_sfd?
                switch (g[1].tipo)
                {
                case tipoInt: // func_sfdi
                    strcpy(eax.sval, (*tf[idx].sfunc)(g[0].dval, g[1].ival));
                    break;
                case tipoDouble: // func_sfdd
                    strcpy(eax.sval, (*tf[idx].sfunc)(g[0].dval, g[1].dval));
                    break;
                case tipoStr: // func_sfds
                    strcpy(eax.sval, (*tf[idx].sfunc)(g[0].dval, g[1].sval));
                    break;
                default:
                    fprintf(stderr,"Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoStr: //func_sfs?
                switch (g[1].tipo)
                {
                case tipoInt: // func_sfsi
                    strcpy(eax.sval, (*tf[idx].sfunc)(g[0].sval, g[1].ival));
                    break;
                case tipoDouble: // func_sfsd
                    strcpy(eax.sval, (*tf[idx].sfunc)(g[0].sval, g[1].dval));
                    break;
                case tipoStr: // func_sfss
                    strcpy(eax.sval, (*tf[idx].sfunc)(g[0].sval, g[1].sval));
                    break;
                default:
                    fprintf(stderr,"Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            default:
                fprintf(stderr,"Unknow type of arg 1\n");
                exit(1);
            } //str switch g[0]
            break;
        default:
            fprintf(stderr,"Unknow return type\n");
            exit(1);
        } //switch tipoRet

    /* ---------------- tres argumentos ---------------- */

    if (i==3) /* func_?f??? */
        switch (tf[idx].tipoRet)
        {
        case tipoVoid: // func_vf???
            eax.tipo=tipoUndef;
            switch (g[0].tipo)
            {
            case tipoInt: // func_vfi??
                switch (g[1].tipo)
                {
                case tipoInt: // func_vfii?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_vfiii
                        (*tf[idx].vfunc)(g[0].ival, g[1].ival, g[2].ival);
                        break;
                    case tipoDouble: // func_vfiid
                        (*tf[idx].vfunc)(g[0].ival, g[1].ival, g[2].dval);
                        break;
                    case tipoStr: // func_vfiis
                        (*tf[idx].vfunc)(g[0].ival, g[1].ival, g[2].sval);
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoDouble: // func_vfid?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_vfidi
                        (*tf[idx].vfunc)(g[0].ival, g[1].dval, g[2].ival);
                        break;
                    case tipoDouble: // func_vfidd
                        (*tf[idx].vfunc)(g[0].ival, g[1].dval, g[2].dval);
                        break;
                    case tipoStr: // func_vfids
                        (*tf[idx].vfunc)(g[0].ival, g[1].dval, g[2].sval);
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoStr: // func_vfis?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_vfisi
                        (*tf[idx].vfunc)(g[0].ival, g[1].sval, g[2].ival);
                        break;
                    case tipoDouble: // func_vfisd
                        (*tf[idx].vfunc)(g[0].ival, g[1].sval, g[2].dval);
                        break;
                    case tipoStr: // func_vfiss
                        (*tf[idx].vfunc)(g[0].ival, g[1].sval, g[2].sval);
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                default:
                    fprintf(stderr,"Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoDouble: // func_vfd??
                switch (g[1].tipo)
                {
                case tipoInt: // func_vfdi?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_vfdii
                        (*tf[idx].vfunc)(g[0].dval, g[1].ival, g[2].ival);
                        break;
                    case tipoDouble: // func_vfdid
                        (*tf[idx].vfunc)(g[0].dval, g[1].ival, g[2].dval);
                        break;
                    case tipoStr: // func_vfdis
                        (*tf[idx].vfunc)(g[0].dval, g[1].ival, g[2].sval);
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoDouble: // func_vfdd?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_vfddi
                        (*tf[idx].vfunc)(g[0].dval, g[1].dval, g[2].ival);
                        break;
                    case tipoDouble: // func_vfddd
                        (*tf[idx].vfunc)(g[0].dval, g[1].dval, g[2].dval);
                        break;
                    case tipoStr: // func_vfdds
                        (*tf[idx].vfunc)(g[0].dval, g[1].dval, g[2].sval);
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoStr: // func_vfds?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_vfdsi
                        (*tf[idx].vfunc)(g[0].dval, g[1].sval, g[2].ival);
                        break;
                    case tipoDouble: // func_vfdsd
                        (*tf[idx].vfunc)(g[0].dval, g[1].sval, g[2].dval);
                        break;
                    case tipoStr: // func_vfdss
                        (*tf[idx].vfunc)(g[0].dval, g[1].sval, g[2].sval);
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                default:
                    fprintf(stderr,"Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoStr: //func_vfs??
                switch (g[1].tipo)
                {
                case tipoInt: // func_vfsi?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_vfsii
                        (*tf[idx].vfunc)(g[0].sval, g[1].ival, g[2].ival);
                        break;
                    case tipoDouble: // func_vfsid
                        (*tf[idx].vfunc)(g[0].sval, g[1].ival, g[2].dval);
                        break;
                    case tipoStr: // func_vfsis
                        (*tf[idx].vfunc)(g[0].sval, g[1].ival, g[2].sval);
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoDouble: // func_vfsd?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_vfsdi
                        (*tf[idx].vfunc)(g[0].sval, g[1].dval, g[2].ival);
                        break;
                    case tipoDouble: // func_vfsdd
                        (*tf[idx].vfunc)(g[0].sval, g[1].dval, g[2].dval);
                        break;
                    case tipoStr: // func_vfsds
                        (*tf[idx].vfunc)(g[0].sval, g[1].dval, g[2].sval);
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoStr: // func_vfss?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_vfssi
                        (*tf[idx].vfunc)(g[0].sval, g[1].sval, g[2].ival);
                        break;
                    case tipoDouble: // func_vfssd
                        (*tf[idx].vfunc)(g[0].sval, g[1].sval, g[2].dval);
                        break;
                    case tipoStr: // func_vfsss
                        (*tf[idx].vfunc)(g[0].sval, g[1].sval, g[2].sval);
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                default:
                    fprintf(stderr,"Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            default:
                fprintf(stderr,"Unknow type of arg 1\n");
                exit(1);
            } //void switch g[0]
            break;

        case tipoInt: // func_if???
            eax.tipo=tipoInt;
            switch (g[0].tipo)
            {
            case tipoInt: // func_ifi??
                switch (g[1].tipo)
                {
                case tipoInt: // func_ifii?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_ifiii
                        eax.ival=(*tf[idx].ifunc)(g[0].ival, g[1].ival, g[2].ival);
                        break;
                    case tipoDouble: // func_ifiid
                        eax.ival=(*tf[idx].ifunc)(g[0].ival, g[1].ival, g[2].dval);
                        break;
                    case tipoStr: // func_ifiis
                        eax.ival=(*tf[idx].ifunc)(g[0].ival, g[1].ival, g[2].sval);
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoDouble: // func_ifid?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_ifidi
                        eax.ival=(*tf[idx].ifunc)(g[0].ival, g[1].dval, g[2].ival);
                        break;
                    case tipoDouble: // func_ifidd
                        eax.ival=(*tf[idx].ifunc)(g[0].ival, g[1].dval, g[2].dval);
                        break;
                    case tipoStr: // func_ifids
                        eax.ival=(*tf[idx].ifunc)(g[0].ival, g[1].dval, g[2].sval);
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoStr: // func_ifis?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_ifisi
                        eax.ival=(*tf[idx].ifunc)(g[0].ival, g[1].sval, g[2].ival);
                        break;
                    case tipoDouble: // func_ifisd
                        eax.ival=(*tf[idx].ifunc)(g[0].ival, g[1].sval, g[2].dval);
                        break;
                    case tipoStr: // func_ifiss
                        eax.ival=(*tf[idx].ifunc)(g[0].ival, g[1].sval, g[2].sval);
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                default:
                    fprintf(stderr,"Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoDouble: // func_ifd??
                switch (g[1].tipo)
                {
                case tipoInt: // func_ifdi?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_ifdii
                        eax.ival=(*tf[idx].ifunc)(g[0].dval, g[1].ival, g[2].ival);
                        break;
                    case tipoDouble: // func_ifdid
                        eax.ival=(*tf[idx].ifunc)(g[0].dval, g[1].ival, g[2].dval);
                        break;
                    case tipoStr: // func_ifdis
                        eax.ival=(*tf[idx].ifunc)(g[0].dval, g[1].ival, g[2].sval);
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoDouble: // func_ifdd?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_ifddi
                        eax.ival=(*tf[idx].ifunc)(g[0].dval, g[1].dval, g[2].ival);
                        break;
                    case tipoDouble: // func_ifddd
                        eax.ival=(*tf[idx].ifunc)(g[0].dval, g[1].dval, g[2].dval);
                        break;
                    case tipoStr: // func_ifdds
                        eax.ival=(*tf[idx].ifunc)(g[0].dval, g[1].dval, g[2].sval);
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                case tipoStr: // func_ifds?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_ifdsi
                        eax.ival=(*tf[idx].ifunc)(g[0].dval, g[1].sval, g[2].ival);
                        break;
                    case tipoDouble: // func_ifdsd
                        eax.ival=(*tf[idx].ifunc)(g[0].dval, g[1].sval, g[2].dval);
                        break;
                    case tipoStr: // func_ifdss
                        eax.ival=(*tf[idx].ifunc)(g[0].dval, g[1].sval, g[2].sval);
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                default:
                    fprintf(stderr,"Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoStr: //func_ifs??
                switch (g[1].tipo)
                {
                case tipoInt: // func_ifsi?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_ifsii
                        eax.ival=(*tf[idx].ifunc)(g[0].sval, g[1].ival, g[2].ival);
                        break;
                    case tipoDouble: // func_ifsid
                        eax.ival=(*tf[idx].ifunc)(g[0].sval, g[1].ival, g[2].dval);
                        break;
                    case tipoStr: // func_ifsis
                        eax.ival=(*tf[idx].ifunc)(g[0].sval, g[1].ival, g[2].sval);
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoDouble: // func_ifsd?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_ifsdi
                        eax.ival=(*tf[idx].ifunc)(g[0].sval, g[1].dval, g[2].ival);
                        break;
                    case tipoDouble: // func_ifsdd
                        eax.ival=(*tf[idx].ifunc)(g[0].sval, g[1].dval, g[2].dval);
                        break;
                    case tipoStr: // func_ifsds
                        eax.ival=(*tf[idx].ifunc)(g[0].sval, g[1].dval, g[2].sval);
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoStr: // func_ifss?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_ifssi
                        eax.ival=(*tf[idx].ifunc)(g[0].sval, g[1].sval, g[2].ival);
                        break;
                    case tipoDouble: // func_ifssd
                        eax.ival=(*tf[idx].ifunc)(g[0].sval, g[1].sval, g[2].dval);
                        break;
                    case tipoStr: // func_ifsss
                        eax.ival=(*tf[idx].ifunc)(g[0].sval, g[1].sval, g[2].sval);
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                default:
                    fprintf(stderr,"Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            default:
                fprintf(stderr,"Unknow type of arg 1\n");
                exit(1);
            } // int switch g[0]
            break;

        case tipoDouble: // func_df???
            eax.tipo=tipoDouble;
            switch (g[0].tipo)
            {
            case tipoInt: // func_dfi??
                switch (g[1].tipo)
                {
                case tipoInt: // func_dfii?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_dfiii
                        eax.dval=(*tf[idx].dfunc)(g[0].ival, g[1].ival, g[2].ival);
                        break;
                    case tipoDouble: // func_dfiid
                        eax.dval=(*tf[idx].dfunc)(g[0].ival, g[1].ival, g[2].dval);
                        break;
                    case tipoStr: // func_dfiis
                        eax.dval=(*tf[idx].dfunc)(g[0].ival, g[1].ival, g[2].sval);
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoDouble: // func_dfid?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_dfidi
                        eax.dval=(*tf[idx].dfunc)(g[0].ival, g[1].dval, g[2].ival);
                        break;
                    case tipoDouble: // func_dfidd
                        eax.dval=(*tf[idx].dfunc)(g[0].ival, g[1].dval, g[2].dval);
                        break;
                    case tipoStr: // func_dfids
                        eax.dval=(*tf[idx].dfunc)(g[0].ival, g[1].dval, g[2].sval);
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoStr: // func_dfis?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_dfisi
                        eax.dval=(*tf[idx].dfunc)(g[0].ival, g[1].sval, g[2].ival);
                        break;
                    case tipoDouble: // func_dfisd
                        eax.dval=(*tf[idx].dfunc)(g[0].ival, g[1].sval, g[2].dval);
                        break;
                    case tipoStr: // func_dfiss
                        eax.dval=(*tf[idx].dfunc)(g[0].ival, g[1].sval, g[2].sval);
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                default:
                    fprintf(stderr,"Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoDouble: // func_dfd??
                switch (g[1].tipo)
                {
                case tipoInt: // func_dfdi?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_dfdii
                        eax.dval=(*tf[idx].dfunc)(g[0].dval, g[1].ival, g[2].ival);
                        break;
                    case tipoDouble: // func_dfdid
                        eax.dval=(*tf[idx].dfunc)(g[0].dval, g[1].ival, g[2].dval);
                        break;
                    case tipoStr: // func_dfdis
                        eax.dval=(*tf[idx].dfunc)(g[0].dval, g[1].ival, g[2].sval);
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoDouble: // func_dfdd?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_dfddi
                        eax.dval=(*tf[idx].dfunc)(g[0].dval, g[1].dval, g[2].ival);
                        break;
                    case tipoDouble: // func_dfddd
                        eax.dval=(*tf[idx].dfunc)(g[0].dval, g[1].dval, g[2].dval);
                        break;
                    case tipoStr: // func_dfdds
                        eax.dval=(*tf[idx].dfunc)(g[0].dval, g[1].dval, g[2].sval);
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoStr: // func_dfds?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_dfdsi
                        eax.dval=(*tf[idx].dfunc)(g[0].dval, g[1].sval, g[2].ival);
                        break;
                    case tipoDouble: // func_dfdsd
                        eax.dval=(*tf[idx].dfunc)(g[0].dval, g[1].sval, g[2].dval);
                        break;
                    case tipoStr: // func_dfdss
                        eax.dval=(*tf[idx].dfunc)(g[0].dval, g[1].sval, g[2].sval);
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                default:
                    fprintf(stderr,"Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoStr: //func_dfs??
                switch (g[1].tipo)
                {
                case tipoInt: // func_dfsi?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_dfsii
                        eax.dval=(*tf[idx].dfunc)(g[0].sval, g[1].ival, g[2].ival);
                        break;
                    case tipoDouble: // func_dfsid
                        eax.dval=(*tf[idx].dfunc)(g[0].sval, g[1].ival, g[2].dval);
                        break;
                    case tipoStr: // func_dfsis
                        eax.dval=(*tf[idx].dfunc)(g[0].sval, g[1].ival, g[2].sval);
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoDouble: // func_dfsd?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_dfsdi
                        eax.dval=(*tf[idx].dfunc)(g[0].sval, g[1].dval, g[2].ival);
                        break;
                    case tipoDouble: // func_dfsdd
                        eax.dval=(*tf[idx].dfunc)(g[0].sval, g[1].dval, g[2].dval);
                        break;
                    case tipoStr: // func_dfsds
                        eax.dval=(*tf[idx].dfunc)(g[0].sval, g[1].dval, g[2].sval);
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoStr: // func_dfss?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_dfssi
                        eax.dval=(*tf[idx].dfunc)(g[0].sval, g[1].sval, g[2].ival);
                        break;
                    case tipoDouble: // func_dfssd
                        eax.dval=(*tf[idx].dfunc)(g[0].sval, g[1].sval, g[2].dval);
                        break;
                    case tipoStr: // func_dfsss
                        eax.dval=(*tf[idx].dfunc)(g[0].sval, g[1].sval, g[2].sval);
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                default:
                    fprintf(stderr,"Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            default:
                fprintf(stderr,"Unknow type of arg 1\n");
                exit(1);
            } //double switch g[0]
            break;

        case tipoStr: // func_sf???
            eax.tipo=tipoStr;
            switch (g[0].tipo)
            {
            case tipoInt: // func_sfi??
                switch (g[1].tipo)
                {
                case tipoInt: // func_sfii?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_sfiii
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0].ival, g[1].ival, g[2].ival));
                        break;
                    case tipoDouble: // func_sfiid
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0].ival, g[1].ival, g[2].dval));
                        break;
                    case tipoStr: // func_sfiis
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0].ival, g[1].ival, g[2].sval));
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoDouble: // func_sfid?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_sfidi
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0].ival, g[1].dval, g[2].ival));
                        break;
                    case tipoDouble: // func_sfidd
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0].ival, g[1].dval, g[2].dval));
                        break;
                    case tipoStr: // func_sfids
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0].ival, g[1].dval, g[2].sval));
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoStr: // func_sfis?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_sfisi
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0].ival, g[1].sval, g[2].ival));
                        break;
                    case tipoDouble: // func_sfisd
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0].ival, g[1].sval, g[2].dval));
                        break;
                    case tipoStr: // func_sfiss
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0].ival, g[1].sval, g[2].sval));
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                default:
                    fprintf(stderr,"Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoDouble: // func_sfd??
                switch (g[1].tipo)
                {
                case tipoInt: // func_sfdi?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_sfdii
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0].dval, g[1].ival, g[2].ival));
                        break;
                    case tipoDouble: // func_sfdid
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0].dval, g[1].ival, g[2].dval));
                        break;
                    case tipoStr: // func_sfdis
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0].dval, g[1].ival, g[2].sval));
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoDouble: // func_sfdd?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_sfddi
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0].dval, g[1].dval, g[2].ival));
                        break;
                    case tipoDouble: // func_sfddd
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0].dval, g[1].dval, g[2].dval));
                        break;
                    case tipoStr: // func_sfdds
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0].dval, g[1].dval, g[2].sval));
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoStr: // func_sfds?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_sfddi
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0].dval, g[1].sval, g[2].ival));
                        break;
                    case tipoDouble: // func_sfddd
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0].dval, g[1].sval, g[2].dval));
                        break;
                    case tipoStr: // func_sfdds
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0].dval, g[1].sval, g[2].sval));
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                default:
                    fprintf(stderr,"Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            case tipoStr: //func_sfs??
                switch (g[1].tipo)
                {
                case tipoInt: // func_sfsi?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_sfsii
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0].sval, g[1].ival, g[2].ival));
                        break;
                    case tipoDouble: // func_sfsid
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0].sval, g[1].ival, g[2].dval));
                        break;
                    case tipoStr: // func_sfsis
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0].sval, g[1].ival, g[2].sval));
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoDouble: // func_sfsd?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_sfsdi
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0].sval, g[1].dval, g[2].ival));
                        break;
                    case tipoDouble: // func_sfsdd
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0].sval, g[1].dval, g[2].dval));
                        break;
                    case tipoStr: // func_sfsds
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0].sval, g[1].dval, g[2].sval));
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                case tipoStr: // func_sfss?
                    switch (g[2].tipo)
                    {
                    case tipoInt: // func_sfssi
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0].sval, g[1].sval, g[2].ival));
                        break;
                    case tipoDouble: // func_sfssd
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0].sval, g[1].sval, g[2].dval));
                        break;
                    case tipoStr: // func_sfsss
                        strcpy(eax.sval, (*tf[idx].sfunc)(g[0].sval, g[1].sval, g[2].sval));
                        break;
                    default:
                        fprintf(stderr,"Unknow type of arg 3\n");
                        exit(1);
                    }
                    break;
                default:
                    fprintf(stderr,"Unknow type of arg 2\n");
                    exit(1);
                }
                break;
            default:
                fprintf(stderr,"Unknow type of arg 1\n");
                exit(1);
            } //string switch g[0]
            break;
        default:
            fprintf(stderr,"Unknow return type\n");
            exit(1);
        } //switch tipoRet

}

int main(void)
{
    superTipo i, d, s, r, p;
    printf("Compilado em %s as %s\n", __DATE__, __TIME__);

    loadi(2, NULL, &i);
    loadd(2, NULL, &d);
    loads("\n!\nMeu printf deu %d\n!\n", NULL, &s);
    loadfunc(tipoVoid,   (void *)func_vfv, "func_vfv", &tf[0], 0);

    loadfunc(tipoVoid,   (void *)func_vfd, "func_vfd", &tf[1], 1);
    loadfunc(tipoInt,    (void *)func_ifd, "func_ifd", &tf[2], 1); /* int (*ifunc)(); */
    loadfunc(tipoDouble, (void *)func_dfd, "func_dfs", &tf[3], 1);
    loadfunc(tipoStr,    (void *)func_sfs, "func_sfi", &tf[4], 1);

    loadfunc(tipoInt,    (void *)func_ifi, "func_ifi", &tf[5], 1);  /* int (*ifunc)(); */

    loadfunc(tipoVoid,   (void *)func_vfii, "func_vfii", &tf[6], 2);
    loadfunc(tipoInt,    (void *)func_ifdi, "func_ifdi", &tf[7], 2);  /* int (*ifunc)(); */
    loadfunc(tipoDouble, (void *)func_dfsi, "func_dfsi", &tf[8], 2);
    loadfunc(tipoStr,    (void *)func_sfsi, "func_sfsi", &tf[9], 2);

    loadfunc(tipoVoid,   (void *)func_vfid, "func_vfid", &tf[10], 2);
    loadfunc(tipoInt,    (void *)func_ifdd, "func_ifdd", &tf[11], 2);  /* int (*ifunc)(); */
    loadfunc(tipoDouble, (void *)func_dfsd, "func_dfsd", &tf[12], 2);
    loadfunc(tipoStr,    (void *)func_sfsd, "func_sfsd", &tf[13], 2);

    loadfunc(tipoVoid,   (void *)func_vfis, "func_vfis", &tf[14], 2);
    loadfunc(tipoInt,    (void *)func_ifds, "func_ifds", &tf[15], 2);  /* int (*ifunc)(); */
    loadfunc(tipoDouble, (void *)func_dfss, "func_dfss", &tf[16], 2);
    loadfunc(tipoStr,    (void *)func_sfss, "func_sfss", &tf[17], 2);

    loadfunc(tipoVoid,    (void *)printf, "imprima", &tf[18], 2);
    loadfunc(tipoVoid,    (void *)func_vfsi, "func_vfsi", &tf[19], 2);

/*
    int idx;
    for (idx=0; idx<MAX_TF; idx++)
        printf("idx:%d MAX_TF:%d idNome:%s\n", idx, MAX_TF, tf[idx].idNome);*/

    printf("antes de param esp: %d\n", esp.ival);
    param(i, NULL, NULL);
    printf("apos param esp: %d\n", esp.ival);
    call("func_ifi", 1, NULL);
    mov(eax, NULL, &r);
    pop(&p);
    printf("func_ifi returns: %d \n",r.ival);
    printf("apos call esp: %d\n", esp.ival);

    printf("antes: %f \n",d.dval);
    param(d, NULL, NULL);
    call("func_vfd", 1, NULL);
    mov(eax, NULL, &r);
    pop(&p);
    printf("returns: %f \n",r.dval);

    printf("antes: %d \n",i.ival);
    param(i, NULL, NULL);
    call("func_ifd", 1, NULL);
    mov(eax, NULL, &r);
    pop(&p);
    printf("returns: %d \n",r.ival);

    param(i, NULL, NULL);
    param(s, NULL, NULL);
    call("func_vfsi", 2, NULL);
    mov(eax, NULL, &r);
    pop(&p);
    pop(&p);

    /* colocar na pilha na ordem inversa */
    printf("\nantes Printf\n");
    param(i, NULL, NULL);
    param(s, NULL, NULL);
    call("imprima", 2, NULL);
    mov(eax, NULL, &r);
    pop(&p);
    pop(&p);
    printf("\ndepois Printf\n");

    printf("antes: %s \n",s.sval);
    param(s, NULL, NULL);
    param(s, NULL, NULL);
    call("func_sfss", 2, NULL);
    mov(eax, NULL, &r);
    pop(&p);
    pop(&p);
    printf("returns: %s \n",r.sval);

    r.dval=3.0;
    r.ival=3;
    printf("ifdi antes: r->d %f, r->i %d\n", r.dval, r.ival);
    param(i, NULL, NULL);
    param(d, NULL, NULL);
    call("func_ifdi", 2, NULL);
    mov(eax, NULL, &r);
    pop(&p);
    pop(&p);
    printf("func_ifdi returns ival: %d, dval: %f \n",r.ival, r.dval);

    printf("esp: %d\n", esp.ival);

    return 0;
}

