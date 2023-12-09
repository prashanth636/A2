#include <cstdio>
#include <cstdlib>
#include <cuda.h>
#include <cuda_runtime.h>
#include <cmath>

#define BLOCK_SIZE 256

extern "C" __global__ void Gaussian_kernel_density_estimate(float* X, float* Y, int N, float h) {
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index < N) {
        float sum = 0.0f;
        for (int i = 0; i < N; ++i) {
            float diff = X[index] - X[i];
            float weight = exp(-diff * diff / (2.0f * h * h));
            sum += weight;
        }
        Y[index] = sum / (N * h * sqrtf(2.0f * 3.141592654f));
    }
}