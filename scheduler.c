#include <stdio.h>
#include "prob.h"

void schedule_fcfs(Process process[], int n)
{
    printf("FCFS scheduler a correr...\n");

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (process[j].priority > process[j + 1].priority)
            {
                Process temp = process[j];
                process[j] = process[j + 1];
                process[j + 1] = temp;
            }
        }
    }
}
