#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <mpi.h>

#include "functions.h"

const int MAX_STRING = 100;

#define idx2(i,j) (i*n_cols[myrank] + j)

// Used to index local copies of the data in matrix A ex. 4.
#define idx(i,j) (i*N + j)


int MPI_count_friends_of_ten(int M, int N, int** v){

  int my_rank, numprocs;

  // find out process ID and how many processes were started
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size (MPI_COMM_WORLD, &numprocs);

  MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

  // Calculate displacements and number of rows for each process.
  int *n_rows = malloc(numprocs*sizeof *n_rows);

  // Used when scattering A.
  int *sendcounts = malloc(numprocs*sizeof *sendcounts);
  int *Sdispls = malloc(numprocs*sizeof *Sdispls);

  // Used when gathering y.
  int *Gdispls = malloc(numprocs*sizeof *Gdispls);
  Sdispls[0] = 0;
  Gdispls[0] = 0;

  int rows = N/numprocs;
  int remainder = N%numprocs;



  // Last remainder processes gets an extra row.
  for (int rank = 0; rank < numprocs-1; rank++) {
      n_rows[rank] = rows + ((rank >= (numprocs - remainder)) ? 1:0);
      sendcounts[rank] = n_rows[rank]*N;
      Sdispls[rank+1] = Sdispls[rank] + sendcounts[rank];
      Gdispls[rank+1] = Gdispls[rank] + n_rows[rank];
  }
  n_rows[numprocs-1] = rows + ((numprocs-1) >= (numprocs - remainder) ? 1:0);

  sendcounts[numprocs-1] = n_rows[numprocs-1]*N;

  // Allocate local buffers.
  int *A;
  if (my_rank == 0){
      A = malloc(M*N * sizeof *A);

      // Initialize to some values:
      for (size_t i = 0; i < M; i++) {
          for (size_t j = 0; j < N; j++) {
              A[idx(i,j)] = v[i][j];
          }
      }
  }
  else {
      A = malloc(N*n_rows[my_rank] * sizeof *A);
  }


  if (my_rank == 0){
    printMatrixToTerminal(v, M, N);
    int n = M*N;
    printVectorToTerminal(A, n);
  }



  // Scatter A.
  MPI_Scatterv(A,                 // Sendbuff, matters only for root process.
               sendcounts,
               Sdispls,
               MPI_INT,
               A,                 // Recieve buff is the same as sendbuf here.
               N*n_rows[my_rank],
               MPI_INT,
               0,
               MPI_COMM_WORLD);

  int result = 0;
  int my_sum = 0;
  int total_sum = 0;

  int triple_friends = 10;

  for (int i = 0; i < M; i++){
    for (int j = 0; j < N; j++){

      // check the sum in horizontal row.
  		if ((j - 2) >= 0) {
        result = A[idx(i,j)] + A[idx(i,j-1)] + A[idx(i,j-2)];

        if (result == triple_friends){
            my_sum++;
        }

  		}

  		// check the sum in vertical row.
  		if ((i - 2) >= 0) {
        result = A[idx(i,j)] + A[idx(i-1,j)] + A[idx(i-2,j)];

        if (result == triple_friends){
            my_sum++;
        }

  		}

  		// check the sum diagonally
  		if ((i - 2) >= 0 && (j - 2) >= 0){
        result = A[idx(i,j)] + A[idx(i-1,j-1)] + A[idx(i-2,j-2)];

        if (result == triple_friends){
            my_sum++;
        }

  	   }

       // check the sum anti-diagonally
   		if ((i - 2) >= 0 && (j - 2) <= 0){
        result = A[idx(i,j)] + A[idx(i-1,j-1)] + A[idx(i-2,j-2)];

         if (result == triple_friends){
             my_sum++;
         }

   	   }

    }
  }


  // Gather the results
  MPI_Gatherv(&my_sum,
              n_rows[my_rank],
              MPI_INT,
              &total_sum,              // Matters only at root,
              n_rows,
              Gdispls,
              MPI_INT,
              0,
              MPI_COMM_WORLD);


  free(A);
  free(n_rows);
  free(Sdispls);
  free(Gdispls);
  free(sendcounts);

  //MPI_Bcast(&total_sum, 1, MPI_INT, 0, MPI_COMM_WORLD);

  return total_sum;
}


void Distribution(int section, int* my_x, int* my_s, int* my_r, int my_rank, int workers, int rest, int stride){
/*
Partitioning data boundaries for workers.
Input args:
    section:              Equal sized partion of the x-dim in image
    my_x:                 Number of columns a worker is assigned to recieve from master
    my_s:                 Index where the first column is drawn
    my_r:                 Number of columns a worker is assigned to deliver to master
    my_rank:              Worker ID
    workers:              Number of workers
    rest:                 Partion of image in x-dim that was left out of partitioning.
    stride:               How many columns the image shall "see" over boundaries
*/

    if (my_rank == workers)     // Last worker
    {
        *my_x = section+stride+rest;
        *my_r = section+rest;
        *my_s = (my_rank-1)*section-stride;
    }
    else if (my_rank == 1)      // First worker
    {
        *my_x = section+stride;
        *my_r = section;
        *my_s = 0;
    }
    else                         // Middel workers
    {
        *my_x = section+stride*2;
        *my_r = section;
        *my_s = (my_rank-1)*section-stride;
    }
}

void setup_ranks(int *dim, int *period, int *coords, int m, int my_rank, int num_procs, int *l_m){
  /* Function:
   * 1) Finds length of domains l_m
   * 2) Setup coords which contains indices in m-direction
   */
  (*l_m) = m/dim[0];
  int rest_m = m%dim[0];

  if (rest_m != 0) (*l_m)++;

  coords[0] = (*l_m)*my_rank; // start index in m-direction
  coords[1] = (*l_m)*(my_rank+1); // stop index + 1 in m-dir

  if (my_rank == num_procs-1) coords[1] = m;
  /* Image
   * |    ...   0   ...   |
   * |    ...   1   ...   |
   * |          :         |
   * |    num_procs - 1   |
   * a rank will use indices:
   * im = coords[0], ... , coords[1] - 1
   * in = 0, ... , n - 1
   */
}

void communicate2D_vertical(double **up_local, int M, int N_local, int my_rank, int numprocs){
  MPI_Status status;

  int lower_neigh = (my_rank>1) ? my_rank-1 : MPI_PROC_NULL;
  int upper_neigh = (my_rank<(numprocs-1)) ? my_rank+1 : MPI_PROC_NULL;

  // send to lower neighbor, receive from upper neighor
  MPI_Sendrecv (&(up_local[1][1]), M, MPI_DOUBLE, lower_neigh, 5, &(up_local[N_local+1][1]), M, MPI_DOUBLE, upper_neigh, 5, MPI_COMM_WORLD, &status);

  // send to upper neighbor, receive from lower neighor
  MPI_Sendrecv (&(up_local[N_local][1]), M, MPI_DOUBLE, upper_neigh, 6, &(up_local[0][1]), M, MPI_DOUBLE, lower_neigh, 6, MPI_COMM_WORLD, &status);
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
