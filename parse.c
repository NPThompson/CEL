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



list parsestr( const char* src, unsigned int span )
{   char* c = copystr(src, span);
     return str(c);	
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
	        && src[ret] != '\n'
	        && src[ret] != '\t'

	       
	        && src[ret] != '\0' )
		{
			ret++;
		}
	return ret;
}



int skipspaces( const char* src )
{	int ret = 0;
	while( src[ret] == ' ' || src[ret] == '\n' || src[ret] == '\t' )
	{	ret++;
	}
	return ret;
}


//returns a linear list of tokens, separating on spaces and parenthesese
list tokenize( const char* src )
{	if( *src == '\0' ) return NULL;
	int span = delimspan( src );
	return cons( parsestr( src, span ), tokenize( src + span + skipspaces( src + span )));
}



int tokentype( list token )
{ if( eqatom(token, str("("))){ return TOKEN_OPEN_PAREN;  }
  if( eqatom(token, str(")"))){ return TOKEN_CLOSE_PAREN; }
  return TOKEN_IDENTIFIER;
}



list matchparen( list token )
{ int balance = 0;
  while(token != NULL ){
    switch( tokentype(car( token )))
    {	case TOKEN_OPEN_PAREN : balance++;
	  break;
        case TOKEN_CLOSE_PAREN: balance--;
	  if( balance == 0 ) return token;
	default : break;
    }
    token = cdr(token);
  }
  return NULL;
}



list horner( list token )
{ int sum = 0;
  for(int i = 0; i < strlen(token->string); ++i )
    { sum = (sum * 10) + ((token->string[i]) - '0');
    }
  return num(sum);
}



list parseliteral( list token )
{  if(isdigit(token->string[0]))
    { return horner(token);
    } else return token;
}


//takes a token list and nests compound expressions
list parsetokens( list token )
{ list l,r;
  if(token == NULL) return NULL;
  switch( tokentype( car(token) ) )
    {  case TOKEN_OPEN_PAREN :
	r = parsetokens(cdr( matchparen(token)));
	l = parsetokens(cdr(token));
	return cons(l,car(r));

       case TOKEN_CLOSE_PAREN: return NULL;

    default: return cons(parseliteral(car(token)), parsetokens(cdr(token)));
    }
}



list parse( const char* src )
{   assert( balanceparens( src ));
    list tokens = tokenize( src );
    list exprs = parsetokens( tokens );
    return car(exprs);
}



list parsefile( FILE* stream )
{ char buf[2048];
  fgets( buf, 2048, stream );
  return parse(buf);
}


list parsef(const char* src, ...)
{ va_list values;
  va_start(values, src);
  
  list tokens = tokenize(src);

  list cur = tokens;
  do{
    if(eqatom(car(cur),str("%")))
      {*car(cur) = *va_arg(values, list);
      }
    cur = cdr(cur);
  }while(cur != NULL );

  list parsed = parsetokens( tokens );
  //  freelist( tokens );
  return parsed;
}


