/*NOTE: WIN32*/
#include "prg_curses.h"

#include <stdio.h>
#include <stdlib.h>

#include <stdarg.h>

#include <windows.h>
#include <stdint.h>

#define internal static

typedef int32_t i32;
typedef uint32_t u32;

typedef int64_t i64;
typedef uint64_t u64;

typedef int16_t i16;
typedef uint16_t u16;

typedef int8_t i8;
typedef uint8_t u8;

typedef float f32;
typedef double f64;

typedef i32 b32;

// Copied and pasted from a previous toy thing.
internal i32
Handmade_Printf( i32 y, i32 x, const char* format_string, ... ){
	i32 written_characters = 0;

	HANDLE con_stdout = GetStdHandle( STD_OUTPUT_HANDLE );

	CONSOLE_SCREEN_BUFFER_INFO console_screen_info;

	GetConsoleScreenBufferInfo( con_stdout, &console_screen_info );

	va_list va_args;
	va_start( va_args, format_string );

	i16 _x = x;
	i16 _y = y;

	do{
		switch( (*format_string) ){
			case '\r':
			{
				_x = 0;
			}
			break;
			case '\n':
			{
				_x = 0;
				_y++;
			}
			break;
			case '\t':
			{
				// implementation dependent? Supposed to be pretty intelligent
				// but idk.
				_x += 4;
			}
			break;
			case '%':
			{
			}
			break;
			default:
			{
				DWORD con_out_written;

				COORD write_coordinate = {
					console_screen_info.dwCursorPosition.X + _x,
					console_screen_info.dwCursorPosition.Y + _y
				};

				WriteConsoleOutputCharacter(
					con_stdout, (format_string), 1,
					write_coordinate,
					&con_out_written
				);

				_x += con_out_written;
			}
			break;
		}	
	}while( *(format_string++) );
	va_end( va_args );

	return (written_characters & (format_string != 0));
}

void prg_initscr(){
	// blank on win32.
}

void prg_endwin(){
	// blank on win32.
}

void prg_mvprintw( int y, int x, char* string, ... ){
	// NOTE(jerry): I'm fired for this.
	char print_buffer [ 1024 ] = {0};
	va_list args;
	va_start( args, string );
	vsprintf( print_buffer, string, args );
	va_end( args );

	Handmade_Printf( y, x, print_buffer );
}

void prg_refresh(){
}

// NOTE(jerry): copied and pasted from MSDN, I'm not implementing more.
void cls( HANDLE hConsole ){
    COORD coordScreen = { 0, 0 };    /* here's where we'll home the
                                        cursor */ 
    BOOL bSuccess;
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */ 
    DWORD dwConSize;                 /* number of character cells in
                                        the current buffer */ 

    /* get the number of character cells in the current buffer */ 

    bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi );
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    /* fill the entire screen with blanks */ 

    bSuccess = FillConsoleOutputCharacter( hConsole, (TCHAR) ' ',
										   dwConSize, coordScreen, &cCharsWritten );

    /* get the current text attribute */ 

    bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi );

    /* now set the buffer's attributes accordingly */ 

    bSuccess = FillConsoleOutputAttribute( hConsole, csbi.wAttributes,
										   dwConSize, coordScreen, &cCharsWritten );

    /* put the cursor at (0, 0) */ 

    bSuccess = SetConsoleCursorPosition( hConsole, coordScreen );
    return;
}
// NOTE(jerry): copied and pasted from MSDN, I'm not implementing more.

void prg_clear(){
    cls( GetStdHandle(STD_OUTPUT_HANDLE) );
}
