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

// Prints NxN matrix values in a file.
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
void WriteVectortoFile(double *a, int N, int num_threads){
  FILE *fp;
  char filename[100];
  snprintf(filename, sizeof(filename), "Python/Results/Data/Time%d", num_threads);
  fp = fopen(filename, "w");
  fprintf(fp, "Time\n");

  for (int i = 0; i < N; i++){
      fprintf(fp, "%f", a[i]);
      fprintf(fp, "\n");
  }
  fclose(fp);
}


// Prints two vectors in a file.
void WriteVectortoFile2(int *a, int *b, int N_rows, int N_links){
  FILE *fp;
  fp = fopen("CRS", "w");
  fprintf(fp, " row \n");

  for (int i = 0; i < N_rows; i++){
      fprintf(fp, " %d ", a[i]);
  }
  fprintf(fp, "\n");
  fprintf(fp, "\ncol \n");
  for (int i = 0; i < N_links; i++){
      fprintf(fp, " %d ", b[i]);
  }

  fclose(fp);

}

// Print NxN matrix values to terminal.
void printMatrixToTerminal(char **A, int N){
  for (int i = 0; i < N; i++){
    for (int j = 0; j < N; j++){
    printf("%d ", A[i][j]);
    }
  printf("\n");
  }
}

// Print vectors values.
void printVectorToTerminal(int *a, int N){
  //printf(" row  col \n");
  for (int i = 0; i < N; i++){
    printf("  %d  ", a[i]);
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





// Function to sort character array b
// according to the order defined by a
// where "a" n-largest values get sorted
void sort_numbers(int *a, int *b, int n, int N){
   int temp1, temp2;
   for (int i = 0; i < n; i++){
      for (int j = i + 1; j < N; j++){
         if (a[i] < a[j]){
            temp1 = a[i];
            temp2 = b[i];
            a[i] = a[j];
            b[i] = b[j];
            a[j] = temp1;
            b[j] = temp2;
         }
      }
   }
}


// Calculates the 2 element combination of a element set consisting of n
int factorial(int n){
  if (n < 2){
    return 0;
  }

  else{
    int result;
    int term1 = 1;
    int r = 2;

    for (int i = n; i > n-2; i--){
      term1 *= i;
    }

    result = term1/r;
    return result;
  }
}

// Counts the number of mutual webpage linkage occurences for each row
// and adds that to each webpage that contributed to the linkage
void counter(int *temp_num_involvements, int *num_involvements, int temp, int N){
  for (int i = 0; i < N; i++){
    if (temp_num_involvements[i] > 0){
      temp_num_involvements[i] = temp - temp_num_involvements[i];
      num_involvements[i] += temp_num_involvements[i];
      temp_num_involvements[i] = 0;
    }
  }
}
