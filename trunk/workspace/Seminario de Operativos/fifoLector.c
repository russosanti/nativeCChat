#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int
main4(int argc, char **argv)
{
	int fd;
	int c;
	
	fd = open(argv[1], O_RDONLY);
	
	while (read(fd, &c, 1) > 0)
	{
		printf("%c ", c);
	}
	close(fd);
}
