%{
/*
    Compilador PORTUGOL v.2q
    Autor: Ruben Carlo Benante
    Email: benante@gmail.com
    Data criação: 23/04/2009
    Data modificação: 24/05/2009
*/

  #include <math.h>
  #include <stdlib.h>
  #include "portugol.h"
  #include "y.tab.h"

  FILE *fhead=NULL;
%}

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
importe  { return IMPORTE; }   /* import double sqrt ( double ) */
define   { return DEFINE; }    /* define int funcId ( int argId ) */
"#debug" { return DEBUG; }     /* pre-processor directive */
_ARVORE  { return ARVORE; }    /* turn on print-syntatic-tree option */
_TABELA   { return TABELA; }   /* turn on print-symbol-table option */

 /* funcoes reservadas */
imprima  { return IMPRIMA; }   /* printf(format,x); format=={"%d", "%.2f", "%s"} */
leia     { return LEIA; }      /* scanf("%f",&x); */
saia     { return SAIA; }      /* exit(x) */

 /* Pontuacao */
">="    { return GE; }
"<="    { return LE; }
"=="    { return EQ; }
"!="    { return NE; }
">"     { return GT; }
"<"     { return LT; }
"e"     { return E; }
"ou"    { return OU; }
"nao"   { return NAO; }

[-+*/=();%]    { return yytext[0]; }

 /* Identificadores */
[a-zA-Z][a-zA-Z0-9_]*      {    tabelaSimb *ps = achaId(yytext);
                                yylval.pSimb = ps;
                                return IDENT;
                            }

 /* Constantes */
[0-9]+"."[0-9]+([eE][+-]?[0-9]+)?   {  tabelaSimb *ps = achaFloat(atof(yytext));
                                       yylval.pSimb = ps;
                                       return REALCON;
                                    }

[0-9]+                { tabelaSimb *ps = achaInt(atoi(yytext));
                        yylval.pSimb = ps;
                        return INTCON;
                      }

"\""[^"\n]*"\""     {  tabelaSimb *ps = achaStr(yytext);
                       yylval.pSimb = ps;
                       return TEXTOCON;
                    }

 /* espacos e comentarios */
\n              { lineno++; }
[ \t\r]+        ; /* do nothing */
"//".*          ; /* one-line comments */

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
        fprintf(yyout, "Compilador PORTUGOL versao 2q, por Ruben Carlo Benante (24/05/09).\n");

    addFuncVoid("imprima", (void *)printf, "printf");
    addFuncVoid("leia", (void *)scanf, "scanf");
    addFuncVoid("saia", (void *)exit, "exit");
    addFuncDouble("raiz", sqrt, "sqrt");
    addFuncDouble("exp", exp, "exp");
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

void addFuncDouble(char *id, double (*func)(), char *idF)
{
    tabelaSimb *ps = achaId(id); //ps->idNome = strdup(nome);
    ps->dfunc =  func;
    ps->tipoD = tipoIdFuncDouble;
    ps->idx = geraTF();
    ps->idFunc = strdup(idF);
}

void addFuncVoid(char *id, void (*func)(), char *idF)
{
    tabelaSimb *ps = achaId(id); //idName
    ps->vfunc =  func;
    ps->tipoD = tipoIdFuncVoid;
    ps->idx = geraTF();
    ps->idFunc = strdup(idF);
}
