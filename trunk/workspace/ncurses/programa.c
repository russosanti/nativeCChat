/*
 * programa.c
 *
 *  Created on: Jun 3, 2011
 *      Author: claudio
 */

#include <ncurses.h>
int main2() {
initscr();
printw("Hola linux!");
refresh();
getch();
endwin();
return 0;
}
