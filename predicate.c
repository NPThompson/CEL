/*predicate.c*/
#include"cel.h"







int eqtype( box C1, box C2 )
{	return C1.type == C2.type;
}	



int eqstring( list str1, list str2 )
{	if( str1->left.type == BOX_STR && str2->left.type == BOX_STR )
	return eqlist( str1->left.ptr, str2->left.ptr );
	else return 0;
}



int eqstrch( list str1, const char* str2 )
{	list strlist = cons( str( str2 ), nil() );
	int result = eqstring( str1, strlist );
	freelist( strlist );
	return result;
}



int eqbox( box C1, box C2 )
{	if( !eqtype( C1, C2 ) ){ return 0; }
	if( C1.type == BOX_PTR || C1.type == BOX_STR )
	{	return eqlist( C1.ptr, C2.ptr );
	}
	switch( C1.type )
	{	case BOX_Z   : return C1.z 		== C2.z;
		case BOX_DEC : return C1.dec 	== C2.dec;
		case BOX_CH  : return C1.ch 	== C2.ch;
	}
	return 0;//Bizarre failure case
}



int eqlist( list L1, list L2 )
{	if( L1 == NULL || L2 == NULL ) return L1 == L2;	
	return eqbox( L1->left, L2->left ) && eqbox( L1->right, L2->right );
}



