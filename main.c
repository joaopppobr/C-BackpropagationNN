#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "network.h"
int main()
{
    srand((time NULL));
    int l,i,j,k;
    NETWORK  Net;
    initialize_network(&Net);
    randomize_weights(&Net);

    //This tests if the weights are being assigned correctly.
    /*
    for (l=1; l<NUM_LAYERS; l++) {
        for (i=1; i<=Net.layer[l]->units; i++) {
            for (j=0; j<=Net.layer[l-1]->units; j++) {
                printf("%f\n",Net.layer[1]->weight[i][j]);
            }
        }
    }
    */

    //This should be a test to see if the activation function
    //works properly.]
    forward_propagate(&Net);
    for (k = 1; k <= 1; k++)
        printf("%f", Net.layer[2]->output[k]);


    return 0;
}