#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "network.h"

#define min(x,y)    ((x)<(y)?(x):(y))
#define max(x,y)    ((x)>(y)?(x):(y))
#define srq(x)      ((x)*(x))
#define LO  0.1
#define HI  0.9
#define BIAS    1

int main() {
    NETWORK* Net;
    int i;

    initialize_network(Net);
    randomize_weights(Net);
    for(i=0; i<NUM_LAYERS; i++){
        printf("%f", Net->layer[i]->weight);
    }
    return 0;
}