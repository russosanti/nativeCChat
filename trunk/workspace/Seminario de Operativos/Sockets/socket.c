#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

main()
{
	int server, client;
	struct sockaddr_in sser, scli;
	int lenstru = sizeof(sser);
	server = socket(AF_INET,SOCK_STREAM,0);
	sser.sin_family = AF_INET;
	sser.sin_port = htons(8006);      //host to network short (convierte el numero a un tipo de dato corto para red)
	sser.sin_addr.s_addr = inet_addr("127.0.0.1"); //Pasamos la IP, inet_addr convierte el string a una direccion IPv4
	bind(server,(struct sockaddr *)&sser,lenstru);
	listen(server,100);
	while (1)
	{
		client = accept(server,(struct sockaddr *)&scli, &lenstru);
		if (client != -1)
		{
			char buf[30];
			int nb;
			nb=read(client, buf, 30);
			buf[nb]='\0';
			printf("%s\n", buf);
			write(client, "gracias cliente", 30);
			close(client);
		}  
		//falta hacer como procede si es igual -1
	}
}

