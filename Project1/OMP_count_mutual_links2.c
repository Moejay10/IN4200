#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <omp.h> // OpenMP

#include "functions.h"


int OMP_count_mutual_links2(int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements, int num_threads){

  for (int i = 0; i < N; i++){
    num_involvements[i] = 0;
  }

  int Total_involvements = 0;
  int temp = 0;

  #pragma omp parallel for private(temp) reduction(+:Total_involvements, num_involvements[:N]) num_threads(num_threads)
  for (int i = 1; i <= N; i++){
    temp = row_ptr[i] - row_ptr[i-1];
    for (int j = row_ptr[i-1]; j < row_ptr[i]; j++){
        num_involvements[col_idx[j]] += temp-1;
      }

    Total_involvements += factorial(temp);
  }

  return Total_involvements;
}



void test_OMP_count_mutual_links2(int num_threads){
  /* Function to test count_mutual_links2
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

}
