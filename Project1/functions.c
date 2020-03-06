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
    int nnz = 0;
    int N_selflinks   = 0;

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

    int N_rows = *Nodes +1;

    //Allocating memory for vectors
    int *colum_indices = (int*)malloc(*N_links*sizeof(int));
    int *row_indices = (int*)malloc(*N_links*sizeof(int));


    while (fscanf(datafile, "%d %d", &col, &row) != EOF){ // Scan to end of file

      if (row != col){
        colum_indices[nnz] = col;       // Saves coloumn index
        row_indices[nnz] = row;         // Saves row index

        nnz++;                          // Number of valid links
      }
      N_selflinks++;
    }


    fclose (datafile);

    *N_links = nnz;

    //Allocating memory for vectors
    //*val = (int*)malloc(*N_links*sizeof(int));
    *col_idx = (int*)malloc(*N_links*sizeof(int));
    *row_ptr = (int*)malloc(N_rows*sizeof(int));

    int *temp_row_ptr = (int*)malloc(N_rows*sizeof(int));

    for (int i = 0; i < N_rows; i++){
      temp_row_ptr[i] = 0;
      (*row_ptr)[i] = 0;
    }

    for (int i = 0; i < *N_links; i++){
    temp_row_ptr[row_indices[i]]++;
  }

  int sum = 0;
  int temp;
  for (int i = 0; i < N_rows; i++){
    temp = temp_row_ptr[i];
    temp_row_ptr[i] = sum;
    sum += temp;
  }

  //temp_row_ptr[N_rows] = *N_links;

  int rows, dest;
  for (int i = 0; i < *N_links; i++){
    rows = row_indices[i];
    dest = temp_row_ptr[rows];

    (*col_idx)[dest] = colum_indices[i];
    //(*val)[dest] = vals[i];

    temp_row_ptr[rows]++;
  }

  int last = 0;
  for (int i = 0; i < N_rows; i++){
    temp = temp_row_ptr[i];
    temp_row_ptr[i] = last;
    last = temp;
  }

  for (int i = 1; i < N_rows; i++){
    (*row_ptr)[i] = temp_row_ptr[i-1];
  }
  free(temp_row_ptr);
  free(colum_indices);
  free(row_indices);

}


int count_mutual_links1(int N, char **table2D, int *num_involvements){

  int *temp_num_involvements = (int*)malloc(N*sizeof(int));


  for (int i = 0; i < N; i++){
    num_involvements[i] = 0;
    temp_num_involvements[i] = 0;
  }

  int Total_involvements = 0;
  int temp;
  for (int i = 0; i < N; i++){
    temp = 0;
    for (int j = 0; j < N; j++){
      temp += table2D[i][j];
      temp_num_involvements[j] = table2D[i][j];
    }

    counter(temp_num_involvements, num_involvements, temp, N);

    Total_involvements += factorial(temp);
  }

  free(temp_num_involvements);

  return Total_involvements;
}


int count_mutual_links2(int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements){

  int *temp_num_involvements = (int*)malloc(N*sizeof(int));


  for (int i = 0; i < N; i++){
    num_involvements[i] = 0;
    temp_num_involvements[i] = 0;

  }

  int Total_involvements = 0;
  int temp = 0;


  for (int i = 1; i <= N; i++){
    temp = row_ptr[i] - row_ptr[i-1];

    for (int j = row_ptr[i-1]; j < row_ptr[i]; j++){
      temp_num_involvements[col_idx[j]] = 1;
    }

    counter(temp_num_involvements, num_involvements, temp, N);

    Total_involvements += factorial(temp);
  }


  temp = N_links - row_ptr[N];
  for (int j = row_ptr[N]; j < N_links; j++){
    temp_num_involvements[col_idx[j]] = 1;
  }

  counter(temp_num_involvements, num_involvements, temp, N);

  Total_involvements += factorial(temp);

  free(temp_num_involvements);

  return Total_involvements;
}


void top_n_webpages (int num_webpages, int *num_involvements, int n){

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
void printVectorToTerminal(int *a, int N){
  //printf(" row  col \n");
  for (int i = 0; i < N; i++){
    printf("  %d  ", a[i]);
    printf("\n");
  }
}

// Print vectors values.
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

void counter(int *temp_num_involvements, int *num_involvements, int temp, int N){
  for (int i = 0; i < N; i++){
    if (temp_num_involvements[i] > 0){
      temp_num_involvements[i] = temp - temp_num_involvements[i];
      num_involvements[i] += temp_num_involvements[i];
      temp_num_involvements[i] = 0;
    }
  }
}
