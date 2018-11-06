#include"cel.h"

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<assert.h>








list str1( const char* src, unsigned int span )
{   char* c = copystr(src, span);
     return str(c);	
}



list horner( const char* src, int span )
{ int sum = 0;
  for(int i = 0; i < span; ++i )
    { sum = (sum * 10) + (src[i] - '0');
    }
  return num( sum );
}



list atomicliteral( const char* src, int span )
{  if(isdigit(src[0]))
    { return horner(src,span);
    } else return str1(src,span);
}




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



int delimspan( const char* src )
{	if( *src == '\0' ) 
		return 0;
	if( *src == '(' || *src == ')' || *src == '\'' )
	{	return 1;
	}
	
	int ret = 0;
	
	while( src[ret] != '(' 
		&& src[ret] != ')'
	        && src[ret] != '\''
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
	return cons( atomicliteral( src, span ), tokenize( src + span + skipspaces( src + span )));
}



int oparen( list token )
{ return eq(token, str("("));
}



int cparen( list token )
{ return eq(token, str(")"));
}



list matchparen( list token )
{ int balance = 0;

  while( !null(token) )
    { if( oparen( car( token )))
	balance++;
      if( cparen( car( token )))
	{ balance--;
	  if( balance == 0 )
	    return token;
	}
      token = cdr( token );
    }
  
  crashif( 1, "%s", "could not match parens in token list");
}



list nestexprs( list ls )
{ if(null(ls)) return NULL;
  if( oparen( car(ls) ))
    return cons( nestexprs( cdr(ls)),
		 nestexprs( cdr(matchparen(ls)))
		 );
  if( cparen( car(ls) ))
    return NULL;

  return cons( car( ls ), nestexprs( cdr(ls) ));
}



void scan( const char* src )
{ crashif( !balanceparens( src ), "%s", "source code must have balanced parenthesese");
}



list ps( const char* src )
{ scan( src );
  list tokens = tokenize(src);
  if(atomic(tokens))
    return tokens;
  else return car(nestexprs( tokens ));//For some reason nestexprs leaves a redundant cons in front
}



list psf( FILE* stream )
{ char buf[2048];
  fgets( buf, 2048, stream );
  return ps(buf);
}


list psv(const char* src, ...)
{ va_list values;
  va_start(values, src);
  
  list tokens = tokenize(src);

  list cur = tokens;
  do{
    if(eq(car(cur),str("%")))
      {*car(cur) = *va_arg(values, list);
      }
    cur = cdr(cur);
  }while(cur != NULL );

  return car(nestexprs( tokens ));//For some reason nestexprs leaves a redundant cons in front
}


