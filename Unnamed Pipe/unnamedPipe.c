#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define READ_END	0
#define	WRITE_END	1

void reportAndDie(const char* msg) {
	perror(msg);
	exit(-1);
}

int main() {
	char buf;
	int pipeFDs[2];
	const char* msg = "This is the winter of our disconent\n";
	
	if (pipe(pipeFDs) < 0)
		reportAndDie("pipe(...)");
		
	pid_t cpid = fork();
	if (cpid < 0)
		reportAndDie("fork()");
		
	// child
	if (cpid == 0) {
		close(pipeFDs[WRITE_END]);
		while (read(pipeFDs[READ_END], &buf, 1) > 0)
			write(STDOUT_FILENO, &buf, sizeof(buf));
		close(pipeFDs[READ_END]);
		_exit(0);
	}
	// parent
	else {
		close(pipeFDs[READ_END]);
		write(pipeFDs[WRITE_END], msg, strlen(msg));
		close(pipeFDs[WRITE_END]);
		wait(0);
		exit(0);
	}

	return 0;
}
