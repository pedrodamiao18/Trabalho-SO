# A Simple Makefile for ProbSched
#
# Variáveis: compilador, flags, bibliotecas, e os ficheiros objeto
#
CC = cc
FLAGS = -c -Wall
LIBS = -lm
OBS = main.o process.o scheduler.o simulator.o utils.o

# Alvo por defeito
all : prob

main.o : prob.h main.c
	$(CC) $(FLAGS) main.c

process.o : prob.h process.c
	$(CC) $(FLAGS) process.c

scheduler.o : prob.h scheduler.c
	$(CC) $(FLAGS) scheduler.c

simulator.o : prob.h simulator.c
	$(CC) $(FLAGS) simulator.c

utils.o : prob.h utils.c
	$(CC) $(FLAGS) utils.c

prob : $(OBS)
	$(CC) -o prob $(OBS) $(LIBS)

clean limpar:
	rm -f prob *.o
	rm -f *~
	echo "Remover: Ficheiros executáveis, objetos e temporários."
