#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

mainso2()
{
	int client;
	struct sockaddr_in scli;
	int lenstru = sizeof(scli);
	client = socket(AF_INET,SOCK_STREAM,0);
	scli.sin_family = AF_INET;
	scli.sin_port = htons(8006);
	scli.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (connect(client,(struct sockaddr*)&scli,lenstru)!= -1)
	{
		char buf[30];
		int nb;
		write(client, "Hola Servidor", 30);
		nb = read(client, buf, 30);
		buf[nb] = '\0';
		printf("%s\n", buf);
		close(client);
	}
}
