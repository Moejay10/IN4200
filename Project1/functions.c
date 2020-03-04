#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <omp.h> // OpenMP

#include "functions.h"



void read_graph_from_file_1(char *filename, int *Nodes, char ***table2D){
/// -----------------------------------------------------------
// # Read file and extract data
// Input:
// * filename:  Holding the name of the web graph
// * Nodes:     Empty parameter

/// -----------------------------------------------------------
    int row = 0;
    int col = 0;
    int Edges = 0;
    FILE *datafile;
    datafile = fopen(filename, "r");

    if (datafile == NULL) {
        printf("Failure to open file %s\n", filename);
        exit(0);
    }

    fscanf(datafile, "%*[^\n]\n");                 // Skip lines to relevant data
    fscanf(datafile, "%*[^\n]\n");
    fscanf(datafile, "# Nodes: %d Edges: %d\n", &*Nodes, &Edges); // Extract data
    //fscanf(datafile, "# Nodes: %d\n", &*Nodes); // Extract data
    fscanf(datafile, "%*[^\n]\n");

    int N = *Nodes;

    alloc2DMatrix(table2D, N);
    construct2DMatrix(table2D, N);

    while (fscanf(datafile, "%d %d", &col, &row) != EOF){ // Scan to end of file

        if (row == col){
          continue;                                       // Assure we skip self links
        }
        (*table2D)[row][col] = 1;
    }

    fclose (datafile);
}

void read_graph_from_file_2(char *filename, int *Nodes, int *N_links, int **row_ptr, int **col_idx){
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
    fscanf(datafile, "# Nodes: %d Edges: %d\n", &*Nodes, &*N_links); // Extract data
    fscanf(datafile, "%*[^\n]\n");

    //int N = *Nodes;
    int E = *N_links;

    allocVector(col_idx, E);
    allocVector(row_ptr, E);

    while (fscanf(datafile, "%d %d", &col, &row) != EOF){ // Scan to end of file


        (*col_idx)[index] = col;                 // Saves coloumn index
        (*row_ptr)[index] = row;                 // Saves row index

        index++;
    }

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

void construct2DMatrix(char ***A, int N){

  for (int i = 0; i < N; i++){
    for (int j = 0; j < N; j++){
      (*A)[i][j] = 0;
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
void WriteVectortoFile(int *a, int *b, int N){
  FILE *fp;
  fp = fopen("CRS", "w");
  fprintf(fp, " row  col \n");

  for (int i = 0; i < N; i++){
      fprintf(fp, "  %d  ", a[i]);
      fprintf(fp, "  %d  ", b[i]);
      fprintf(fp, "\n");
  }
  fclose(fp);
}


// Print vectors values in a file.
void WriteVectortoFile2(int **a, int **b, int N){
  FILE *fp;
  fp = fopen("CRS", "w");
  fprintf(fp, " row  col \n");

  for (int i = 0; i < N; i++){
      fprintf(fp, "  %d  ", (*a)[i]);
      fprintf(fp, "  %d  ", (*b)[i]);
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
void printVectorToTerminal(int *a, int *b, int N){
  printf(" row  col \n");
  for (int i = 0; i < N; i++){
    printf("  %d  ", a[i]);
    printf("  %d  ", b[i]);
    printf("\n");
  }
}

// Print vectors values.
void printVectorToTerminal2(int **a, int **b, int N){
  printf(" row  col \n");
  for (int i = 0; i < N; i++){
    printf("  %d  ", (*a)[i]);
    printf("  %d  ", (*b)[i]);
    printf("\n");
  }
}


// Function to sort character array b
// according to the order defined by a
void sort_numbers_ascending(int *a, int *b, int N){
   int temp1, temp2, temp3, i, j;
   for (i = 0; i < N; i++){
      for (j = i + 1; j < N; j++){
         if (a[i] > a[j]){
            temp1 = a[i];
            temp2 = b[i];
            a[i] = a[j];
            b[i] = b[j];
            a[j] = temp1;
            b[j] = temp2;
         }

         if( a[i] == a[j] && b[i] > b[j] ){
           temp3 = b[i];
           b[i] = b[j];
           b[j] = temp3;
         }

      }
   }
}
