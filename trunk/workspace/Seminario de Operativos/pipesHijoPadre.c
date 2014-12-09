//int main2(int argc, char **argv)
//{
//	pid_t pid;
//	int p[2];
//	pipe(p);
//
//	pid=fork();
//
//	/* hijo - escritor */
//	if (pid == 0)
//	{
//		close(p[0]);
//		char c;
//		while (1)
//		{
//			read(0, &c, 1);
//			write(p[1], &c, 1);
//		}
//		close(p[1]);
//		exit(0);
//	}
//	else {
//
//		/* padre - escritor */
//		if (pid > 0)
//		{
//			close(p[1]);
//			while (read(p[0], &c, 1) > 0)
//			{
//				write(1, &c, 1);
//			}
//			close(p[0]);
//			exit(0);
//		}
//		else
//		{
//			printf("ERROR Fork\n");
//		}
//	}
//}
//
////TP:
////-> Hacer un SHELL.
////-> Un chat entre procesos emparentados usando pipe con y sin ncurses, con y sin señales.
////-> Un chat entre procesos independientes usando FIFO's con y sun ncurses, con y sin señales.
//
//
////Si lo hago con un solo pipe es sincrónico.
////Haciendolo con dos pipes tambien es sincrónico.
////Para hacerlo asincrónico tengo que tener 4 procesos con 2 pipes. Se genera un par de procesos lectores y otro escritores. Esto se hace on fifos porque son procesos independientes.
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//

