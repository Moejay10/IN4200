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
