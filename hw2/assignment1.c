#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(){
	pid_t pid  = fork();

	if(pid < 0){
		printf("failed");
	}else if(pid == 0){
		execl("/usr/bin/ls", "ls", NULL);
		perror("execl failed");
		return 1;
	}else{
		wait(NULL);
		printf("Parent process done\n");
	}
	return 0;
}
	
