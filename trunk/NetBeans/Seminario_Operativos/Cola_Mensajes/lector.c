//lector

#include<stdio.h>
#include<string.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<unistd.h>

struct mensaje{
	long tipo;//si o si de tipo long y mayor que 0;
	char mensaje[20];
};
int mainmsgq()
{
	int msgid=msgget(0xA,0);
        struct mensaje mem;
	msgrcv(msgid,&mem,sizeof(mem)-sizeof(long),2,0);// el cuarto parametro es el tipo de mensaje que se lee
                                                        //el quinto parametro es el flag, puede ser:
        // IPC_NOWAIT -> en lugar de quedarse bloqueado muestra -1
        //MSG_NOERROR -> no te tira error cuando lee nada
        //MSG_ECEPT si no hay mensajes del tipo pasado, lee del tipo que haya
        printf("tipo: %d\n",mem.tipo);
        printf("mensaje: %s\n",mem.mensaje);
}

//ipcs-->dice la cantidad de mensajes