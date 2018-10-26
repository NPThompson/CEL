/*	CEL	|	C-Embedded Lisp	|	Noah Thompson 2018	*/



#ifndef C_EMBEDDED_LISP_H
#define C_EMBEDDED_LISP_H



#include<stdlib.h>
#include<stdio.h>	
#include<stdarg.h>



//type enumeration for atomic values
#define STRING   0x00
#define NUMBER   0x01
#define PAIR     0x02
#define OPERATOR 0x03

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
    struct atom*(*operator)(struct atom*);
  };
  char type;
};

typedef struct atom atom;
typedef atom*       list;





int tokentype(list);
list matchparen(list);

list str(  const char*  );
list num(  double       );
list op(   list(*)(list));

list car(  list      );
list cdr(  list      );
list cons( list, list);

int  atomic( list       );
int type(   list       );
int form(   list       );

int  eqlist( list, list	);
int  eqatom( list, list );

char* copystr(const char*, unsigned int);
void freelist( list );


list tokenize( const char* );
list parsestr( const char*, unsigned int );

list parse( const char* );
list parsef(const char*, ... );

list parsefile( FILE* );
list cel_stdlib();
list assoc( list, list );

void printlist( list, FILE* );
void printatom( list, FILE* );
void freelist( list );





list eval(  list, list );
list apply( list, list, list );


list plus( list );






#endif
