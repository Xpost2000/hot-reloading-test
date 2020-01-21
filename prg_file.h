#ifndef PRG_FILE_H
#define PRG_FILE_H

// NOTE(jerry): Can I forward declare FILE? I think so but idk.
#include <stdio.h>
#include <stdlib.h>

struct prg_file;
/*
  A gimped FILE?
  
  I only need it to store file info.

  NOTE(jerry): in a real project, I obviously would not do this.
*/
struct prg_file* open_prg_file( const char* filepath );
void close_prg_file( struct prg_file* file );

FILE* get_std_file( struct prg_file* file );

int file_changed( struct prg_file* file );
void file_check( struct prg_file* file );

#endif
