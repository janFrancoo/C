#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define MAX_WRITES	256

int main() {
	srand(time(0));
	
	const char *fifoName = "./francoPipe";
	mkfifo(fifoName, 0666); // read/write
	int fd = open(fifoName, O_CREAT | O_WRONLY);
	
	int i;
	for (i=0; i<MAX_WRITES; i++) {
		int n = rand() % 1000;
		write(fd, &n, sizeof(int));
	}
	
	sleep(5);
	write(fd, &i, sizeof(int));

	close(fd);
	unlink(fifoName);

	return 0;
}
