
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
#include "listas.h"
#include "tdatols.h"
#include <time.h>
#include "gtk/gtk.h"
#include <sys/sem.h>
#include "operipc.h"


typedef struct
{
        GtkWidget *view;
        GtkWidget *resp;
    	int sock;
    	char username[];
} MyWidgets;


#define PORT 4000  //el puerto usado
#define MAXBUFF 1024  //tamaño del buffer
#define USRN 64
#define TIME_24   1
#define TIME_12   0


void thread_function();
void error(char *msg);
void Enter();
int server(int port);
void cant_proc(int *MAXPROC);
int proc_handler(int sig);
int valid_username(char buffer[],tlista_s *l);
void Read(int sock,char buffer[]);
void Write(int sock, char buffer[]);
void clrbuff ( void );
void al_apretar_boton (GtkWidget *button, gpointer user_data);
static gboolean delete_event( GtkWidget *widget, GdkEvent  *event, gpointer data );
static gboolean evento_conexion( GtkWidget *widget, GdkEvent  *event, gpointer   data );
void get_time_string(int mode24, char time_str[]);
gboolean insertar_detras (gpointer user_data);
int recvtimeout(int s, char *buf, int len, int timeout);
static gpointer esperar_usuario( gpointer user_data );
int crear_sem(int x);
void pantalla (int sock,char username[]);

int proc;    //variable global de procesos la defino aca para poder usarla en el handler
tlista_s l;  //lista global para todos los usuarios

int main(int   argc,
        char *argv[])
{
	server(PORT);   //llama a la rutina servidor
	return(0);
}

// Funcion para los threads
void thread_function()
{
}

// Muestra errores del sistema
void error(char *msg)
{
    perror(msg);  //toma los errores del sistema
    exit(1);      //sale con error
}

//Pide el ingreso de un enter
void Enter()
{
    char enter[256];
    fflush(stdin);
    printf("Presione enter para continuar");
    fgets(enter,256,stdin);
    fflush(stdin);
    system("clear");
}
//-----------------------------------------------
// Simula el proceso de un servidor y las conexiones con los usuarios
int server(int port)
{
     int sockfd, newsockfd, portno, clilen, pid;
     struct sockaddr_in serv_addr, cli_addr;

     if (port<=0){
         fprintf(stderr,"ERROR de configuracion del puerto\n");
         exit(1);                                        //evaluo el puerto
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);   //creo un socket para los accept
     if (sockfd < 0)
        error("ERROR creando el socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = port;
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)  //hago el bind del socket
    	 error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     proc = 0;  //cantidad de procesos abiertos
     int MAXPROC = 100;  //cantidad maxima de procesos por default
     cant_proc(&MAXPROC); //preg si se quiere configurar la cantidad maxima de procesos
     int n;  //n es para el error en el enviar (write) el estado del servidor
     printf("SERVIDOR INICIALIZADO\n\n");
     char buffer[USRN];
     lcrear(&l);
     int semid;
     while (1) {
    	 newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen); //acepto el cliente y le creo un socket
    	          if (newsockfd < 0)
    	         	 error("ERROR on accept");
    	          proc = proc + 1;  //un proceso nuevo
    	          signal(SIGCHLD, proc_handler);  //me fijo si murio o no algun proceso
    	          if(proc>MAXPROC){  //si la cantidad de procesos es o no mayor al maximo
    	         	 proc = proc - 1;  //si es mayor rechazo al proceso y le mando en el socket que no puedo aceptar mas
    	         	 n = write(newsockfd,"SERVIDOR OCUPADO",16); //escribo que esta ocupado el server
    	         	 if (n < 0) error("ERROR writing - Conexion con el cliente perdida"); //si hay error escribiendo
    	          }else{
    	         	 n = write(newsockfd,"OK",3);  //escribo que puede aceptar mas clientes
    	         	 if (n < 0) error("ERROR writing - Conexion con el cliente perdida");
    	         	 bzero(buffer,USRN);
    	         	 n = read(newsockfd,buffer,USRN);  //leo su username
    	         	 if (n < 0) error("ERROR reading - Conexion con el cliente perdida");
    	         	 while(!valid_username(buffer,&l)){
    	         		 n = write(newsockfd,"INVALID",8);  //escribo que su username es invalido
    	         		 if(n < 0) error("ERROR writing - Conexion con el cliente perdida");
    	         		 n = read(newsockfd,buffer,USRN);  //leo su username
    	         		 if(n < 0) error("ERROR reading - Conexion con el cliente perdida");
    	         	 }
    	         	 if(strcasecmp(buffer,"EXIT")==0){
    	         		 n = write(newsockfd,"EXIT",5);  //escribo sale con esxito
    	         		 if (n < 0) error("ERROR writing - Conexion con el cliente perdida");
    	         		 close(newsockfd);
    	         		 proc = proc-1;
    	         	 }else{
    	         		 n = write(newsockfd,"VALID",6);  //escribo que puede aceptar mas clientes
    	         		 if (n < 0) error("ERROR writing - Conexion con el cliente perdida");

    	         		 pid = fork();  //hace el fork para el nuevo cliente
    	        		 	 if (pid < 0)  //si hay error en el fork
    	        			 	 error("ERROR on fork");
    	        		 	 if (pid == 0)  {       //si es el hijo
    	         			 close(sockfd);          //cierro el sockfd en el hijo y uso el new
    	         			 pantalla(newsockfd,buffer); //y entro a la pantalla
    	         			 exit(0);
    	        		 	 }else{
    	        		 		Tdato_String x;
    	        		 		strcpy(x.clave,buffer);
    	        		 		x.id = pid;
    	        		 		semid = semget(0xD,0,0);
    	        		 		P(semid,0);
    	        		 		linsertarorden(&l,x,'A');
    	        		 		V(semid,0);
    	        			 	close(newsockfd);  //cierra el socket y espera otra coneccion
    	        		 	 }
    	         	 }
    	          }
    	      }
    	      return 0; //Nunca se llega pero debe devolver un valor
}

