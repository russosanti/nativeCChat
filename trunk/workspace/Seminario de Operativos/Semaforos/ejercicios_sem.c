// Hay que hacer A(BoC), (AoB)C, ABACABACABAC

#include <stdio.h>
//#include "operipc.h"

void mainss4(){
    int semid = semget(0XA,0,0);
    while(1){
        P(semid,1);
        printf("A\n");
        sleep(1);
        V(semid,0);
    }
}
