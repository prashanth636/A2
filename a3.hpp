/*  Prasanth Varma
 *  Vegesna
 *  pvegesna
 */

#ifndef A3_HPP
#ifndef A3_HPP
#define A3_HPP

#include <cstdio>
#include <cstdlib>
#include <cuda.h>
#include <cuda_runtime.h>
#include <cmath>
#include "a3.cu"

#define BLOCK_SIZE 256

//extern "C" void Gaussian_kernel_density_estimate(float* X, float* Y, int N, float h);

void gaussian_kde(int n, float h, const std::vector<float>& x, std::vector<float>& y) {
    wrapper(n, h, x,)
} // gaussian_kde

#endif // A3_HPP
