#ifndef C_IMPLEMENTATION_NETWORK_H
#define C_IMPLEMENTATION_NETWORK_H

#define BIAS    1
/*These definitions below are specific
to each application, but are here as placeholders*/
#define NUM_LAYERS  3
#define DAYS 30

typedef struct{ //Layer of network;
    int units;
    double* output;
    double* error;
    double** weight;
    double** saved_weights;
    double** delta;
    double** dweight;
} LAYER;

typedef struct{ //Network
    LAYER** layer;
    LAYER*   input_layer;
    LAYER* output_layer;
    double l_rate; // Learning Rate
    double error;
    double alpha;

} NETWORK;

void randomize_weights(NETWORK* net);
void initialize_network(NETWORK* net);
void forward_propagate(NETWORK* net);
double sigmoid_transfer(double activation);
void insert_input(NETWORK* net, double* input);
double calculate_error(NETWORK* net, double* target);
void calculate_delta(NETWORK* net, double* target);
void backpropagate(NETWORK* net);
void update_weights(NETWORK* net);
void run_network(NETWORK* net, double* input, double* output, double* target, int status);
void set_definitions(NETWORK* net, double* input);

#endif //C_IMPLEMENTATION_NETWORK_H
