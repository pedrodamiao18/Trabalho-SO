CC = cc
FLAGS = -c -Wall
LIBS = -lm
OBS = main.o process.o scheduler.o simulator.o 

all : simulation

main.o : simulation.h main.c
	$(CC) $(FLAGS) main.c

process.o : simulation.h process.c
	$(CC) $(FLAGS) process.c

scheduler.o : simulation.h scheduler.c
	$(CC) $(FLAGS) scheduler.c

simulator.o : simulation.h simulator.c
	$(CC) $(FLAGS) simulator.c

simulation : $(OBS)
	$(CC) -o simulation $(OBS) $(LIBS)

clean limpar:
	rm -f simulation *.o
	rm -f *~
	echo "Remover: Ficheiros executáveis, objetos e temporários."
