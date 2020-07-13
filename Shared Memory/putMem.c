#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void reportAndDie (const char *msg) {
	perror(msg);
	exit(-1);
}

char *setup (key_t key, int byteCount, int flags) {
	int memId = shmget(key, byteCount, flags);
	if (memId < 0)
		reportAndDie("shmget failed");
		
	char *memPtr = shmat(memId, 0, 0);
	if (memPtr == (void *) -1)
		reportAndDie("shmat failed");
		
	return memPtr;
}


int main() {
	const char *message = "Hello, world!";
	int len = strlen(message) + 1;
	key_t key = 2769;
	
	char *memPtr = setup(key, len, IPC_CREAT | 0666); // read & write
	memcpy(memPtr, message, len);

	while (strcmp(memPtr, message) == 0)
		sleep(1);
		
	printf("A new message is arrived: %s\n", memPtr);

	return 0;
}
