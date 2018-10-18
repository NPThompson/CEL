/*	CEL	|	C-Embedded Lisp	|	Noah Thompson 2018	*/



#ifndef C_EMBEDDED_LISP_H
#define C_EMBEDDED_LISP_H



#include<stdlib.h>
#include<stdio.h>	



/*
 *	boxs are passed by value 	  
 *	lists are passed by reference 
 *	memory allocation is done only for lists
 */

//Flag for box type
#define BOX_Z	0x00
#define BOX_DEC	0x01
#define BOX_STR	0x10//Strings are lists of chars treated as an aggregate
#define BOX_CH	0x11
#define BOX_PTR	0x20

 



//Enum for switch on list type
#define SXPR_ATOMIC		0x00	//Linear list element or end of list 
#define SXPR_COMPOUND	0x01	//Compound expression
#define SXPR_TUPLE		0x02	//Both boxes hold non-pointer values: ( val1 . val2 )
#define SXPR_EMPTY		0x03	//Empty list | nil

 
 
struct pair;

typedef struct pair*(*prop)(struct pair*);

struct box
{	char type;
	union{
		int				z;
		double			dec;
		char 			ch;
		struct pair* 	ptr;
		prop			op;
	};
}; typedef struct box box;

struct pair
{	box left, right;
}; typedef struct pair pair;

typedef pair* list;







list tokenize( const char* );
box  parsestr( const char*, int );
list quoted( const char* );
list parse( const char* );
list parsefile( FILE* );
list cel_stdlib();
list lookup( list, list );


void printlist( list, FILE* );
void printatom( box, FILE* );
void freelist( list );

list cons( box, box );

list cdr( list );
list car( list );

box str(const char*	);
box ptr(list		);
box z(	int			);
box ch(	char		);
box nil();

int type( list );

int eqlist( list,	list	);
int eqtype( box,	box	);
int eqbox( 	box,	box	);

int eqstring(	list,	list	);
int eqstrch( 	list,   const char* );


list eval(  list, list );
list apply( list, list, list );









#endif
