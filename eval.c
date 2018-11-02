#include"cel.h"
#include<assert.h>




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
 


list eval(  list expr, list env )
{ if(null(expr))
    return expr;
  if(type(expr) == STRING )
    return assoc(expr,env);
  if(type(expr) == PAIR )
    return apply( eval(   car(expr), env),
  		  evlist( cdr(expr), env),
  		  env
  		  );
  return expr;
}



list apply( list op, list args, list env)
{ return op->operator.fp( args );
}