//configura la cantidad de procesos a aceptar
void cant_proc(int *MAXPROC)
{
	pthread_t thread2;
	pthread_create( &thread2, NULL,thread_function, NULL );
	char opc;
	printf("Desea configurar la cantidad de procesos a aceptar? (S: SI , N: NO)\n");
	printf("(El default es 100)\n");
	scanf("%c",&opc);
	fflush(stdin);
	while(opc!='S' && opc!='N' && opc!='s' && opc!='n'){
		printf("La opcion puede ser 'S': SI o 'N': NO");
		scanf("%c",&opc);
		fflush(stdin);
	}
	system("clear");
	if(opc=='S' || opc=='s'){
		printf("Ingrese la maxima cantidad de procesos a aceptar por el servidor:\n");
		scanf("%d",MAXPROC);
		fflush(stdin);
		scanf("%c",&opc);  //para limpiar el buffer
		system("clear");
		printf("MAXIMA cantidad de procesos a aceptar cambiada\n\n");
		Enter();
	}
	clrbuff();
	pthread_join(thread2, NULL);
}

//handler para cuando muere un hijo
// resta 1 a la cantidad de procesos y elimina el username
int proc_handler(int sig)
{
  pid_t pid;

  pid = wait(NULL);
  int semid =semget(0xD,0,0);
  P(semid,0);
  proc = proc - 1;

  if(!lvacia(&l)){
	  lppio(&l);
	  Tdato_String x;
	  linfo(&l,&x);
	  int existe = 0;
	  if(x.id == pid){
		  existe = 1;
	  }else{
		  lsig(&l);
	  }
	  while(!lfin(&l) && !existe){
		  linfo(&l,&x);
		  if(x.id == pid){
			  existe = 1;
		  }else{
			  lsig(&l);
		  }
	  }
	  if(existe){
		  lborraractual(&l);
		  printf("Usuario: %s exited. ",x.clave);
	  }else{
		  printf("Error: no se pudo borrar el usuario perteneciente al proceso %d",pid);
	  }
  }else{
	  printf("Error: no se pudo borrar el usuario perteneciente al proceso %d",pid);
  }
  V(semid,0);
  printf("Process %d exited.\n", pid);
}

//Funcion para validar el username
int valid_username(char buffer[],tlista_s *l){
	int existe = 0;
	int semid = semget(0xD,0,0);
	if(strcasecmp(buffer,"EXIT")==0){
		return(1);
	}else{
		P(semid,0);
		lbuscar(l,buffer,&existe);
		V(semid,0);
		return(!existe);
	}
}


