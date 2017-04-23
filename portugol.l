%{
/*
    Compilador PORTUGOL v.1.0
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
imprima { return IMPRIMA; }
inicio  { return INICIO; }
fim     { return FIM; }

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
    printf("\n  //Linha:%d Erro: %s Token: %s", lineno, s, yytext);
}

int main(int ac, char **av)
{
    int i;

    if(ac>1 && (yyin = fopen(av[1],"r"))==NULL)
    {
        perror(av[1]);
        exit(1);
    }

    if(ac>2 && (yyout = fopen(av[2],"w"))==NULL)
    {
        perror(av[2]);
        exit(1);
    }

    printf("//    Gerado pelo compilador PORTUGOL versao 1.0\n");
    printf("//    Autor: Ruben Carlo Benante\n");
    printf("//    Email: benante@gmail.com\n");
    printf("//    Data: 23/04/2009\n\n");
    printf("#include <stdio.h>\n");
    printf("#include <stdlib.h>\n\n");
    printf("float var[26] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};\n\n");
    printf("int main(void)\n");

    if(!yyparse())
        printf("\nSucesso! Programa em Portugol compilado.\n\n");
    else
    {
        printf("\n\n  printf(\"Falha! Programa em Portugol nao compilado.\\n\\n\");");
        printf("\n  //Falha! Programa em Portugol nao compilado.\n\n}//main falhou");
    }
}
