CC = cc
CFLAGS = -Wall
LIBS=-lm
OBJ =

all:

main.o : libs.h main.c
        $(CC) $(FLAGS) main.c

clean:
        # rm -f soshell *.o
        rm -f *~
        echo "Remover: Ficheiros executáveis, objetos e temporários."
