#include <stdio.h>
#include <string.h>
#include <mpi.h>

#define MAX_LEN	64

void report(char *title, int rank, char digitsIn[]) {
	printf("%s %2i received: %s\n", title, rank, digitsIn);
}

int main() {
	char digitsOut[MAX_LEN + 1];
	char digitsIn[MAX_LEN + 1];
	memset(digitsOut, '\0', sizeof(digitsOut));
	memset(digitsIn, '\0', sizeof(digitsIn));
	
	int rank = -1, size = -1;
	MPI_Status status;
	
	MPI_Init(0, 0);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if (rank == 0) {
		sprintf(digitsOut, "%i", rank);
		
		MPI_Send(digitsOut, strlen(digitsOut) + 1, MPI_CHAR, rank + 1, 1, MPI_COMM_WORLD);
		MPI_Recv(digitsIn, MAX_LEN, MPI_CHAR, size - 1, 1, MPI_COMM_WORLD, &status);
		report("Master process", rank, digitsIn);
	} else {
		MPI_Recv(digitsIn, MAX_LEN, MPI_CHAR, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
		report("Worker process", rank, digitsIn);
		sprintf(digitsOut, "%s %i", digitsIn, rank);
		MPI_Send(digitsOut, strlen(digitsOut) + 1, MPI_CHAR, (rank + 1) % size, 1, MPI_COMM_WORLD);
	}
	
	MPI_Finalize();

	return 0;
}
