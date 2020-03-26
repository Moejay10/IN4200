#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <omp.h> // OpenMP

#include "functions.h"


int OMP_count_mutual_links1(int N, char **table2D, int *num_involvements, int num_threads){

  int *temp_num_involvements = (int*)malloc(N*sizeof(int));

  for (int i = 0; i < N; i++){
    num_involvements[i] = 0;
    temp_num_involvements[i] = 0;
  }

  int Total_involvements = 0;
  int temp;

  #pragma omp parallel for private(temp) reduction(+:Total_involvements, num_involvements[:N], temp_num_involvements[:N]) num_threads(num_threads)
  for (int i = 0; i < N; i++)
  {
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



void test_OMP_count_mutual_links1(int num_threads){
  /* Function to test count_mutual_links1
  using the example illustrated in the home exam. */

  // Hard coding the exact values:
  int N_exact = 8;
  int num_involvements_exact[8] = {2, 0, 4, 6, 5, 2, 4, 3};
  int Total_involvements_exact = 13;
  int Matrix_exact[8][8] =
  {
    {0, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 1, 1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 1, 0},
    {0, 0, 0, 1, 1, 0, 0, 1},
    {0, 0, 0, 0, 1, 0, 0, 1},
    {0, 0, 0, 0, 1, 1, 1, 0},
  };

  // Provide the parameters for the function:
  char **table2D;
  int Total_involvements_test = 0;
  int *num_involvements_test = (int*)malloc(8*sizeof(int));

  // Parameter for counting the number of errors in the extracted matrix
  int numberofErrors = 0;

  alloc2DMatrix(&table2D, N_exact);

  for (int i = 0; i < N_exact; i++){
    for (int j = 0; j < N_exact; j++){
      table2D[i][j] = Matrix_exact[i][j];
    }
  }



  printf("\n Testing OMP_count_mutual_links1 \n");

  Total_involvements_test = OMP_count_mutual_links1(N_exact, table2D, num_involvements_test, num_threads);

  if (Total_involvements_exact != Total_involvements_test){
    printf("The total number of mutual webpage linkage occurences was extracted incorrectly in function OMP_count_mutual_links1 \n");
    printf("Total_involvements_exact is: %d, while the extracted Total_involvements_test is: %d \n", Total_involvements_exact, Total_involvements_test);
  }

  else
  {
    printf("The total number of mutual webpage linkage occurences was extracted correctly in function OMP_count_mutual_links1 \n");
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
    printf("OMP_count_mutual_links1 has %d errors in num_involvements. \n", numberofErrors);
  }

  else
  {
    printf("OMP_count_mutual_links1 has no errors in num_involvements. \n");
  }

}
