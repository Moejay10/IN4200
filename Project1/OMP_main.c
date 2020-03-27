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
  // Defining variables
  char* filename = argv[1];
  int num_threads = atoi(argv[2]);

  double start, end;
  double timer[6];

  for (int i = 0; i < 6; i++){
    timer[i] = 0;
  }

  int runs = 10; // Number of time running the program to find the average time




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
  for (int i = 0; i < runs; i++){

    int Nodes = 0;
    int N_links = 0;
    int Nodes1 = 0;
    int n = 8;

    char **table2D;

    int *row_ptr = NULL;
    int *col_idx = NULL;

    // Data in table format
    if (strcmp(filename, "web-NotreDame.txt") == 0 )
    {
      printf("\n File is to big for read_graph_from_file_1 \n");
    }

    else
    {
      // Set up average time for clocking the task
      start = omp_get_wtime();
      read_graph_from_file1(filename, &Nodes, &table2D); // Do not use to big of a file
      end = omp_get_wtime();
      timer[0] += end - start;

      if (i == runs - 1){
        timer[0] /= runs;
        printf("The average time used for read_graph_from_file_1 is %fs \n", timer[0]);

      }

      int Total_involvements1;
      int *num_involvements1 = (int*)malloc(Nodes*sizeof(int));

      start = omp_get_wtime();
      Total_involvements1 = OMP_count_mutual_links1(Nodes, table2D, num_involvements1, num_threads);
      end = omp_get_wtime();
      timer[1] += end - start;

      if (i == runs - 1){
        timer[1] /= runs;
        printf("The average time used for OMP_count_mutual_links1 is %fs \n", timer[1]);

        printf("Total number of mutual web linkage are %d \n", Total_involvements1);
      }


      start = omp_get_wtime();
      OMP_top_n_webpages(Nodes, num_involvements1, n, num_threads);
      end = omp_get_wtime();
      timer[2] += end - start;

      if (i == runs - 1){
        timer[2] /= runs;
        printf("The average time used for OMP_top_n_webpages is %fs \n", timer[2]);
      }

      free(num_involvements1);
      free2D(table2D);

    }

    // Data in CRS format
    start = omp_get_wtime();
    read_graph_from_file2(filename, &Nodes1, &N_links, &row_ptr, &col_idx);
    end = omp_get_wtime();
    timer[3] += end - start;

    if (i == runs - 1){
      timer[3] /= runs;
      printf("The average time used for read_graph_from_file_2 is %fs \n", timer[3]);
    }

    int Total_involvements2;
    int *num_involvements2 = (int*)malloc(Nodes1*sizeof(int));

    start = omp_get_wtime();
    Total_involvements2 = OMP_count_mutual_links2(Nodes1, N_links, row_ptr, col_idx, num_involvements2, num_threads);
    end = omp_get_wtime();
    timer[4] += end - start;

    if (i == runs - 1){
      timer[4] /= runs;
      printf("The average time used for OMP_count_mutual_links2 is %fs \n", timer[4]);

      printf("Total number of mutual web linkage are %d \n", Total_involvements2);
    }


    start = omp_get_wtime();
    OMP_top_n_webpages(Nodes1, num_involvements2, n, num_threads);
    end = omp_get_wtime();
    timer[5] += end - start;

    if (i == runs - 1){
      timer[5] /= runs;
      printf("The average time used for OMP_top_n_webpages is %fs \n", timer[5]);
    }

    free(num_involvements2);
    free(col_idx);
    free(row_ptr);
  }


  return 0;
}