//Pantalla principal del chat
void pantalla (int sock,char username[]){

	GtkWidget *window;
	GtkWidget *box1;
	GtkWidget *separator;
	GtkWidget *label;
	GtkWidget *quitbox;
	GtkWidget *scrolled_window;
	GtkTextBuffer *buffer1;
	GtkWidget *envio;
	GtkTextBuffer *buffer_resp;
	MyWidgets  datos_conexion;
	gchar *titulo;
	GtkTextIter iter;
	GtkTextMark *end_mark;

    GThread   *thread;
    GError    *error = NULL;

	char time_str[12];
	char mensaje[MAXBUFF];
	gchar *text2;
	int n;
	text2 = (gchar*)g_malloc ((gsize)(sizeof (mensaje)* sizeof (gchar)));
	titulo = (gchar*)g_malloc ((gsize)(sizeof (mensaje)* sizeof (gchar)));

	get_time_string(TIME_24, time_str);

	// Copiar los datos de ingreso a datos_conexion
	datos_conexion.sock = sock;
	strcpy(datos_conexion.username,username);


	/* Incio de uso de GTK */
	gtk_init (0, NULL);

	/* Crea la ventana */
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

	g_signal_connect (window, "delete-event",
			  G_CALLBACK (delete_event), &datos_conexion);

	strcpy(titulo,"Chat con ");
	strcat(titulo, datos_conexion.username);
	gtk_window_set_title (GTK_WINDOW(window), titulo);
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);
	gtk_widget_set_size_request (GTK_WIDGET (window), 350, 230);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

	box1 = gtk_vbox_new (FALSE, 2);

	label = gtk_label_new ("Mensajería Instantánea");

	gtk_misc_set_alignment (GTK_MISC (label), 0, 0);

	gtk_box_pack_start (GTK_BOX (box1), label, FALSE, FALSE, 0);

	gtk_widget_show (label);

	// Crea la ventana de arriba donde muestra los mensajes intercambiados
	datos_conexion.resp = gtk_text_view_new ();
	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (datos_conexion.resp), GTK_WRAP_WORD_CHAR);
	buffer_resp = gtk_text_view_get_buffer (GTK_TEXT_VIEW (datos_conexion.resp));

	scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
			   	           GTK_POLICY_AUTOMATIC,
					   GTK_POLICY_AUTOMATIC);

	gtk_container_add (GTK_CONTAINER (scrolled_window), datos_conexion.resp);
	gtk_text_buffer_set_text (buffer_resp, "", -1);
	gtk_text_view_set_editable(GTK_TEXT_VIEW (datos_conexion.resp), FALSE);
	gtk_box_pack_start (GTK_BOX (box1), scrolled_window, TRUE, TRUE, 0);
	gtk_widget_show (datos_conexion.resp);
	gtk_widget_show (scrolled_window);

	separator = gtk_hseparator_new ();
	gtk_box_pack_start (GTK_BOX (box1), separator, TRUE, TRUE, 5);
	gtk_widget_show (separator);


	// Crea la ventana de abajo donde contesta los mensajes
	datos_conexion.view = gtk_text_view_new ();
	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (datos_conexion.view), GTK_WRAP_WORD_CHAR);
	buffer1 = gtk_text_view_get_buffer (GTK_TEXT_VIEW (datos_conexion.view));

	scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
			   	           GTK_POLICY_AUTOMATIC,
					   GTK_POLICY_AUTOMATIC);

	gtk_container_add (GTK_CONTAINER (scrolled_window), datos_conexion.view);
	gtk_text_buffer_set_text (buffer1, "Texto inicial ", -1);
	gtk_box_pack_start (GTK_BOX (box1), scrolled_window, TRUE, TRUE, 0);
	gtk_widget_show (datos_conexion.view);
	gtk_widget_show (scrolled_window);


	separator = gtk_hseparator_new ();
	gtk_box_pack_start (GTK_BOX (box1), separator, TRUE, TRUE, 5);
	gtk_widget_show (separator);

	gtk_text_buffer_create_tag(buffer_resp, "lmarg",
	      "left_margin", 5, NULL);
	gtk_text_buffer_create_tag(buffer_resp, "blue_fg",
	      "foreground", "blue", NULL);
	gtk_text_buffer_create_tag(buffer_resp, "black_fg",
	      "foreground", "black", NULL);
	gtk_text_buffer_create_tag(buffer_resp, "red_fg",
	      "foreground", "red", NULL);

	quitbox = gtk_hbox_new (TRUE, 1);

	envio = gtk_button_new_with_label ("Enviar");
	gtk_box_pack_start (GTK_BOX (quitbox), envio, TRUE, FALSE, 0);
	g_signal_connect (G_OBJECT (envio), "clicked",
                     G_CALLBACK (al_apretar_boton),
                     &datos_conexion);

	gtk_box_pack_start (GTK_BOX (box1), quitbox, FALSE, FALSE, 0);

	gtk_container_add (GTK_CONTAINER (window), box1);

    /* Crear nuevo thread para ver si llega un nuevo mensaje del cliente */
    thread = g_thread_create( esperar_usuario,&datos_conexion,
                              FALSE, &error );
    if( ! thread )
    {
        g_print( "Error: %s\n", error->message );
        return( -1 );
    }

	gtk_widget_show (envio);
	gtk_widget_show (quitbox);

	gtk_widget_show (box1);
	gtk_widget_show (window);

	gtk_main ();

	return 0;
}

