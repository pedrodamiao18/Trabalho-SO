#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "simulation.h"

int main() {
    srand(time(NULL));
    srand48(time(NULL));

    burst_mode = BURST_NORMAL; // ou BURST_EXPONENTIAL

    simulate();
    return 0;
}
