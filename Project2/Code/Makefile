CC := gcc # Which Compiler to use

LIB := -lm # Which libraries to use

FLAGS := -g #-Wall # Which flags to use (Warnings)

PROGRAMS := program.exe mpi_program.exe

.PHONY : all clean

all: $(PROGRAMS)

program.exe: serial_main.c functions.c
	$(CC) $(FLAGS) serial_main.c functions.c $(LIB) -o program.exe

mpi_program.exe: mpi_main.c functions.c
		mpicc mpi_main.c functions.c $(LIB) -fopenmp -o mpi_program.exe

clean :
		rm -f *.o $(PROGRAMS)
