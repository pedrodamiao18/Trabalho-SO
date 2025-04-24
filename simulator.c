#include <stdio.h>
#include <stdlib.h>
#include "simulation.h"

void simulate()
{
    printf("Simulation started...\n");

    int n = rand() % 10 + 5; 
    Process lst[n];

    for (int i = 0; i < n; i++) {
        lst[i] = create_random_process(i);
    }

    printf("\n Generated Processes:\n");
    for (int i = 0; i < n; i++) {
        print_process(lst[i]);
    }

    printf("\n Executing FCFS scheduler...\n");
    schedule_fcfs(lst, n);

    printf("\n Executing SJF scheduler... \n");
    schedule_sjf(lst, n);

    printf("\n Executing Priority Scheduling... \n");
    schedule_priority_non_preemptive(lst, n);

    printf("\n Executing Earliest Deadline First scheduler... \n");
    schedule_edf(lst, n);

    printf("\nSimulation completed\n");
    printf("Total number of processes: %d\n", n);
}
