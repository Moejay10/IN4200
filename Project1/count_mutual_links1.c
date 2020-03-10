#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <omp.h> // OpenMP


int count_mutual_links1(int N, char **table2D, int *num_involvements){

  int *temp_num_involvements = (int*)malloc(N*sizeof(int));


  for (int i = 0; i < N; i++){
    num_involvements[i] = 0;
    temp_num_involvements[i] = 0;
  }

  int Total_involvements = 0;
  int temp;
  for (int i = 0; i < N; i++){
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
