#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define	JOB_SIZE	100
#define	CHUNK_SIZE	10

int main() {
	int i, tCount, tId, chunk = CHUNK_SIZE;
	float a[JOB_SIZE], b[JOB_SIZE], c[JOB_SIZE];
	
	for (i=0; i<JOB_SIZE; i++)
		a[i] = b[i] = i * 1.1f;
		
	#pragma omp parallel shared(a, b, c, tCount, chunk) private(i, tId)
	{
		tId = omp_get_thread_num();
		if (tId == 0) {
			tCount = omp_get_num_threads();
			printf("Thread count = %d\n", tCount);
		}
		
		printf("I am thread %d...\n", tId);
		
		#pragma omp for schedule(dynamic, chunk)
		for (i=0; i<JOB_SIZE; i++) {
			c[i] = a[i] + b[i];
			printf("%d -> c[%d] = %f\n", tId, i, c[i]);
		}
	}
	
	printf("I am main single thread...\n");
	for (i=0; i<JOB_SIZE; i++)
		printf("c[%d] = %f\n", i, c[i]);
	
	return 0;
}
