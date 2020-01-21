#include "prg_curses.h"

#include <curses.h>

void prg_initscr(){
	initscr();
}

void prg_endwin(){
	endwin();
}

void prg_mvprintw( int y, int x, char* string, ... ){
	// NOTE(jerry): I'm fired for this.
	char print_buffer [ 1024 ] = {0};
	va_list args;
	va_start( args, string );
	vsprintf( print_buffer, string, args );
	va_end( args );

	mvprintw( y, x, print_buffer );
}

void prg_refresh(){
	refresh();
}

void prg_clear(){
	clear();
}
