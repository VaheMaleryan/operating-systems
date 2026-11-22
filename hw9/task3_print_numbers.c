#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { THREAD_COUNT = 3 };

static void *print_numbers(void *argument)
{
    const int *id = argument;
    for (int number = 1; number <= 5; ++number) {
        printf("Thread %d: %d\n", *id, number);
    }
    return NULL;
}

int main(void)
{
    pthread_t threads[THREAD_COUNT];
    int ids[THREAD_COUNT] = {1, 2, 3};
    int started = 0;
    int status = EXIT_SUCCESS;

    for (int i = 0; i < THREAD_COUNT; ++i) {
        int error = pthread_create(&threads[i], NULL, print_numbers, &ids[i]);
        if (error != 0) {
            fprintf(stderr, "pthread_create: %s\n", strerror(error));
            status = EXIT_FAILURE;
            break;
        }
        ++started;
    }

    for (int i = 0; i < started; ++i) {
        int error = pthread_join(threads[i], NULL);
        if (error != 0) {
            fprintf(stderr, "pthread_join: %s\n", strerror(error));
            status = EXIT_FAILURE;
        }
    }
    return status;
}
