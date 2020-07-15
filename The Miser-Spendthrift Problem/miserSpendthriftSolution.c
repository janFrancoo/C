#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

static int balance = 0;
static pthread_mutex_t lock;

void reportAndDie(const char *message) {
	perror(message);
	exit(0);
}

// miser
void *deposit(void *n) {
	int *p = (int *) n;
	
	for (int i=0; i<*p; i++) {
		if (pthread_mutex_lock(&lock) == 0) {
			balance++;
			pthread_mutex_unlock(&lock);
		} else
			reportAndDie("mutex_lock failed");
	}
		
	return 0;
}

// spendthrift
void *withdraw(void *n) {
	int *p = (int *) n;
	
	for (int i=0; i<*p; i++) {
		if (pthread_mutex_lock(&lock) == 0) {
			balance--;
			pthread_mutex_unlock(&lock);
		} else
			reportAndDie("mutex_lock failed");
	}
		
	return 0;
}

int main (int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Enter number of operations\n");
		return 0;
	}

	int n = atoi(argv[1]);
	
	pthread_mutex_init(&lock, 0);
	pthread_t miser, spendthrift;
	if (pthread_create(&miser, 0, deposit, &n) < 0)
		reportAndDie("miser thread failed");
		
	if (pthread_create(&spendthrift, 0, withdraw, &n) < 0)
		reportAndDie("spendthrift thread failed");

	pthread_join(miser, 0);
	pthread_join(spendthrift, 0);
	pthread_mutex_destroy(&lock);
	
	printf("Final result = %d", balance);
	return 0;
}
