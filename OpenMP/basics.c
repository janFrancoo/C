#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int tCount = 0, tId;
	
	#pragma omp parallel private(tCount, tId)
	{
		tId = omp_get_thread_num();
		printf("I am thread %d\n", tId);
		
		if (tId == 0) {
			tCount = omp_get_num_threads();
			printf("Thread count on this machine = %d\n", tCount);
		}
	}

	printf("Goodbye, cruel world!\n");

	return 0;
}
