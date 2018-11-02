#include"celdebug.h"



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

  for( int i = 1; i < actual_depth; ++i )//begin from one because no one cares about the prst() procedure
    { _printrelevant(procnames[i]);
      fprintf(stderr, ": ");
    }

  free(procnames);
}
