#!/bin/bash
# Compila arq com lex e yacc (portugol v2q)
#/*
#    Autor: Ruben Carlo Benante
#    Email: benante@gmail.com
#    Data: 23/04/2009
#    Modificado em: 24/05/2009
#*/
#
# Exemplo:
# ./flexyacc portugol teste
#
# inicia os seguintes processos:
#      flex portugol.l
#      yacc -d portugol.y
#      gcc y.tab.c lex.yy.c portugol.c -o portugol.bin
#
# entrada:
#          portugol.l (arquivo em linguagem lex, analisador lexico)
#          portugol.y (arquivo em linguagem yacc, analisador sintatico)
#          portugol.c (arquivo em linguagem c, gerador de codigo)
#
# saida:
#        lex.yy.c (saida do lex, em linguagem c)
#        y.tab.c  (saida do yacc, em linguagem c)
#        y.tab.h  (saida do yacc, definicoes da linguagem portugol)
#        portugol.bin (saida do gcc, arquivo executavel, finalmente o compilador portugol)
#
# Para compilar um fonte.ptg veja abaixo.

echo --- flex -------------------- flex $1.l
flex $1.l
echo --- bison ------------------- bison -dy $1.y
#yacc -d $1.y
bison -dy $1.y
echo --- gcc --------------------- gcc y.tab.c lex.yy.c $1.c -o $1.bin -lm -ly
gcc y.tab.c lex.yy.c $1.c -o $1.bin -lm -ly

#Descomente as ultimas linhas para compilar usando o portugol (ou compilar e executar):
#
#./portugol.bin teste1.ptg teste1.c
#
#entrada:
#           teste1.ptg (arquivo em linguagem portugol)
#
#saida:
#           teste1.asm.c (arquivo em linguagem c -- ou .asm.c para quadruplas)
#           teste1.bin (arquivo executavel)
#

echo --- portugol ---------------- ./$1.bin $2.ptg  $2.asm.c
./$1.bin $2.ptg  $2.asm.c
echo --- gcc --------------------- gcc $2.asm.c -o $2.bin -lm
gcc $2.asm.c -o $2.bin -lm
echo --- Running! ---------------- ./$2.asm.bin
./$2.bin
