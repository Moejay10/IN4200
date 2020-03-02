#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <omp.h> // OpenMP

#include "functions.h"



void read_graph_from_file_1(char *filename, int *Nodes, int *Edges, char ***table2D){
/// -----------------------------------------------------------
// # Read file and extract data
// Input:
// * filename:  Holding the name of the web graph
// * Nodes:     Empty parameter
// * Edges:     Empty parameter

/// -----------------------------------------------------------
    //char **A;
    int row = 0;
    int col = 0;

    FILE *datafile;
    datafile = fopen(filename, "r");

    if (datafile == NULL) {
        printf("Failure to open file %s\n", filename);
        exit(0);
    }

    fscanf(datafile, "%*[^\n]\n");                 // Skip lines to relevant data
    fscanf(datafile, "%*[^\n]\n");
    fscanf(datafile, "# Nodes: %d Edges: %d\n", &*Nodes, &*Edges); // Extract data
    fscanf(datafile, "%*[^\n]\n");

    int N = *Nodes;

    //alloc2DMatrix(&A, N);
    alloc2DMatrix(table2D, N);

    while (fscanf(datafile, "%i %i", &col, &row) != EOF){ // Scan to end of file

        if (row == col){
            continue;                            // Assure we skip self links
        }
        //A[row][col] = 1;
        (*table2D)[row][col] = 1;
    }

    //WriteMatrixtoFile(A, N);
    //printMatrixToTerminal(A, N);
    //free2D(A);

    fclose (datafile);
}

void read_graph_from_file_2(char *filename, int *Nodes, int *Edges, int **row_ptr, int **col_idx, int **val){
/// -----------------------------------------------------------
// # Read file and extract data
// Input:
// * filename:  Holding the name of the web graph
// * Nodes:     Empty parameter
// * Edges:     Empty parameter

/// -----------------------------------------------------------

    int row = 0;
    int col = 0;
    int index   = 0;
    FILE *datafile;
    datafile = fopen(filename, "r");

    if (datafile == NULL) {
        printf("Failure to open file %s\n", filename);
        exit(0);
    }

    fscanf(datafile, "%*[^\n]\n");                 // Skip lines to relevant data
    fscanf(datafile, "%*[^\n]\n");
    fscanf(datafile, "# Nodes: %d Edges: %d\n", &*Nodes, &*Edges); // Extract data
    fscanf(datafile, "%*[^\n]\n");

    //int N = *Nodes;
    int E = *Edges;

    allocVector(val, E);
    allocVector(col_idx, E);
    allocVector(row_ptr, E);


    while (fscanf(datafile, "%i %i", &col, &row) != EOF){ // Scan to end of file

        if (row == col){
            continue;                            // Assure we skip self links
        }

        (*val)[index] = 1;
        (*col_idx)[index] = col;
        (*row_ptr)[index] = row;

        index++;
    }

    //printVectorToTerminal(val, col_idx, row_ptr, E);

    //WriteVectortoFile(val, col_idx, row_ptr, E);

    //free1D(val);
    //free1D(col_idx);
    //free1D(row_ptr);


    fclose (datafile);
}

void alloc2DMatrix(char ***A, int N){

  *A = malloc(N * sizeof *A);
    (*A)[0] = malloc(N*N * sizeof (*A)[0]);
    if (!(*A)[0] || !*A){
        // Allocation failed.
        printf("Allocation failed\n");
    }

    for (size_t i = 1; i < N; i++) {
        (*A)[i] = &((*A)[0][i*N]);
    }
}

void allocVector(int **a, int N){
    *a = malloc(N * sizeof *a);
    }



// Free pointers allocated in alloc2D.
void free2D(char **A){
    free(A[0]);
    free(A);
}

void free1D(int *a){
    free(a);
}

void construct2DMatrix(char **A, int N){

  for (int i = 0; i < N; i++){
    for (int j = 0; j < N; j++){
      A[i][j] = 0;
    }
  }

}

// Print matrix values in a file.
void WriteMatrixtoFile(char **A, int N){
  FILE *fp;
  fp = fopen("Table2D", "w");

  for (int i = 0; i < N; i++){
    for (int j = 0; j < N; j++){
      fprintf(fp, "%d ", A[i][j]);
    }
    fprintf(fp, "\n");
  }
  fclose(fp);
}

// Print vectors values in a file.
void WriteVectortoFile(int *a, int *b, int*c, int N){
  FILE *fp;
  fp = fopen("CRS", "w");
  fprintf(fp, " val  col  row \n");

  for (int i = 0; i < N; i++){
      fprintf(fp, "  %d  ", a[i]);
      fprintf(fp, "  %d  ", b[i]);
      fprintf(fp, "  %d  ", c[i]);
      fprintf(fp, "\n");
  }
  fclose(fp);
}

// Print matrix values.
void printMatrixToTerminal(char **A, int N){
  for (int i = 0; i < N; i++){
    for (int j = 0; j < N; j++){
    printf("%d ", A[i][j]);
    }
  printf("\n");
  }
}

// Print vectors values.
void printVectorToTerminal(int *a, int *b, int*c, int N){
  printf(" val  col  row \n");
  for (int i = 0; i < N; i++){
    printf("  %d  ", a[i]);
    printf("  %d  ", b[i]);
    printf("  %d  ", c[i]);
    printf("\n");
  }
}