/* Lectura de una respuesta del cliente */
static gpointer
esperar_usuario( gpointer user_data )
{
    while( TRUE )
    {
        sleep( 3 );

        gdk_threads_enter();

        char mensaje[MAXBUFF];
    	MyWidgets               *widgetsydatos;
    	GtkTextBuffer           *buffer_resp;
    	widgetsydatos = (MyWidgets *)user_data;
    	GtkTextMark *end_mark;
    	char time_str[12];
    	GtkTextIter iter;

    	gchar *text2;
    	int n;
    	text2 = (gchar*)malloc (sizeof (mensaje)* sizeof (gchar));

    	buffer_resp = gtk_text_view_get_buffer (GTK_TEXT_VIEW (widgetsydatos->resp));

   	// Recibe lo que manda el cliente y si no hay nada se va por timeout
    	n = recvtimeout(widgetsydatos->sock, mensaje, sizeof mensaje, 5); // 5 second timeout
    	if (n == -1) {
    		perror("recvtimeout");
    	}
    	else if (n == -2) {
    		// timeout
    	} else {
    	  if(strcasecmp(mensaje,"CLOSE")==0){
    		g_print ("Sesión cerrada por %s \n", widgetsydatos->username);
    		exit(0);
    	  }else{
    		get_time_string(TIME_24, time_str);
    		strcpy(text2,mensaje);

    		text2 = g_strconcat(widgetsydatos->username," [",time_str,"]:  \n", text2, " \n  ",NULL);

    		gtk_text_buffer_get_end_iter(buffer_resp, &iter);
     		gtk_text_buffer_insert(buffer_resp,&iter, text2, -1);

     	// Sube el scroll para mostrar el final siempre
     		gtk_text_buffer_get_end_iter(buffer_resp, &iter);
     		end_mark = gtk_text_buffer_get_insert (buffer_resp);
     		gtk_text_buffer_place_cursor(buffer_resp, &iter);
     		gtk_text_view_scroll_to_mark( GTK_TEXT_VIEW (widgetsydatos->resp),
    				  end_mark, 0.0, TRUE, 0.0, 1.0);

    	  }
    	}

    	gdk_threads_leave();
    }

    return( NULL );
}

// Evento que se ejecuta cuando cierra la ventana
static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
	MyWidgets               *widgetsydatos;
	widgetsydatos = (MyWidgets *)data;
	// Envia el cierre al cliente //
    g_print ("Server: CERRAR  \n");
    Write(widgetsydatos->sock,"CLOSE");
    exit(0);
    gtk_main_quit ();
    return FALSE;
}

