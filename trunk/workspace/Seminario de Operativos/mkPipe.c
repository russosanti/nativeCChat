//EJERCICIO BASICOI DE PIPES
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main7(int argc,char * argv[])
{
	int fd;
	fd = mkfifo(argv[1],0777);

	if (fd<0)
	{
		perror("ERROR MKFIFO\n");
		exit(1);
	}
	exit(0);
}

