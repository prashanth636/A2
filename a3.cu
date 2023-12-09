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

void wrapper(int n, float h, const std::vector<float>& x, std::vector<float>& y) {
    float* X_d, * Y_d;

    cudaMalloc(&X_d, n * sizeof(float));
    cudaMalloc(&Y_d, n * sizeof(float));

    // Copy data from host to device
    cudaMemcpy(X_d, x.data(), n * sizeof(float), cudaMemcpyHostToDevice);

    int num_blocks = (n + BLOCK_SIZE - 1) / BLOCK_SIZE;
    Gaussian_kernel_density_estimate<<<num_blocks, BLOCK_SIZE>>>(X_d, Y_d, n, h);

    // Copy data from device to host
    cudaMemcpy(y.data(), Y_d, n * sizeof(float), cudaMemcpyDeviceToHost);

    cudaFree(X_d);
    cudaFree(Y_d);
}