# Compila o compilador Portugol usando lex e yacc,
# e opcionalmente gera o .asm.c e o .bin
# a partir do fonte .ptg usando o novo compilador gerado.
#
#/*
#    arquivo: makefile
#    Autor: Ruben Carlo Benante
#    Email: benante@gmail.com
#    Data: 23/04/2009
#    Modificado: 21/03/2011
#    Versao: Portugol v3r
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
#Para compilar usando o portugol (ou compilar e executar):
#
# inicia os seguintes processos:
#      portugol.bin teste.ptg teste.asm.c                  (gera teste.asm.c)
#      gcc -x c teste.asm.c -o teste.bin -lm               (gera teste.bin)
#
#entrada:
#           teste1 (arquivo em linguagem portugol extensão .ptg)
#
#saida:
#           teste1.qdp (arquivo em linguagem de quadruplas)
#           teste1.bin (arquivo executavel)
#
######################################
#echo --- Running! ---------------- ./$2.bin
#./$2.bin
######################################

.PHONY : clean cleanall cleanptg run all teste

#portugol.bin : lex.yy.c y.tab.c portugol.c
portugol.bin : lex.yy.c y.tab.c portugol.c portugol.h y.tab.h
#portugol.bin : lex.yy.o y.tab.o portugol.o
	@echo --- gcc -------------------------------------------------
	gcc y.tab.c lex.yy.c portugol.c -o portugol.bin -lm -ly
#	gcc y.tab.o lex.yy.o portugol.o -o portugol.bin -lm -ly

#portugol.o: portugol.c portugol.h y.tab.h
#	@echo --- gcc -c ----------------------------------------------
#	gcc portugol.c -c -o portugol.o
#
#lex.yy.o : lex.yy.c portugol.h y.tab.h
#	@echo --- gcc -c ----------------------------------------------
#	gcc lex.yy.c -c -o lex.yy.o
#
#y.tab.o: y.tab.c portugol.h
#	@echo --- gcc -c ----------------------------------------------
#	gcc y.tab.c -c -o y.tab.o

lex.yy.c : portugol.l
	@echo --- flex ------------------------------------------------
	flex portugol.l

y.tab.c y.tab.h : portugol.y
	@echo --- bison -----------------------------------------------
	bison -dy portugol.y -o y.tab.c

teste :
	@echo --- testing ---------------------------------------------
	@echo $(o)

#Portugol -----------

%.asm.c : %.ptg portugol.bin
	@echo --- portugol --------------------------------------------
	./portugol.bin $< $@

%.bin : %.asm.c
	@echo --- gcc -------------------------------------------------
	gcc -x c $< -o $@ -lm

run : $(o).bin
	@echo --- running! --------------------------------------------
	./$(o).bin

all : $(o).bin

clean:
	rm lex.yy.c y.tab.c y.tab.h portugol.bin

cleanall:
	-rm lex.yy.c y.tab.c y.tab.h *.bin *.o

cleanptg:
	rm *.bin *.asm.c

