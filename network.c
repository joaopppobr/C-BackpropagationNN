#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//This is an arbitrary definition for the sake of testing only. In the real application
//this should not be included
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

/* I think there's a better way to write this function
   Idea: Do this with an upper layer and a lower layer, so you
   can propagate trough the entire network more easily.

   Example: PropagateLayer(NETWORK* Net, LAYER* Lower, LAYER* Upper)

   This would then work for any two layers of the network, and we could
   simply do a "for" to propagate the entire network.*/

double forward_propagate(NETWORK* net){
    int i, l, j, k;
    double sumH[Units[1]], SumO[Units[2]];

        for (j = 1; j <= Units[1]; j++) {         //Hidden Layer Activation
            sumH[j] = net->layer[1]->weight[0][j];
            for (i = 1; i <= Units[0]; i++) {
                sumH[j] += net->input_layer->output[i] * net->layer[1]->weight[i][j];
            }
            net->layer[1]->output[j] = 1.0 / (1.0 + exp(-sumH[j]));
        }

        for (k = 1; k <= Units[NUM_LAYERS-1]; k++) {         /* k loop computes output unit activations */
            SumO[k] = net->layer[2]->weight[0][k];
            for (j = 1; j <= NUM_LAYERS-2; j++) {
                SumO[k] += net->layer[1]->output[j] * net->layer[1]->weight[j][k];
            }
            net->layer[2]->output[k] = 1.0 / (1.0 + exp(-SumO[k]));
        }
}

double sigmoid_transfer(double activation){
    return 1.0/(1.0 + exp(-activation));
}

/* I dont know yet how to write this function
 *
 *
 *
void forward_propagate(NETWORK* net){
    int i, j;
    for (i=0; i<=NUM_LAYERS; i++) {
        for(j=0; j<=Units[i]; j++){
            activation = activate()
        }
    }
}
*/




