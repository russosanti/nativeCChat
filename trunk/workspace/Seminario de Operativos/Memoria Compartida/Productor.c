#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
//#include "../Semaforos/operipc.h"

#define n 5

void mainmemp(){
	maincr(n,2);
	int shmid2 = shmget(0XB,1,IPC_CREAT|IPC_EXCL|0666);
	int shmid;
	int semid = semget(0XA,0,0);
	shmid = shmget(0XA,0,0);
	char *c;
	int *contador;
	char l = 'a';
	char *aux;
	int *aux2;
	c = (char*)shmat(shmid,0,0);
	contador = (int*)shmat(shmid2,0,0);
	aux = c;
	aux2 = n;
	P(semid,0);
	*contador = 0;
	V(semid,1);
	/*int entra == 0;
	while(*contador == n){
		P(semid,0);
		c[entra] = l;
		entra = (entra + 1) mod n;
		*contador = *contador + 1;
		V(semid,1);
		wait(1);
	}*/
	shmdt(aux);
}


void mainaa12(){
	maincr(1,2);
	int shmid;
	int semid = semget(0XA,0,0);
	shmid = shmget(0XA,0,0);
	char *c;
	char l = 'a';
	char *aux;
	c = (char*)shmat(shmid,0,0);
	aux = c;
	while(l<='z'+1){
		P(semid,0);
		*c = l;
		//c++; //al sumarle uno apunta a la direccion de memoria siguiente
		l++;
		V(semid,1);
	}
	shmdt(aux);
	//shmdt(aux2);
}