/* Ejecuta cuando se apreta el boton de envio del mensaje */
void al_apretar_boton (GtkWidget *button, gpointer user_data)
{
	char mensaje[MAXBUFF];
	MyWidgets               *widgetsydatos;
	GtkTextBuffer           *buffer;
	GtkTextBuffer           *buffer_resp;
	widgetsydatos = (MyWidgets *)user_data;
	GtkTextMark *end_mark;
	char time_str[12];

	GtkTextIter start;
	GtkTextIter end;

	get_time_string(TIME_24, time_str);
	gchar *text;
	gchar *text2;

	text = (gchar*)malloc (sizeof (mensaje)* sizeof (gchar));
	text2 = (gchar*)malloc (sizeof (mensaje)* sizeof (gchar));
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (widgetsydatos->view));

	gtk_text_buffer_get_start_iter (buffer, &start);
	gtk_text_buffer_get_end_iter (buffer, &end);

	text = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);

	text2 = g_strconcat("Server [",time_str,"]: \n  ",NULL);

	buffer_resp = gtk_text_view_get_buffer (GTK_TEXT_VIEW (widgetsydatos->resp));

	gtk_text_buffer_get_end_iter(buffer_resp, &end);
	gtk_text_buffer_insert(buffer_resp,&end, text2, -1);


	gtk_text_buffer_get_end_iter(buffer_resp, &end);
	text2 = g_strconcat(text,"\n",NULL);
	gtk_text_buffer_insert(buffer_resp,&end, text2, -1);

	strcpy(mensaje, text);
	// Envia la respuesta al cliente //
	if(strcasecmp(mensaje,"CLOSE")==0){
	  g_print ("Server: CERRAR  \n");
	  Write(widgetsydatos->sock,mensaje);
	  exit(0);
	}else{
	  Write(widgetsydatos->sock,mensaje);
	}

	// Sube el scroll para mostrar el final siempre
	gtk_text_buffer_get_end_iter(buffer_resp, &end);
	end_mark = gtk_text_buffer_get_insert (buffer_resp);
	gtk_text_buffer_place_cursor(buffer_resp, &end);
	gtk_text_view_scroll_to_mark( GTK_TEXT_VIEW (widgetsydatos->resp),
			  end_mark, 0.0, TRUE, 0.0, 1.0);

	/* limpia el bufer de texto ingresado para comenzar a ingresar un nuevo mensaje.   */
	gtk_text_buffer_set_text (buffer, "", -1);
}


// lee del buffer del socket
void Read(int sock,char buffer[]){
	bzero(buffer,MAXBUFF);
	int n = read(sock,buffer,MAXBUFF);
	if (n<0) error("ERROR reading - Conexion con el cliente perdida");
}

// escribe en el buffer del socket
void Write(int sock, char buffer[]){
	 if (write(sock,buffer,MAXBUFF)<0) error("ERROR writing - Conexion con el cliente perdida");
}

// limpia el buffer del teclado
void clrbuff ( void ){
  int ch;

  do
    ch = getchar();
  while ( ch != EOF && ch != '\n' );

  clearerr ( stdin );
}

// procesa el timeout del socket
// si no lee nada sale con -2, con error con -1, y si no la cantidad que leyo
int recvtimeout(int s, char *buf, int len, int timeout)
{
	fd_set fds;
	int n;
	struct timeval tv;
	FD_ZERO(&fds);
	FD_SET(s, &fds);
	tv.tv_sec = timeout;
	tv.tv_usec = 0;
	n = select(s+1, &fds, NULL, NULL, &tv);
	if (n == 0) return -2; // timeout!
	if (n == -1) return -1; // error
	return recv(s, buf, len, 0);
}

// convierte la hora del sistema en string para mostrar en pantalla con cada mensaje
void get_time_string(int mode24, char time_str[])
{
  struct tm *now = NULL;
  int hour = 0;
  time_t time_value = 0;

  time_value = time(NULL);
  now = localtime(&time_value);
  hour = now->tm_hour;
  if(!mode24 && hour>12)
    hour -= 12;

  sprintf (time_str,"%2d:%02d:%02d",hour,now->tm_min,now->tm_sec);

  if(!mode24){
    if(now->tm_hour>24){
       printf("PM\n");
    }else{
       printf("AM\n");
    }
  }
}

// crea e inicializa los semaforos
int crear_sem(int x)
{
	int semid= semget(0xD,x,IPC_CREAT|IPC_EXCL|0666);
	semid= semget(0xD,0,0);
	semctl(semid,0,SETVAL,1);
	return semid;
}
