#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <omp.h> // OpenMP


int count_mutual_links2(int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements){

  int *temp_num_involvements = (int*)malloc(N*sizeof(int));


  for (int i = 0; i < N; i++){
    num_involvements[i] = 0;
    temp_num_involvements[i] = 0;
  }

  int Total_involvements = 0;
  int temp = 0;


  for (int i = 1; i <= N; i++){
    temp = row_ptr[i] - row_ptr[i-1];

    for (int j = row_ptr[i-1]; j < row_ptr[i]; j++){
      temp_num_involvements[col_idx[j]] = 1;
    }

    counter(temp_num_involvements, num_involvements, temp, N);

    Total_involvements += factorial(temp);
  }


  temp = N_links - row_ptr[N];
  for (int j = row_ptr[N]; j < N_links; j++){
    temp_num_involvements[col_idx[j]] = 1;
  }

  counter(temp_num_involvements, num_involvements, temp, N);

  Total_involvements += factorial(temp);

  free(temp_num_involvements);

  return Total_involvements;
}



int OMP_count_mutual_links2(int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements, int num_threads){

  int *temp_num_involvements = (int*)malloc(N*sizeof(int));


  for (int i = 0; i < N; i++){
    num_involvements[i] = 0;
    temp_num_involvements[i] = 0;
  }

  int Total_involvements = 0;
  int temp = 0;

  #pragma omp parallel for private(temp) reduction(+:Total_involvements, num_involvements[:N], temp_num_involvements[:N]) num_threads(num_threads)
  for (int i = 1; i <= N; i++){
    temp = row_ptr[i] - row_ptr[i-1];

    for (int j = row_ptr[i-1]; j < row_ptr[i]; j++){
      temp_num_involvements[col_idx[j]] = 1;
    }

    counter(temp_num_involvements, num_involvements, temp, N);
    /*
    for (int i = 0; i < N; i++){
      if (temp_num_involvements[i] > 0){
        temp_num_involvements[i] = temp - temp_num_involvements[i];
        num_involvements[i] += temp_num_involvements[i];
        temp_num_involvements[i] = 0;
      }
    }
    */

    Total_involvements += factorial(temp);
  }


  temp = N_links - row_ptr[N];
  for (int j = row_ptr[N]; j < N_links; j++){
    temp_num_involvements[col_idx[j]] = 1;
  }

  counter(temp_num_involvements, num_involvements, temp, N);

  Total_involvements += factorial(temp);

  free(temp_num_involvements);

  return Total_involvements;
}
