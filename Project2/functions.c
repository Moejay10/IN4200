#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "functions.h"

// Allocates memory for a NxN matrix
void alloc2DMatrix(int ***A, int M, int N){
  *A = malloc(M * sizeof *A);
    (*A)[0] = malloc(M*N * sizeof (*A)[0]);
    if (!(*A)[0] || !*A){
        // Allocation failed.
        printf("Allocation failed\n");
    }
    for (size_t i = 1; i < M; i++) {
        (*A)[i] = &((*A)[0][i*N]);
    }
}

// Allocates memory for a vector
void allocVector(int **a, int N){
    *a = malloc(N * sizeof *a);
    }



// Frees double pointers.
void free2D(int **A){
    free(A[0]);
    free(A);
}

// Frees single pointers.
void free1D(int *a){
    free(a);
}

// Fills a NxN matrix with zeros
void construct2DMatrix(int ***A, int M, int N){
  for (int i = 0; i < M; i++){
    for (int j = 0; j < N; j++){
      (*A)[i][j] = 0;
    }
  }

}

// Print vectors values.
void printVectorToTerminal(int *a, int N){
  //printf(" row  col \n");
  for (int i = 0; i < N; i++){
    printf("%d ", a[i]);
  }
  printf("\n");

}



// Print NxN matrix values to terminal.
void printMatrixToTerminal(int **A, int M, int N){
  for (int i = 0; i < M; i++){
    for (int j = 0; j < N; j++){
    printf("%d ", A[i][j]);
    }
  printf("\n");
  }
}



// Prints two vectors to the terminal.
void printVectorToTerminal2(int *a, int *b, int N_rows, int N_links){
  printf("row \n");
  for (int i = 0; i < N_rows; i++){
    printf(" %d ", a[i]);
  }

  printf("\n");

  printf("\ncol \n");
  for (int i = 0; i < N_links; i++){
    printf(" %d ", b[i]);
    printf("\n");
  }
}
