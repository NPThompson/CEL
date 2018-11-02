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

  if( !atomic(expr) && type(car(expr)) != PAIR && eq(car(expr), str("fn")) )//Make a lambda
    { return fn( car(cdr(expr)), car(cdr(cdr(expr))), env);
    }
 
  if(type(expr) == PAIR )
    return apply( eval(   car(expr), env),
  		  evlist( cdr(expr), env),
  		  env
  		  );
  
  if( type(expr) == NUMBER ) return expr;

  crashif(1,"expression cannot be evaluated");
}



list apply( list op, list args, list env)
{ if( type(op) == OPERATOR )
    return op->operator.fp( args );
//two appends: arguments first priority, then original environment, then current environment
  if( type(op) == LAMBDA )
    return eval( op->lambda.body, append( zip(op->lambda.params, args), append( op->lambda.env, env )));
  crashif(1, "operator is not a primitive or a compound operation");
}

