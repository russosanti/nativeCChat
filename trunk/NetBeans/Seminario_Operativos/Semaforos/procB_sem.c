#include <stdio.h>
#include "operipc.h"

void mainpb(){
    int semid = semget(0XA,0,0);
    while(1){
        P(semid,0);
        printf("B\n");
        sleep(1);
        V(semid,3);
    }
}