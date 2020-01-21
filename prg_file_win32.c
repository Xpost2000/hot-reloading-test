#include "prg_file.h"

#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef BY_HANDLE_FILE_INFORMATION win32_stat;

struct prg_file{
	char* file_name;
	FILE* handle;

	win32_stat last_stat_info;
	win32_stat current_stat_info;
};

struct prg_file* open_prg_file( const char* filepath ){
	struct prg_file* new_file;

	// NOTE(jerry): The string is NOT dynamic.
	// it's only ever being read so no need to change.
	new_file = malloc( sizeof( struct prg_file ) );

	new_file->file_name = filepath;
	new_file->handle = fopen( filepath, "r" );

	// NOTE(jerry): technically I could do an assignment.
	// hmmm... I'm fired?
	{
		OFSTRUCT ofStructDump;
		// NOTE(jerry): MSDN suggests CreateFile
		HANDLE win32_file =
			OpenFile( filepath, &ofStructDump, OF_READ );

		GetFileInformationByHandle(
			win32_file, &new_file->current_stat_info
		);
		GetFileInformationByHandle(
			win32_file, &new_file->last_stat_info
		);

		CloseHandle( win32_file );
	}

	return new_file;
}

void close_prg_file( struct prg_file* file ){
	fclose( file->handle );
	free( file );
}

FILE* get_std_file( struct prg_file* file ){
	return file->handle;
}

int file_changed( struct prg_file* file ){
	win32_stat current_stat = file->current_stat_info;
	win32_stat last_stat = file->last_stat_info;

	typedef union _caster{
		FILETIME ft;
		unsigned long long numbers;
	}caster;

	caster st_mtime_a = {current_stat.ftLastWriteTime};
	caster st_mtime_b = {last_stat.ftLastWriteTime};

	file->last_stat_info = file->current_stat_info;

	return ( st_mtime_a.numbers >
			 st_mtime_b.numbers );
}

void file_check( struct prg_file* file ){
	{
		OFSTRUCT ofStructDump;
		// NOTE(jerry): MSDN suggests CreateFile
		HANDLE win32_file =
			OpenFile( file->file_name, &ofStructDump, OF_READ );

		GetFileInformationByHandle(
			win32_file, &file->current_stat_info
		);

		CloseHandle( win32_file );
	}
}
