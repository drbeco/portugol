#!/bin/bash
# Compila com Portugol v2q e gera .asm.c e .asm.bin
#/*
#    Autor: Ruben Carlo Benante
#    Email: benante@gmail.com
#    Data: 23/04/2009
#*/
#
# Exemplo:
# ./ptg-v1q.sh teste1
#
# entrada:
#          teste1.ptg
#          arquivo em linguagem portugol
#
# saida:
#        teste1.asm.c
#        arquivo em quadruplas
#
#        teste1.asm.bin
#        arquivo executavel

echo portugol $1.ptg $1.asm.c
./portugol-v2q.bin $1.ptg $1.asm.c
echo gcc $1.asm.c -o $1.asm.bin
gcc $1.asm.c -o $1.asm.bin
echo ./$1.asm.bin
./$1.asm.bin

