#makefile for cel
OBJ= io.o eval.o list.o cel_lib.o parse.o gc.o celdebug.o


repl:$(OBJ) repl.o 
	gcc $^ -o repl -rdynamic

debug:
	gcc io.c eval.c list.c repl.c cel_lib.c parse.c -g -o debugrepl

test:$(OBJ) iotest.o
	gcc $^ -o test

%.o:%.c
	gcc $^ -c -o $@

clean:
	rm *.o *.exe
