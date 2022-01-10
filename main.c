#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "functions.h"


int main()
{
    srand(time(NULL));

    int random;
    node *pt = NULL;
    bool h;
    int cont1, cont2, remove_array[1000];

    for (cont1 = 0; cont1 < 1000; cont1++) {
        cont2 = 0;
        while (cont2 < 10000){
            random  = (((rand() & 255)<<8 | (rand() & 255))<<8 | (rand() & 255))<<7 | (rand() & 127);
            random = random % 100001;
            if (insertAVL(random, &pt, &h)){
                if (cont2 < 1000) {
                    remove_array[cont2] = random;
                }
                cont2++;
            }
        }
        /*printf("\n");
        printPreOrder(&pt);
        printf("\n");*/
        printf("\nHeight: %d", heightAVL(&pt));
        printf("\nNumber of nodes: %d\n", numberNodesAVL(&pt));

        cont2 = 0;
        while (cont2 < 1000) {
            if (removeAVL(remove_array[cont2], &pt, &h)) {
                //printf("\nRemoved node %d\n", remove_array[cont2]);
                cont2++;
            }
        }
        /*printf("\n");
        printPreOrder(&pt);
        printf("\n");*/
        printf("\nHeight: %d", heightAVL(&pt));
        printf("\nNumber of nodes: %d\n\n", numberNodesAVL(&pt));
        printf("-----------------------------\n");

        freePosOrder(&pt);
    }

    return 0;
}
