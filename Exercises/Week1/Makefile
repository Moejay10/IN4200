ex1a:
	gcc Ex1a.c -o ex1a

ex1b:

	gcc Ex1b.c -o ex1b

ex1c:
	gcc Ex1c.c -o ex1c

ex1c_optimised:
	gcc -O3 Ex1c.c -o ex1c_optimised

ex1d:
	gcc Ex1d.c -o ex1d

ex2a:
	gcc Ex2a.c Ex2a_functions.c -o ex2a -lm


ex3:
	gcc Ex3.c -o ex3

all:
	make ex1a ex1b ex1c ex1c_optimised ex1d ex2a ex3

remove:
	ls | grep -v "\." | grep -v Makefile |xargs rm
