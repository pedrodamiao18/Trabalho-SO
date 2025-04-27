#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "simulation.h"

SimulationParams sim_params;

void parse_line(char *line, char *key, char *value)
{
    char *equals = strchr(line, '=');

    if (equals != NULL)
    {
        *equals = '\0';
        strcpy(key, line);
        strcpy(value, equals + 1);

        value[strcspn(value, "\n")] = '\0';
    }
    else
    {

        key[0] = '\0';
        value[0] = '\0';
    }
}

void load_parameters(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Failed to open parameters file");
        exit(EXIT_FAILURE);
    }

    char line[128];
    char key[64], value[64];

    while (fgets(line, sizeof(line), file))
    {
        parse_line(line, key, value);

        if (strlen(key) > 0 && strlen(value) > 0)
        {
            // if (strcmp(key, "algorithm") == 0)
            //  {
            //      strcpy(sim_params.algorithm, value);
            //  }
            /*else*/ if (strcmp(key, "n_processes") == 0)
            {
                sim_params.n_processes = atoi(value);
            }
            else if (strcmp(key, "burst_mode") == 0)
            {
                if (strcmp(value, "NORMAL") == 0)
                    sim_params.burst_mode = BURST_NORMAL;
                else
                    sim_params.burst_mode = BURST_EXPONENTIAL;
            }
            else if (strcmp(key, "time_quantum") == 0)
            {
                sim_params.time_quantum = atoi(value);
            }
        }
    }

    fclose(file);
}

void simulate()
{
    printf("Simulation started...\n");

    int n = sim_params.n_processes;
    Process lst[n];

    for (int i = 0; i < n; i++)
    {
        lst[i] = create_random_process(i);
    }

    printf("\nGenerated Processes:\n");
    for (int i = 0; i < n; i++)
    {
        print_process(lst[i]);
    }

    // if (strcmp(sim_params.algorithm, "FCFS") == 0)
    // {
    printf("\nExecuting FCFS scheduler...\n");
    schedule_fcfs(lst, n);
    // }
    //  else if (strcmp(sim_params.algorithm, "SJF") == 0)
    // {
    printf("\nExecuting SJF scheduler...\n");
    schedule_sjf(lst, n);
    //  }
    // else if (strcmp(sim_params.algorithm, "PRIORITY") == 0)
    //{
    printf("\nExecuting Priority Scheduling (Non-Preemptive)...\n");
    schedule_priority_non_preemptive(lst, n);
    //}
    // else if (strcmp(sim_params.algorithm, "EDF") == 0)
    //{
    printf("\nExecuting Earliest Deadline First scheduler...\n");
    schedule_edf(lst, n);
    //}
    // else if (strcmp(sim_params.algorithm, "RR") == 0)
    //{
    printf("\nExecuting Round Robin scheduler (Time Quantum = %d ms)...\n", sim_params.time_quantum);
    schedule_rr(lst, n, sim_params.time_quantum);
    //}
    // else
    //{
    //   printf("\nUnknown algorithm '%s'.\n", sim_params.algorithm);
    //   exit(EXIT_FAILURE);
    //}

    printf("\nSimulation completed.\n");
    printf("Total number of processes: %d\n", n);
}
