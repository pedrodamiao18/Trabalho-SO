#include <stdio.h>
#include "simulation.h"

void sort_by_burst(Process process[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (process[j].burst_time < process[j + 1].burst_time)
            {
                Process temp = process[j];
                process[j] = process[j + 1];
                process[j + 1] = temp;
            }
        }
    }
}

void print_gantt_chart(int start[], int finish[], int id[], int n)
{
    printf("\nGantt Chart:\n");

    for (int i = 0; i < n; i++)
    {
        printf("|  P%-2d  ", id[i]);
    }
    printf("|\n");

    printf("%-3d", start[0]);
    for (int i = 0; i < n; i++)
    {
        printf("     %-3d", finish[i]);
    }
    printf("\n");
}

// Função FCFS
void schedule_fcfs(Process process[], int n)
{
    int time = 0;
    double total_waiting = 0;
    double total_turnaround = 0;

    int start[n], finish[n], pid[n];

    printf("\n FCFS Results:\n");
    printf("| PID | Burst   | Start | Finish | Waiting | Turnaround |\n");
    printf("|-----|---------|-------|--------|---------|------------|\n");

    for (int i = 0; i < n; i++)
    {
        pid[i] = process[i].id;
        start[i] = (time > process[i].arrival_time) ? time : process[i].arrival_time;
        finish[i] = start[i] + process[i].burst_time;

        int waiting = start[i] - process[i].arrival_time;
        int turnaround = finish[i] - process[i].arrival_time;

        total_waiting += waiting;
        total_turnaround += turnaround;
        time = finish[i];

        printf("| %3d | %7.2f | %5d | %6d | %7d | %10d |\n",
               process[i].id, process[i].burst_time, start[i], finish[i], waiting, turnaround);
    }

    print_gantt_chart(start, finish, pid, n);

    printf("\n Statistics:\n");
    printf("Average waiting time     = %.2f\n", total_waiting / n);
    printf("Average turnaround time    = %.2f\n", total_turnaround / n);
}

// Shortest Job First (SJF)
void schedule_sjf(Process process[], int n)
{
    int time = 0;
    int completed = 0;
    int done[n];
    for (int i = 0; i < n; i++)
        done[i] = 0;

    double total_waiting = 0;
    double total_turnaround = 0;

    int start[n], finish[n], pid[n];

    printf("\n SJF Results:\n");
    printf("| PID | Arrival | Burst  | Start | Finish | Waiting | Turnaround |\n");
    printf("|-----|---------|--------|-------|--------|---------|------------|\n");

    while (completed < n)
    {
        int shortest = -1;

        for (int i = 0; i < n; i++)
        {
            if (!done[i] && process[i].arrival_time <= time)
            {
                if (shortest == -1 || process[i].burst_time < process[shortest].burst_time)
                    shortest = i;
            }
        }

        if (shortest == -1)
        {
            time++;
            continue;
        }

        start[completed] = time;
        finish[completed] = start[completed] + process[shortest].burst_time;
        pid[completed] = process[shortest].id;

        int waiting = start[completed] - process[shortest].arrival_time;
        int turnaround = finish[completed] - process[shortest].arrival_time;

        total_waiting += waiting;
        total_turnaround += turnaround;

        time = finish[completed];
        done[shortest] = 1;
        completed++;

        printf("| %3d | %7.2f | %6.2f | %5d | %6d | %7d | %10d |\n",
               process[shortest].id,
               process[shortest].arrival_time,
               process[shortest].burst_time,
               start[completed - 1], finish[completed - 1], waiting, turnaround);
    }

    print_gantt_chart(start, finish, pid, n);

    printf("\n Statistics:\n");
    printf("Average waiting time     = %.2f\n", total_waiting / n);
    printf("Average turnaround time  = %.2f\n", total_turnaround / n);
}

// Priority Scheduling (Non-preemptive)
void schedule_priority_non_preemptive(Process process[], int n)
{
    double time = 0;
    int completed = 0;
    int done[n];
    for (int i = 0; i < n; i++)
        done[i] = 0;

    double total_waiting = 0;
    double total_turnaround = 0;

    int start[n], finish[n], pid[n];

    printf("\n Priority Scheduling Results (Non-preemptive):\n");
    printf("| PID | Priority | Arrival | Burst | Start | Finish | Waiting | Turnaround |\n");
    printf("|-----|----------|---------|-------|-------|--------|---------|------------|\n");

    while (completed < n)
    {
        int best = -1;

        for (int i = 0; i < n; i++)
        {
            if (!done[i] && process[i].arrival_time <= time)
            {
                if (
                    best == -1 ||
                    process[i].priority < process[best].priority ||
                    (process[i].priority == process[best].priority &&
                     process[i].burst_time < process[best].burst_time))
                {
                    best = i;
                }
            }
        }

        if (best == -1)
        {
            int min_priority = 1000;
            for (int i = 0; i < n; i++)
            {
                if (!done[i] && process[i].priority < min_priority)
                {
                    best = i;
                    min_priority = process[i].priority;
                }
            }
            time = process[best].arrival_time;
            continue;
        }

        start[completed] = time;
        finish[completed] = start[completed] + process[best].burst_time;
        pid[completed] = process[best].id;

        int waiting = start[completed] - process[best].arrival_time;
        int turnaround = finish[completed] - process[best].arrival_time;

        total_waiting += waiting;
        total_turnaround += turnaround;

        time = finish[completed];
        done[best] = 1;
        completed++;

        printf("| %3d | %8d | %7.2f | %5.2f | %5d | %6d | %7d | %10d |\n",
               process[best].id,
               process[best].priority,
               process[best].arrival_time,
               process[best].burst_time,
               start[completed - 1], finish[completed - 1], waiting, turnaround);
    }

    print_gantt_chart(start, finish, pid, n);

    printf("\n Statistics:\n");
    printf("Average waiting time     = %.2f\n", total_waiting / n);
    printf("Average turnaround time  = %.2f\n", total_turnaround / n);
}

