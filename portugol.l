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
  //#include "portugol.tab.h"

  FILE *fhead=NULL;
  //extern int indente, escopo;

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
principal   {
                tabelaSimb *ps = achaId(yytext);
                yylval.pSimb = ps;
                return PRINCIPAL;
            } /* main */
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
"//".*          ; /* "//".*\n ; comentario de linha */

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
    //int i;

    cabecalhoMain[0]=cabecalhoMain[1]=cabecalhoMain[MAX_CABECA-1]='\0';
    indente=0;
    yyin=stdin;
    yyout=stdout;
    fhead=stdout;
    fprintf(stderr, "pass 1... (analise lexica e sintatica)\n");
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

    if(yyparse()) //falhou
    {
        fprintf(stderr, "//    Falha! Programa em Portugol nao compilado.\n\n");
        if(yyout!=stdout)
            fprintf(yyout, "//    Falha! Programa em Portugol nao compilado.\n\n");
    return 1;
    }

    return 0;
}

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
    //ps->pes=&esco; //feito por achaFuncEsc(), em pass2 / mudou para addIdEsc() tanto para funcoes como variaveis
    return ps;
}
