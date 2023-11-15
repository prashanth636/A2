/*  Prasanth varma
 *  Vegesna
 *  pvegesna
 *  50538639
 */

#ifndef A2_HPP
#define A2_HPP
#include <vector>
#include <mpi.h>
using namespace std;

void swap(vector<short int>& arr, int i, int j)
{
    int t = arr[i];
    arr[i] = arr[j];
    arr[j] = t;
}

void quicksort(vector<short int>& arr, int start, int end)
{
    int pivot, index;
    if (end <= 1)
        return;
    pivot = arr[start + end / 2];
    swap(arr, start, start + end / 2);
    index = start;
    for (int i = start + 1; i < start + end; i++)
    {
        if (arr[i] < pivot)
        {
            index++;
            swap(arr, i, index);
        }
    }
    swap(arr, start, index);
    quicksort(arr, start, index - start);
    quicksort(arr, index + 1, start + end - index - 1);
}

vector<short int> merge(const vector<short int>& arr1, int n1, const vector<short int>& arr2, int n2)
{
    vector<short int> result;
    int i = 0;
    int j = 0;

    while (i < arr1.size() && j < arr2.size())
    {
        if (arr1[i] < arr2[j])
        {
            result.push_back(arr1[i]);
            i++;
        }
        else
        {
            result.push_back(arr2[j]);
            j++;
        }
    }

    while (i < arr1.size())
    {
        result.push_back(arr1[i]);
        i++;
    }

    while (j < arr2.size())
    {
        result.push_back(arr2[j]);
        j++;
    }

    return result;
}

void isort(std::vector<short int>& Xi, MPI_Comm comm) {
	int number_of_elements;
    int chunk_size, own_chunk_size;
    vector<short int> chunk;
    MPI_Status status;
 
    int number_of_process, rank_of_process; 
    MPI_Comm_size(comm, &number_of_process);
    MPI_Comm_rank(comm, &rank_of_process);
	
    if (rank_of_process == 0) {
		number_of_elements = Xi.size();
		
		printf("%d \n", number_of_process);
		
        // Computing chunk size
        chunk_size
            = (number_of_elements % number_of_process == 0)
                  ? (number_of_elements / number_of_process)
                  : (number_of_elements / number_of_process
                     - 1);
		
        // Padding data with zero
        for (int i = number_of_elements;
             i < number_of_process * chunk_size; i++) {
            Xi.push_back(0);
        }
 
        // Printing the array read from file
        printf("Elements in the array is : \n");
        for (int i = 0; i < number_of_elements; i++) {
            printf("%d ", Xi[i]);
        }
    }
 
    // BroadCast the Size to all the
    // process from root process
    MPI_Bcast(&number_of_elements, 1, MPI_INT, 0,
              comm);
 
    // Computing chunk size
    chunk_size
        = (number_of_elements % number_of_process == 0)
              ? (number_of_elements / number_of_process)
              : number_of_elements
                    / (number_of_process - 1);
 
    // Calculating total size of chunk
    // according to bits
    chunk.resize(chunk_size);
 
    // Scatter the chuck size data to all process
    MPI_Scatter(Xi.data(), chunk_size, MPI_INT, chunk.data(),
                chunk_size, MPI_INT, 0, comm);
    //free(data);
 
    // Compute size of own chunk and
    // then sort them
    // using quick sort
 
    own_chunk_size = (number_of_elements
                      >= chunk_size * (rank_of_process + 1))
                         ? chunk_size
                         : (number_of_elements
                            - chunk_size * rank_of_process);
 
    // Sorting array with quick sort for every
    // chunk as called by process
    quicksort(chunk, 0, own_chunk_size);
 
    for (int step = 1; step < number_of_process; step = 2 * step) {
        if (rank_of_process % (2 * step) != 0) {
            MPI_Send(chunk.data(), own_chunk_size, MPI_INT,
                     rank_of_process - step, 0,
                     comm);
            break;
        }
 
        if (rank_of_process + step < number_of_process) {
            int received_chunk_size
                = (number_of_elements
                   >= chunk_size
                          * (rank_of_process + 2 * step))
                      ? (chunk_size * step)
                      : (number_of_elements
                         - chunk_size
                               * (rank_of_process + step));
            vector<short int> chunk_received(received_chunk_size);
            MPI_Recv(chunk_received.data() , received_chunk_size,
                     MPI_INT, rank_of_process + step, 0,
                     comm, &status);
 
            Xi = merge(chunk, own_chunk_size,
                         chunk_received,
                         received_chunk_size);
 
            //free(chunk);
            //free(chunk_received);
            chunk = Xi;
            own_chunk_size
                = own_chunk_size + received_chunk_size;
        }
    }
 
    if (rank_of_process == 0) {
        for (int i = 0; i < number_of_elements; i++) {
            printf("%d ", chunk[i]);
        }
    }
} // isort

#endif // A2_HPP