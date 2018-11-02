//gc.c
#include"cel.h"



//for garbage collector

#define START_CAPACITY 2048

struct{ list reference; int delete; } gc_table[START_CAPACITY];


list makels()
{ return (list)malloc(sizeof(atom));
}
