//escritor
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main1(int argc,char * argv[])
{
	pid_t pid;
	int fd1;
	int fd2;
	char mensajeEnv[256];
	char mensajeRec[256];

	if (fd1 = open("pipe1",O_WRONLY)<0)//ESCRIBE PD1
	{
		perror("ERROR OPEN FIFO 1\n");
		exit(1);
	}
	printf("COMIENZA PROC1////\n");
	if (fd2 = open("pipe2",O_RDONLY)<0)//LEE PD2
	{
		perror("ERROR OPEN FIFO 2\n");
		exit(1);
	}
	printf("COMIENZA PROC2////\n");
	pid=fork();
	switch(pid)
	{
		case 0://HIJO
			while(1)
			{
				read(fd2,mensajeRec,strlen(mensajeRec));
				printf("RCB:|%s|%d",mensajeRec,strlen(mensajeRec));
			}
		break;
		case -1:
			perror("ERROR AL CREAR EL FORK");
			exit(1);
		break;

		default://PADRE
			gets(mensajeEnv);
			mensajeEnv[strlen(mensajeEnv)]='\0';
			printf("SND:|%s|%d",mensajeEnv,strlen(mensajeEnv));
			write(fd1,mensajeEnv,strlen(mensajeEnv)+1);
		break;
	}
close(fd1);
}

