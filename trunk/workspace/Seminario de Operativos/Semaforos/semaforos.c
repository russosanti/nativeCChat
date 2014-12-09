// Acordarse que seccion critica es la parte del codigo que acceden a recursos compartidos.

#include<stdio.h>
#include<sys/sem.h>


void crear_sem(int x){  //aca si te da -1 quiere decir que ya esta creado el semforo
	int semid;
	semid = semget(0XA,x,IPC_CREAT|IPC_EXCL|0666);  //OXA indica q A es hexadecimal
	printf("semid %d\n",semid);
}

// para romper un semaforo con ipcrm sem id(el id del semaforo);

void ini_sem(){  //inicializa semaforos
	int semid = semget(0XA,0,0); //retorna -1 si falla sino el id
	semctl(semid,0,SETVAL,0);    // estos dos tambien retornan -1 si fallan
	semctl(semid,1,SETVAL,0);
	semctl(semid,2,SETVAL,1);
	semctl(semid,3,SETVAL,0);
	printf("semid: %d\n",semid);
}

void main2(){
	int semid = semget(0XA,0,0);
	printf("SEM 0 = %d\n",semctl(semid,0,GETVAL));
	printf("SEM 1 = %d\n",semctl(semid,1,GETVAL));
	printf("semid: %d\n",semid);
}
