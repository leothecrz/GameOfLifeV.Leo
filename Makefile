
CC=gcc
FLAGS= -lstdc++ -lSDL2


all: main

main: main.o
	$(CC) main.o -o RUN $(FLAGS)
	@rm *.o

debug:
	$(CC) main.c -g $(FLAGS) -o DEBUG
