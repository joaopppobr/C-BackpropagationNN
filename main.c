#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "network.h"
int main() {
    printf("teste");
    NETWORK *Net;
    int i;
    initialize_network(Net);
    randomize_weights(Net);
    printf("teste");
   // for(i=0; i<NUM_LAYERS; i++){
   //     printf("teste %f", Net->layer[i]->weight);
   // }
    return 0;
}