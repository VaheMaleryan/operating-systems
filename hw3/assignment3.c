#include <stdio.h>
#include <stdlib.h>

void first(){
    printf("First cleanup function\n");
}

void second(){
    printf("Second cleanup function\n");
}

void test(){
    printf("exit() called from test function\n");
    exit(0);
}

int main(int argc, char *argv[]){

    atexit(first);
    atexit(second);

    printf("Program started\n");

    if(argc > 1){
        test();
    }

    printf("exit() called from main\n");
    exit(0);
}
