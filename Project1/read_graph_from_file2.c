#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
//#include <omp.h> // OpenMP

#include "functions.h"


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

  temp_row_ptr[N_rows] = *N_links;

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

  for (int i = 0; i < N_rows; i++){
    (*row_ptr)[i] = temp_row_ptr[i];
  }
  free(temp_row_ptr);
  free(colum_indices);
  free(row_indices);

}
