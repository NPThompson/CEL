#include"cel.h"
#include<assert.h>






//the various forms of CEL's expressions are enumerated here
#define FORM_APPLY       0x00
#define FORM_ATOM        0x01
#define FORM_SYMBOL      0x02
#define FORM_QUOTED      0x03
#define FORM_UNDEF       0x04


int form( list expr )
{    switch( type( expr ))
     {    case SXPR_COMPOUND : return FORM_APPLY;
          case SXPR_ATOMIC   : if( expr->left.type == BOX_STR ) return FORM_SYMBOL; else return FORM_ATOM;
          case SXPR_TUPLE    : return FORM_ATOM;
          default: return FORM_UNDEF;
     }
}











int type( list xpr )
{	if( xpr == NULL ) 
		return SXPR_EMPTY;
	if( xpr->left.type == BOX_PTR && xpr->right.type == BOX_PTR ) 
		return SXPR_COMPOUND;
	if( xpr->left.type != BOX_PTR && xpr->right.type == BOX_PTR )
		return SXPR_ATOMIC;
	return SXPR_TUPLE;//Only remaining possibility is left & right = atomic, => xpr = tuple
}



list lookup( list key, list table )
{	do{
		if( eqbox( car(table)->left, key->left ) ) return cdr( car ( table ));
		table = cdr( table );
	} while( table != NULL );

	return NULL;
}



list evlist( list expr, list env )
{	return NULL;
}



list eval(  list expr, list env )
{    switch( form( expr ))
     {    case FORM_APPLY       : return expr;
          case FORM_QUOTED      : return expr;
          case FORM_ATOM        : return expr;
          case FORM_SYMBOL      : return lookup( expr, env );
          default : printf( "could not determine the form of the expression" ); assert(0); 
     }
}



list apply( list op, list args, list env)
{	return NULL;
}
