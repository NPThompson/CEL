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
{ if(null(datum))
    {fprintf(stream, "()"); return;}
  if(!null(datum) && !atomic(datum))
    prf(datum,stream);
  else
    switch( type(datum) )
   {
    case STRING : fprintf(stream, "\"%s\"",datum->string);
	break;

    case NUMBER:
        fprintf(stream, "%.2f",datum->number);
      break;

    case OPERATOR: fprintf(stream, "<op:%s>", datum->operator.name);
      break;

   case LAMBDA:
     _prf("(fn ");
     pratom( datum->lambda.params, stream );
     _prf(" -> ");
     pratom( datum->lambda.body, stream );
     _prf(")");
     break;
      

   case HASH:
     _prf("[");
     for(int i = 0; i < HASH_SIZE; ++i )
       { if(!null(datum->array.records[i] ))
	   { pratom( datum->array.records[i], stream );
             _prf(", ");
	   }
       }
     _prf("]");
     break;
     
   case ARRAY:
     _prf("[");
     for( int i = 0; i < datum->array.size; ++i )
       { pratom( datum->array.records[i], stream );
	 if( i < datum->array.size - 1 )_prf(", ");
       }
     _prf("]\n");
     break;
     
    default:
      break;
  }
}

#define TCASE( _X_ ) case _X_ : fprintf( stream, "<" #_X_ ">" ); break;
void prt( int type, FILE* stream )
{ 
  switch(type)
    { TCASE( STRING );
      TCASE( SYMBOL );
      TCASE( NUMBER );
      TCASE( PAIR   );
      TCASE( OPERATOR);
      TCASE( HASH   );
      TCASE( LAMBDA );
      TCASE( ARRAY  );
    default: fprintf(stream,"<unknown type>"); break;
    }
}
#undef TCASE

void prf( list exp, FILE* stream )
{ _prf("(");
  do{
    if(null(exp)) break;
    if(atomic(exp)/*tuple*/){
      _prf(". ");
      pratom( exp, stream );
      break;
    } else {
      pratom(car(exp),stream);
      exp = cdr(exp);
      if( !null(exp))
	_prf(" ");
    }
  }while(1);
  _prf(")");
}



void pr( list exp )
{ pratom(exp,stdout);
}
