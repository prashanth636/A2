/*  YOUR_FIRST_NAME
 *  YOUR_LAST_NAME
 *  YOUR_UBIT_NAME
 */

#ifndef A2_HPP
#define A2_HPP

#include <vector>
#include <mpi.h>
#include <iostream>
#include <sstream>

void isort(std::vector<short int>& Xi, MPI_Comm comm) {
	
	int number_of_process, rank_of_process; 
    MPI_Comm_size(comm, &number_of_process);
    MPI_Comm_rank(comm, &rank_of_process);
	
	std::ostringstream oss;
    for (const auto& num : Xi) {
        oss << num << " ";
    }

    std::string result = oss.str();

    // Print the result
    std::cout << "Rank: " << rank_of_process << " Resulting string: " << result << std::endl;
} // isort

#endif // A2_HPP
