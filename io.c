/*io.c*/

//use `quoted( "----" )' to parse input for now

#include"cel.h"

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<assert.h>




//Requires that stream is defined in this scope
#define _prf( txt ) fprintf( stream, txt )



void pratom( list datum, FILE* stream )
{ if(null(datum)) return;
  if(!null(datum) && !atomic(datum))
    prf(datum,stream);
  else
    switch( type(datum) )
   {
    case STRING : fprintf(stream, "'%s'",datum->string);
	break;

    case NUMBER:
        fprintf(stream, "%.2f",datum->number);
      break;

    case OPERATOR: fprintf(stream, "<op:%s>", datum->operator.name);
      break;

    default:
      break;
  }
}



void prf( list exp, FILE* stream )
{ _prf("(");
  do{
    if(null(exp)) break;
    pratom(car(exp),stream);
    _prf(" ");
    exp = cdr(exp);
  }while(1);
  _prf(")");
}



void pr( list exp )
{ pratom(exp,stdout);
}
