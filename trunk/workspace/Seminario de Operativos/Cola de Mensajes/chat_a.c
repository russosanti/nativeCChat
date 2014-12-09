//escritor
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/msg.h>
#include<unistd.h>

#define MAX 256

typedef struct msj
	{
		long tipo;//si o si de tipo long y mayor que 0;
		char mensaje[256];
	};


int maincm2()
{
	crear_cmsj();
	int msgid;
	msgid=msgget(0xA,0);
	//solo se puede enviar la direccion de una estructura que contiene como minimo 2 tipos(ambos obligatorios)
	struct msj memo;
	strcpy(memo.mensaje,"/0");
	while(strcasecmp(memo.mensaje,"CLOSE\n")!=0){
		memo.tipo=1;
		printf("YO: ");
		fgets(memo.mensaje,MAX,stdin);
		msgsnd(msgid,&memo,sizeof(memo)-sizeof(long),0);
		if(strcasecmp(memo.mensaje,"CLOSE\n")!=0){
			msgrcv(msgid,&memo,sizeof(memo)-sizeof(long),2,0);
			printf("EL: %s",memo.mensaje);
		}
	}
}

//ipcs -q -->dice la cantidad de mensajes
