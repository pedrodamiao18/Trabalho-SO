#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <time.h>

#include "prob.h"

BurstDistribution burst_mode = BURST_NORMAL; // modo por defeito

double exponential(double m) {
    double u = drand48();
    return -m * log(1 - u);
}

double normal_burst(double m, double devs) {
    double u1 = drand48();
    double u2 = drand48();
    double z = sqrt(-2.0 * log(u1)) * cos(2 * M_PI * u2);
    double burst = m + z * devs;

    if(burst < 0)
        return 0.1;
    else 
        return burst;
}

Process create_random_process(int id) {
    Process p;
    p.id = id;
    p.arrival_time = exponential(10.0);

    switch (burst_mode) {
        case BURST_EXPONENTIAL:
            p.burst_time = exponential(5.0); // média de 5ms
            break;
        case BURST_NORMAL:
            p.burst_time = normal_burst(10.0, 2.0); // média de 10ms, desvio de 2
            break;
    }

    p.remaining_time = p.burst_time;
    p.priority = rand() % 5 + 1;
    p.deadline = p.arrival_time + 20;
    p.period = 0;

    return p;
}

void print_process(Process p) {
    printf("Process %d | Arrival: %.2f | Burst: %.2f | Priority: %d\n",
           p.id, p.arrival_time, p.burst_time, p.priority);
}
