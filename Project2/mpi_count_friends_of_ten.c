#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <mpi.h>

#include "functions.h"
#include "count_friends_of_ten.c"


// Used to index local copies of the data in matrix A
#define idx(i,j) (i*N + j)
#define idx2(i,j) (i + j*M)

#define idx3(i,j) (i*n_cols[my_rank] + j)
#define idx4(i,j) (j*n_rows[my_rank] + i)
#define idx5(i,j) (i*n_cols[my_rank] + j*n_rows[my_rank])




int MPI_count_friends_of_ten(int M, int N, int** v){

  int my_rank, numprocs;

  // find out process ID and how many processes were started
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size (MPI_COMM_WORLD, &numprocs);

  MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

  // Calculate displacements and number of rows for each process.
  int *n_rows = malloc(numprocs*sizeof *n_rows);
  int *n_cols = malloc(numprocs*sizeof *n_cols);

  // Used when scattering A.
  int *sendrows = malloc(numprocs*sizeof *sendrows);
  int *sendcols = malloc(numprocs*sizeof *sendcols);

  int *rowdispls = malloc(numprocs*sizeof *rowdispls);
  int *coldispls = malloc(numprocs*sizeof *coldispls);
  rowdispls[0] = 0;
  coldispls[0] = 0;

  int rows = M/numprocs;
  int remainder_row = M%numprocs;

  int cols = N/numprocs;
  int remainder_col = N%numprocs;

  // Last remainder processes gets an extra row.
  for (int rank = 0; rank < numprocs-1; rank++) {

    n_rows[rank] = rows + ((rank >= (numprocs - remainder_row)) ? 1:0);
    n_cols[rank] = cols + ((rank >= (numprocs - remainder_col)) ? 1:0);

    sendrows[rank] = n_rows[rank]*N;
    sendcols[rank] = n_cols[rank]*M;

    rowdispls[rank+1] = rowdispls[rank] + sendrows[rank];
    coldispls[rank+1] = coldispls[rank] + sendcols[rank];

  }
  n_rows[numprocs-1] = rows + ((numprocs-1) >= (numprocs - remainder_row) ? 1:0);
  n_cols[numprocs-1] = cols + ((numprocs-1) >= (numprocs - remainder_col) ? 1:0);

  sendrows[numprocs-1] = n_rows[numprocs-1]*N;
  sendcols[numprocs-1] = n_cols[numprocs-1]*M;

  n_rows[1] += n_rows[0];
  n_cols[1] += n_cols[0];

  n_rows[0] = 0;
  n_cols[0] = 0;

  sendrows[1] += sendrows[0];
  sendcols[1] += sendcols[0];

  sendrows[0] = 0;
  sendcols[0] = 0;

  rowdispls[1] = 0;
  coldispls[1] = 0;


  // Allocate local buffers.
  int *A;
  int *B;
  if (my_rank == 0){
      A = malloc(M*N * sizeof *A);
      B = malloc(M*N * sizeof *B);


      // Initialize to some values:
      for (int i = 0; i < M; i++) {
          for (int j = 0; j < N; j++) {
              A[idx(i,j)] = v[i][j];
              B[idx2(i,j)] = v[i][j];
          }
      }
  }

  else {
      A = malloc(N*n_rows[my_rank] * sizeof *A);
      B = malloc(M*n_cols[my_rank] * sizeof *B);

  }


  if (my_rank == 0){
    printMatrixToTerminal(v, M, N);
    int n = M*N;
    //printVectorToTerminal(A, n);
    //printVectorToTerminal(B, n);
  }


  // Scatter A
  MPI_Scatterv(A,                 // Sendbuff, matters only for root process.
               sendrows,
               rowdispls,
               MPI_INT,
               A,                 // Recieve buff is the same as sendbuf here.
               N*n_rows[my_rank],
               MPI_INT,
               0,
               MPI_COMM_WORLD);

  // Scatter B
  MPI_Scatterv(B,                 // Sendbuff, matters only for root process.
               sendcols,
               coldispls,
               MPI_INT,
               B,                 // Recieve buff is the same as sendbuf here.
               M*n_cols[my_rank],
               MPI_INT,
               0,
               MPI_COMM_WORLD);



  int result = 0;
  int my_sum = 0;
  int total_sum = 0;

  int triple_friends = 10;
/*
  if (my_rank > 0){
    // Print the matrix
    for (int i = 0; i < M; i++){
      printf("rank %d \n", my_rank+1);
      for (int j = 0; j < N; j++){
        if (i < n_rows[my_rank]){
          printf("%d", A[idx(i,j)]);
        }
      }
      printf("\n");
    }
  }
*/

/*
if (my_rank > 0){
  for (int j = 0; j < N; j++){
    printf("rank %d \n", my_rank+1);
    for (int i = 0; i < M; i++){
      if (j < n_cols[my_rank]){
        printf("%d", B[idx2(i,j)]);
      }
    }
    printf("\n");
  }
}
*/

  if (numprocs > 1){

    for (int i = 0; i < M; i++){
      for (int j = 0; j < N; j++){

        if (my_rank > 0){

          if (i < n_rows[my_rank]){
            // check the sum in horizontal row.
            if ((j - 2) >= 0) {
              result = A[idx(i,j)] + A[idx(i,j-1)] + A[idx(i,j-2)];

              if (result == triple_friends){
                  my_sum++;
              }
            }
          }


          if (j < n_cols[my_rank]){
            // check the sum in vertical row.
            if ((i - 2) >= 0) {
              result = B[idx2(i,j)] + B[idx2(i-1,j)] + B[idx2(i-2,j)];

              if (result == triple_friends){
                  my_sum++;
              }
            }
          }

        }


        if (my_rank == 0){

          // check the sum diagonally
      		if ((i - 2) >= 0 && (j - 2) >= 0){
            result = v[i][j] + v[i-1][j-1] + v[i-2][j-2];

            if (result == triple_friends){
                my_sum++;
            }
      	   }

           // check the sum anti-diagonally
       		if ((i - 2) >= 0 && (j - 2) <= 0){
             result = v[i][j] + v[i-1][j-1] + v[i-2][j-2];

             if (result == triple_friends){
                 my_sum++;
             }
       	   }

        }


      }
    }

  }

  else{

    my_sum = count_friends_of_ten(M,N,v);

  }




  // Summing up all contributions and distributing to every processor.
  MPI_Allreduce(&my_sum,
                &total_sum,
                1,
                MPI_INT,
                MPI_SUM,
                MPI_COMM_WORLD);


  free(A);
  free(B);
  free(n_rows);
  free(n_cols);
  free(rowdispls);
  free(coldispls);
  free(sendrows);
  free(sendcols);

  return total_sum;
}




