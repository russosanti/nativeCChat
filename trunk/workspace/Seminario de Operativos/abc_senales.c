#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<fcntl.h>
#include<unistd.h>

void wrp();
void wrh();

int fd;
char a = 'A';
char x = 'b';

int mainsen(){
	int pid;

	if((fd = open("abc_senales.txt",O_CREAT | O_TRUNC | O_WRONLY,0666))<0){
		perror("Error al abrir el archivo");
	}

	pid = fork();

	if(pid==0)
	{
		x='b';
		signal(SIGUSR1,(void *)wrh);
		sleep(2);
		while(1){
			if(x>'z'){
				kill(getppid(),SIGINT);
				raise(SIGINT);
			}else{
				kill(getppid(),SIGUSR2);
				pause();
			}
		}
	}else{
		if(pid>0){
			a='A';
			signal(SIGUSR2,(void *)wrp);
			while(1){
				printf("%c\n",a);
				if(a>'Z'){
					printf("aaa: %c\n",a);
					exit(0);
					kill(pid,SIGINT);
					raise(SIGINT);
					break;
				}else{
					pause();
					kill(pid,SIGUSR1);
				}
			}
		}else{
			perror("Error en el fork");
			exit(1);
		}
	}
	close(fd);
	return(0);
}

void wrp(){
	if(write(fd,&a,1)<0){
		perror("Error al escribir en el archivo");
	}
	a=a+2;
}

void wrh(){
	if(write(fd,&x,1)<0){
		perror("Error al escribir en el archivo");
	}
	x=x+2;
}


