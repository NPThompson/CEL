#makefile for cel
OBJ= io.o eval.o list.o predicate.o repl.o cel_lib.o parse.o


repl:$(OBJ)
	gcc $^ -o repl

%.o:%.c
	gcc $^ -c -o $@
	
clean:
	del *.o *.exe