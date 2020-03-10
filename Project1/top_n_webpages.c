#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <omp.h> // OpenMP


void top_n_webpages(int num_webpages, int *num_involvements, int n){
  int *temp_num_involvements = (int*)malloc(num_webpages*sizeof(int));

  for (int i = 0; i < num_webpages; i++){
    temp_num_involvements[i] = i+1;
  }

  sort_numbers(num_involvements, temp_num_involvements, num_webpages);

  printf("Webpage   # Involvements \n");

  for (int i = 0; i < n; i++){
    printf(" %d            %d \n", temp_num_involvements[i], num_involvements[i]);
    printf("\n");
  }

  free(temp_num_involvements);

}


void OMP_top_n_webpages(int num_webpages, int *num_involvements, int n, int num_threads){
  int *temp_num_involvements = (int*)malloc(num_webpages*sizeof(int));
  int temp1, temp2;

  for (int i = 0; i < num_webpages; i++){
    temp_num_involvements[i] = i+1;
  }

  //sort_numbers(num_involvements, temp_num_involvements, num_webpages);
  int i;
  #pragma omp parallel for private(i) num_threads(num_threads)
  for (i = 0; i < num_webpages; i++){
     for (int j = i + 1; j < num_webpages; j++){
        if (num_involvements[i] < num_involvements[j]){
           temp1 = num_involvements[i];
           temp2 = temp_num_involvements[i];
           num_involvements[i] = num_involvements[j];
           temp_num_involvements[i] = temp_num_involvements[j];
           num_involvements[j] = temp1;
           temp_num_involvements[j] = temp2;
        }
     }
  }

  printf("Webpage   # Involvements \n");

  for (int i = 0; i < n; i++){
    printf(" %d            %d \n", temp_num_involvements[i], num_involvements[i]);
    printf("\n");
  }

  free(temp_num_involvements);

}
