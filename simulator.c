#include <stdio.h>
#include <stdlib.h>
#include "prob.h"

void simulate()
{
    printf("Simulação iniciada...\n");

    int n = rand() % 10 + 5; // entre 5 e 14 processos
    Process lst[n];

    for (int i = 0; i < n; i++) {
        lst[i] = create_random_process(i);
    }

    printf("\n Processos Gerados:\n");
    for (int i = 0; i < n; i++) {
        print_process(lst[i]);
    }

    printf("\n A executar escalonador FCFS...\n");
    schedule_fcfs(lst, n);

    printf("\n A executar escalonador SJF... \n");
    schedule_sjf(lst,n);

    printf("\nSimulação finalizada \n");
    printf("Total de processos: %d\n", n);
}
