CC := gcc # Which Compiler to use

LIB := -lm -fopenmp # Which libraries to use (this is the math)

FLAGS := -Wall # Which flags to use

PROGRAMS := program.exe

.PHONY : all clean

all: $(PROGRAMS)

program.exe: main.c functions.c
	$(CC) $(FLAGS) main.c functions.c $(LIB) -o program.exe


clean :
		rm -f *.o $(PROGRAMS)
