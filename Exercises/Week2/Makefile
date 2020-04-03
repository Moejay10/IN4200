CC := gcc
FLAGS := -Wall
PROGRAMS := ex1.exe ex2.exe ex3.exe

.PHONY : all clean

all: $(PROGRAMS)

ex1.exe: Ex1.c
	$(CC) $(FLAGS) Ex1.c -o ex1.exe

ex2.exe: Ex2.c
		$(CC) $(FLAGS) Ex2.c -o ex2.exe

ex3.exe: Ex3.c
		$(CC) $(FLAGS) Ex3.c -o ex3.exe -lm -O3

clean :
		rm -f *.o $(PROGRAMS)
