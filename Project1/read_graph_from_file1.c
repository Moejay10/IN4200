#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "functions.h"


void read_graph_from_file1(char *filename, int *Nodes, char ***table2D){
/// -----------------------------------------------------------
// # Read file and extract data
// Input:
// * filename:  Holding the name of the web graph
// * Nodes:     Empty parameter

/// -----------------------------------------------------------
    int row = 0;
    int col = 0;
    int Edges = 0;
    FILE *datafile;
    datafile = fopen(filename, "r");

    if (datafile == NULL) {
        printf("Failure to open file %s\n", filename);
        exit(0);
    }

    fscanf(datafile, "%*[^\n]\n");                 // Skip lines to relevant data
    fscanf(datafile, "%*[^\n]\n");
    fscanf(datafile, "# Nodes: %d Edges: %d\n", &*Nodes, &Edges); // Extract data
    //fscanf(datafile, "# Nodes: %d\n", &*Nodes); // Extract data
    fscanf(datafile, "%*[^\n]\n");

    int N = *Nodes;

    alloc2DMatrix(table2D, N);
    construct2DMatrix(table2D, N);

    while (fscanf(datafile, "%d %d", &col, &row) != EOF){ // Scan to end of file

        if (row == col){
          continue;                                       // Assure we skip self links
        }
        (*table2D)[row][col] = 1;
    }

    fclose (datafile);
}



void test_read_graph_from_file1(){
  /* Function to test read_graph_from_file1
  using the example illustrated in the home exam. */

  // Hard coding the exact values:
  int N_exact = 8;
  int Matrix_exact[8][8] =
  {
    {0, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 1, 1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 1, 0},
    {0, 0, 0, 1, 1, 0, 0, 1},
    {0, 0, 0, 0, 1, 0, 0, 1},
    {0, 0, 0, 0, 1, 1, 1, 0},
  };

  // Provide the parameters for the function:
  int N_test = 0;
  char **table2D;
  char *filename;
  filename = "8nodes_graph.txt";
  read_graph_from_file1(filename, &N_test, &table2D);

  // Parameter for counting the number of errors in the extracted matrix
  int numberofErrors = 0;

  // Verifying the results between read_graph_from_file1 and the exact answer:
  // First asserting the number of nodes
  if (N_exact != N_test){ // If N_test is wrong, then we cant compare the matrices
    printf("The number of Nodes was extracted incorrectly in function read_graph_from_file1 \n");
    printf("N_exact is: %d, while the extracted N_test is: %d \n", N_exact, N_test);
  }
  else
  {
    printf("The number of Nodes was extracted correctly in function read_graph_from_file1 \n");
    printf("N_exact is: %d and extracted N_test is: %d \n", N_exact, N_test);

    // Then we assert the values in the extracted matrix
    for (int i = 0; i < N_exact; i++)
    {
      for (int j = 0; j < N_exact; j++)
      {
        if (Matrix_exact[i][j] != table2D[i][j])
        {
          numberofErrors++;
        }
      }
    }

    if (numberofErrors > 0)
    {
      printf("read_graph_from_file1 has %d errors in the matrix. \n", numberofErrors);
    }

    else
    {
      printf("read_graph_from_file1 has no errors in the matrix. \n");
    }
  }

}
