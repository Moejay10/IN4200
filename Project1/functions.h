#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h> // fabs
#include <time.h>
#include <omp.h> // OpenMP


void read_graph_from_file_1(char *filename, int *Nodes, int *Edges);
void alloc2DMatrix(char ***A, int N);
void free2D(char **A);
void construct2DMatrix(char **A, int N);
void WritetoFile(char **A, int N);
void printToTerminal(char **A, int N);


#endif // FUNCTIONS_H
