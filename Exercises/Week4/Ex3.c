// Testing the memory bandwidth with the scale STREAM micro benchmark.

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


int main(int argc, char const *argv[]) {
    if (argc < 4) {
        printf("Usage: ./prog.exe N_ELEMENTS\n");
        return 1;
    }
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int p = atoi(argv[3]);


    double A[n][m];
    double B[m][p];
    double C[n][p];

    for(int i = 0; i < n; i++){
      for (int j = 0; j < m; j++){
        A[i][j] = i*j;
      }
    }

    for(int i = 0; i < m; i++){
      for (int j = 0; j < p; j++){
        B[i][j] = i*j;
      }

    }

    clock_t start = clock();
    // Matrix multiplication
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < p; j++){
        for (int k = 0; k < m; k++){
          C[i][j] = A[i][k]*B[j][k];
        }
      }
    }
    clock_t end = clock();

    double total = (double)(end - start)/CLOCKS_PER_SEC;


    printf("Time: %f\n", total);


    return 0;
}
