#ifndef PRG_CURSES_H
#define PRG_CURSES_H

/*
  An interface implementing the 3 ncurses function I
  require. Implemented in os files.

  That's literally it.

  Basic curses like interface.
*/

void prg_initscr();

void prg_endwin();

void prg_mvprintw( int y, int x, char* string, ... );

void prg_refresh();

void prg_clear();

#endif
