CC := gcc # Which Compiler to use

LIB := -lm # Which libraries to use

FLAGS := -g #-Wall # Which flags to use (Warnings)

PROGRAMS := ex2.exe ex3.exe

.PHONY : all clean

all: $(PROGRAMS)

ex2.exe: Exercise2.c
	$(CC) $(FLAGS) Exercise2.c -fopenmp $(LIB) -o ex2.exe

ex3.exe: Exercise2.c
	$(CC) $(FLAGS) Exercise3.c -fopenmp $(LIB) -o ex3.exe


clean :
		rm -f *.o $(PROGRAMS)
