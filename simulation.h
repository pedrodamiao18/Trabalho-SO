#ifndef PROCESS_H
#define PROCESS_H

typedef struct
{
    int id;
    double arrival_time;
    double burst_time;
    int remaining_time;
    int priority;
    double deadline;
    int period;
} Process;

typedef enum
{
    BURST_EXPONENTIAL,
    BURST_NORMAL
} BurstDistribution;

extern BurstDistribution burst_mode;

Process create_random_process(int id);
void print_process(Process p);

double exponential_burst(double mean);
double normal_burst(double mean, double stddev);

void schedule_rr(Process process[], int n, int time_quantum);
void schedule_fcfs();
void schedule_sjf();
void schedule_priority_non_preemptive();
void schedule_priority_preemptive();
void schedule_edf();
void simulate();

typedef struct
{
    int n_processes;
    BurstDistribution burst_mode;
    int time_quantum;
} SimulationParams;

extern SimulationParams sim_params;

void load_parameters(const char *filename);

#endif
