#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int
main3(int argc, char **argv)
{
	int fd;
	
	/* Creo un fifo */
	fd = mkfifo(argv[1], 0666);
	
	if (fd < 0) 
	{
		printf("ERROR mkfifo\n");
		exit(1);
	}	
	exit(0);
}
