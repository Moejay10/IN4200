#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <omp.h> // OpenMP

#include "read_graph_from_file1.c"
#include "read_graph_from_file2.c"

#include "count_mutual_links1.c"
#include "count_mutual_links2.c"

#include "top_n_webpages.c"

#include "functions.h"


int main(int argc, char *argv[]){


  if (argc < 2){

        printf("Filename required.\n");
        exit(0);
  }
  char* filename = argv[1];

  int Nodes = 0;
  int N_links = 0;
  int Nodes1 = 0;
  int N_links1 = 0;
  clock_t start, end;
  double timer;

  char **table2D;
  char **table2D_1;

  int *row_ptr = NULL;
  int *col_idx = NULL;

  int *row_ptr1 = NULL;
  int *col_idx1 = NULL;


// ------------------------- TEST PROGRAM ----------------------------//

  printf("TEST PROGRAM PART \n");

  test_read_graph_from_file1();
  test_read_graph_from_file2();
  printf("\n");

  char *openmp;
  openmp = "no";
  test_count_mutual_links1(openmp, 1);
  test_count_mutual_links2(openmp, 1);

  printf("\n");

  openmp = "yes";
  int numberofThreads = 2;
  test_count_mutual_links1(openmp, numberofThreads);
  test_count_mutual_links2(openmp, numberofThreads);

  printf("\n");

  openmp = "no";
  numberofThreads = 1;
  int n = 8;
  test_top_n_webpages(openmp, n, numberofThreads);

  printf("\n");

  openmp = "yes";
  numberofThreads = 2;
  n = 8;
  test_top_n_webpages(openmp, n, numberofThreads);

  printf("\n");
  printf("\n");


  if (strcmp(filename, "web-NotreDame.txt") == 0 )
  {
    printf("File is to big for read_graph_from_file_1 \n");
  }

  else{
        // Set up time for clocking the task
        start = clock();
        read_graph_from_file1(filename, &Nodes, &table2D); // Do not use to big of a file
        end = clock();
        timer = (double)(end - start)/CLOCKS_PER_SEC;

        printf("Time used for read_graph_from_file_1 is %fs \n", timer);

        int Total_involvements;
        int *num_involvements = (int*)malloc(Nodes*sizeof(int));

        start = clock();
        Total_involvements = count_mutual_links1(Nodes, table2D, num_involvements);
        end = clock();

        timer = (double)(end - start)/CLOCKS_PER_SEC;
        printf("Time used for count_mutual_links1 is %fs \n", timer);

        //printf("Total number of mutual web linkage are %d \n", Total_involvements);


    if (strcmp(filename, "100nodes_graph.txt") == 0 )
    {
      printf("table2D is too big to print out \n");
    }

    else{
          //printMatrixToTerminal(table2D, Nodes);
          //WriteMatrixtoFile(table2D, Nodes);

          //printf("Number of involvements per webpage is \n");
          //printVectorToTerminal(num_involvements, Nodes);


        }

      printf("Total number of mutual web linkage are %d \n", Total_involvements);

      start = clock();
      top_n_webpages(Nodes, num_involvements, 8);
      end = clock();

      timer = (double)(end - start)/CLOCKS_PER_SEC;
      printf("Time used for top_n_webpages is %fs \n", timer);

      free(num_involvements);
      free2D(table2D);
    }



  printf("\n");


  start = clock();
  read_graph_from_file2(filename, &Nodes, &N_links, &row_ptr, &col_idx);
  end = clock();

  timer = (double)(end - start)/CLOCKS_PER_SEC;

  printf("Time used for read_graph_from_file_2 is %fs \n", timer);



  printVectorToTerminal2(row_ptr, col_idx, Nodes + 1, N_links);
  //WriteVectortoFile2(row_ptr, col_idx, Nodes + 1, N_links);

  int Total_involvements1;
  int *num_involvements1 = (int*)malloc(Nodes*sizeof(int));

  start = clock();
  Total_involvements1 = count_mutual_links2(Nodes, N_links, row_ptr, col_idx, num_involvements1);
  end = clock();

  timer = (double)(end - start)/CLOCKS_PER_SEC;
  printf("Time used for count_mutual_links2 is %fs \n", timer);

  printf("Total number of mutual web linkage are %d \n", Total_involvements1);

  //printf("Number of involvements per webpage is \n");
  //printVectorToTerminal(num_involvements1, Nodes);

  start = clock();
  top_n_webpages(Nodes, num_involvements1, 8);
  end = clock();

  timer = (double)(end - start)/CLOCKS_PER_SEC;
  printf("Time used for top_n_webpages is %fs \n", timer);

  free(num_involvements1);
  free(col_idx);
  free(row_ptr);




  if (strcmp(filename, "web-NotreDame.txt") == 0 )
  {
    printf("File is to big for read_graph_from_file_1 \n");
  }

  else{
  // Set up time for clocking the task
  start = clock();
  read_graph_from_file1(filename, &Nodes1, &table2D_1); // Do not use to big of a file
  end = clock();
  timer = (double)(end - start)/CLOCKS_PER_SEC;

  printf("Time used for read_graph_from_file_1 is %fs \n", timer);

  printf("\n");
  printf("OpenMP Parallelisation 1 \n");

  int Total_involvements2;
  int *num_involvements2 = (int*)malloc(Nodes*sizeof(int));
  int num_threads = 2;

  start = clock();
  Total_involvements2 = OMP_count_mutual_links1(Nodes, table2D_1, num_involvements2, num_threads);
  end = clock();

  timer = (double)(end - start)/CLOCKS_PER_SEC;
  printf("Time used for OMP_count_mutual_links1 is %fs \n", timer);

  printf("Total number of mutual web linkage are %d \n", Total_involvements2);

  start = clock();
  OMP_top_n_webpages(Nodes, num_involvements2, 8, num_threads);
  end = clock();

  timer = (double)(end - start)/CLOCKS_PER_SEC;
  printf("Time used for OMP_top_n_webpages is %fs \n", timer);

  free(num_involvements2);
  free2D(table2D_1);

  }

  printf("\n");
  printf("OpenMP Parallelisation 2 \n");

  start = clock();
  read_graph_from_file2(filename, &Nodes1, &N_links1, &row_ptr1, &col_idx1);
  end = clock();

  timer = (double)(end - start)/CLOCKS_PER_SEC;

  printf("Time used for read_graph_from_file_2 is %fs \n", timer);

  int Total_involvements3;
  int *num_involvements3 = (int*)malloc(Nodes*sizeof(int));
  int num_threads1 = 2;

  start = clock();
  Total_involvements3 = OMP_count_mutual_links2(Nodes1, N_links1, row_ptr1, col_idx1, num_involvements3, num_threads1);
  end = clock();

  timer = (double)(end - start)/CLOCKS_PER_SEC;
  printf("Time used for OMP_count_mutual_links2 is %fs \n", timer);

  printf("Total number of mutual web linkage are %d \n", Total_involvements3);

  //printf("Number of involvements per webpage is \n");
  //printVectorToTerminal(num_involvements3, Nodes);

  start = clock();
  OMP_top_n_webpages(Nodes1, num_involvements3, 8, num_threads1);
  end = clock();

  timer = (double)(end - start)/CLOCKS_PER_SEC;
  printf("Time used for OMP_top_n_webpages is %fs \n", timer);

  free(num_involvements3);
  free(col_idx1);
  free(row_ptr1);



  return 0;
}
