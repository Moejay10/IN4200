#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <omp.h> // OpenMP

#include "read_graph_from_file1.c"
#include "read_graph_from_file2.c"

#include "OMP_count_mutual_links1.c"
#include "OMP_count_mutual_links2.c"

#include "OMP_top_n_webpages.c"

#include "functions.h"


int main(int argc, char *argv[]){


  if (argc < 3){

        printf("Filename and number of num_threads is required.\n");
        exit(0);
  }
  char* filename = argv[1];
  int num_threads = atoi(argv[2]);


  int Nodes = 0;
  int N_links = 0;
  int Nodes1 = 0;
  int n = 8;
  double start, end, timer;

  char **table2D;

  int *row_ptr = NULL;
  int *col_idx = NULL;


// ------------------------- TEST PROGRAM ----------------------------//

  printf("\n TEST PROGRAM PART \n");

  test_read_graph_from_file1();
  test_read_graph_from_file2();
  printf("\n");

  test_OMP_count_mutual_links1(num_threads);
  test_OMP_count_mutual_links2(num_threads);

  printf("\n");

  test_OMP_top_n_webpages(8, num_threads);

  printf("\n");
  printf("\n");

  // ------------------------- MAIN PROGRAM ----------------------------//
  printf("\n MAIN PROGRAM PART \n");
  printf("\n");

  // ------------------------- Parallelized version ----------------------------//
  printf("\n Parallelized version of the code running \n \n");

  if (strcmp(filename, "web-NotreDame.txt") == 0 )
  {
    printf("\n File is to big for read_graph_from_file_1 \n");
  }

  else
  {
    // Set up time for clocking the task
    start = omp_get_wtime();
    read_graph_from_file1(filename, &Nodes, &table2D); // Do not use to big of a file
    end = omp_get_wtime();
    timer = end - start;

    printf("Time used for read_graph_from_file_1 is %fs \n", timer);

    int Total_involvements1;
    int *num_involvements1 = (int*)malloc(Nodes*sizeof(int));

    start = omp_get_wtime();
    Total_involvements1 = OMP_count_mutual_links1(Nodes, table2D, num_involvements1, num_threads);
    end = omp_get_wtime();

    timer = end - start;
    printf("Time used for OMP_count_mutual_links1 is %fs \n", timer);

    printf("Total number of mutual web linkage are %d \n", Total_involvements1);

    start = omp_get_wtime();
    OMP_top_n_webpages(Nodes, num_involvements1, n, num_threads);
    end = omp_get_wtime();

    timer = end - start;
    printf("Time used for OMP_top_n_webpages is %fs \n", timer);

    free(num_involvements1);
    free2D(table2D);

  }


  start = omp_get_wtime();
  read_graph_from_file2(filename, &Nodes1, &N_links, &row_ptr, &col_idx);
  end = omp_get_wtime();

  timer = end - start;

  printf("Time used for read_graph_from_file_2 is %fs \n", timer);

  int Total_involvements2;
  int *num_involvements2 = (int*)malloc(Nodes1*sizeof(int));

  start = omp_get_wtime();
  Total_involvements2 = OMP_count_mutual_links2(Nodes1, N_links, row_ptr, col_idx, num_involvements2, num_threads);
  end = omp_get_wtime();

  timer = end - start;
  printf("Time used for OMP_count_mutual_links2 is %fs \n", timer);

  printf("Total number of mutual web linkage are %d \n", Total_involvements2);

  start = omp_get_wtime();
  OMP_top_n_webpages(Nodes1, num_involvements2, n, num_threads);
  end = omp_get_wtime();

  timer = end - start;
  printf("Time used for OMP_top_n_webpages is %fs \n", timer);

  free(num_involvements2);
  free(col_idx);
  free(row_ptr);


  return 0;
}
