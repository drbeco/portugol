# Compila o compilador Portugol usando lex e yacc,
# e opcionalmente gera o .asm.c e o .bin
# a partir do fonte .ptg usando o novo compilador gerado.
#
#/*
#    arquivo: makefile
#    Autor: Ruben Carlo Benante
#    Email: ***@beco.cc
#    Data: 23/04/2009
#    Modificado: 22/03/2011
#    Versao: Portugol v3q
#*/
#
# Exemplo:
# ./flexyagcc portugol teste
#
# inicia os seguintes processos:
#      flex portugol.l                                          (gera lex.yy.c)
#      bison -dy portugol.y                                     (gera yy.tab.c e yy.tab.h)
#      gcc y.tab.c lex.yy.c portugol.c -o portugol.bin -lm -ly  (gera portugol.bin)
#
# inicia opcionalmente (ultimas linhas descomentadas):
#      portugol.bin teste.ptg teste.asm.c                (gera teste.asm.c)
#      gcc -x c teste.asm.c -o teste.bin -lm             (gera teste.bin)
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
#        teste.asm.c   (saida do compilador portugol, arquivo em codigo de quadruplas)
#        teste.bin     (saida do gcc, arquivo executavel, o fonte .ptg em binario)
#
######################################

LEX  = flex
YACC = bison
YFLAGS  = -dy
CC = gcc
#CFLAGS = -g0 -O3 -Wall
CFLAGS = -g0
OBJS = y.tab.o lex.yy.o portugol.o
DEPS =  portugol.h y.tab.h
SOURCES = y.tab.c lex.yy.c portugol.c
.PHONY : clean cleanall cleanasm run all teste

#portugol.bin : lex.yy.c y.tab.c y.tab.h portugol.c portugol.h
portugol.bin : $(SOURCES) $(DEPS) $(OBJS)
	@echo --- gcc portugol ----------------------------------------
	$(CC) $(CFLAGS) $(OBJS) -o portugol.bin -lm -ly
#	gcc lex.yy.c y.tab.c portugol.c -o portugol.bin -lm -ly
#	$(CC) $(CFLAGS) $(SOURCES) -o portugol.bin -lm -ly

%.o : %.c
	@echo --- gcc objects -----------------------------------------
	$(CC) $(CFLAGS) -c $< -o $@

# prevent built-in YACC and LEX
%.c: %.y
%.c: %.l

#portugol.tab.c y.tab.h : portugol.y
#y.tab.c y.tab.h : portugol.y
#%.c : %.y
y.tab.c y.tab.h : portugol.y
	@echo --- bison -----------------------------------------------
	$(YACC) $(YFLAGS) portugol.y

#%.c : %.l
lex.yy.c : portugol.l
	@echo --- flex ------------------------------------------------
	$(LEX) $(LFLAGS) portugol.l

teste :
	@echo --- testing ---------------------------------------------
	@echo $(o)

#Portugol -----------

%.asm.c : %.ptg portugol.bin
	@echo --- portugol --------------------------------------------
	./portugol.bin $< $@

%.bin : %.asm.c
	@echo --- gcc asm ---------------------------------------------
	$(CC) -x c $< -o $@ -lm

run : $(o).bin
	@echo --- running! --------------------------------------------
	./$(o).bin

all : $(o).bin

clean:
	-rm lex.yy.c y.tab.c y.tab.h *.o portugol.bin

cleanall:
	-rm lex.yy.c y.tab.c y.tab.h *.o *.bin

cleanasm:
	-rm *.asm.c

