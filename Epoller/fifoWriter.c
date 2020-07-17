#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_WRITES		3000
#define	CHUNK_SIZE		4
#define MAX_MS_TO_SLEEP	10

int main() {
	srand(time(0));
	
	const char *pipeName = "./e_pipe";
	mkfifo(pipeName, 0666);
	int fd = open(pipeName, O_CREAT | O_WRONLY);
	
	for (int i=0; i<MAX_WRITES; i++) {
		for (int j=0; j<CHUNK_SIZE; j++) {
			int n = rand();
			write(fd, &n, sizeof(int));
		}
		usleep((rand() % MAX_MS_TO_SLEEP) + 1);
	}
	
	close(fd);
	unlink(pipeName);
	return 0;
}
