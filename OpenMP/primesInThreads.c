#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void isPrime(int num) {
	if (num == 2) {
		printf("2 is prime\n");
		return;
	}
	
	for (int i=2; i<sqrt(num); i++)
		if (num % i == 0) {
			printf("%d is not prime\n", num);
			return;
		}
		
	printf("%d is prime\n", num);
}

int main() {
	srand(time(0));
	
	#pragma omp parallel
	{
		isPrime(rand() % 100);
	}
	
	return 0;
}
