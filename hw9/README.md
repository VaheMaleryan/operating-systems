# HW9 - POSIX Threads

| Exercise | Source |
| --- | --- |
| 1. Basic Thread Creation | [task1_create_threads.c](task1_create_threads.c) |
| 2. Array Processing with Threads | [task2_array_sums.c](task2_array_sums.c) |
| 3. Printing Numbers with Threads | [task3_print_numbers.c](task3_print_numbers.c) |
| 4. Calculating Square of Numbers in Parallel | [task4_parallel_squares.c](task4_parallel_squares.c) |

Compile and run from the `hw9` folder with a C compiler and POSIX threads.

```sh
cc -std=c11 -Wall -Wextra -Wpedantic -pthread task1_create_threads.c -o task1
cc -std=c11 -Wall -Wextra -Wpedantic -pthread task2_array_sums.c -o task2
cc -std=c11 -Wall -Wextra -Wpedantic -pthread task3_print_numbers.c -o task3
cc -std=c11 -Wall -Wextra -Wpedantic -pthread task4_parallel_squares.c -o task4
./task1
./task2
./task3
./task4
```

The printed thread IDs are worker numbers assigned by `main`. In exercise 3,
each worker prints 1 through 5 in order. The relative order of lines from
different workers can vary. Each program joins its workers before exiting.
