#include"cel.h"
#include<assert.h>


list assoc(list key, list table)
{ while( table != NULL )
    { if(eqatom(key,(car(car(table))))) return car(cdr(car(table)));
      else table = cdr(table);
    }
  return NULL;
}



list evlist( list expr, list env )
{ if(expr == NULL) return NULL;
  else return cons(eval(car(expr),env), evlist(cdr(expr),env));
}



list eval(  list expr, list env )
{ if(expr == NULL) return expr;
  if(atomic(expr)){
    list l = assoc(expr,env);
    if(l == NULL) return expr;
    else return l;
  }
  else return cons(eval(car(expr),env), evlist(cdr(expr), env));
}


list apply( list op, list args, list env)
{ if(atomic(op))
    { return op->operator(args);
    }
  else return NULL;
 }

