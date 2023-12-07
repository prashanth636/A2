/*  Prasanth Varma
 *  Vegesna
 *  pvegesna
 *  person number: 50538639
 */

#ifndef A1_HPP
#define A1_HPP

#include <vector>


void filter_2d(long long int n, long long int m, const std::vector<float>& K, std::vector<float>& A) {
	std::vector<float> R(std::vector<float>(n * m, 0.0));
	
	#pragma omp parallel
	{
		#pragma omp for 			//applying parallel for over the given number of rows
		for (int i = 1; i < n - 1; ++i) {
			for (int j = 1; j < m - 1; ++j) {
				int x = i * m + j;
				for (int ki = -1; ki <= 1; ++ki) {
					for (int kj = -1; kj <= 1; ++kj) {
						A[x] += A[(i + ki) * m + (j + kj)] * K[(ki + 1) * 3 + (kj + 1)];  // multiplying the kernel elements with submatrix elements and accumulating.
					}
				}
			}
		}
    } //the task wait gets implicitly called here at the end of the parallel construct.
} // filter_2d

#endif // A1_HPP
