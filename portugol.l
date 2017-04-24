%{
/*
    Compilador PORTUGOL v.3q
    Autor: Ruben Carlo Benante
    Email: benante@gmail.com
    Data criação: 23/04/2009
    Data modificação: 25/05/2009
*/

  #include <math.h>
  #include <stdlib.h>
  #include "portugol.h"
  #include "y.tab.h"

  extern int scanf(const char *, ...); //bug2-----------
  FILE *fhead=NULL;
%}


LE [A-Za-zÁÉÍÓÚÀÈÌÒÙÃẼĨÕŨÂÊÎÔÛÄËÏÖÜÇÑáéíóúàèìòùãẽĩõũâêîôûäëïöüçñºª¹²³]
DI [0-9]
BT ("\\"[^%\n])
AS "\""
PA "%%"
PL ("%"({DI}*\.{DI}+)?(d|f|s))
P1 "%"
SY [^"%\\\n]
TU ({LE}|{DI}|{PA}|{BT}|{SY})
TT ({LE}|{DI}|{P1}|{BT}|{SY})
FO ({AS}{TU}*{PL}{TU}*{AS})
TX ({AS}{TT}*{AS})

%%

 /* comandos reservados */
principal { return PRINCIPAL; } /* main */
inicio    { return INICIO; }    /* { */
fim       { return FIM; }       /* } */
se        { return SE; }        /* if */
entao     { return ENTAO; }     /* then_separator */
senao     { return SENAO; }     /* else */
enquanto  { return ENQUANTO; }  /* while */
aborte    { return ABORTE; }    /* exit(1) */
para      { return PARA; }      /* for */
inteiro   { return INT; }       /* int */
real      { return REAL; }      /* float */
texto     { return TEXTO; }     /* char* */
nada      { return NADA; }      /* void */
ponteiro  { return PONT; }      /* pointer */
externa   { return EXTERNA; }   /* externa real sqrt ( real ) */
define    { return DEFINE; }    /* define uma macro */
retorne   { return RETORNE; }   /* return */
#debug    { return DEBUG; }     /* pre-processor directive */
_ARVORE   { return ARVORE; }    /* turn on print-syntatic-tree option */
_TABELA   { return TABELA; }    /* turn on print-symbol-table option */
 /*funcao   { return FUNCAO; }     define uma funcao: tipoRet funcId ( tipoArg1 argId1, tipoArg2 argId2 ) */

 /* Pontuacao */
"++"    { return INC; }
"--"    { return DEC; }
">="    { return GE; }
"<="    { return LE; }
"=="    { return EQ; }
"!="    { return NE; }
">"     { return GT; }
"<"     { return LT; }
"e"     { return E; }
"ou"    { return OU; }
"nao"   { return NAO; }

[-+*/=();%,&]    { return yytext[0]; }

 /* Identificadores */
 /* [a-zA-Z][a-zA-Z0-9_]*      {    tabelaSimb *ps = achaId(yytext); */

{LE}({LE}|{DI}|_)*          {   /* identificador: letra pode ser seguida de letra|digito|sublinhado */
                                tabelaSimb *ps = achaId(yytext);
                                yylval.pSimb = ps;
                                return IDENT;
                            }

 /* Constantes */
{DI}+"."{DI}+([eE][+-]?{DI}+)?   {  /* double */
                                    tabelaSimb *ps = achaDouble(atof(yytext));
                                    yylval.pSimb = ps;
                                    return REALCON;
                                 }

{DI}+       {  /* inteiro */
               tabelaSimb *ps = achaInt(atoi(yytext));
               yylval.pSimb = ps;
               return INTCON;
            }

{FO}        {  /* formato */
               tabelaSimb *ps = achaStr(yytext);
               yylval.pSimb = ps;
               yylval.pSimb->formatadoSval = 1;
               return TEXTOCON;
            }

{TX}        {  /* string */
               tabelaSimb *ps = achaStr(yytext);
               yylval.pSimb = ps;
               yylval.pSimb->formatadoSval = 0;
               return TEXTOCON;
            }

 /* espacos e comentarios */
\n              { lineno++; }
[ \t\r]+        ; /* faz nada */
"//".*          ; /* "//".*\n ; */

 /* Outras coisas */
.           { yyerror("caracter invalido"); }

%%

int yywrap(void)
{
  return 1;
}

void yyerror(char *s)
{
    fprintf(stderr, "//    Linha:%d. Erro: %s Token: '%s'.\n", lineno, s, yytext);
}

int main(int ac, char **av)
{
    int i;

    yyin=stdin;
    yyout=stdout;
    fhead=stdout;
    if(ac>2) //tem arquivo de saida
    {
        if((yyout = fopen(av[2],"w"))==NULL)
        {
            fprintf(stderr, "Nao consigo abrir arquivo %s para gravacao.\n", av[2]);
            exit(1);
        }
        if((fhead = fopen("saida.h","w"))==NULL)
        {
            fprintf(stderr, "Nao consigo abrir arquivo saida.h para gravacao.\n");
            exit(1);
        }
    }

    if(ac>1)
    {
        if((yyin = fopen(av[1],"r"))==NULL)
        {
            fprintf(stderr, "Nao consigo abrir arquivo %s para leitura.\n", av[1]);
            exit(1);
        }
    }
    else
        fprintf(yyout, "Compilador PORTUGOL versao 3r, por Ruben Carlo Benante (25/05/09, 10/03/11).\n");

    //int a=max(2,3);

/* comentato 10/03/11, estava ok esta:
// void printf ( str a , int b );
addFuncVoid("imprima", (void *)printf, "printf", 2, tipoIdFuncVoid);
*/

    //** addFuncVoid("leia", (void *)scanf, "scanf", 0, tipoIdFuncDouble);   // void scanf ( float &a ); real leia ( void );
    //**addFuncInt("leia", scanf, "scanf", 0, tipoIdFuncDouble);      // int scanf ( float &a ); real leia ( void );

/*  comentato 10/03/11:  estava com problemas
// bug2-----------int scanf ( float &a ); real leia ( void );
addFuncInt2("leia", scanf, "scanf", 0, tipoIdFuncDouble);
*/

    //    addFuncVoid("leiaI", (void *)scanf, "scanf", 0);   // void scanf ( float &a ); int leiaI ( void );
    //    addFuncVoid("leiaR", (void *)scanf, "scanf", 0);   // void scanf ( float &a ); real leiaR ( void );
    //    addFuncVoid("leiaT", (void *)scanf, "scanf", 0);   // void scanf ( float &a ); texto leiaT ( void );

/*  comentato 10/03/11, estava ok esta:
// void exit ( int a );
addFuncVoid("saia", (void *)exit, "exit", 1, tipoIdFuncVoid);
troquei por retornar inteiro
*/

//addFunc("saia", (void *)exit, "exit" /*similar em c*/, 1/*num param*/, tipoIdFuncInt /*tipo de retorno e na TS*/, tipoConInt /*tipo arg*/);

/* comentato 10/03/11, estava ok esta:
addFuncDouble("raiz", sqrt, "sqrt", 1, tipoIdFuncDouble);              // float sqrt ( float a );
    addFuncDouble("exp", exp, "exp", 1, tipoIdFuncDouble);
    addFuncDouble("elevado", pow, "pow", 2, tipoIdFuncDouble);
    addConStr("?");
*/
    if(yyparse()) //falhou
    {
        fprintf(stderr, "//    Falha! Programa em Portugol nao compilado.\n\n");
        if(yyout!=stdout)
            fprintf(yyout, "//    Falha! Programa em Portugol nao compilado.\n\n");
    return 1;
    }

    return 0;
}

// void addConStr(char *s)
// {
//     tabelaSimb *ps = achaStr(s);
// }

//addFunc("saia", (void *)exit, "exit" /*similar em c*/, 1/*num param*/, tipoIdFuncInt /*tipo de retorno e na TS*/, tipoConInt /*tipo arg*/);
//adiciona, substitui, ou cria! Criado por achaId
tabelaSimb *addFunc(char *id, void *func, char *idF /*similar em c*/, int nump, int tret /*tipo retorno e TS*/, int *ta /*tipo arg*/)
{
    int i;
    tabelaSimb *ps = achaId(id); //acha ou cria na tabela de simbolos
    if(tret==tipoIdFuncDouble)
    {
      if(func!=NULL)
        ps->dfunc =  func;
      ps->tipoD = tipoIdFuncDouble;
      ps->tipoRetNovo = tipoIdFuncDouble;
    }
    else
      if(tret==tipoIdFuncInt)
      {
        if(func!=NULL)
          ps->ifunc =  func;
        ps->tipoD = tipoIdFuncInt;
        ps->tipoRetNovo = tipoIdFuncInt;
      }
      else
        if(tret==tipoIdFuncVoid)
        {
          if(func!=NULL)
            ps->vfunc =  func;
          ps->tipoD = tipoIdFuncVoid;
          ps->tipoRetNovo = tipoIdFuncVoid;
        }
        else
          if(tret==tipoIdFuncStr)
          {
            if(func!=NULL)
              ps->sfunc =  func;
            ps->tipoD = tipoIdFuncStr;
            ps->tipoRetNovo = tipoIdFuncStr;
          }
          else
          {
            fprintf(stderr, "//    Falha! Programa em Portugol nao compilado. Tipo de funcao desconhecido.\n\n");
            exit(1);
          }

    if(idF!=NULL)
      ps->idFunc = strdup(idF);
    else
      ps->idFunc = NULL;
    ps->numPar = nump;
    for(i=0; i<nump; i++)
        ps->tipoParam[i]=ta[i];
    ps->idx = geraTF();
    return ps;
}

// void addFuncDouble(char *id, double (*func)(), char *idF, int nump, int tp)
// {
//     tabelaSimb *ps = achaId(id); //acha ou cria na tabela de simbolos
//     ps->dfunc =  func;
//     ps->idFunc = strdup(idF);
//     ps->numPar = nump;
//     ps->tipoRetNovo = tp;
//
//     ps->tipoD = tipoIdFuncDouble;
//     ps->idx = geraTF();
// }


//bug2--------------
//addFuncInt("leia", (void *)scanf, "scanf", 0, tipoIdFuncDouble);      // int scanf ( float &a ); real leia ( void );
/* comentato 10/03/11, estava com problemas:
void addFuncInt2(char *id, int (*func)(const char *, ...), char *idF, int nump, int tp)
{
    tabelaSimb *ps = achaId(id);
    ps->i2func =  func;
    ps->idFunc = strdup(idF);
    ps->numPar = nump;
    ps->tipoRetNovo = tp;

    ps->tipoD = tipoIdFuncInt;
    ps->idx = geraTF();
}
*/

// void addFuncVoid(char *id, void (*func)(), char *idF, int nump, int tp)
// {
//     tabelaSimb *ps = achaId(id); //idName
//     ps->vfunc =  func;
//     ps->idFunc = strdup(idF);
//     ps->numPar = nump;
//     ps->tipoRetNovo = tp;
//
//     ps->tipoD = tipoIdFuncVoid;
//     ps->idx = geraTF();
// }
