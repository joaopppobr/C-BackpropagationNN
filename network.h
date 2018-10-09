//
// Created by joaopedro on 09/10/18.
//

#ifndef C_IMPLEMENTATION_NETWORK_H
#define C_IMPLEMENTATION_NETWORK_H

#define min(x,y)    ((x)<(y)?(x):(y))
#define max(x,y)    ((x)>(y)?(x):(y))
#define srq(x)      ((x)*(x))
#define LO  0.1
#define HI  0.9
#define BIAS    1

typedef struct{ //Layer of network;
    int units;
    double* output;
    double* error;
    double** weight;
    double** saved_weights;
    double** delta;
} LAYER;

typedef struct{ //Network
    LAYER** layer;
    LAYER*   input_layer;
    LAYER* output_layer;
    double l_rate;
    double error;

} NETWORK;

void randomize_weights(NETWORK* net);
void initialize_network(NETWORK* net);
/*These definitions below are specific
to each application, but are here as placeholders*/
#define NUM_LAYERS  4
#define LEARNING_RATE 0.25
int Units[NUM_LAYERS] = {20, 10, 10, 5}; //INPUTS, HIDDEN, OUTPUTS


#endif //C_IMPLEMENTATION_NETWORK_H
