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
	const char *newMessage = "Hello, hell!";
	int len = 14;
	key_t key = 2769;
	
	char *memPtr = setup(key, len, 0666);
	strcpy(memPtr, newMessage);
	puts(memPtr);

	return 0;
}
