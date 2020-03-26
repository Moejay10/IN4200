#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h> // fabs
#include <time.h>


void alloc2DMatrix(char ***A, int N);
void allocVector(int **a, int N);

void construct2DMatrix(char ***A, int N);

void free2D(char **A);
void free1D(int *a);

void WriteMatrixtoFile(char **A, int N);
void WriteVectortoFile(int *a, int *b, int N);
void WriteVectortoFile2(int *a, int *b, int N_rows, int N_links);


void printMatrixToTerminal(char **A, int N);
void printVectorToTerminal(int *a, int N);
void printVectorToTerminal2(int *a, int *b, int N_rows, int N_links);


void sort_numbers(int *a, int *b, int n, int N);
int factorial(int n);
void counter(int *temp_num_involvements, int *num_involvements, int temp, int N);


#endif // FUNCTIONS_H
