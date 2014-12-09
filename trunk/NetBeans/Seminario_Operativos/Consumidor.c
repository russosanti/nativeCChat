#include <sys/ipc.h>
#include <sys/shm.h>
#include<sys/sem.h>
#include <unistd.h>
//#include "../Semaforos/operipc.h"


#define n 5

void mainmemc(){
	int shmid2;
	int shmid;
	int semid = semget(0XA,0,0);
	shmid = shmget(0XA,0,0);
	char *c;
	int *contador;
	char *aux;
	int *aux2;
	c = (char*)shmat(shmid,0,0);
	contador = (int*)shmat(shmid2,0,0);
	aux = c;
	aux2 = n;
	P(semid,1);
	V(semid,0);
        int sale = 0;
	while(*contador == 0){
		P(semid,1);
		printf("%c",c[sale]);
                //sale = (sale + 1) mod n;
		*contador = *contador - 1;
		V(semid,0);
	}
	shmdt(aux);
        shmdt(aux2);
}

void mainasasa(){
	int shmid;
        int semid = semget(0XA,0,0);
	shmid = shmget(0XA,0,0);
	char *c;
	char *aux;
	c = aux = (char*)shmat(shmid,0,0);
	while(*c<='z'){
            P(semid,1);
            printf("%c\n",*c);
            //c++; //al sumarle uno apunta a la direccion de memoria siguiente
            V(semid,0);
	}
	shmdt(aux);
}

