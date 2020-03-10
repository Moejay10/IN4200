#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <omp.h> // OpenMP

#include "functions.h"


int main(int argc, char *argv[]){

  if (argc < 2){

        printf("Filename required.\n");
        exit(0);
  }
  char* filename = argv[1];

  int Nodes = 0;
  int N_links = 0;
  double start, end, timer;


  char **table2D;

/*

  if (strcmp(filename, "web-NotreDame.txt") == 0 )
  {
    printf("File is to big for read_graph_from_file_1 \n");
  }

  else{
        // Set up time for clocking the task
        start = omp_get_wtime();

        read_graph_from_file_1(filename, &Nodes, &table2D); // Do not use to big of a file

        end = omp_get_wtime();
        timer = end - start;

        printf("Time used for read_graph_from_file_1 is %fs \n", timer);

        int Total_involvements;
        int *num_involvements = (int*)malloc(Nodes*sizeof(int));

        start = omp_get_wtime();
        Total_involvements = count_mutual_links1(Nodes, table2D, num_involvements);
        end = omp_get_wtime();

        timer = end - start;
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

      start = omp_get_wtime();
      top_n_webpages(Nodes, num_involvements, 3);
      end = omp_get_wtime();

      timer = end - start;
      printf("Time used for top_n_webpages is %fs \n", timer);

      free(num_involvements);
      //free2D(table2D);



      printf("\n");
      printf("OpenMP Parallelisation 1 \n");

      int Total_involvements2;
      int *num_involvements2 = (int*)malloc(Nodes*sizeof(int));
      int num_threads = 2;

      start = omp_get_wtime();
      Total_involvements2 = OMP_count_mutual_links1(Nodes, table2D, num_involvements2, num_threads);
      end = omp_get_wtime();

      timer = end - start;
      printf("Time used for OMP_count_mutual_links1 is %fs \n", timer);

      printf("Total number of mutual web linkage are %d \n", Total_involvements2);

      start = omp_get_wtime();
      OMP_top_n_webpages(Nodes, num_involvements2, 3, num_threads);
      end = omp_get_wtime();

      timer = end - start;
      printf("Time used for OMP_top_n_webpages is %fs \n", timer);

      free(num_involvements2);
      free2D(table2D);

    }

*/

  printf("\n");

  int *row_ptr = NULL;
  int *col_idx = NULL;

  start = omp_get_wtime();
  read_graph_from_file_2(filename, &Nodes, &N_links, &row_ptr, &col_idx);

  end = omp_get_wtime();
  timer = end - start;

  printf("Time used for read_graph_from_file_2 is %fs \n", timer);
  //int N_rows = Nodes + 1;


  //printVectorToTerminal2(row_ptr, col_idx, N_rows, N_links);
  //WriteVectortoFile2(row_ptr, col_idx, N_rows, N_links);

  int Total_involvements1;
  int *num_involvements1 = (int*)malloc(Nodes*sizeof(int));

  start = omp_get_wtime();
  Total_involvements1 = count_mutual_links2(Nodes, N_links, row_ptr, col_idx, num_involvements1);
  end = omp_get_wtime();

  timer = end - start;
  printf("Time used for count_mutual_links2 is %fs \n", timer);

  printf("Total number of mutual web linkage are %d \n", Total_involvements1);

  //printf("Number of involvements per webpage is \n");
  //printVectorToTerminal(num_involvements1, Nodes);

  start = omp_get_wtime();
  //top_n_webpages(Nodes, num_involvements1, 3);
  end = omp_get_wtime();

  timer = end - start;
  printf("Time used for top_n_webpages is %fs \n", timer);

  free(num_involvements1);
  //free(col_idx);
  //free(row_ptr);







printf("\n");
printf("OpenMP Parallelisation 2 \n");

int Total_involvements3;
int *num_involvements3 = (int*)malloc(Nodes*sizeof(int));
int num_threads1 = 2;

start = omp_get_wtime();
Total_involvements3 = OMP_count_mutual_links2(Nodes, N_links, row_ptr, col_idx, num_involvements3, num_threads1);
end = omp_get_wtime();

timer = end - start;
printf("Time used for OMP_count_mutual_links2 is %fs \n", timer);

printf("Total number of mutual web linkage are %d \n", Total_involvements3);

//printf("Number of involvements per webpage is \n");
//printVectorToTerminal(num_involvements3, Nodes);

start = omp_get_wtime();
//OMP_top_n_webpages(Nodes, num_involvements1, 3, num_threads1);
end = omp_get_wtime();

timer = end - start;
printf("Time used for OMP_top_n_webpages is %fs \n", timer);

free(num_involvements3);
free(col_idx);
free(row_ptr);


  return 0;
}
