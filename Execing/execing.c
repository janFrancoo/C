#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	const char *args[] = {"./fileStatus", "tmp", 0};
	
	int ret = execv("./fileStatus", args);
	if (ret == -1)
		perror("execv err");
	else
		printf("You can not see me!\n");
	
	return 0;
}
