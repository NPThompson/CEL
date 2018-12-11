#include"celdebug.h"
#include"cel.h"

#define MAX_DEPTH 64


//filters out irrelevant information in the stack frame, printing just the name of the procedure
void _printrelevant(const char* benumbered )
{ int start = 0;
  while( benumbered[start] != '(' )
  { start++; }
  start++;
  do{ fputc(benumbered[start++], stderr ); }while(benumbered[start] != '+');
    
}



//print stack trace
void prst()
{ void *calladdrs[ MAX_DEPTH ];
  char **procnames;
  size_t actual_depth;

  actual_depth = backtrace( calladdrs, MAX_DEPTH );
  procnames = backtrace_symbols( calladdrs, actual_depth );

  for( int i = actual_depth - 3; i > 1; --i )//prints backwards, starting from main
    { _printrelevant(procnames[i]);
      fprintf(stderr, ((i == 2) ? "\n" : " -> "));
    }

  free(procnames);
}



void errv(const char* msg, ... )
{ va_list values;
  va_start(values, msg);

  for( int i = 0; i < strlen(msg); ++ i)
    { if(msg[i] == '%')
	{ switch( msg[i + 1] )
	    { case 'l' :
		prf( va_arg( values, list ), stderr );
              case 't' :
		prt(va_arg( values, int ), stderr );
	      default: break;
	    }
	  i += 2;//skip '%x'
	}
      fputc( msg[i], stderr );
    }
  //happened in stack trace...
  fprintf(stderr, "\n\tin: ");
  prst();
  exit(0);//die 
}
