#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<sys/signal.h>
#include<fcntl.h>
#include<unistd.h>

#define mamin ('a'-'A')


char to_mayus(char a);
char to_minus(char a);


int main10(){
	int pid;
	char a = 'A';
	int pp[2];
	int ph[2];
	int fd;

	if((fd = open("abc.txt",O_CREAT | O_TRUNC | O_WRONLY,0666))<0){
		perror("Error al abrir el archivo");
	}

	if(pipe(pp)<0){
		perror("Error al crear Pipe Padre");
	}
	if(pipe(ph)<0){
		perror("Error al crear Pipe Hijo");
	}

	pid = fork();

	if(pid==0)
	{
		close(pp[1]);
		close(ph[0]);
		while(read(pp[0],&a,1)>0){
			if(write(fd,&a,1)<0){
				perror("Error al escribir en el archivo");
			}
			a++;
			a = to_minus(a);
			if (a=='z'||a=='Z'){
				kill(getppid(),SIGINT);
				raise(SIGINT);

			}
			write(ph[1],&a,1);
		}
	}else{
		if(pid>0){
			close(pp[0]);
			close(ph[1]);
			write(pp[1],&a,1);
			while(read(ph[0],&a,1)>0){
				if(write(fd,&a,1)<0){
					perror("Error al escribir en el archivo");
				}
				a++;
			    a = to_mayus(a);
			    if(a=='z'||a=='Z'){
			       	kill(pid,SIGINT);
			       	raise(SIGINT);
       			}
			   write(pp[1],&a,1);
			}
		}else{
			perror("Error en el fork");
			exit(1);
		}
	}
	close(fd);
	return(0);
}

char to_mayus(char a){
	return(a-mamin);
}

char to_minus(char a){
	return (a+mamin);
}
