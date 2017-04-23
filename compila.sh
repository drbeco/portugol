#!/bin/bash
# Compila o Portugol1, com lex e yacc
#/*
#    Compilador PORTUGOL v.1.0
#    Autor: Ruben Carlo Benante
#    Email: benante@gmail.com
#    Data: 23/04/2009
#*/

flex $1.l
yacc -d $1.y
gcc -o $1.bin y.tab.c lex.yy.c $1.c
#./$1.bin teste1.ptg > teste1.c
#gcc -o teste1.bin teste1.c
#./teste1.bin
