#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//This is a arbitrary definition for the sake of testing only. In the real application
//this should note be included
int Units[NUM_LAYERS] = {30, 10, 1}; //INPUTS, HIDDEN LAYERS, OUTPUTS


//Random number generator that generates a double.
double RandomEqualREAL(double Low, double High)
{
    return ((double) rand() / RAND_MAX) * (High-Low) + Low;
}

void initialize_network(NETWORK* net){
    int i,j;

    net->layer = (LAYER**) calloc(NUM_LAYERS, sizeof(LAYER*));

    for(i=0; i<NUM_LAYERS; i++){
        net->layer[i] = (LAYER*) malloc(sizeof(LAYER));

        net->layer[i]->units = Units[i];

        net->layer[i]->output = (double*) calloc(Units[i]+1, sizeof(double));
        net->layer[i]->error = (double*) calloc(Units[i]+1, sizeof(double));
        net->layer[i]->weight = (double**) calloc(Units[i]+1, sizeof(double*));
        net->layer[i]->saved_weights = (double**) calloc(Units[i]+1, sizeof(double*));
        net->layer[i]->delta = (double**) calloc(Units[i]+1, sizeof(double*));
        net->layer[i]->output[0] = BIAS;

        if (i != 0) {
            for (j=1; j<=Units[i]; j++) {
                net->layer[i]->weight[j]     = (double*) calloc(Units[i-1]+1, sizeof(double));
                net->layer[i]->saved_weights[j] = (double*) calloc(Units[i-1]+1, sizeof(double));
                net->layer[i]->delta[j]    = (double*) calloc(Units[i-1]+1, sizeof(double));
            }
        }
    }

    net->input_layer = net->layer[0];
    net->output_layer = net->layer[NUM_LAYERS-1];
    net->l_rate = LEARNING_RATE;

}

void randomize_weights(NETWORK* net){
    int l,i,j;

    for (l=1; l<NUM_LAYERS; l++) {
        for (i=1; i<=net->layer[l]->units; i++) {
            for (j=0; j<=net->layer[l-1]->units; j++) {
                net->layer[l]->weight[i][j] = RandomEqualREAL(-0.5, 0.5);
                }
            }
        }
    }


double activate(NETWORK* net){
    int i, l, j, k;

    double activation = 0.00;

    for (l=1; l<NUM_LAYERS; l++) {
        for (i=1; i<=net->layer[l]->units; i++) {
            for (j=0; j<=net->layer[l-1]->units; j++) {
                for (k=0; k<=Units[0]-1; k++) {
                    activation += net->layer[l]->weight[i][j] * net->input_layer->output[k];
                }
            }
        }
    }
    return activation;
}







