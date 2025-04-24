#include <stdio.h>
#include "simulation.h"

void sort_by_burst(Process process[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (process[j].burst_time < process[j + 1].burst_time) {
                Process temp = process[j];
                process[j] = process[j + 1];
                process[j + 1] = temp;
            }
        }
    }
}

// First-Come, First-Served (FCFS)
void schedule_fcfs(Process process[], int n) {
    sort_by_burst(process, n);

    int time = 0;
    double total_waiting = 0;
    double total_turnaround = 0;

    printf("\n FCFS Results:\n");
    printf("| PID | Burst   | Start | Finish | Waiting | Turnaround |\n");
    printf("|-----|---------|-------|--------|---------|------------|\n");

    for (int i = 0; i < n; i++) {
        double burst = process[i].burst_time;
        
        int start;
        if (time < burst)
            start = burst;
        else
            start = time;
            
        int finish = start + process[i].burst_time;
        int waiting = start - burst;
        int turnaround = finish - burst;

        total_waiting += waiting;
        total_turnaround += turnaround;
        time = finish;

        printf("| %3d | %7.2f | %5d | %6d | %7d | %10d |\n",
               process[i].id, burst, start, finish, waiting, turnaround);
    }

    printf("\n Statistics:\n");
    printf("Average waiting time     = %.2f\n", total_waiting / n);
    printf("Average turnaround time  = %.2f\n", total_turnaround / n);
}

// Shortest Job First (SJF)
void schedule_sjf(Process process[], int n) {
    int time = 0;
    int completed = 0;
    int done[n];
    for (int i = 0; i < n; i++) done[i] = 0;

    double total_waiting = 0;
    double total_turnaround = 0;

    printf("\n SJF Results:\n");
    printf("| PID | Arrival | Burst  | Start | Finish | Waiting | Turnaround |\n");
    printf("|-----|---------|--------|-------|--------|---------|------------|\n");

    while (completed < n) {
        int shortest = -1;

        for (int i = 0; i < n; i++) {
            if (!done[i] && process[i].arrival_time <= time) {
                if (shortest == -1 || process[i].burst_time < process[shortest].burst_time)
                    shortest = i;
            }
        }

        if (shortest == -1) {
            time++; 
            continue;
        }

        int start = time;
        int finish = start + process[shortest].burst_time;
        int waiting = start - process[shortest].arrival_time;
        int turnaround = finish - process[shortest].arrival_time;

        total_waiting += waiting;
        total_turnaround += turnaround;

        time = finish;
        done[shortest] = 1;
        completed++;

        printf("| %3d | %7.2f | %6.2f | %5d | %6d | %7d | %10d |\n",
               process[shortest].id,
               process[shortest].arrival_time,
               process[shortest].burst_time,
               start, finish, waiting, turnaround);
    }

    printf("\n Statistics:\n");
    printf("Average waiting time     = %.2f\n", total_waiting / n);
    printf("Average turnaround time  = %.2f\n", total_turnaround / n);
}

// Priority Scheduling (Non-preemptive)
void schedule_priority_non_preemptive(Process process[], int n) {
    double time = 0;
    int completed = 0;
    int done[n];
    for (int i = 0; i < n; i++) 
        done[i] = 0;

    double total_waiting = 0;
    double total_turnaround = 0;

    printf("\n Priority Scheduling Results (Non-preemptive):\n");
    printf("| PID | Priority | Arrival | Burst | Start | Finish | Waiting | Turnaround |\n");
    printf("|-----|----------|---------|-------|-------|--------|---------|------------|\n");

    while (completed < n) {
        int best = -1;

        for (int i = 0; i < n; i++) {
            if (!done[i] && process[i].arrival_time <= time) {
                if (
                    best == -1 ||
                    process[i].priority < process[best].priority || 
                    (process[i].priority == process[best].priority &&
                     process[i].burst_time < process[best].burst_time)
                ) {
                    best = i;
                }
            }
        }

        if (best == -1) {
            int min_priority = 1000;
            for (int i = 0; i < n; i++) {
                if (!done[i] && process[i].priority < min_priority) {
                    best = i;
                    min_priority = process[i].priority;
                }
            }
            time = process[best].arrival_time;
            continue;
        }

        double start = time;
        double finish = start + process[best].burst_time;
        int waiting = start - process[best].arrival_time;
        int turnaround = finish - process[best].arrival_time;

        total_waiting += waiting;
        total_turnaround += turnaround;

        time = finish;
        done[best] = 1;
        completed++;

        printf("| %3d | %8d | %7.2f | %5.2f | %5.2f | %6.2f | %7d | %10d |\n",
            process[best].id,
            process[best].priority,
            process[best].arrival_time,
            process[best].burst_time,
            start, finish, waiting, turnaround);
    }

    printf("\n Statistics:\n");
    printf("Average waiting time     = %.2f\n", total_waiting / n);
    printf("Average turnaround time  = %.2f\n", total_turnaround / n);
}

// Earliest Deadline First (EDF)
void schedule_edf(Process process[], int n) {
    int time = 0;
    int completed = 0;
    int done[n];
    for (int i = 0; i < n; i++) done[i] = 0;

    double total_waiting = 0;
    double total_turnaround = 0;
    int deadline_misses = 0;

    printf("\n EDF Results:\n");
    printf("| PID | Deadline | Arrival | Burst | Start | Finish | Waiting | Turnaround |\n");
    printf("|-----|----------|---------|-------|-------|--------|---------|------------|\n");

    while (completed < n) {
        int best = -1;

        for (int i = 0; i < n; i++) {
            if (!done[i] && process[i].arrival_time <= time) {
                if (best == -1 || process[i].deadline < process[best].deadline)
                    best = i;
            }
        }

        if (best == -1) {
            time++;
            continue;
        }

        int start = time;
        int finish = start + process[best].burst_time;
        int waiting = start - process[best].arrival_time;
        int turnaround = finish - process[best].arrival_time;

        total_waiting += waiting;
        total_turnaround += turnaround;
        time = finish;

        if (finish > process[best].deadline) 
            deadline_misses++;

        done[best] = 1;
        completed++;

        printf("| %3d | %8.2f | %7.2f | %5.2f | %5d | %6d | %7d | %10d |",
               process[best].id,
               process[best].deadline,
               process[best].arrival_time,
               process[best].burst_time,
               start, finish, waiting, turnaround);

        if (finish > process[best].deadline) 
            printf(" Deadline miss!");
        printf("\n");
    }

    printf("\n Statistics:\n");
    printf("Average waiting time      = %.2f\n", total_waiting / n);
    printf("Average turnaround time   = %.2f\n", total_turnaround / n);
    printf("Deadline misses           = %d out of %d\n", deadline_misses, n);
}
