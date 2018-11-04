#include"cel.h"
#include<assert.h>



//eval case enumeration
#define CEL_QUOTE  0x00
#define CEL_APPLY  0x01
#define CEL_ATOM   0x02
#define CEL_SYMBOL 0x03
#define CEL_COND   0x04
#define CEL_LAMBDA 0x07
#define CEL_NIL    0x05
#define CEL_UNDEF  0x06

//Lambda accessors
#define FN_EXP( _op ) car(cdr(cdr( _op )))
#define FN_PAR( _op ) car(cdr( _op ))
#define FN_ENV( _op ) cdr(cdr(cdr( _op )))




int form( list expr )
{ if( null( expr ))
    return CEL_NIL;
  if( atomic( expr ) && type( expr ) != STRING )
    return CEL_ATOM;
  if( type( expr ) == STRING )
    return CEL_SYMBOL;
  if( !atomic( expr ) )
    { if( type(car(expr)) == STRING )
	{if( eq( car(expr), str( "'")))
	   return CEL_QUOTE;
	  if( eq( car(expr), str( "fn")))
	    return CEL_LAMBDA;
	}
      return CEL_APPLY;
    }
  return CEL_UNDEF;
}




#define GETKEY( x ) car(car(x))
#define GETVAL( x ) car(cdr(car(x)))




list assoc(list key, list table)
{ while( table != NULL )
    { if(eq(key, GETKEY(table)))
	return GETVAL(table);
      else table = cdr(table);
    }
  return NULL;
}



list evlist( list expr, list env )
{ if( null(expr) || atomic(expr) )
    return expr;
  else return
	 cons( eval(   car( expr ), env),
	       evlist( cdr( expr ), env)
	       );
}
 

//env is a pointer to a pointer to an atom, so that def can extend it
list eval(  list expr, list env )
{ switch( form( expr ))
    {
    case CEL_NIL :
	return expr;
    case CEL_ATOM :
        return expr;
    case CEL_SYMBOL :
      return assoc( expr, env );
    case CEL_QUOTE :
      return cdr( expr );
    case CEL_LAMBDA :
      return fn(car(cdr(expr)),car(cdr(cdr(expr))), env);
    case CEL_APPLY :
      return apply( eval(   car(expr), env),
  		    evlist( cdr(expr), env),
  		    env
  		  );
    default:
      crashif(1,"could not evaluate the expression");
    }
}



list apply( list op, list args, list env)
{ if( type(op) == OPERATOR )
    return op->operator.fp( args );
//two appends: arguments first priority, then original environment, then current environment
  if( !atomic( op ) && !atomic( car( op )) && eq( cdr(car( op )), str( "fn")) )
    return eval( FN_EXP( op ), append( zip( FN_PAR( op ), args), append( FN_ENV( op ), env )));
  crashif(1, "operator is not a primitive or a compound operation");
}

#undef FN_EXP
#undef FN_ENV
#undef FN_PAR

#undef CEL_APPLY
#undef CEL_QUOTE
#undef CEL_COND
#undef CEL_LAMBDA
#undef CEL_ATOM
#undef CEL_NIL
