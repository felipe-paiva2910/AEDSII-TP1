all: main.o tp1.o
	gcc main.o tp1.o -o tp1
main.o : main.c
	gcc -c main.c
tp1.o: tp1.c tp1.h
	gcc -c tp1.c
