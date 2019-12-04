ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: main.o shell.o
	$(CC) -o program main.o shell.o

main.o: main.c shell.h
	$(CC) -c  main.c

shell.o: shell.c shell.h
	$(CC) -c  shell.c

run:
	./program

clean:
	rm*.o
	rm*~
