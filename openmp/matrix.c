#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const int N = 600;

int main()
{
    omp_set_num_threads(8);
    float A[N][N], B[N][N], C[N][N];
    #pragma omp parallel for
     for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = 1.0f;
            B[i][j] = 1.0f;
            C[i][j] = 0.0f;
        }
    }

    double begin = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    double end = omp_get_wtime()-begin;
    printf("time %.6f second\n", end);
}
