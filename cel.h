/*	CEL	|	C-Embedded Lisp	|	Noah Thompson 2018	*/



#ifndef C_EMBEDDED_LISP_H
#define C_EMBEDDED_LISP_H




#include"celdebug.h"



#include<stdlib.h>
#include<stdio.h>	
#include<stdarg.h>



//type enumeration for atomic values
#define STRING   0x00
#define NUMBER   0x01
#define PAIR     0x02
#define OPERATOR 0x03
#define LAMBDA   0x04

//type enumeration for expression forms
#define NIL      0x00
#define ATOM     0x01
#define TUPLE    0x02
#define LIST     0x03
#define COMPOUND 0x04








struct atom;
 
struct atom{
  union{
    char*   string;

    double  number;

    struct{
      struct atom* car;
      struct atom* cdr;
    } pair;

    struct{
      struct atom*(*fp)(struct atom*);
      const char*    name;
    } operator;

    struct{
      struct atom* body;
      struct atom* params;
      struct atom* env;
    } lambda;
    
  };
  unsigned short type;
};

typedef struct atom atom;
typedef atom*       list;




list makels();

list str(  const char*                );
list num(  double                     );
list op(   list(*)(list), const char* );
list fn( list, list, list );//make lambda

list car(  list      );
list cdr(  list      );
list cons( list, list);

int atomic(   list     );
int null(   list       );
int type(   list       );

char* copystr(const char*, unsigned int );
int  eq( list, list );

list tokenize( const char* );



//print
void pr( list );
void prf(list,FILE*);
	 
//parse
list ps( const char* );
list psv(const char*, ... );//variadic parse
list psf( FILE* );

list cel_stdlib();
list assoc( list, list );


list fold( list, list(*fn)( list, list));
list map(  list, list(*fn)( list )     );
list zip( list, list );


list evlist(list, list);
list eval(  list, list );
list apply( list, list, list );
list append( list, list );




list plus( list );







#endif
