#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <omp.h> // OpenMP

#include "functions.h"


int count_mutual_links2(int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements){



  for (int i = 0; i < N; i++){
    num_involvements[i] = 0;
  }

  int Total_involvements = 0;
  int temp = 0;


  for (int i = 1; i < N+1; i++){
    temp = row_ptr[i] - row_ptr[i-1];
    for (int j = row_ptr[i-1]; j < row_ptr[i]; j++){
        num_involvements[col_idx[j]] += temp-1;
      }

    Total_involvements += factorial(temp);
  }


  return Total_involvements;
}





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
