#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initWindow(void);
void salir (void); //Esta función se utiliza al Salir del programa
void dibujarTableRecepcion(void);
void dibujarTableEnvio(void);
void initPairColors(void);
void updateWindows(void);
WINDOW *tSnd;
WINDOW *tRcb;

int colScr;
int rowScr;
int posRcb=0;
int posSnd=0;
int main(void)
{
	char nombre[128];
	char txtSend[60];
	initWindow();	
	initPairColors();
	bkgd(COLOR_PAIR(1)); /*Aqui define el color de fondo del programa*/
	move(4,2); //Aqui mueve el cursor a linea 4 columna 2.
	printw("Escriba su nombre"); //Imprimimos el texto en la posición especificada             en la linea anterior.
	move(5,2);
	getstr(nombre);
	clear();
	refresh();    //Actualiza la ventana

	getmaxyx(stdscr, rowScr, colScr);	
	while(strcpy(txtSend,"EXIT")!=0)
	{
		dibujarTableRecepcion();
		dibujarTableEnvio();
		mvwprintw(tRcb, posRcb, 2, "%s",txtSend); 
		posRcb=posRcb+1;
		mvwprintw(tSnd, posSnd, 2, "%s:",nombre); 
		updateWindows();
		gets(txtSend);
		
	}
	getch();      //Espera que el usuario presione un tecla
	salir();    // llama a la función salir
}
/*********************************************************************/
void initWindow()
{
	initscr();   /*Esta función inicializa los ncurses*/
	start_color(); //Esta función inicia los colores
	//keypad(stdscr,TRUE);

}
/*********************************************************************/
void salir()
{
   endwin(); /*Siempre que finalizamos un programa con una biblioteca curses,
                    debemos ejecutar este comando.*/
   exit(0);
}
/*********************************************************************/
void dibujarTableRecepcion()
{
	//lineas,cols,iniY,iniX
	tRcb=newwin(rowScr-10,colScr,0,0);
	wbkgd(tRcb, COLOR_PAIR(3));
	wrefresh(tRcb);

}
/*********************************************************************/
void dibujarTableEnvio()
{
	//lineas,cols,iniY,iniX
	tSnd=newwin(8,colScr,rowScr-8,0);
	wbkgd(tSnd, COLOR_PAIR(1));
	wrefresh(tSnd);

}
/*********************************************************************/
void initPairColors()
{
	//Define pares de colores que serán definidos en el programa
	init_pair(1,COLOR_WHITE,COLOR_BLUE); //Texto(Blanco) | Fondo(Azul)
	init_pair(2,COLOR_BLUE,COLOR_WHITE); //Texto(Azul) | Fondo(Branco)
	init_pair(3,COLOR_RED,COLOR_WHITE); //Texto(rojo) | Fundo(Blanco)
}
/*********************************************************************/
void updateWindows()
{
	wrefresh(tRcb);
	wrefresh(tSnd);
}
