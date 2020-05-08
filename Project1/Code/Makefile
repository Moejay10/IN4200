CC := gcc # Which Compiler to use

LIB := -lm # Which libraries to use

FLAGS := -g #-Wall # Which flags to use (Warnings)

PROGRAMS := program.exe omp_program.exe

.PHONY : all clean

all: $(PROGRAMS)

program.exe: main.c functions.c
	$(CC) $(FLAGS) main.c functions.c -O3 $(LIB) -o program.exe

omp_program.exe: OMP_main.c functions.c
		$(CC) $(FLAGS) OMP_main.c functions.c -fopenmp -O3 $(LIB) -o omp_program.exe

clean :
		rm -f *.o $(PROGRAMS)
