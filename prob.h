#ifndef PROCESS_H
#define PROCESS_H

typedef struct {
    int id;
    int arrival_time;
    double burst_time;
    int remaining_time;
    int priority;
    int deadline;
    int period;
} Process;

Process create_random_process(int id);
void print_process(Process p);

void schedule_fcfs();

void simulate();

int read_config(const char *filename);

#endif // PROCESS_H