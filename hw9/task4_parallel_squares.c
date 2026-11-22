#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void *print_square(void *argument)
{
    const int *number = argument;
    long long square = (long long)*number * *number;
    printf("Square of %d is %lld\n", *number, square);
    return NULL;
}

int main(void)
{
    int values[] = {1, 2, 3, 4, 5};
    const size_t count = sizeof(values) / sizeof(values[0]);
    pthread_t threads[sizeof(values) / sizeof(values[0])];
    size_t started = 0;
    int status = EXIT_SUCCESS;

    for (size_t i = 0; i < count; ++i) {
        int error = pthread_create(&threads[i], NULL, print_square, &values[i]);
        if (error != 0) {
            fprintf(stderr, "pthread_create: %s\n", strerror(error));
            status = EXIT_FAILURE;
            break;
        }
        ++started;
    }

    for (size_t i = 0; i < started; ++i) {
        int error = pthread_join(threads[i], NULL);
        if (error != 0) {
            fprintf(stderr, "pthread_join: %s\n", strerror(error));
            status = EXIT_FAILURE;
        }
    }
    return status;
}