void test_MPI_count_friends_of_ten(){
  /* Function to test count_friends_of_ten
  using the example illustrated in the home exam. */

  // Hard coding the exact values:
  int M = 4;
  int N = 5;
  int Total_triple_friends_exact = 7;
  int v_exact[4][5] =
  {
    {1, 5, 6, 3, 1},
    {2, 4, 4, 1, 7},
    {7, 2, 3, 1, 2},
    {3, 2, 2, 5, 3},
  };

  // Provide the parameters for the function:
  int **v_test;
  int Total_triple_friends_test = 0;

  alloc2DMatrix(&v_test, M, N);

  construct2DMatrix(&v_test, M, N);

  for (int i = 0; i < M; i++){
    for (int j = 0; j < N; j++){
      v_test[i][j] = v_exact[i][j];
    }
  }

  printf("\n Testing count_friends_of_ten \n");

  Total_triple_friends_test = MPI_count_friends_of_ten(M, N, v_test);

  if (Total_triple_friends_test != Total_triple_friends_exact){
    printf("The total number of triple-friends of ten was extracted incorrectly in function count_friends_of_ten \n");
    printf("Total_triple_friends_exact is: %d, while the extracted Total_triple_friends_test is: %d \n", Total_triple_friends_exact, Total_triple_friends_test);
  }

  else
  {
    printf("The total number of triple-friends of ten was extracted correctly in function count_friends_of_ten \n");
  }


  free2D(v_test);

}
