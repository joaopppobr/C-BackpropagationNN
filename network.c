#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int Units[NUM_LAYERS] = {20, 10, 10, 5}; //INPUTS, HIDDEN, OUTPUTS

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

        if(i!=0){
            for(j=1; j<Units[1]; j++) {
                net->layer[i]->weight[j] = (double *) calloc(Units[i-1] + 1, sizeof(double));
                net->layer[i]->saved_weights[j] = (double *) calloc(Units[i-1] + 1, sizeof(double));
                net->layer[i]->delta[j] = (double *) calloc(Units[i-1] + 1, sizeof(double));
            }
        }
    }

    net->input_layer = net->layer[0];
    net->output_layer = net->layer[NUM_LAYERS-1];
    net->l_rate = LEARNING_RATE;

}

void randomize_weights(NETWORK* net){
    int i,j,k;

    for(i=1; i<NUM_LAYERS; i++){
        for(j=1; j<=net->layer[i]->units; j++){
            for(k=0; k<=net->layer[i-1]->units; k++){
                net->layer[i]->weight[j][k]= ((double) rand() / RAND_MAX) * (0.5-0.5)+0.5;
            }
        }
    }
}

/*
double* activate(NETWORK* net){
    size_t len_weights = sizeof(net->layer->weight) / sizeof(int);
    int i;
    double* activation = weights[-1];
    for(i=0; i<len_weights-1; i++){
        activation += weights[i]*inputs[i];
    }
    return activation;
}
 */



