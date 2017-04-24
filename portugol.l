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
inicio   { return INICIO; }    /* { */
fim      { return FIM; }       /* } */
se       { return SE; }        /* if */
entao    { return ENTAO; }     /* then_separator */
senao    { return SENAO; }     /* else */
enquanto { return ENQUANTO; }  /* while */
aborte   { return ABORTE; }    /* exit(1) */
para     { return PARA; }      /* for */
int      { return INT; }       /* int */
real     { return REAL; }      /* float */
texto    { return TEXTO; }     /*  char* */
ponteiro { return PONT; }      /* pointer */
importe  { return IMPORTE; }   /* import double sqrt ( double ) */
define   { return DEFINE; }    /* define int funcId ( int argId ) */
#debug   { return DEBUG; }     /* pre-processor directive */
_ARVORE  { return ARVORE; }    /* turn on print-syntatic-tree option */
_TABELA  { return TABELA; }    /* turn on print-symbol-table option */

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
{LE}({LE}|{DI}|_)*          {    tabelaSimb *ps = achaId(yytext);
                                yylval.pSimb = ps;
                                return IDENT;
                            }

 /* Constantes */
{DI}+"."{DI}+([eE][+-]?{DI}+)?   {  tabelaSimb *ps = achaFloat(atof(yytext));
                                    yylval.pSimb = ps;
                                    return REALCON;
                                 }

{DI}+       {  tabelaSimb *ps = achaInt(atoi(yytext));
               yylval.pSimb = ps;
               return INTCON;
            }

{FO}        {  tabelaSimb *ps = achaStr(yytext);
               yylval.pSimb = ps;
               yylval.pSimb->formatadoSval = 1;
               return TEXTOCON;
            }

{TX}        {  tabelaSimb *ps = achaStr(yytext);
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
        fprintf(yyout, "Compilador PORTUGOL versao 3q, por Ruben Carlo Benante (25/05/09).\n");

    //int a=max(2,3);
    addFuncVoid("imprima", (void *)printf, "printf", 2, tipoIdFuncVoid);  // void printf ( str a , int b );
    //** addFuncVoid("leia", (void *)scanf, "scanf", 0, tipoIdFuncDouble);   // void scanf ( float &a ); real leia ( void );
//**addFuncInt("leia", scanf, "scanf", 0, tipoIdFuncDouble);      // int scanf ( float &a ); real leia ( void );
addFuncInt2("leia", scanf, "scanf", 0, tipoIdFuncDouble);      // bug2-----------int scanf ( float &a ); real leia ( void );
//    addFuncVoid("leiaI", (void *)scanf, "scanf", 0);   // void scanf ( float &a ); int leiaI ( void );
//    addFuncVoid("leiaR", (void *)scanf, "scanf", 0);   // void scanf ( float &a ); real leiaR ( void );
//    addFuncVoid("leiaT", (void *)scanf, "scanf", 0);   // void scanf ( float &a ); texto leiaT ( void );
    addFuncVoid("saia", (void *)exit, "exit", 1, tipoIdFuncVoid);        // void exit ( int a );
    addFuncDouble("raiz", sqrt, "sqrt", 1, tipoIdFuncDouble);              // float sqrt ( float a );
    addFuncDouble("exp", exp, "exp", 1, tipoIdFuncDouble);
    addFuncDouble("elevado", pow, "pow", 2, tipoIdFuncDouble);
    addConStr("?");
    if(yyparse()) //falhou
    {
        fprintf(stderr, "//    Falha! Programa em Portugol nao compilado.\n\n");
        if(yyout!=stdout)
            fprintf(yyout, "//    Falha! Programa em Portugol nao compilado.\n\n");
    return 1;
    }

    return 0;
}

void addConStr(char *s)
{
    tabelaSimb *ps = achaStr(s);
}

void addFuncDouble(char *id, double (*func)(), char *idF, int nump, int tp)
{
    tabelaSimb *ps = achaId(id); //acha ou cria na tabela de simbolos
    ps->dfunc =  func;
    ps->idFunc = strdup(idF);
    ps->numPar = nump;
    ps->tipoRetNovo = tp;

    ps->tipoD = tipoIdFuncDouble;
    ps->idx = geraTF();
}

//bug2--------------
//addFuncInt("leia", (void *)scanf, "scanf", 0, tipoIdFuncDouble);      // int scanf ( float &a ); real leia ( void );
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

void addFuncVoid(char *id, void (*func)(), char *idF, int nump, int tp)
{
    tabelaSimb *ps = achaId(id); //idName
    ps->vfunc =  func;
    ps->idFunc = strdup(idF);
    ps->numPar = nump;
    ps->tipoRetNovo = tp;

    ps->tipoD = tipoIdFuncVoid;
    ps->idx = geraTF();
}
