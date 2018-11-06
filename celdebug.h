#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<execinfo.h>


#ifndef CEL_DEBUG_H
#define CEL_DEBUG_H

//print stack trace
void prst();

#define crashif( _PROP_, _MSG_, ... )do{ \
if( _PROP_ )                                  \
{ fprintf(stderr, "The Error:\n\t" #_PROP_ "\nOccurred in: " );  \
  prst();                                     \
  fprintf(stderr, _MSG_, __VA_ARGS__ );       \
  exit( 0 ); }                                \
}while(0)

#endif
