#include"celdebug.h"

#define MAX_DEPTH 64



void _printrelevant(const char* benumbered )
{ int start = 0;
  while( benumbered[start] != '(' )
  { start++; }
  start++;
  do{ fputc(benumbered[start++], stderr ); }while(benumbered[start] != '+');
    
}

void prst()
{ void *calladdrs[ MAX_DEPTH ];
  char **procnames;
  size_t actual_depth;

  actual_depth = backtrace( calladdrs, MAX_DEPTH );
  procnames = backtrace_symbols( calladdrs, actual_depth );

  for( int i = actual_depth - 3; i > 0; --i )//prints backwards, ignores first and last stack frames( main and prst() )
    { _printrelevant(procnames[i]);
      if( i != 1 )
        fprintf(stderr, " -> ");
      else fprintf( stderr, ":");
    }

  free(procnames);
}

