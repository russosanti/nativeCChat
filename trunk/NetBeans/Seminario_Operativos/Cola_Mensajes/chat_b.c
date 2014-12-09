//lector

#include<stdio.h>
#include<string.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<unistd.h>

#define MAX 256

struct mensaje{
	long tipo;//si o si de tipo long y mayor que 0;
	char mensaje[256];
};
int main()
{
	int msgid=msgget(0xA,0);
        struct mensaje mem;
        //bzero(mem.mensaje,MAX);
        strcpy(mem.mensaje,"/0");
        mem.tipo = 2;
	while(strcasecmp(mem.mensaje,"CLOSE\n")!=0){
            msgrcv(msgid,&mem,sizeof(mem)-sizeof(long),1,0);
            printf("EL: %s",mem.mensaje);
            if(strcasecmp(mem.mensaje,"CLOSE\n")!=0){
                mem.tipo = 2;
                printf("YO: ");
                fgets(mem.mensaje,MAX,stdin);
                msgsnd(msgid,&mem,sizeof(mem)-sizeof(long),0);
            }
	}
}

//ipcs-->dice la cantidad de mensajes
