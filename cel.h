/*	CEL	|	C-Embedded Lisp	|	Noah Thompson 2018	*/



#ifndef C_EMBEDDED_LISP_H
#define C_EMBEDDED_LISP_H




#include"celdebug.h"

#include<stdlib.h>
#include<stdio.h>	
#include<stdarg.h>



//type enumeration for atomic values
#define STRING   0x00
#define SYMBOL   0x01
#define NUMBER   0x02
#define PAIR     0x03
#define OPERATOR 0x04
#define HASH     0x05//Hash table and array both use the array structure in the atom union,
#define ARRAY    0x06//But treat it differently.
#define LAMBDA   0x07



#define caar(  S_EXPR ) car(car(S_EXPR))
#define cdar(  S_EXPR ) cdr(car(S_EXPR))
#define cadr(  S_EXPR ) car(cdr(S_EXPR))
#define cddr(  S_EXPR ) cdr(cdr(S_EXPR))
#define cadar( S_EXPR ) car(cdr(car(S_EXPR)))
#define caddr( S_EXPR ) car(cdr(cdr(S_EXPR)))
#define cdddr( S_EXPR ) cdr(cdr(cdr(S_EXPR)))

#define HASH_SIZE 256


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
    
    struct{
      struct atom** records;
      unsigned int size;
    } array;
    
  };
  unsigned short type;
};

typedef struct atom atom;
typedef atom*       list;














//As opposed to malloc: makels tracks the new list for eventual garbage collection
list makels();

//Atomic initializers : list wraps primitive value
list str(  const char*                );
list num(  double                     );
list op(   list(*)(list), const char* );
list fn( list, list, list );//make lambda
list ar( list );
list ht( list );//from list of pairs

//Pair Selection and Construction
list car(  list      );
list cdr(  list      );
list cons( list, list);

//Predicates
int atomic( list );
int null(   list );
int   eq( list, list );

int type(   list );
char* copystr(const char*, unsigned int );






//print 
void pr( list );
void prf(list,FILE*);
void prt(int, FILE*);


//parse
list tokenize( const char* );       //transforms buffer into list of tokens
list ps( const char* );             //parse buffer
list psv(const char*, ... );        //variadic parse
list psf( FILE* );                  //parse file

//library functions
list cel_corelib();                 //core functions: arithmetic, car, cdr, etc.
list assoc( list, list );           //returns the value associated with the symbol in a table
list append( list, list);           //append the second list to the first



void ins( list, const char*, list );       //insert entry into hash table
list ix(  list, const char*);              //index hash table

list fold( list, list(*fn)( list, list));
list map(  list, list(*fn)( list )     );
list zip( list, list );
unsigned int lgh(list);                    //length of a list

//EVAL/APPLY
list eval( list, list, list );














#endif
