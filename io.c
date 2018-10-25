/*io.c*/

//use `quoted( "----" )' to parse input for now

#include"cel.h"

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<assert.h>










 

void printatom( list datum, FILE* stream )
{   switch( type(datum) )
    { case STRING : fprintf(stream, "'%s'",datum->string);
	break;
    case NUMBER: fprintf(stream, "%.2f",datum->number);
      break;

    case OPERATOR: fprintf(stream, "<op>");
      break;
    default:
      break;
    }
}



void printlist( list l, FILE* stream )
{ switch(form(l))
    { case NIL: break;

      case LIST:
        printatom(car(l),stream);
        fprintf(stream," ");
	printlist(cdr(l), stream);
	break;
	
      case COMPOUND:
	fprintf(stream,"(");
	  printlist(car(l),stream);
	fprintf(stream,")");
	
	printlist(cdr(l),stream);
	break;

      case ATOM: printatom(l, stream);
	break;

      case TUPLE:
	printatom(car(l),stream);
	fprintf(stream," . ");
	printatom(cdr(l),stream);
	break;
    }
} 

