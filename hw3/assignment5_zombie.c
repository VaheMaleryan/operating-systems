#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){

    pid_t child = fork();

    if(child < 0){
        perror("fork failed");
        return 1;
    }
    else if(child == 0){
        printf("Child PID: %d\n", getpid());
        exit(0);
    }
    else{
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", child);
        sleep(30);
    }

    return 0;
}
