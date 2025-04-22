#ifndef PROCESS_H
#define PROCESS_H

typedef struct {
    int id;
    double arrival_time;
    double burst_time;
    int remaining_time;
    int priority;
    int deadline;
    int period;
} Process;

typedef enum {
    BURST_EXPONENTIAL,
    BURST_NORMAL
} BurstDistribution;

extern BurstDistribution burst_mode;

Process create_random_process(int id);
void print_process(Process p);

// Distribuições
double exponential_burst(double mean);
double normal_burst(double mean, double stddev);

// Outros
void schedule_fcfs();
void schedule_sjf ();
void schedule_priority ();
void simulate();

#endif // PROCESS_H
