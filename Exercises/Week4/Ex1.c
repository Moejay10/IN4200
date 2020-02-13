// Testing the memory bandwidth with the scale STREAM micro benchmark.

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


int main(int argc, char const *argv[]) {
    if (argc < 2) {
        printf("Usage: ./prog.exe N_ELEMENTS\n");
        return 1;
    }
    int N = atoi(argv[1]);

    double *A = malloc(N * sizeof *A);
    double *B = malloc(N * sizeof *B);

    for (size_t i = 0; i < N; i++) {
        A[i] = i;
        B[i] = i;
    }

    double s = 1.5;

    clock_t start = clock();
    for (size_t i = 0; i < N; i++) {
        A[i] = s*B[i];
    }
    clock_t end = clock();

    double total = (double)(end - start)/CLOCKS_PER_SEC;
    int n_bytes = N * sizeof *A;

    printf("Time: %lfms\n", 1000*total);
    printf("Bytes per sec: %3e\n", n_bytes/total);
    printf("Flops: %3e\n", N/total);

    free(A);
    free(B);

    return 0;
}
