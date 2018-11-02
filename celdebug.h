#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<execinfo.h>


#ifndef CEL_DEBUG_H
#define CEL_DEBUG_H

#define MAX_DEPTH 10

//print stack trace
void prst();

#define crashif( prop, msg ) if( prop ){ fprintf(stderr, "Error in: "); prst(); fprintf(stderr, "\n%s\n", msg ); exit( 0 ); }

#endif
