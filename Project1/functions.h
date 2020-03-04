#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h> // fabs
#include <time.h>
#include <omp.h> // OpenMP


void read_graph_from_file_1(char *filename, int *Nodes, int *Edges, char ***table2D);
void read_graph_from_file_2(char *filename, int *Nodes, int *Edges, int **row_ptr, int **col_idx);

void alloc2DMatrix(char ***A, int N);
void allocVector(int **a, int N);

void construct2DMatrix(char **A, int N);

void free2D(char **A);
void free1D(int *a);

void WriteMatrixtoFile(char **A, int N);
void WriteVectortoFile(int *a, int *b, int N);

void printMatrixToTerminal(char **A, int N);
void printVectorToTerminal(int *a, int *b, int N);
void printVectorToTerminal2(int **a, int **b, int N);


void sort_numbers_ascending(int *a, int *b, int N);


#endif // FUNCTIONS_H