void schedule_priority_preemptive(Process process[], int n) {
    int time = 0;
    int completed = 0;
    int done[n];
    int remaining[n];
    for (int i = 0; i < n; i++) {
        done[i] = 0;
        remaining[i] = process[i].burst_time; 
    }

    double total_waiting = 0;
    double total_turnaround = 0;

    printf("\n Priority Scheduling Results (Preemptive):\n");

    int current = -1;

    int start_arr[n];  
    int finish_arr[n];
    int id_arr[n];
    int gantt_index = 0;

    while (completed < n) {
        int best = -1;

        for (int i = 0; i < n; i++) {
            if (!done[i] && process[i].arrival_time <= time) {
                if (best == -1 || process[i].priority < process[best].priority ||
                   (process[i].priority == process[best].priority && remaining[i] < remaining[best])) {
                    best = i;
                }
            }
        }

        if (best != -1) {
            if (current != best) {
                if (current != -1) {
                    finish_arr[gantt_index - 1] = time;
                }

                start_arr[gantt_index] = time;
                id_arr[gantt_index] = process[best].id;
                gantt_index++;
                current = best;
            }

            remaining[current]--;
            time++;

            if (remaining[current] == 0) {
                finish_arr[gantt_index - 1] = time;
                
                int waiting = start_arr[gantt_index - 1] - process[current].arrival_time;
                int turnaround = time - process[current].arrival_time;

                total_waiting += waiting;
                total_turnaround += turnaround;

                done[current] = 1;
                completed++;
                current = -1;
            }
        } else {
            time++;
        }
    }

    print_gantt_chart(start_arr, finish_arr, id_arr, gantt_index);

    printf("\n Statistics:\n");
    printf("Average waiting time     = %.2f\n", total_waiting / n);
    printf("Average turnaround time  = %.2f\n", total_turnaround / n);
}

// Earliest Deadline First (EDF)
void schedule_edf(Process process[], int n)
{
    int time = 0;
    int completed = 0;
    int done[n];
    for (int i = 0; i < n; i++)
        done[i] = 0;

    double total_waiting = 0;
    double total_turnaround = 0;
    int deadline_misses = 0;

    printf("\n EDF Results:\n");
    printf("| PID | Deadline | Arrival | Burst | Start | Finish | Waiting | Turnaround |\n");
    printf("|-----|----------|---------|-------|-------|--------|---------|------------|\n");

    while (completed < n)
    {
        int best = -1;

        for (int i = 0; i < n; i++)
        {
            if (!done[i] && process[i].arrival_time <= time)
            {
                if (best == -1 || process[i].deadline < process[best].deadline)
                    best = i;
            }
        }

        if (best == -1)
        {
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
// Round Robin (RR) - Implementação conforme a descrição da imagem
void schedule_rr(Process process[], int n, int time_quantum)
{
    int time = 0;
    int completed = 0;
    int remaining_time[n];
    int start[n * n], finish[n * n], pid[n * n];
    int gantt_count = 0;

    for (int i = 0; i < n; i++)
    {
        remaining_time[i] = process[i].burst_time;
    }

    double total_waiting = 0;
    double total_turnaround = 0;

    printf("\n Round Robin Results (Time Quantum = %d ms):\n", time_quantum);
    printf("| PID | Burst Time | Start | Finish | Waiting | Turnaround |\n");
    printf("|-----|------------|-------|--------|---------|------------|\n");

    while (completed < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (remaining_time[i] > 0 && process[i].arrival_time <= time)
            {

                int exec_time = (remaining_time[i] > time_quantum) ? time_quantum : remaining_time[i];


                start[gantt_count] = time;
                finish[gantt_count] = time + exec_time;
                pid[gantt_count] = process[i].id;
                gantt_count++;

                time += exec_time;
                remaining_time[i] -= exec_time;

                if (remaining_time[i] == 0)
                {
                    completed++;
                    int turnaround = time - process[i].arrival_time;
                    int waiting = turnaround - process[i].burst_time;

                    total_waiting += waiting;
                    total_turnaround += turnaround;

                    printf("| %3d | %10.2f | %5d | %6d | %7d | %10d |\n",
                           process[i].id, process[i].burst_time,
                           time - exec_time, time, waiting, turnaround);
                }
            }
        }

        int all_arrived = 1;
        for (int i = 0; i < n; i++)
        {
            if (remaining_time[i] > 0 && process[i].arrival_time > time)
            {
                all_arrived = 0;
                break;
            }
        }

        if (!all_arrived && completed < n)
        {
            time++;
        }
    }

    print_gantt_chart(start, finish, pid, gantt_count);

    printf("\n Statistics:\n");
    printf("Average waiting time      = %.2f ms\n", total_waiting / n);
    printf("Average turnaround time   = %.2f ms\n", total_turnaround / n);
}
