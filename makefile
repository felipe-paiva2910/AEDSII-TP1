debug:	tp1_debug

tp1:	main.o	tp1.o
	gcc	main.o	tp1.o	-o	tp1
main.o:	main.c
	gcc	-c	main.c
tp1.o:	tp1.c	tp1.h
	gcc	-c	tp1.c

tp1_debug:	maind.o	tp1d.o
	gcc	-g3	maind.o	tp1d.o	-o	tp1_debug	
maind.o:main.c
	gcc	-g3	-c	main.c	-o	maind.o
tp1d.o:	tp1.c	tp1.h
	gcc	-g3	-c	tp1.c	-o	tp1d.o
