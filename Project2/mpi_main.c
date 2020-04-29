#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "mpi_count_friends_of_ten.c"

#include "functions.h"


int main(int argc, char** argv){


  // Initialization
  int my_rank, numprocs;

  int M, N, num_triple_friends;
  int **v = NULL;

  // MPI initializations
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size (MPI_COMM_WORLD, &numprocs);


  if (my_rank == 0){
    // Test
    //test_MPI_count_friends_of_ten()

    // Decide the values for M and N
    M = 4;
    N = 5;

    // Allocate 2D array v and assign it with suitable values
    alloc2DMatrix(&v, M, N);

    construct2DMatrix(&v, M, N);

    int v_exact[4][5] =
    {
      {1, 5, 6, 3, 1},
      {2, 4, 4, 1, 7},
      {7, 2, 3, 1, 2},
      {3, 2, 2, 5, 3},
    };

    for (int i = 0; i < M; i++){
      for (int j = 0; j < N; j++){
        v[i][j] = v_exact[i][j];
      }
    }

  }

  //MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
  //MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);


  num_triple_friends = MPI_count_friends_of_ten(M, N, v);

  printf("MPI rank <%d>: number of triple friends=%d\n", my_rank, num_triple_friends);

  if (my_rank == 0){
    // Deallocation of 2D array v
    free2D(v);
  }

  MPI_Finalize();
  return 0;

}
