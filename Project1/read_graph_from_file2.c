#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
//#include <omp.h> // OpenMP

#include "functions.h"


void read_graph_from_file2(char *filename, int *Nodes, int *N_links, int **row_ptr, int **col_idx){
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


    for (int i = 0; i < N_rows; i++){
      (*row_ptr)[i] = 0;
    }

    for (int i = 0; i < *N_links; i++){
    (*row_ptr)[row_indices[i]]++;
  }

  int sum = 0;
  int temp;
  for (int i = 0; i < N_rows; i++){
    temp = (*row_ptr)[i];
    (*row_ptr)[i] = sum;
    sum += temp;
  }

  (*row_ptr)[N_rows] = *N_links;

  int rows, dest;
  for (int i = 0; i < *N_links; i++){
    rows = row_indices[i];
    dest = (*row_ptr)[rows];

    (*col_idx)[dest] = colum_indices[i];
    //(*val)[dest] = vals[i];

    (*row_ptr)[rows]++;
  }

  int last = 0;
  for (int i = 0; i < N_rows; i++){
    temp = (*row_ptr)[i];
    (*row_ptr)[i] = last;
    last = temp;
  }


  free(colum_indices);
  free(row_indices);

}



void test_read_graph_from_file2(){
  /* Function to test read_graph_from_file1
  using the example illustrated in the home exam. */

  // Hard coding the exact values:
  int N_exact = 8;
  int N_links_exact = 17;
  int row_ptr_exact[9] = {0, 1, 4, 5, 6, 9, 12, 14, 17};
  int col_idx_exact[17] = {6, 0, 2, 3, 0, 1, 2, 3, 6, 3, 4, 7, 4, 7, 4, 5, 6};

  // Provide the parameters for the function:
  int N_test = 0;
  int N_links_test = 0;
  int *row_ptr_test = (int*)malloc(9*sizeof(int));
  int *col_idx_test = (int*)malloc(17*sizeof(int));
  char *filename;
  filename = "8nodes_graph.txt";
  read_graph_from_file2(filename, &N_test, &N_links_test, &row_ptr_test, &col_idx_test);

  // Parameter for counting the number of errors in the extracted matrix
  int numberofErrors1 = 0;
  int numberofErrors2 = 0;


  // Verifying the results between read_graph_from_file1 and the exact answer:
  // First asserting the number of nodes
  if (N_exact != N_test || N_links_exact != N_links_test){ // If N_test is wrong, then we cant compare the vectors
    printf("Either the number of Nodes or Edges was extracted incorrectly in function read_graph_from_file2 \n");
    printf("N_exact is: %d and N_links_exact is %d, while the extracted N_test is: %d and N_links_test is %d \n", N_exact, N_links_exact, N_test, N_links_test);
  }
  else
  {
    printf("Both the number of Nodes & Edges was extracted correctly in function read_graph_from_file2 \n");
    printf("N_exact is: %d and N_links_exact is %d, while the extracted N_test is: %d and N_links_test is %d \n", N_exact, N_links_exact, N_test, N_links_test);

    // Then we assert the values in the extracted vectors row_ptr anc col_idx
    for (int i = 0; i < N_exact + 1; i++){
      if (row_ptr_exact[i] != row_ptr_test[i])
      {
        numberofErrors1++;
      }
    }

    for (int j = 0; j < N_links_exact; j++){
      if (col_idx_exact[j] != col_idx_test[j])
      {
        numberofErrors2++;
      }
    }

    if (numberofErrors1 > 0)
    {
      printf("read_graph_from_file2 has %d errors in row_ptr. \n", numberofErrors1);
    }

    else if (numberofErrors2 > 0)
    {
      printf("read_graph_from_file2 has %d errors in col_idx. \n", numberofErrors2);
    }

    else
    {
      printf("read_graph_from_file1 has no errors in the vectors row_ptr or col_idx. \n");
    }
  }

}
