#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <omp.h> // OpenMP

#include "functions.h"

int cmpfunc (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}


void top_n_webpages(int num_webpages, int *num_involvements, int n){
  int *temp1_num_involvements = (int*)malloc(num_webpages*sizeof(int));
  int *temp2_num_involvements = (int*)malloc(num_webpages*sizeof(int));



  for (int i = 0; i < num_webpages; i++){
    temp1_num_involvements[i] = num_involvements[i];
    temp2_num_involvements[i] = -1;

  }

  qsort(num_involvements, num_webpages, sizeof(int), cmpfunc);

  for (int i = num_webpages - 1; i > num_webpages - 1 - n; i--){
    for (int j = 0; j < num_webpages; j++){
      if (num_involvements[i] == temp1_num_involvements[j]){
        temp1_num_involvements[j] = -1;
        temp2_num_involvements[i] = j+1;
        break;
      }
    }

  }

  printf("Webpage   # Involvements \n");

  for (int i = num_webpages-1; i > num_webpages-1-n; i--){
    printf(" %d            %d \n", temp2_num_involvements[i], num_involvements[i]);
    printf("\n");
  }

  free(temp1_num_involvements);
  free(temp2_num_involvements);


}


void OMP_top_n_webpages(int num_webpages, int *num_involvements, int n, int num_threads){
  int *temp1_num_involvements = (int*)malloc(num_webpages*sizeof(int));
  int *temp2_num_involvements = (int*)malloc(num_webpages*sizeof(int));



  for (int i = 0; i < num_webpages; i++){
    temp1_num_involvements[i] = num_involvements[i];
    temp2_num_involvements[i] = -1;
  }

  qsort(num_involvements, num_webpages, sizeof(int), cmpfunc);

  int i;
  #pragma omp parallel for private(i) num_threads(num_threads)
  for (i = num_webpages - 1; i > num_webpages - 1 - n; i--){
    for (int j = 0; j < num_webpages; j++){
      if (num_involvements[i] == temp1_num_involvements[j]){
        temp1_num_involvements[j] = -1;
        temp2_num_involvements[i] = j+1;
        break;
      }
    }

  }

  printf("Webpage   # Involvements \n");

  for (int i = num_webpages-1; i > num_webpages-1-n; i--){
    printf(" %d            %d \n", temp2_num_involvements[i], num_involvements[i]);
    printf("\n");
  }

  free(temp1_num_involvements);
  free(temp2_num_involvements);
}



void test_top_n_webpages(char *openmp, int n, int num_threads){
  /* Function to test read_graph_from_file1
  using the example illustrated in the home exam. */

  // Hard coding the exact values:
  int N_exact = 8;
  int num_involvements_exact[8] = {2, 0, 4, 6, 5, 2, 4, 3};
  int ordered_num_involvements_exact[8] = {6, 5, 4, 4, 3, 2, 2, 0};


  // Provide the parameters for the function:
  int *num_involvements_test = (int*)malloc(8*sizeof(int));;


  // Parameter for counting the number of errors in the extracted matrix
  int numberofErrors = 0;

  for (int i = 0; i < N_exact; i++){
    num_involvements_test[i] = num_involvements_exact[i];
  }



  if (strcmp(openmp, "no") == 0 )
  {
    top_n_webpages(N_exact, num_involvements_test, n);


    for (int i = 0; i < N_exact; i++){
      if (ordered_num_involvements_exact[i] != num_involvements_test[i])
      {
        numberofErrors++;
      }
    }

    if (numberofErrors > 0)
    {
      printf("top_n_webpages has %d errors in num_involvements. \n", numberofErrors);
    }

    else
    {
      printf("top_n_webpages has no errors in num_involvements. \n");
    }

  }

  else if (strcmp(openmp, "yes") == 0 )
  {
    OMP_top_n_webpages(N_exact, num_involvements_test, n, num_threads);


    for (int i = 0; i < N_exact; i++){
      if (ordered_num_involvements_exact[i] != num_involvements_test[i])
      {
        numberofErrors++;
      }
    }

    if (numberofErrors > 0)
    {
      printf("OMP_top_n_webpages has %d errors in num_involvements. \n", numberofErrors);
    }

    else
    {
      printf("OMP_top_n_webpages has no errors in num_involvements. \n");
    }

  }

  else
  {
    printf("No openmp specification parameter was given \n");
  }


}
