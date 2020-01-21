#include "prg_file.h"

#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>

struct prg_file{
	char* file_name;
	FILE* handle;

	struct stat last_stat_info;
	struct stat current_stat_info;
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
	stat( new_file->file_name, &new_file->last_stat_info );
	stat( new_file->file_name, &new_file->current_stat_info );

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
	struct stat current_stat = file->current_stat_info;
	struct stat last_stat = file->last_stat_info;

	file->last_stat_info = file->current_stat_info;

	return ( current_stat.st_mtime !=
			 last_stat.st_mtime );
}

void file_check( struct prg_file* file ){
	stat( file->file_name, &file->current_stat_info );
}
