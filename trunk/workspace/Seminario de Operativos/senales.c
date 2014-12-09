#include<stdio.h>
#include<unistd.h>
#include<signal.h>


void mains0()
{
       alarm(20);


       while(1){
               printf("Estyo esperando la senial");
               sleep(2);
       }

}

void fc(void);

void mains1()
{
	signal(SIGINT,fc);
	while(1){
		sleep(1);
	}
}
void fc(void){
	printf("Presiono Ctrl-c\n");
}

//int main(){
//
//	while(1){
//       printf("y?\n");
//	}
//       return 0;
//}       pera pararlo de la consola le puedo mandar $kill -9 pid o $kill -l esas son las senales
// SIGNKILL o SIGSTOP

void falarma(void);

void mains2()
{
	signal(SIGINT,(void *)fc);  //casteo a un puntero
	signal(SIGALRM,(void *)falarma);
	alarm(20);
	while(1){
		printf("y\n");
		sleep(1);
	}
}

void falarma(void){
	signal(SIGINT,SIG_DFL);
}

//Ignorar senales
void mains3()
{
	signal(SIGINT,SIG_IGN);
	signal(SIGALRM,SIG_IGN);
	signal(SIGTERM,SIG_IGN);
	while(1){
		printf("a");
		sleep(1);
	}
}

