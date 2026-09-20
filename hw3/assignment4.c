#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){

    pid_t child1 = fork();
    pid_t child2;
    int status1, status2;

    if(child1 < 0){
        perror("fork failed");
        return 1;
    }
    else if(child1 == 0){
        printf("Child 1 PID: %d\n", getpid());
        exit(0);
    }

    child2 = fork();

    if(child2 < 0){
        perror("fork failed");
        return 1;
    }
    else if(child2 == 0){
        printf("Child 2 PID: %d\n", getpid());
        exit(5);
    }

    waitpid(child1, &status1, 0);

    if(WIFEXITED(status1)){
        printf("Child 1 exit status: %d\n", WEXITSTATUS(status1));

        if(WEXITSTATUS(status1) == 0){
            printf("Child 1 completed successfully\n");
        }
        else{
            printf("Child 1 returned an error\n");
        }
    }

    waitpid(child2, &status2, 0);

    if(WIFEXITED(status2)){
        printf("Child 2 exit status: %d\n", WEXITSTATUS(status2));

        if(WEXITSTATUS(status2) == 0){
            printf("Child 2 completed successfully\n");
        }
        else{
            printf("Child 2 returned an error\n");
        }
    }

    return 0;
}
