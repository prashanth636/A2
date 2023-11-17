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
using namespace std;

vector<short int> createLocalSample(std::vector<short int>& Xi, int p, int interval) {
	vector<short int> localSample(p);
	for (int i = 0; (i < Xi.size()) && (i/interval <= p); i = i + interval) {
		localSample.push_back(Xi[i]);
	}
	return localSample;
}

void isort(std::vector<short int>& Xi, MPI_Comm comm) {
	
	int size, rank; 
    MPI_Comm_size(comm, &size);
    MPI_Comm_rank(comm, &rank);
	
	std::ostringstream oss, oss2;
    for (const auto& num : Xi) {
        oss << num << " ";
    }
	std::string input = oss.str();
	sort(Xi.begin(), Xi.end());
	
	std::vector<short int> localSample = createLocalSample(Xi, size, Xi.size()/size);
	
	int localSize = localSample.size();
    vector<int> gatheredVector;

    if (rank == 0) {
        gatheredVector.resize(localSize * size);
    }
    MPI_Gather(localSample.data(), localSize, MPI_INT,
               gatheredVector.data(), localSize, MPI_INT,
               0, comm);
    if (rank == 0) {
		sort(gatheredVector.begin(), gatheredVector.end());
        std::cout << "Gathered Vector on Processor 0: ";
        for (int val : gatheredVector) {
            std::cout << val << ".";
        }
        std::cout << std::endl;
	}
	
	for (const auto& num : localSample) {
		oss2 << num << " ";
	}
    std::string result = oss2.str();
    std::cout << "Rank: " << rank << " Input string: " << input << "\n\tResult: " << result << std::endl;
} // isort

#endif // A2_HPP
