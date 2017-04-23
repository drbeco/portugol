%{
/*
    Compilador PORTUGOL v.1q
    Autor: Ruben Carlo Benante
    Email: benante@gmail.com
    Data: 23/04/2009
*/

  #include <math.h>
  #include <stdlib.h>
  #include "portugol.h"
  #include "y.tab.h"

  void yyerror(char *s);
  int lineno = 1;
%}

%%

 /* Palavras reservadas */
se      { return SE; }
entao   { return ENTAO; }
senao   { return SENAO; }
inicio  { return INICIO; }
fim     { return FIM; }
imprima { return IMPRIMA; }

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

[-+*/=();]    { return yytext[0]; }

 /* Identificador */
[A-Z]   {   yylval.varno = yytext[0] - 'A';
            return ID;
        }

 /* Numero */
[0-9]+("."[0-9]+)? { yylval.floatval = atof(yytext);
                    return FLUTUANTE; }

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
    fprintf(stderr, "//    Linha:%d Erro: %s Token: %s\n", lineno, s, yytext);
}

int main(int ac, char **av)
{
    int i;

    yyin=stdin;
    yyout=stdout;
    if(ac>2) //tem arquivo de saida
        if((yyout = fopen(av[2],"w"))==NULL)
        {
            fprintf(stderr, "Nao consigo abrir arquivo de saida.\n");
            exit(1);
        }

    if(ac>1)
    {
        if((yyin = fopen(av[1],"r"))==NULL)
        {
            fprintf(stderr, "Nao consigo abrir arquivo de entrada.\n");
            exit(1);
        }
        fprintf(yyout, "//    Gerado pelo compilador PORTUGOL versao 1q\n");
        fprintf(yyout, "//    Autor: Ruben Carlo Benante\n");
        fprintf(yyout, "//    Email: benante@gmail.com\n");
        fprintf(yyout, "//    Data: 23/04/2009\n\n");
        fprintf(yyout, "#include \"quadruplas.h\"\n\n");
        fprintf(yyout, "int main(void)\n");
    }
    else
        fprintf(yyout, "Compilador PORTUGOL versao 1q, by Ruben Carlo Benante.\n");

    if(yyparse()) //falhou
    {
        fprintf(stderr, "//    Falha! Programa em Portugol nao compilado.\n\n");
        if(yyout!=stdout)
            fprintf(yyout, "//    Falha! Programa em Portugol nao compilado.\n\n");
    return 1;
    }

    //fprintf(stderr, "\n//    Sucesso! Programa em Portugol compilado.\n\n");
    return 0;
}
