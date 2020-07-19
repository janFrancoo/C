#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main() {
	int rank = -1, size = -1;

	MPI_Init(0, 0);
	
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if (rank == 0)
		printf("I am the master proccess, my id = %d, workers = %d\n", rank, size - 1);
	else if (rank == 1 || rank == 2)
		printf("I am a worker process, my id = %d\n", rank);
	else if (rank == 3) {
		int sum = 0;
		for (int i=1; i<=1000; i++)
			sum += i;
		printf("I am a worker process, my id = %d and I calculated sum as %d\n", rank, sum);
	}
	
	MPI_Finalize();
	
	return 0;
}
