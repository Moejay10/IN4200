CC := gcc # Which Compiler to use

LIB := -lm # Which libraries to use (this is the math)

FLAGS := -Wall # Which flags to use

PROGRAMS := ex1.exe ex3.exe

.PHONY : all clean

all: $(PROGRAMS)

ex1.exe: Ex1.c Functions.c
	$(CC) $(FLAGS) Ex1.c Functions.c $(LIB) -o ex1.exe


ex3.exe: Ex3.c Functions.c
		$(CC) $(FLAGS)  Ex3.c Functions.c $(LIB) -o ex3.exe

clean :
		rm -f *.o $(PROGRAMS)
