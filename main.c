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

    /* The code below tests the input insertion and forward propagation

    double input[30] = {1,2,4,3,5,7,6,8,7,6,7,6,4,7,8,9,5,2,4, 3,1,2,4,3,5,7,6,8,7,6};
    insert_input(&Net, input);

    for(i=0; i<30; i++){
        printf("Inputs %f\n", Net.input_layer->output[i]);
    }

    forward_propagate(&Net);
    //This is a test to see if the activation function
    //works properly.

    for (k = 1; k <= Net.output_layer->units; k++)
        printf("Output: %f\n", Net.layer[2]->output[k]);

    for (k = 1; k <= Net.layer[1]->units; k++)
        printf("Hidden: %f\n", Net.layer[1]->output[k]);

        */


    return 0;
}