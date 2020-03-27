#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <omp.h> // OpenMP

#include "functions.h"


void OMP_top_n_webpages(int num_webpages, int *num_involvements, int n, int num_threads){
  /// -----------------------------------------------------------
  // # Finds the top n webpages with respect to the number of involvements
  // in mutual linkages
  // Parallelized version of top_n_webpages

  // Input:
  // * num_webpages:      Holds the number of nodes for the webgraph found in read_graph_from_file
  // * num_involvements:  Holds the number of involvements per webpage as outbound
  //   n:                 Holds the number of the top webpages
  //   num_threads:       Holds the number of threads

  /// -----------------------------------------------------------

  // Allocates memory
  int *temp1_num_involvements = (int*)malloc(num_webpages*sizeof(int));

  // Filling vector with zeros
  for (int i = 0; i < num_webpages; i++){
    temp1_num_involvements[i] = i+1;
  }

  int temp1, temp2;
  // Function to sort character array temp1_num_involvements
  // according to the order defined by num_involvements
  // where num_involvements n-largest values get sorted
  #pragma omp parallel for ordered schedule(dynamic) num_threads(num_threads)
  for (int i = 0; i < n; i++){
    #pragma omp ordered
     for (int j = i + 1; j < num_webpages; j++){
        if (num_involvements[i] < num_involvements[j]){
           temp1 = num_involvements[i];
           temp2 = temp1_num_involvements[i];
           num_involvements[i] = num_involvements[j];
           temp1_num_involvements[i] = temp1_num_involvements[j];
           num_involvements[j] = temp1;
           temp1_num_involvements[j] = temp2;
        }
     }
  }

  printf("Webpage   # Involvements \n");
  // Prints the top n webpages with respect
  // to the number of involvements in mutual linkages
  for (int i = 0; i < n; i++){
    printf(" %d            %d \n", temp1_num_involvements[i], num_involvements[i]);
    printf("\n");
  }

  free(temp1_num_involvements);
}


void test_OMP_top_n_webpages(int n, int num_threads){
  /* Function to test OMP_top_n_webpages
  using the example illustrated in the home exam. */

  // Hard coding the exact values:
  int N_exact = 8;
  int num_involvements_exact[8] = {2, 0, 4, 6, 5, 2, 4, 3};
  int ordered_num_involvements_exact[8] = {6, 5, 4, 4, 3, 2, 2, 0};
  int webpages_ranking_exact[8] = {4, 5, 3, 7, 8, 1, 6, 2};


  // Provide the parameters for the function:
  int *num_involvements_test = (int*)malloc(8*sizeof(int));;


  for (int i = 0; i < N_exact; i++){
    num_involvements_test[i] = num_involvements_exact[i];
  }

  printf("\n Testing OMP_top_n_webpages \n");

  OMP_top_n_webpages(N_exact, num_involvements_test, n, num_threads);

  printf("\n The correct output is \n");
  printf("Webpage   # Involvements \n");
  for (int i = 0; i < n; i++){
    printf(" %d            %d \n", webpages_ranking_exact[i], ordered_num_involvements_exact[i]);
    printf("\n");
  }

  free(num_involvements_test);

}


/*
int cmpfunc (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
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
*/
