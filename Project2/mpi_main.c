#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "mpi_count_friends_of_ten.c"

#include "functions.h"


int main(int argc, char *argv[]){

/*
  if (argc < 2){

        printf("Filename required.\n");
        exit(0);
  }
*/

  int M = 0, N = 0, rank, num_triple_friends;
  int **v = NULL;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0){
    // Test
    //test_MPI_count_friends_of_ten()

    // Decide the values for M and N


    // Allocate 2D array v and assign it with suitable values


  }

  //num_triple_friends = MPI_count_friends_of_ten(M, N, v);

  //printf("MPI rank <%d>: number of triple friends=%d\n", rank, num_triple_friends);

  if (rank == 0){
    // Deallocation of 2D array v
    free2D(v);
  }

  MPI_Finalize();
  return 0;

}
