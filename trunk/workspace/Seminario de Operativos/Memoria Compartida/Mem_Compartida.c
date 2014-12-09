#include <sys/ipc.h>
#include <sys/shm.h>
#include<sys/sem.h>
#include <unistd.h>

void maincr(int buff,int sem){
	int shmid = shmget(0XA,buff,IPC_CREAT|IPC_EXCL|0666); //el 26 es la cantidad de bytes que usa el area compartida
	printf("shmid %d\n",shmid);
	crear_sem(sem); // creo 2 semaforos, esta en semaforos.c
	int semid = semget(0XA,0,0);
	semctl(semid,0,SETVAL,1);
	semctl(semid,1,SETVAL,0);
}

void mainac(){
	int shmid = shmget(0XA,26,IPC_CREAT|IPC_EXCL|0666); //el 26 es la cantidad de bytes que usa el area compartida
	printf("shmid %d\n",shmid);
}

// para ver cuando lo cree uso $opcs -m

