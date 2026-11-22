#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { THREAD_COUNT = 2 };

struct array_part {
    int id;
    const int *values;
    size_t length;
};

static void *sum_part(void *argument)
{
    const struct array_part *part = argument;
    long long sum = 0;
    for (size_t i = 0; i < part->length; ++i) {
        sum += part->values[i];
    }
    printf("Thread %d partial sum: %lld\n", part->id, sum);
    return NULL;
}

int main(void)
{
    const int values[] = {2, 4, 6, 8, 10, 12};
    const size_t length = sizeof(values) / sizeof(values[0]);
    const size_t midpoint = length / 2;
    struct array_part parts[THREAD_COUNT] = {
        {1, values, midpoint},
        {2, values + midpoint, length - midpoint},
    };
    pthread_t threads[THREAD_COUNT];
    int started = 0;
    int status = EXIT_SUCCESS;

    for (int i = 0; i < THREAD_COUNT; ++i) {
        int error = pthread_create(&threads[i], NULL, sum_part, &parts[i]);
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
