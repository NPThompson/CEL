#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<execinfo.h>
#include<stdarg.h>

#ifndef CEL_DEBUG_H
#define CEL_DEBUG_H

//print stack trace
void prst();

//variadic error:
//%t for type
//%l for list
void errv(const char* msg, ...);

#endif
