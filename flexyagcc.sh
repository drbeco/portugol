#!/bin/bash
# Compila o compilador usando lex e yacc, e opcionalmente gera o .qdp e o .bin
# a partir do fonte .ptg usando o novo compilador gerado.
#
#/*
#    Autor: Ruben Carlo Benante
#    Email: benante@gmail.com
#    Data: 23/04/2009
#    Modificado: 25/05/2009
#    Versao: Portugol v3q
#*/
#
# Exemplo:
# ./flexyagcc portugol teste
#
# inicia os seguintes processos:
#      flex portugol.l                                   (gera lex.yy.c)
#      yacc -d portugol.y                                (gera yy.tab.c e yy.tab.h)
#      gcc y.tab.c lex.yy.c portugol.c -o portugol.bin   (gera portugol.bin)
#
# inicia opcionalmente (ultimas linhas descomentadas):
#      portugol.bin teste.ptg teste.qdp                (gera teste.qdp)
#      gcc -x c teste.qdp -o teste.bin -lm             (gera teste.bin)
#
#
# entrada:
#          portugol.l (arquivo em linguagem lex, analisador lexico)
#          portugol.y (arquivo em linguagem yacc, analisador sintatico)
#          portugol.c (arquivo em linguagem c, gerador de codigo)
# entrada opcional:
#          teste.ptg  (arquivo em linguagem portugol)
#
# saida:
#        lex.yy.c (saida do lex, em linguagem c)
#        y.tab.c  (saida do yacc, em linguagem c)
#        y.tab.h  (saida do yacc, definicoes da linguagem portugol)
#        portugol.bin (saida do gcc, arquivo executavel, finalmente o compilador portugol)
# saida opcional:
#        teste.qdp   (saida do compilador portugol, arquivo em codigo de quadruplas)
#        teste.bin   (saida do gcc, arquivo executavel, o fonte .ptg em binario)
#
# Para opcionalmente compilar um fonte.ptg veja abaixo.
######################################

echo --- flex -------------------- flex $1.l
flex $1.l
echo --- bison ------------------- bison -dy $1.y
#yacc -d $1.y
bison -dy $1.y
echo --- gcc --------------------- gcc y.tab.c lex.yy.c $1.c -o $1.bin -lm -ly
gcc y.tab.c lex.yy.c $1.c -o $1.bin -lm -ly
#-lc -lgcc

#Para compilar usando o portugol (ou compilar e executar):
#
# inicia os seguintes processos:
#      portugol.bin teste.ptg teste.qdp                  (gera teste.qdp)
#      gcc -x c teste.qdp -o teste.bin -lm               (gera teste.bin)
#
#entrada:
#           teste1 (arquivo em linguagem portugol extensão .ptg)
#
#saida:
#           teste1.qdp (arquivo em linguagem de quadruplas)
#           teste1.bin (arquivo executavel)
#
# Descomente as ultimas linhas para ativar:
######################################

echo --- portugol ---------------- ./$1.bin $2.ptg  $2.qdp
./$1.bin $2.ptg  $2.asm.c
echo --- gcc --------------------- gcc -x c $2.qdp -o $2.bin -lm
gcc -x c $2.asm.c -o $2.bin -lm
echo --- Running! ---------------- ./$2.bin
./$2.bin
