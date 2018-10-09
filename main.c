#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "network.h"
void main() {
    NETWORK Net;
    int i,j,k;
    initialize_random();
    initialize_network(&Net);
    randomize_weights(&Net);
    for(i=1; i<NUM_LAYERS; i++) {
        for (j = 1; j <= Net.layer[i]->units; j++) {
            for (k = 0; k <= Net.layer[i - 1]->units; k++)
                printf("%f\n", Net.layer[i]->weight[j][k]);
        }
    }
}