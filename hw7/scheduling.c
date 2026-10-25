#include <stdio.h>

#define MAX_PROCESSES 100
#define MAX_TIME 1000000

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
    int start_time;
    int completion_time;
};

/* The array is in execution order when this function is called. */
void printResults(struct Process p[], int n)
{
    double total_wait = 0, total_turnaround = 0, total_response = 0;
    int time = 0;

    printf("Gantt Chart: 0");

    for (int i = 0; i < n; i++) {
        if (p[i].start_time > time)
            printf(" -- IDLE -- %d", p[i].start_time);

        printf(" -- P%d -- %d", p[i].pid, p[i].completion_time);
        time = p[i].completion_time;
    }

    printf("\nPID    AT      BT      WT      TAT     RT\n");

    for (int i = 0; i < n; i++) {
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        p[i].response_time = p[i].start_time - p[i].arrival_time;

        printf("P%-5d %-7d %-7d %-7d %-7d %d\n",
               p[i].pid,
               p[i].arrival_time,
               p[i].burst_time,
               p[i].waiting_time,
               p[i].turnaround_time,
               p[i].response_time);

        total_wait += p[i].waiting_time;
        total_turnaround += p[i].turnaround_time;
        total_response += p[i].response_time;
    }

    printf("Average Waiting Time: %.2f\n", total_wait / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround / n);
    printf("Average Response Time: %.2f\n", total_response / n);
}

void fcfs(struct Process original[], int n)
{
    struct Process p[MAX_PROCESSES], temp;
    int time = 0;

    for (int i = 0; i < n; i++)
        p[i] = original[i];

    /* Bubble sort preserves input order when arrival times are equal. */
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (p[j].arrival_time > p[j + 1].arrival_time) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival_time)
            time = p[i].arrival_time;

        p[i].start_time = time;
        time += p[i].burst_time;
        p[i].completion_time = time;
    }

    printf("\n=== First Come First Served (FCFS) ===\n");
    printResults(p, n);
}

void sjf(struct Process p[], int n)
{
    struct Process result[MAX_PROCESSES];
    int done[MAX_PROCESSES] = {0};
    int time = 0, completed = 0;

    while (completed < n) {
        int selected = -1;

        /* Only processes that have arrived can use the CPU. */
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].arrival_time <= time) {
                if (selected == -1 ||
                    p[i].burst_time < p[selected].burst_time ||
                    (p[i].burst_time == p[selected].burst_time &&
                     p[i].arrival_time < p[selected].arrival_time)) {
                    selected = i;
                }
            }
        }

        /* If nothing is ready, jump to the next arrival. */
        if (selected == -1) {
            int next_arrival = -1;

            for (int i = 0; i < n; i++) {
                if (!done[i] &&
                    (next_arrival == -1 ||
                     p[i].arrival_time < next_arrival)) {
                    next_arrival = p[i].arrival_time;
                }
            }

            time = next_arrival;
        } else {
            result[completed] = p[selected];
            result[completed].start_time = time;

            time += p[selected].burst_time;
            result[completed].completion_time = time;

            done[selected] = 1;
            completed++;
        }
    }

    printf("\n=== Shortest Job First (SJF) ===\n");
    printResults(result, n);
}

int main(void)
{
    struct Process p[MAX_PROCESSES] = {0};
    int n;

    printf("Enter the number of processes (1-%d): ", MAX_PROCESSES);
    fflush(stdout);

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_PROCESSES) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("Enter arrival time and burst time for process %d: ", i + 1);
        fflush(stdout);

        if (scanf("%d %d", &p[i].arrival_time, &p[i].burst_time) != 2 ||
            p[i].arrival_time < 0 || p[i].arrival_time > MAX_TIME ||
            p[i].burst_time < 1 || p[i].burst_time > MAX_TIME) {
            printf("Invalid input: arrival must be 0-%d, burst 1-%d.\n",
                   MAX_TIME, MAX_TIME);
            return 1;
        }
    }

    fcfs(p, n);
    sjf(p, n);

    return 0;
}
