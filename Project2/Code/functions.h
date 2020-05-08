#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h> // fabs
#include <time.h>


void alloc2DMatrix(int ***A, int M, int N);
void allocVector(int **a, int N);

void construct2DMatrix(int ***A, int M, int N);
void random2DMatrix(int ***A, int M, int N);

void free2D(int **A);
void free1D(int *a);


void printMatrixToTerminal(int **A, int M, int N);
void printVectorToTerminal(int *a, int N);
void printVectorToTerminal2(int *a, int *b, int N_rows, int N_links);




#endif // FUNCTIONS_H
