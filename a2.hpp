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

vector<short int> createLocalSample(std::vector<short int>& Xi, int p, int interval, bool pivot) {
	vector<short int> localSample;
	for (int i = 0; (i < Xi.size()) && (i/interval <= p - 1); i = i + interval) {
		if(!(pivot && i == 0)) localSample.push_back(Xi[i]);
	}
	return localSample;
}

void isort(std::vector<short int>& Xi, MPI_Comm comm) {
	
	int size, rank; 
    MPI_Comm_size(comm, &size);
    MPI_Comm_rank(comm, &rank);
	
	sort(Xi.begin(), Xi.end());
	
	std::vector<short int> localSample = createLocalSample(Xi, size, Xi.size()/size, false);
	
	int localSize = localSample.size();
    vector<short int> gatheredVector, pivots(size - 1, size - 1);

    if (rank == 0) {
        gatheredVector.resize(localSize * size);
    }
    MPI_Gather(localSample.data(), localSize, MPI_SHORT,
               gatheredVector.data(), localSize, MPI_SHORT,
               0, comm);
    if (rank == 0) {
		sort(gatheredVector.begin(), gatheredVector.end());
		auto last = std::unique(gatheredVector.begin(), gatheredVector.end());
		gatheredVector.erase(last, gatheredVector.end());
        if ( gatheredVector.size() >= size ) {
			pivots = createLocalSample(gatheredVector, size, gatheredVector.size()/size, true);
		} else {
			pivots = gatheredVector;
		}
	}
	MPI_Bcast(pivots.data(), size - 1, MPI_SHORT, 0, comm);
	
	int local_size = Xi.size();
	std::vector<int> send_counts(size, 0);
    std::vector<int> send_displacements(size, 0);
	std::vector<int> recv_counts(size, 0);
    std::vector<int> recv_displacements(size, 0);
	for (int i = 0; i < pivots.size(); ++i) {
        for (int j = 0; j < Xi.size(); ++j) {
            if (i == 0 && Xi[j] <= pivots[i]) {
                send_counts[i]++;
            } else if ( Xi[j] > pivots[i - 1] && Xi[j] <= pivots[i]) {
				send_counts[i]++;
			}
			if ( i == pivots.size() - 1 && Xi[j] > pivots[i]) {
				send_counts[i+1]++;
			}
        }
        if (i > 0) {
            send_displacements[i] = send_displacements[i - 1] + send_counts[i - 1];
        }
		if (i == pivots.size() - 1) {
			send_displacements[i + 1] = send_displacements[i] + send_counts[i];
		}
    }
	
	MPI_Alltoall(send_counts.data(), 1, MPI_INT, recv_counts.data(), 1, MPI_INT, comm);
	for (int i = 1; i <= pivots.size(); i++){
		recv_displacements[i] = recv_displacements[i-1] + recv_counts[i-1];
	}
	std::vector<short int> r(recv_displacements.back() + recv_counts.back());
	MPI_Alltoallv(Xi.data(), send_counts.data(), send_displacements.data(), MPI_SHORT,
                  r.data(), recv_counts.data(), recv_displacements.data(), MPI_SHORT, comm);
	
	sort(r.begin(), r.end());
} // isort

#endif // A2_HPP
