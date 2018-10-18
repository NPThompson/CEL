#include"cel.h"

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<assert.h>





#define TOKEN_OPEN_PAREN	0x00
#define TOKEN_CLOSE_PAREN	0x01
#define TOKEN_IDENTIFIER	0x02
#define TOKEN_NUMBER		0x03
#define TOKEN_STRING		0x04








int balanceparens( const char* src )
{	int i = 0;
	int balance = 0;
	do{
		switch( src[i] )
		{	case '(' : balance++;
				break;
			case ')' : balance--;
				break;
			default: break;
		}
		i++;
	}while(src[i] != '\0');
	return balance == 0;
}



box parsestr( const char* src, int span )
{	box A;
	A.type  = BOX_STR;
	A.ptr   = NULL;
	
	//This loops backwards
	for( int i = span - 1; i >= 0; --i )
	{	A.ptr = cons( ch( src[i] ), ptr( A.ptr ));	
	}
	
	return A;	
}


int delimspan( const char* src )
{	if( *src == '\0' ) 
		return 0;
	if( *src == '(' || *src == ')' )
	{	return 1;
	}
	
	int ret = 0;
	
	while( src[ret] != '(' 
		&& src[ret] != ')' 
		&& src[ret] != ' ' 
		&& src[ret] != '\0' )
		{
			ret++;
		}
	return ret;
}



int skipspaces( const char* src )
{	int ret = 0;
	while( src[ret] == ' ' )
	{	ret++;
	}
	return ret;
}


//returns a linear list of tokens, separating on spaces and parenthesese
list tokenize( const char* src )
{	if( *src == '\0' ) return NULL;
	int span = delimspan( src );
	return cons( parsestr( src, span ), ptr( tokenize( src + span + skipspaces( src + span ) )));
}



int tokentype( list token )
{	if( eqstrch( token, "(" ) ){ return TOKEN_OPEN_PAREN;  }
	if( eqstrch( token, ")" ) ){ return TOKEN_CLOSE_PAREN; }
	return TOKEN_IDENTIFIER;
}



list matchparen( list token )
{	int balance = 0;
	do{
		if( token == NULL ) return NULL;
		
		switch( tokentype( token ))
		{	case TOKEN_OPEN_PAREN : balance++;
				break;
			case TOKEN_CLOSE_PAREN: balance--;
				if( balance == 0 ) return token;
				break;
			default : break;
		}
	token = cdr(token);
	}while(1);
}




//takes a token list and nests compound expressions
list parsetokens( list token )
{	if( token == NULL ) return NULL;

	list L, R;

	switch( tokentype( token ) )
	{	case TOKEN_OPEN_PAREN:
				L = parsetokens( cdr( token ));
				R = parsetokens( cdr( matchparen( token )));
			return cons( ptr( L ), ptr( R ));
	
		case TOKEN_CLOSE_PAREN:
			return NULL;
		
		default			:	/*case TOKEN_IDENTIFIER	:*/
			return cons( token->left, ptr( parsetokens( cdr ( token ))));
			break;
			
		// case TOKEN_STRING		:
			// break;
		
		// case TOKEN_NUMBER		:
			// break;
	}
	
}



list parse( const char* src )
{	assert( balanceparens( src ));
	list L = tokenize( src );
	list R = parsetokens( L );
	freelist( L );
	return R;
}



list parsefile( FILE* stream )
{	char buf[2048];
		fgets( buf, 2048, stream );
	return parse(buf);
}


