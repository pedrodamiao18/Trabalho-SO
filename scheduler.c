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
        int arrival = process[i].arrival_time;
        int start = (time < arrival) ? arrival : time;
        int finish = start + process[i].burst_time;
        int waiting = start - arrival;
        int turnaround = finish - arrival;

        total_waiting += waiting;
        total_turnaround += turnaround;
        time = finish;

        printf("| %3d | %7d | %5d | %6d | %7d | %10d |\n",
               process[i].id, arrival, start, finish, waiting, turnaround);
    }

    printf("\n Estatísticas:\n");
    printf("Tempo médio de espera     = %.2f\n", total_waiting / n);
    printf("Tempo médio de retorno    = %.2f\n", total_turnaround / n);
}
