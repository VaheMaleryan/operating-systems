#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main(){
	pid_t ret1, ret2, ret3;

	ret1 = fork();

	if(ret1 < 0){
		printf("first fork failed\n");
		return 1;
	}

	ret2 = fork();

        if(ret2 < 0){
                printf("second fork failed\n");
                return 1;
        }

	ret3 = fork();

        if(ret3 < 0){
                printf("third fork failed\n");
                return 1;
        }

	printf("PID: %d | parent pid: %d | ret1: %d | ret2: %d | ret3: %d\n", getpid(), getppid(), ret1, ret2, ret3);

	sleep(20);

	return 0;

}
