#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <omp.h> // OpenMP

#include "functions.h"


int OMP_count_mutual_links2(int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements, int num_threads){
  /// -----------------------------------------------------------
  // # Counts the total number of mutual webpage linkages occurences
  // and the number of involvements per webpage as outbound
  // Parallelized version of count_mutual_links2

  // Input:
  // * Nodes:             Holds the number of nodes for the webgraph found in read_graph_from_file2
  // * N_links:           Holds the number of edges for the webgraph found in read_graph_from_file2
  // * row_ptr:          The corresponding row_ptr for the webgraph found in read_graph_from_file2
  // * col_idx:          The corresponding col_idx for the webgraph found in read_graph_from_file2
  // * num_involvements:  Empty parameter
  //   num_threads:       Holds the number of threads

  // Output:
  // Total_involvements:  Returns the total number of mutual webpage linkages occurences
  /// -----------------------------------------------------------

  // Filling vector with zeros
  for (int i = 0; i < N; i++){
    num_involvements[i] = 0;
  }

  int Total_involvements = 0;
  int temp = 0;

  // Counts the number of mutual webpage linkage occurences for each row
  // and adds that to each webpage that contributed to the linkage
  #pragma omp parallel for private(temp) reduction(+:Total_involvements, num_involvements[:N]) num_threads(num_threads)
  for (int i = 1; i <= N; i++){
    temp = row_ptr[i] - row_ptr[i-1];
    for (int j = row_ptr[i-1]; j < row_ptr[i]; j++){
        num_involvements[col_idx[j]] += temp-1;
      }
    // Function found in functions.c
    Total_involvements += factorial(temp);    // Finds the total number of
                                              // mutual linkages for each row
  }

  return Total_involvements;
}



void test_OMP_count_mutual_links2(int num_threads){
  /* Function to test OMP_count_mutual_links2
  using the example illustrated in the home exam. */

  // Hard coding the exact values:
  int N_exact = 8;
  int N_links_exact = 17;
  int num_involvements_exact[8] = {2, 0, 4, 6, 5, 2, 4, 3};
  int Total_involvements_exact = 13;
  int row_ptr_exact[9] = {0, 1, 4, 5, 6, 9, 12, 14, 17};
  int col_idx_exact[17] = {6, 0, 2, 3, 0, 1, 2, 3, 6, 3, 4, 7, 4, 7, 4, 5, 6};

  // Provide the parameters for the function:
  int Total_involvements_test = 0;
  int *num_involvements_test = (int*)malloc(8*sizeof(int));;
  int *row_ptr_test = (int*)malloc(9*sizeof(int));
  int *col_idx_test = (int*)malloc(17*sizeof(int));

  // Parameter for counting the number of errors in the extracted matrix
  int numberofErrors = 0;

  for (int i = 0; i < N_exact+1; i++){
    row_ptr_test[i] = row_ptr_exact[i];
  }

  for (int i = 0; i < N_links_exact; i++){
    col_idx_test[i] = col_idx_exact[i];
  }

  printf("\n Testing OMP_count_mutual_links2 \n");

  Total_involvements_test = OMP_count_mutual_links2(N_exact, N_links_exact, row_ptr_test, col_idx_test, num_involvements_test, num_threads);

  if (Total_involvements_exact != Total_involvements_test){
    printf("The total number of mutual webpage linkage occurences was extracted incorrectly in function OMP_count_mutual_links2 \n");
    printf("Total_involvements_exact is: %d, while the extracted Total_involvements_test is: %d \n", Total_involvements_exact, Total_involvements_test);
  }

  else
  {
    printf("The total number of mutual webpage linkage occurences was extracted correctly in function OMP_count_mutual_links2 \n");
    printf("Total_involvements_exact is: %d, while the extracted Total_involvements_test is: %d \n", Total_involvements_exact, Total_involvements_test);
  }

  for (int i = 0; i < N_exact; i++){
    if (num_involvements_exact[i] != num_involvements_test[i])
    {
      numberofErrors++;
    }
  }

  if (numberofErrors > 0)
  {
    printf("OMP_count_mutual_links2 has %d errors in num_involvements. \n", numberofErrors);
  }

  else
  {
    printf("OMP_count_mutual_links2 has no errors in num_involvements. \n");
  }

  free(col_idx_test);
  free(row_ptr_test);
  free(num_involvements_test);
}
