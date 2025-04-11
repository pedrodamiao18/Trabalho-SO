#include <stdio.h>
#include <stdlib.h>

#include "prob.h"
Process create_random_process(int id) {
    Process p;
    p.id = id;
    p.arrival_time = rand() % 10;
    p.burst_time = (drand48() * 10) + 1;
    p.remaining_time = p.burst_time;
    p.priority = rand() % 5 + 1;
    p.deadline = p.arrival_time + 20;
    p.period = 0;
    return p;
}

void print_process(Process p) {
    printf("Process %d | Arrival: %d | Burst: %f | Priority: %d\n",
        p.id, p.arrival_time, p.burst_time, p.priority);
}
