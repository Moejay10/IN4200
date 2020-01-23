#include <stdio.h>
#include <stdlib.h>

int main(){
int m, n;
double **A, **A1;

m = n = 10;  // I'm picking m and n very, very big just to make sure the effect is noticeable.

A = (double **)malloc(m * sizeof(double *));
A[0] = (double *)malloc(m * n * sizeof(double)); // This is the actual underlying 1d array of size m * n.

A1 = (double **)malloc(m * sizeof(double *));
A1[0] = (double *)malloc(m * n * sizeof(double)); // This is the actual underlying 1d array of size m * n.

for (int i = 1; i < m; i ++) {
       A[i] = &(A[0][n * i]);  // This line probably requires some unpacking. Just note that A[0][i * n] is the i'th row of the matrix A
       A1[i] = &(A1[0][n * i]);  // This line probably requires some unpacking. Just note that A[0][i * n] is the i'th row of the matrix A
     }



for (int i = 0; i < m; i++){
  for (int j = 0; j < n; j++){
    A[i][j] = i*j;
  }
}

for (int j = 0; j < m; j++){
  for (int i = 0; i < n; i++){
    A1[i][j] = i*j;
  }
}

for (int i = 0; i < m; i++){
  for (int j = 0; j < n; j++){
    printf("\n Difference Between Rowwise and Colwise: %f", A[i][j]-A1[i][j]);
  }
}
printf("\n");

free(A[0]);
free(A);
free(A1[0]);
free(A1);
return 0;
}
