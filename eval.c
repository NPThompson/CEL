#include"cel.h"
#include<assert.h>


list assoc(list key, list table)
{ while( table != NULL )
    { if(eqatom(key,(car(car(table)))))
      return car(cdr(car(table)));
      else table = cdr(table);
    }
  return NULL;
}



list evlist( list expr, list env )
{ if(expr == NULL) return NULL;
  return cons(eval(car(expr),env), evlist(cdr(expr),env));
}



list eval(  list expr, list env )
{ if( expr == NULL || expr->type == NUMBER || expr->type == OPERATOR ) return expr;
  if( atomic(expr) ) return assoc(expr,env);
  else return apply(eval(car(expr),env), evlist(cdr(expr),env),env);
}



list apply( list op, list args, list env)
{  return op->operator( args );
}

