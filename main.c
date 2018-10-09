#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "network.h"
void main()
{
    srand(4711);
    int l,i,j;
    NETWORK  Net;
    initialize_network(&Net);
    randomize_weights(&Net);

    for (l=1; l<NUM_LAYERS; l++) {
        for (i=1; i<=Net.layer[l]->units; i++) {
            for (j=0; j<=Net.layer[l-1]->units; j++) {
                printf("%f\n",Net.layer[l]->weight[i][j]);
            }
        }
    }
}