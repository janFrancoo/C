#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

static int balance = 0;

void reportAndDie(const char *message) {
	perror(message);
	exit(0);
}

// miser
void *deposit(void *n) {
	int *p = (int *) n;
	
	for (int i=0; i<*p; i++)
		balance++;
		
	return 0;
}

// spendthrift
void *withdraw(void *n) {
	int *p = (int *) n;
	
	for (int i=0; i<*p; i++)
		balance--;
		
	return 0;
}

int main (int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Enter number of operations\n");
		return 0;
	}

	int n = atoi(argv[1]);
	
	pthread_t miser, spendthrift;
	if (pthread_create(&miser, 0, deposit, &n) < 0)
		reportAndDie("miser thread failed");
		
	if (pthread_create(&spendthrift, 0, withdraw, &n) < 0)
		reportAndDie("spendthrift thread failed");

	pthread_join(miser, 0);
	pthread_join(spendthrift, 0);
	
	printf("Final result = %d", balance);
	return 0;
}
