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



/* void printbucket( ht_record r ) */
/* { printf(" %s = %d", r.key, r.data ); */
/*   if( r.next != NULL ) */
/*     {  */
/*       printbucket(*(r.next)); */
/*     } */
/* } */


/* void printtable( ht t ) */
/* { for( int i = 0; i < HT_SIZE; ++i ) */
/*     { if( !_empty( t + i )) */
/* 	{ printf("%d#", ht_hh(t[i].key)); */
/* 	  printbucket( t[i] ); */
/* 	  printf("\n"); */
/* 	} */
/*     } */
/* } */




void pratom( list datum, FILE* stream )
{ if(null(datum)) return;
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

   /* case LAMBDA: */
   /*      fprintf(stream, "<lambda>"); */
   /* 	pratom( datum->lambda.params, stream ); */
   /* 	fprintf(stream, " -> "); */
   /* 	pratom( datum->lambda.body, stream ); */
   /*    break; */
      
    case OPERATOR: fprintf(stream, "<op:%s>", datum->operator.name);
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



void prf( list exp, FILE* stream )
{ _prf("(");
  do{
    if(null(exp)) break;
    if(atomic(exp)/*tuple*/){
      _prf(" . ");
      pratom( exp, stream );
      break;
    } else {
      pratom(car(exp),stream);
      _prf(" ");
      exp = cdr(exp);
    }
  }while(1);
  _prf(")");
}



void pr( list exp )
{ pratom(exp,stdout);
}
