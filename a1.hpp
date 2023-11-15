/*  Prasanth Varma
 *  Vegesna
 *  pvegesna
 *  person number: 50538639
 */

#ifndef A1_HPP
#define A1_HPP

#include <vector>


void filter_2d(long long int n, long long int m, const std::vector<float>& K, std::vector<float>& A) {
	std::vector<float> R(n * m);
	
	#pragma omp parallel
	{
		#pragma omp for 			//applying parallel for over the given number of rows
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				#pragma omp task			//creating fine-grained tasks on each element of the row
				{
					int x = i * m + j;
					if ( i == 0 || j == 0 || i == n-1 || j == m-1) {
						R[x] = A[x];		//copying the values in the borders
					} else {
						for (int ki = 0; ki < 3; ++ki) {
							for (int kj = 0; kj < 3; ++kj) {
								A[x] += A[x + (ki - 1)*m + kj] * K[ki * 3 + kj];  // multiplying the kernel elements with submatrix elements and accumulating.
							}
						}
					}
				}
			}
		}
    } //the task wait gets implicitly called here at the end of the parallel construct.
} // filter_2d

#endif // A1_HPP
