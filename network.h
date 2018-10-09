#ifndef C_IMPLEMENTATION_NETWORK_H
#define C_IMPLEMENTATION_NETWORK_H

#define BIAS    1

/*These definitions below are specific
to each application, but are here as placeholders*/
#define NUM_LAYERS  3
#define LEARNING_RATE 0.25

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

#endif //C_IMPLEMENTATION_NETWORK_H
