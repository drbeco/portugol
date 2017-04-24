#!/bin/bash
# Compila com Portugol e gera .qdp e .bin
#/*
#    Autor: Ruben Carlo Benante
#    Email: benante@gmail.com
#    Data: 23/04/2009
#    Modificado: 25/05/2009
#    Versao: Portugol v3q
#*/
#
# Exemplo:
# ./ptg-qdp.sh teste1
#
# inicia os seguintes processos:
#      portugol.bin teste.ptg teste.qdp                  (gera teste.qdp)
#      gcc -x c teste.qdp -o teste.bin -lm               (gera teste.bin)
#
#entrada:
#           teste1 (arquivo em linguagem portugol extensão .ptg)
#
#saida:
#           teste1.qdp (arquivo em linguagem de quadruplas .qdp)
#           teste1.bin (arquivo executavel)
#
######################################

echo --- portugol ---------------- ./portugol.bin $1.ptg  $1.qdp
./portugol.bin $1.ptg  $1.qdp
echo --- gcc --------------------- gcc $1.qdp -o $1.bin -lm
gcc $1.qdp -o $1.bin -lm
echo --- Running! ---------------- ./$1.bin
./$1.bin
