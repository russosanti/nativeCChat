#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>


int
main5(int argc, char **argv)
{
	int fd;
	int letra = 'a';
	
	fd = open(argv[1], O_WRONLY); /* El open con WRONLY es bloqueante, se bloquea y espera al lector */
	
	while (letra <= 'z')
	{
		write(fd, &letra, 1);
		letra++;
	}
	close(fd);
}
