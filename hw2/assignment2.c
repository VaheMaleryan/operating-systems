#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
	pid_t child1 = fork();

	if(child1 < 0){
		perror("failed");
	}
	else if(child1 == 0){
		execl("/usr/bin/ls", "ls", NULL);
		perror("execl failed");
		return 1;
	}

	wait(NULL);

	pid_t child2 = fork();

	if(child2 < 0){ 
		perror("failed");
	}
	else if(child2 == 0){
		execl("/usr/bin/date", "date", NULL);
		perror("execl failed");
		return 1; 
	}

	wait(NULL);

	printf("parent process done\n");

	return 0;
}
