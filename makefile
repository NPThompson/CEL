#makefile for cel
OBJ= io.o eval.o list.o repl.o cel_lib.o parse.o


repl:$(OBJ)
	gcc $^ -o repl

%.o:%.c
	gcc $^ -c -o $@

clean:
	rm *.o *.exe
