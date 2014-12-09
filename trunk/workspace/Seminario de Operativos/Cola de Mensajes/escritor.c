//escritor

#include<stdio.h>
#include<string.h>
#include<sys/msg.h>
#include<unistd.h>

int mainescq()
{
	crear_cmsj();
	int msgid;
	msgid=msgget(0xA,0);
	//solo se puede enviar la direccion de una estructura que contiene como minimo 2 tipos(ambos obligatorios)
	struct mensaje
	{
		long tipo;//si o si de tipo long y mayor que 0;
		char mensaje[20];
	};
	struct mensaje mem;
	mem.tipo=1;
	strcpy(mem.mensaje,"hola\0");
	msgsnd(msgid,&mem,sizeof(mem)-sizeof(long),0);//-->tercer argumento:long sms menos tipo
}

//ipcs-->dice la cantidad de mensajes
