#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){

    pid_t child = fork();
    int status;

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

        wait(&status);

        if(WIFEXITED(status)){
            printf("Child exit status: %d\n", WEXITSTATUS(status));
        }

        sleep(30);
    }

    return 0;
}
