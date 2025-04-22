#include <stdio.h>
#include "prob.h"

// Função auxiliar para ordenação por arrival_time
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
            if (process[j].priority < process[j + 1].priority) { // Ordem decrescente
                Process temp = process[j];
                process[j] = process[j + 1];
                process[j + 1] = temp;
            }
        }
    }
}


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

void schedule_sjf (Process process[], int n){
    sort_by_burts(process, n);

    int time = 0;
    double total_waiting = 0;
    double total_turnaround = 0;

    printf("\n Resultados SJF:\n");
    printf("| PID | Burts   | Start | Finish | Waiting | Turnaround |\n");
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

    printf("\n Estatísticas:\n");
    printf("Tempo médio de espera     = %.2f\n", total_waiting / n);
    printf("Tempo médio de retorno    = %.2f\n", total_turnaround / n);
}


void schedule_priority (Process process[], int n){
    sort_by_priority(process, n);

    int time = 0;
    double total_waiting = 0;
    double total_turnaround = 0;

    printf("\n Resultados Priority Scheduling:\n");
    printf("| PID | Burts   | Start | Finish | Waiting | Turnaround |\n");
    printf("|-----|---------|-------|--------|---------|------------|\n");

    for (int i = 0; i < n; i++) {
        int priority = process[i].priority;
        
        int start;
        if (time < priority)
            start = priority;
        else
            start = time;
            
        int finish = start + process[i].priority;
        int waiting = start - priority;
        int turnaround = finish - priority;

        total_waiting += waiting;
        total_turnaround += turnaround;
        time = finish;

        printf("| %3d | %7d | %5d | %6d | %7d | %10d |\n",
               process[i].id, priority, start, finish, waiting, turnaround);
    }

    printf("\n Estatísticas:\n");
    printf("Tempo médio de espera     = %.2f\n", total_waiting / n);
    printf("Tempo médio de retorno    = %.2f\n", total_turnaround / n);
}

