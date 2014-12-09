#include <stdio.h>
#include "operipc.h"



void mainpa(){
	//crear_sem(4);
	ini_sem();
    int semid = semget(0XA,0,0);
    while(1){
        P(semid,2);
        printf("A\n");
        sleep(1);
        V(semid,0);
        P(semid,3);
        printf("A\n");
        sleep(1);
        V(semid,1);
    }
}
