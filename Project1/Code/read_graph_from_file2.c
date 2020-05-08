#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
//#include <omp.h> // OpenMP

#include "functions.h"


void read_graph_from_file2(char *filename, int *Nodes, int *N_links, int **row_ptr, int **col_idx){
/// -----------------------------------------------------------
// # Read webgraph files and extract data
// Input:
// * filename:  Holding the name of the web graph
// * Nodes:     Empty parameter
// * N_links:     Empty parameter
// ** row_ptr:     Empty parameter
// ** col_idx:     Empty parameter


/// -----------------------------------------------------------
    int fscan_return; // To get rid of warnings from fscan not using values
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

    fscan_return = fscanf(datafile, "%*[^\n]\n");                 // Skip lines to relevant data
    fscan_return = fscanf(datafile, "%*[^\n]\n");
    fscan_return = fscanf(datafile, "# Nodes: %d Edges: %d\n", &*Nodes, &*N_links); // Extract Nodes and Edges
    fscan_return = fscanf(datafile, "%*[^\n]\n");

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
      N_selflinks++;                    // Number of selflinks
    }


    fclose (datafile);

    *N_links = nnz;                     // Extracting only the valid links

    //Allocating memory for vectors
    //*val = (int*)malloc(*N_links*sizeof(int));
    *col_idx = (int*)malloc(*N_links*sizeof(int));
    *row_ptr = (int*)malloc(N_rows*sizeof(int));

    // Filling row_ptr with zeros
    for (int i = 0; i < N_rows; i++){
      (*row_ptr)[i] = 0;
    }

    // Finding out how many non-zeros values that are on each row
    for (int i = 0; i < *N_links; i++){
      (*row_ptr)[row_indices[i]]++;
    }

    int sum = 0;
    int tmp;
    // Adding the non-zeros values that are on each row
    for (int i = 0; i < N_rows; i++){
      tmp = (*row_ptr)[i];
      (*row_ptr)[i] = sum;
      sum += tmp;
    }

    // Assigning the last value as the number of links
    (*row_ptr)[N_rows] = *N_links;

    int rows, cols;
    // Linking the col_idx to the row_ptr
    for (int i = 0; i < *N_links; i++){
      rows = row_indices[i];
      cols = (*row_ptr)[rows];

      (*col_idx)[cols] = colum_indices[i];
      //(*val)[cols] = vals[i];

      (*row_ptr)[rows]++;
    }


    sum = 0;
    // Rearranging the row_ptr so it starts with a zero as convention says
    for (int i = 0; i < N_rows; i++){
      tmp = (*row_ptr)[i];
      (*row_ptr)[i] = sum;
      sum = tmp;
    }

    free(colum_indices);
    free(row_indices);

}



void test_read_graph_from_file2(){
  /* Function to test read_graph_from_file2
  using the example illustrated in the home exam. */

  printf("\n Testing read_graph_from_file2 \n");

  // Hard coding the exact values:
  int N_exact = 8;
  int N_links_exact = 17;
  int row_ptr_exact[9] = {0, 1, 4, 5, 6, 9, 12, 14, 17};
  int col_idx_exact[17] = {6, 0, 2, 3, 0, 1, 2, 3, 6, 3, 4, 7, 4, 7, 4, 5, 6};

  // Provide the parameters for the function:
  int N_test = 0;
  int N_links_test = 0;
  int *row_ptr_test = NULL;
  int *col_idx_test = NULL;
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

  free(row_ptr_test);
  free(col_idx_test);

}
