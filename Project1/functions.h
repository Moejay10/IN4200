#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h> // fabs
#include <time.h>
#include <omp.h> // OpenMP

/*
void read_graph_from_file_1(char *filename, int *Nodes, char ***table2D);
void read_graph_from_file_2(char *filename, int *Nodes, int *N_links, int **row_ptr, int **col_idx);

int count_mutual_links1(int N, char **table2D, int *num_involvements);
int count_mutual_links2(int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements);

void top_n_webpages(int num_webpages, int *num_involvements, int n);


int OMP_count_mutual_links1(int N, char **table2D, int *num_involvements, int num_threads);
int OMP_count_mutual_links2(int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements, int num_threads);

void OMP_top_n_webpages(int num_webpages, int *num_involvements, int n, int num_threads);
*/

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


void sort_numbers(int *a, int *b, int N);
int factorial(int n);
void counter(int *temp_num_involvements, int *num_involvements, int temp, int N);


#endif // FUNCTIONS_H
