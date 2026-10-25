Homework 7: FCFS and SJF Scheduling

This program is written in C. It simulates First Come First Served (FCFS) and non-preemptive Shortest Job First (SJF).

How to compile and run

Open a terminal in the hw7 folder and compile using this command:

gcc -std=c11 -Wall -Wextra -Wpedantic scheduling.c -o scheduling

Run the program using:

./scheduling

Enter the number of processes. Then enter the arrival time and burst time for each process.

Example input:

4
0 8
1 4
2 9
3 5

How the program works

The program uses a struct to store process information and arrays to store the processes.

The fcfs function sorts processes by arrival time and runs them in that order.

The sjf function chooses the shortest process that has already arrived. If two processes have the same burst time, it chooses the one that arrived earlier. Each process finishes before another one starts.

If no process is ready, the CPU waits until the next arrival. The Gantt chart shows this as IDLE.

The program prints the Gantt chart, waiting time, turnaround time, response time, and their averages for both algorithms.

Calculations

Turnaround time equals completion time minus arrival time.

Waiting time equals turnaround time minus burst time.

Response time equals start time minus arrival time.

Waiting time and response time are equal because both algorithms are non-preemptive.

Sample results

FCFS execution order: P1, P2, P3, P4.
Average waiting time: 8.75
Average turnaround time: 15.25
Average response time: 8.75

SJF execution order: P1, P2, P4, P3.
Average waiting time: 7.75
Average turnaround time: 14.25
Average response time: 7.75


