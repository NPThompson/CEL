/*io.c*/

//use `quoted( "----" )' to parse input for now

#include"cel.h"

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<assert.h>













void printstring( list L, FILE* stream )
{	while( L != NULL )
	{	fprintf( stream, "%c", L->left.ch );		
		L = cdr( L );
	}	
}



void printatom( box C, FILE* stream )
{	switch( C.type )
	{	case BOX_CH  : fprintf( stream, "%c", C.ch ); break;
		case BOX_DEC : fprintf( stream, "%i", C.z  ); break;
		case BOX_STR : printstring( C.ptr, stream ); break;
		default : break;
	}
}



void printlist( list L, FILE* stream )
{	switch( type( L ) )
	{	case SXPR_EMPTY   : break;
		
		case SXPR_COMPOUND: 
			fprintf( stream, "(" );
				printlist( car( L ), stream );
			fprintf( stream, (cdr(L) == NULL ? ")" : ") "));//Pretty-print			
			
			printlist( cdr( L ), stream );
		break;
		
		case SXPR_ATOMIC  : 
			printatom( L->left, stream );
				if( cdr( L ) != NULL ) //Pretty-print
					fprintf(stream, " ");
			printlist( cdr( L ), stream );
		break;
						
		case SXPR_TUPLE	  : 
			printatom( L->left, stream );
				fprintf(stream, " . ");
			printatom( L->right, stream);
		break;		
	}
} 

