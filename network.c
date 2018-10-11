#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//-----------      SET DEFINITION FOR THE NUMBER OF UNITS IN THE LAYERS      -----------//
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
        net->layer[i]->dweight    = (double**) calloc(Units[i]+1, sizeof(double*));
        net->layer[i]->output[0] = BIAS;

        if (i != 0) {
            for (j=1; j<=Units[i]; j++) {
                net->layer[i]->weight[j]     = (double*) calloc(Units[i-1]+1, sizeof(double));
                net->layer[i]->saved_weights[j] = (double*) calloc(Units[i-1]+1, sizeof(double));
                net->layer[i]->delta[j]    = (double*) calloc(Units[i-1]+1, sizeof(double));
                net->layer[i]->dweight[i]    = (double*) calloc(Units[i-1]+1, sizeof(double));
            }
        }
    }

    net->input_layer = net->layer[0];
    net->output_layer = net->layer[NUM_LAYERS-1];

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


/* The function below forward propagates the activations for the whole
   network.*/

//This function works only for networks with 1 hidden layer.
//Soon there will be the implementation for any number of hidden layers.
void forward_propagate(NETWORK* net){
    int i, l, j, k;
    net->error = 0.00;

    double sumH[Units[1]], SumO[Units[2]];

        for (j = 1; j <= net->layer[1]->units; j++) {         //Hidden Layer Activation
            sumH[j] = net->layer[1]->weight[1][j];
            for (i = 1; i <= net->layer[1]->units; i++) {
                sumH[j] += net->input_layer->output[i] * net->layer[1]->weight[i][j];
            }
            net->layer[1]->output[j] = sigmoid_transfer(sumH[j]);
        }

        for (k = 1; k <= net->layer[1]->units; k++) {         // Output layer activation
            SumO[k] = net->output_layer->weight[1][k];
            for (j = 1; j <= net->output_layer->units; j++) {
                SumO[k] += net->layer[1]->output[j] * net->output_layer->weight[j][k];
            }
            net->output_layer->output[k] = sigmoid_transfer(SumO[k]);
        }
}

// This function does what it says: a sigmoid transfer.
double sigmoid_transfer(double activation){
    return 1.0/(1.0 + exp(-activation));
}

//This function lets you insert values to the input layer.
void insert_input(NETWORK* net, double* input){
    int i;

    for(i=1; i<net->input_layer->units; i++){
        net->input_layer->output[i] = input[i-1];
    }
}

void get_output(NETWORK* net, double* output){
    int i;

    for(i=1; i<net->output_layer->units; i++){
        output[i-1] = net->output_layer->output[i];
    }
}

double calculate_error(NETWORK* net, double* target){
    int i;
    double error = 0.00;
    for(i=0; i<net->output_layer->units; i++){
        error = target[i-1] - net->output_layer->output[i];
        net->error = 0.5 * (error * error);
    }

}

// The function below calculates the deltas for the output layer
void calculate_delta(NETWORK* net, double* target){
    int i;
    for(i=0; i<net->output_layer->units; i++){
        *net->output_layer->delta[i] = (target[i-1] - net->output_layer->output[i] * net->output_layer->output[i] * (1.0 - net->output_layer->output[i]));
    }
}

// The function below backpropagates the entire network.
void backpropagate(NETWORK* net){
    int i,j, p;
    
    double sumD[Units[1]];
        for (i = 1; i < net->layer[1]->units; i++) {
            sumD[i] = 0.00;
            for (j = 0; j < net->output_layer->units; j++) {
                sumD[i] = net->output_layer->weight[i][j] * *net->output_layer->delta[j];
            }
            *net->layer[1]->delta[j] = sumD[i] * net->layer[1]->output[i] * (1.0 - net->layer[1]->output[i]);
        }
}

// The function below updates the weights for the entire network after the backpropagation.
void update_weights(NETWORK* net){
    int i,j,k;
    int dweight;

    for(i=1; i<NUM_LAYERS; i++){
        for(j=1; j<net->layer[i]->units; j++) {
            for (k = 0; k < net->layer[i - 1]->units; k++) {
                net->layer[i]->weight[j][k] += net->l_rate * net->layer[i]->error[j] * net->layer[i-1]->output[k] + net->alpha * net->layer[i]->dweight[j][k];
                net->layer[i]->dweight[j][k] = net->l_rate * net->layer[i]->error[j] * net->layer[i-1]->output[k];
            }
        }
    }
}

void run_network(NETWORK* net, double* input, double* output, double* target, int status){
    insert_input(net, input);
    forward_propagate(net);
    get_output(net, output);
    calculate_error(net, target);

    if(status){ //If 1, the network is set to training
        backpropagate(net);
        update_weights(net);
    }
}

void train_network(NETWORK* net, int epochs){

}

void set_definitions(NETWORK* net, double* input){

    //-----------      SET DEFINITIONS FOR THE NETWORK      -----------//

            net->alpha = 0.5;
            net->l_rate = 0.25;

    //-----------      SET DEFINITIONS FOR THE INPUT    -----------//

    double MARKET_YIELDS[DAYS] = {3.41,3.42,3.42,3.42,3.40,3.40,3.39,3.40,3.39,3.40,3.41,3.40,3.40,3.40,3.40,3.41,3.41,3.41,3.42,3.42,3.43,3.45,3.46,3.45,3.44,3.45,3.44,3.43,3.43,3.43};
    input = MARKET_YIELDS;
}
