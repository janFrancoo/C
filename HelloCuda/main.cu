#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cuda.h>
#include <cuda_runtime.h>

#define N 10000000

/*
void vectorAddition(int n, float *vec1, float *vec2, float *out) {
    for (int i=0; i<n; i++)
        out[i] = vec1[i] + vec2[i];
}
*/

__global__ void vectorAddition(int n, float *vec1, float *vec2, float *out) {
    for (int i=0; i<n; i++)
        out[i] = vec1[i] + vec2[i];
}

int main() {
    float *vec1, *vec2, *out;
    float *d_vec1, *d_vec2, *d_out;

    vec1 = (float *) malloc(sizeof(float) * N);
    vec2 = (float *) malloc(sizeof(float) * N);
    out = (float *) malloc(sizeof(float) * N);

    for (int i=0; i<N; i++) {
        vec1[i] = 1.0f;
        vec2[i] = 1.0f;
    }

    cudaMalloc((void**) &d_vec1, sizeof(float) * N);
    cudaMalloc((void**) &d_vec2, sizeof(float) * N);
    cudaMalloc((void**) &d_out, sizeof(float) * N);

    cudaMemcpy(d_vec1, vec1, sizeof(float) * N, cudaMemcpyHostToDevice);
    cudaMemcpy(d_vec2, vec2, sizeof(float) * N, cudaMemcpyHostToDevice);

    clock_t begin = clock();
    // vectorAddition(N, vec1, vec2, out);
    vectorAddition<<<1,1>>>(N, d_vec1, d_vec2, d_out);
    clock_t end = clock();
    double elapsedTime = (double) (end - begin) / CLOCKS_PER_SEC;

    cudaMemcpy(out, d_out, sizeof(float) * N, cudaMemcpyDeviceToHost);

    cudaFree(d_vec1);
    cudaFree(d_vec2);
    cudaFree(d_out);

    free(vec1);
    free(vec2);
    free(out);

    printf("%f", elapsedTime);

    return 0;
}
