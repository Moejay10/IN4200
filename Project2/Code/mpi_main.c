#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#include "mpi_count_friends_of_ten.c"

#include "functions.h"


int main(int argc, char** argv){
/* Description
  ---------------
  Main program parallelised where one chooses the dimensions M and N
  of an MxN matrix, and finds the appropiate values of it.
  Writes out the number of triple friends of the matrix.
*/

// Time parameters
  double start, end, timer;

  // Initialization
  int my_rank, numprocs;

  int M, N, num_triple_friends, friends;
  int **v = NULL;

  // MPI initializations
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size (MPI_COMM_WORLD, &numprocs);

// ------------------------- TEST PROGRAM ----------------------------//
  if (my_rank == 0){
    printf("\n TEST PROGRAM PART \n");
  }
  // Test case with matrix given in the exam
  test_MPI_count_friends_of_ten();


  if (my_rank == 0){
    printf("\n MAIN PROGRAM PART \n");

    // Decide the values for M and N
    M = 1000;
    N = 1500;

    // Allocate 2D array v and assign it with suitable values
    alloc2DMatrix(&v, M, N);
    construct2DMatrix(&v, M, N);
    random2DMatrix(&v, M, N);

  }


  start = omp_get_wtime();
  // call function to find number of friends.
  num_triple_friends = MPI_count_friends_of_ten(M, N, v);
  end = omp_get_wtime();

  timer = end - start;


  printf("MPI rank <%d>: number of triple friends=%d\n", my_rank+1, num_triple_friends);

  if (my_rank == 0){
    // Time
    printf("The time used for MPI_count_friends_of_ten is %fs \n", timer);


    // Deallocation of 2D array v
    free2D(v);
  }

  MPI_Finalize();
  return 0;

}
