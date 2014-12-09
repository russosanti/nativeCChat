#ifndef OPERIPC_H_
#define OPERIPC_H_

#include<sys/sem.h>

void P(int semid, int sem){   //wait
	struct sembuf buf;
	buf.sem_num = sem;
	buf.sem_op = -1;
	buf.sem_flg = 0;
	semop(semid,&buf,1);
}

void V(int semid,int sem){   //signal
	struct sembuf buf;
	buf.sem_num = sem;
	buf.sem_op = 1;
	buf.sem_flg = 0;
	semop(semid,&buf,1);
}

#endif /* OPERIPC_H_ */
