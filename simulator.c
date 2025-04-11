#include <stdio.h>
#include <stdlib.h>

#include "prob.h"

void simulate()
{
    printf("Simulação iniciada...\n");

    int n = rand() % 15;
    Process lst[n];

    for (int i = 0; i < n; i++)
    {
        Process p = create_random_process(i);
        lst[i] = p;
    }

    for (int i = 0; i < n; i++)
    {
        print_process(lst[i]);
    }
    printf("Simulação finalizada...\n");
    printf("Total de processos: %d\n", n);
}