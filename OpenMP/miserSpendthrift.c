#include <omp.h>
#include <stdio.h>

static int balance = 0;

int main() {
	const int cnt = 8000000;
	
	#pragma omp parallel for
	for (int i=0; i<cnt; i++) {
		#pragma omp atomic
		balance++;
		
		#pragma omp atomic
		balance--;
	}

	printf("Final balance = %d\n", balance);

	return 0;
}
