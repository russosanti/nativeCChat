#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 4000  //el puerto usado
#define MAXBUFF 1024  //tamaño del buffer
#define USRN 64

void Enter();
void cliente (int sock,char username[]);
int connection(int sock,char buffer[],char user[]);
void client_error(int socket,char buffer[]);
void Read(int sock,char buffer[]);
void Write(int sock, char buffer[]);
void clrbuff ( void );


void main(int argc, char *argv){
	//int i = atoi(argv[0]);
	//char buffer[MAXBUFF];
	//strcpy(buffer,argv[1]);
	//cliente(i,buffer);
	printf("%s",(char*)argv[0]);
	Enter();
}

//Funcion principal del juego
void cliente(int sock,char username[])
{
   char buffer[MAXBUFF];
   int flag = 1;
   while(flag){
	   flag = connection(sock,buffer,username);
   }
}

int connection(int sock,char buffer[],char user[]){
//	bzero(buffer,MAXBUFF);
	Read(sock,buffer);
	if(strcasecmp(buffer,"CLOSE")==0){
		printf("El usuario %s ha cerrado la conversacion\n",user);
		Enter();
		return(0);
	}else{
		printf("%s: %s\n",user,buffer);
		printf("Resp_a_%s: %s",user);
//		fflush(stdout);  // force the output to be flushed to the screen
		bzero(buffer,MAXBUFF);
		fgets(buffer,MAXBUFF - 1, stdin);
		fflush(stdin);  // x lo tanto tengo que pararme en el ultimo y borrarlo
		buffer[strlen(buffer)-1]='\0';
		if(strcasecmp(buffer,"CLOSE")==0){
			Write(sock,"CLOSE");
			return(0);
		}else{
			Write(sock,buffer);
			return(1);
		}
	}
}

//Le manda al server Exit para que termine la jugada y cierra la aplicacion
void client_error(int socket,char buffer[])
{   //es por errores logicos no en tiempo de ejecucion
    strcpy(buffer,"EXIT");
    //WR(socket,buffer);
    exit(0);
}
void Read(int sock,char buffer[]){
	bzero(buffer,MAXBUFF);
	int n = read(sock,buffer,MAXBUFF);
	if (n<0) error("ERROR reading - Conexion con el cliente perdida");
}

void Write(int sock, char buffer[]){
	 if (write(sock,buffer,MAXBUFF)<0) error("ERROR writing - Conexion con el cliente perdida");
}
void clrbuff( void )
{
  int ch;

  do
    ch = getchar();
  while ( ch != EOF && ch != '\n' );

  clearerr ( stdin );
}

void Enter()
{
    char enter[256];
    fflush(stdin);
    printf("Presione enter para continuar");
    fgets(enter,256,stdin);
    fflush(stdin);
    system("clear");
}
