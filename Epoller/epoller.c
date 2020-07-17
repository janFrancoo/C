#include <fcntl.h>
#include <sys/epoll.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX_EVENTS	12
#define	MAX_READS	12000

#define	TRUE	1
#define	FALSE	0

unsigned is_prime(unsigned n) {
	for (int i=2; i<sqrt(n); i++) {
		if (n % i == 0)
			return FALSE;
	}
	
	printf("%i is prime\n", n);
	return TRUE;
}

void reportAndDie(const char *msg) {
	perror(msg);
	exit(-1);
}

int create_nonblocking(const char *name) {
	int fd = open(name, O_RDONLY);
	if (fd < 0)
		return fd;
	int flag = fcntl(fd, F_SETFL, O_NONBLOCK);
	if (flag < 0)
		return flag;
	return fd;
}

int main() {
	const char *pipeName = "./e_pipe";
	int fd = create_nonblocking(pipeName);
	if (fd < 0)
		reportAndDie("create_nonblocking failed");
		
	int epollFd = epoll_create1(0);
	if (epollFd < 0)
		reportAndDie("epoll_create1 failed");
		
	struct epoll_event toKernel;
	struct epoll_event fromKernel[MAX_EVENTS];
	
	toKernel.events = EPOLLIN;
	toKernel.data.fd = fd;
	if (epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &toKernel) < 0)
		reportAndDie("epoll_ctl failed");
		
	unsigned howMany = 0;
	int count = 0;
	while (count++ < MAX_READS) {
		int n = epoll_wait(epollFd, fromKernel, MAX_EVENTS, -1);
		if (n < 0)
			reportAndDie("epoll_wait failed");
			
		for (int i=0; i<n; i++) {
			int next = 0;
			int bytes_read = read(fromKernel[i].data.fd, &next, sizeof(int));
			if (sizeof(int) == bytes_read)
				if (is_prime(next))
					howMany++;
		}
	}
	
	close(fd);
	close(epollFd);
	unlink(pipeName);
	
	printf("Total primes = %i - Total attempt = %i\n", howMany, MAX_READS);
	
	return 0;
}
