#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
	pid_t child = fork();

	if(child < 0) {
		perror("fork failed");
		return 1;
	}
	else if (child == 0) {
		execl("/usr/bin/echo", "echo", "hello from the child process", NULL);
		perror("execl failed");
		return 1;
	}
	
	wait(NULL);

	printf("Parent process done\n");

	return 0;
}
