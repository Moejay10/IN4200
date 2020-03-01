#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <omp.h> // OpenMP

#include "functions.h"



void read_graph_from_file_1(char *filename, int *Nodes, int *Edges){
/// -----------------------------------------------------------
// # Read file and extract data
// Input:
// * filename:  Holding the name of the web graph
// * Nodes:     Empty parameter
// * Edges:     Empty parameter
// * A:         Empty 2D matrix

/// -----------------------------------------------------------
    char **A;
    int row           = 0;
    int col           = 0;

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

    alloc2DMatrix(&A, N);
    construct2DMatrix(A, N);

    while (fscanf(datafile, "%i %i", &col, &row) != EOF){ // Scan to end of file

        if (row == col){
            continue;                            // Assure we skip self links
        }
        A[row][col] = 1;

    }
    WritetoFile(A, N);
    printToTerminal(A, N);
    free2D(A);

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


// Free pointers allocated in alloc2D.
void free2D(char **A){
    free(A[0]);
    free(A);
}

void construct2DMatrix(char **A, int N){

  for (int i = 0; i < N; i++){
    for (int j = 0; j < N; j++){
      A[i][j] = 0;
    }
  }

}

// Print matrix values in a file.
void WritetoFile(char **A, int N){
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

// Print matrix values.
void printToTerminal(char **A, int N){
  for (int i = 0; i < N; i++){
    for (int j = 0; j < N; j++){
    printf("%d ", A[i][j]);
    }
  printf("\n");
  }
}
