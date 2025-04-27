#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "simulation.h"

int main()
{
    srand(time(NULL));
    srand48(time(NULL));

    load_parameters("config.txt");

    burst_mode = sim_params.burst_mode;

    simulate();

    return 0;
}
