#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

//#include "a3.hpp"
#include <functional>

#include <cstdio>
#include <cstdlib>
#include <cuda.h>
#include <cuda_runtime.h>
#include <cmath>
//#include "a3.cu"

#define BLOCK_SIZE 256

__global__ void Gaussian_kernel_density_estimate(float* X, float* Y, int N, float h) {
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

void gaussian_kde(int n, float h, const std::vector<float>& x, std::vector<float>& y) {
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
} // gaussian_kde

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "usage: " << argv[0] << " n h" << std::endl;
        return -1;
    }

    int n = std::atoi(argv[1]);
    float h = std::atof(argv[2]);

    if (n < 32) {
        std::cout << "hey, n is too small even for debugging!" << std::endl;
        return -1;
    }

    if (h < 0.00001) {
        std::cout << "this bandwidth is too small" << std::endl;
        return -1;
    }

    // in and out (in is set to 1s for fun)
    std::vector<float> x(n);
    std::vector<float> y(n, 0.0);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::lognormal_distribution<float> N(0.0, 1.0);
    std::generate(std::begin(x), std::end(x), std::bind(N, gen));

    // now running your awesome code from a3.hpp
    auto t0 = std::chrono::system_clock::now();

    gaussian_kde(n, h, x, y);

    auto t1 = std::chrono::system_clock::now();

    auto elapsed_par = std::chrono::duration<double>(t1 - t0);
    std::cout << elapsed_par.count() << std::endl;

    return 0;
} // main
