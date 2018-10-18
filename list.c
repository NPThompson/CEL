#include"cel.h"
#include<string.h>





box str( const char* val )
{	return parsestr( val, strlen( val ));
}

box ch( char value )
{	box A;
		A.type	=	BOX_CH;
		A.ch 	=	value;
	return A;
}

box ptr( list L )
{	box A;
		A.type 	= BOX_PTR;
		A.ptr	= L;
	return A;
}

box z( int val )
{	box A;
		A.type 	= BOX_Z;
		A.z		= val;
	return A;
}

box nil()
{	box A;
		A.type 	= BOX_PTR;
		A.ptr   = NULL;
	return A;
}

list cons( box new_car, box new_cdr )
{	list L = (list)malloc(sizeof(pair));//list = pair*
		L->left = new_car;
		L->right = new_cdr;
	return L;
}








//list analysis

list car( list L )
{	if( type( L ) == SXPR_COMPOUND )
	{	return L->left.ptr;
	} else return NULL;
}

list cdr( list L )
{	if( type( L ) == SXPR_ATOMIC || type( L ) == SXPR_COMPOUND )
	{	return L->right.ptr;
	} else return NULL;
}

void freelist( list L )
{	switch( type( L ) )
	{	case SXPR_EMPTY   : break;
		
		case SXPR_ATOMIC  : 
			freelist( cdr( L ) );
			free( L );
		break;
		
		case SXPR_COMPOUND: 
			freelist( car( L ) );
			freelist( cdr( L ) );
			free( L );
		break;
		
		case SXPR_TUPLE	  : 
			free( L );
		break;		
	}
}









