/*
  Hacky cross platform demo.

  Ideally I would've spent more work making
  my own file struct.

  But for a dumb demo this is okay.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "prg_curses.h"
#include "prg_file.h"

int main( int argc, char** argv ){
	prg_initscr();
	// initial load.
	struct prg_file* prgfile = open_prg_file( "data.txt" );
	FILE* file = get_std_file( prgfile );

	static char string_buffer[ 1024 ] = {0};
	fread( string_buffer, 1, 1024, file );

	fclose( file );
	do{
		{
			file_check( prgfile );

			if( file_changed( prgfile ) ){
				prg_clear();

				memset( string_buffer, 0, 1024 );
				file = fopen( "data.txt", "r" );

				fread( string_buffer, 1, 1024, file );

				fclose( file );
			}
		}

		prg_mvprintw( 3, 0, "%s\n", string_buffer );

		prg_refresh();
	}while( 1 );

	close_prg_file( prgfile );
	prg_endwin();
	return 0;
}
