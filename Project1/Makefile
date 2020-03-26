CC := gcc # Which Compiler to use

LIB := -lm # Which libraries to use
LIB1 := -lm -fopenmp # Which libraries to use

FLAGS := -Wall -g # Which flags to use (Warnings)

PROGRAMS := program.exe omp_program.exe

.PHONY : all clean

all: $(PROGRAMS)

program.exe: main.c functions.c
	$(CC) $(FLAGS) main.c functions.c $(LIB) -o program.exe

omp_program.exe: OMP_main.c functions.c
		$(CC) $(FLAGS) OMP_main.c functions.c $(LIB1) -o omp_program.exe

clean :
		rm -f *.o $(PROGRAMS)
