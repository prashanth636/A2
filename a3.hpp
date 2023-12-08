/*  Prasanth Varma
 *  Vegesna
 *  pvegesna
 */

#ifndef A3_HPP
#define A3_HPP

#include <cstdio>
#include <cstdlib>
#include <cuda.h>
#include <cuda_runtime.h>
#include <cmath>
#include <a3.cu>

#define BLOCK_SIZE 256

void gaussian_kde(int n, float h, const std::vector<float>& x, std::vector<float>& y) {
    float* X_d, * Y_d;

    cudaMalloc(&X_d, n * sizeof(float));
    cudaMalloc(&Y_d, n * sizeof(float));

    // Copy data from host to device
    cudaMemcpy(X_d, x.data(), n * sizeof(float), cudaMemcpyHostToDevice);
    
    Gaussian_kernel_density_estimate<<<(n + BLOCK_SIZE - 1) / BLOCK_SIZE, BLOCK_SIZE>>>(X_d, Y_d, n, h);

    // Copy data from device to host
    cudaMemcpy(y.data(), Y_d, n * sizeof(float), cudaMemcpyDeviceToHost);

    cudaFree(X_d);
    cudaFree(Y_d);
} // gaussian_kde

#endif // A3_HPP
