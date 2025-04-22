#include <stdio.h>
#include "prob.h"

void sort_by_arrival(Process process[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (process[j].arrival_time > process[j + 1].arrival_time) {
                Process temp = process[j];
                process[j] = process[j + 1];
                process[j + 1] = temp;
            }
        }
    }
}

void sort_by_burts(Process process[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (process[j].burst_time > process[j + 1].burst_time) {
                Process temp = process[j];
                process[j] = process[j + 1];
                process[j + 1] = temp;
            }
        }
    }
}

void sort_by_priority(Process process[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (process[j].priority < process[j + 1].priority) { 
                Process temp = process[j];
                process[j] = process[j + 1];
                process[j + 1] = temp;
            }
        }
    }
}

//First-Come, First-Served (FCFS)
void schedule_fcfs(Process process[], int n)
{
    sort_by_arrival(process, n);

    int time = 0;
    double total_waiting = 0;
    double total_turnaround = 0;

    printf("\n Resultados FCFS:\n");
    printf("| PID | Arrival | Start | Finish | Waiting | Turnaround |\n");
    printf("|-----|---------|-------|--------|---------|------------|\n");

    for (int i = 0; i < n; i++) {
        double arrival = process[i].arrival_time;
        
        int start;
        if (time < arrival)
            start = arrival;
        else
            start = time;
            
        int finish = start + process[i].burst_time;
        int waiting = start - arrival;
        int turnaround = finish - arrival;

        total_waiting += waiting;
        total_turnaround += turnaround;
        time = finish;

        printf("| %3d | %7.2f | %5d | %6d | %7d | %10d |\n",
               process[i].id, arrival, start, finish, waiting, turnaround);
    }

    printf("\n Estatísticas:\n");
    printf("Tempo médio de espera     = %.2f\n", total_waiting / n);
    printf("Tempo médio de retorno    = %.2f\n", total_turnaround / n);
}

//Shortest Job (SJ)
void schedule_sjf(Process process[], int n) {
    int time = 0;
    int completed = 0;
    int done[n];
    for (int i = 0; i < n; i++) done[i] = 0;

    double total_waiting = 0;
    double total_turnaround = 0;

    printf("\n Resultados SJF:\n");
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

    printf("\n Estatísticas:\n");
    printf("Tempo médio de espera     = %.2f\n", total_waiting / n);
    printf("Tempo médio de retorno    = %.2f\n", total_turnaround / n);
}

//Priority Scheduling (Preemptive and Non-Preemptive)
void schedule_priority(Process process[], int n) {
    int time = 0;
    int completed = 0;
    int done[n];
    for (int i = 0; i < n; i++) done[i] = 0;

    double total_waiting = 0;
    double total_turnaround = 0;

    printf("\n Resultados Priority Scheduling:\n");
    printf("| PID | Priority | Arrival | Burst | Start | Finish | Waiting | Turnaround |\n");
    printf("|-----|----------|---------|-------|-------|--------|---------|------------|\n");

    while (completed < n) {
        int best = -1;

        for (int i = 0; i < n; i++) {
            if (!done[i] && process[i].arrival_time <= time) {
                if (best == -1 || process[i].priority < process[best].priority)
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
        done[best] = 1;
        completed++;

        printf("| %3d | %8d | %7.2f | %5.2f | %5d | %6d | %7d | %10d |\n",
               process[best].id,
               process[best].priority,
               process[best].arrival_time,
               process[best].burst_time,
               start, finish, waiting, turnaround);
    }

    printf("\n Estatísticas:\n");
    printf("Tempo médio de espera     = %.2f\n", total_waiting / n);
    printf("Tempo médio de retorno    = %.2f\n", total_turnaround / n);
}


