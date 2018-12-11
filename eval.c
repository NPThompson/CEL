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
#define CEL_DEFINE 0x08




list apply(list,list,list,list);
list evlist(list,list,list);


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
	  if( eq( car(expr), str("def")))
	    return CEL_DEFINE;
	}
      return CEL_APPLY;
    }
  return CEL_UNDEF;
}




list evlist( list expr, list local, list global )
{ if( null(expr) || atomic(expr) )
    return expr;
  else return
	 cons( eval(   car( expr ), local, global),
	       evlist( cdr( expr ), local, global)
	       );
}



list assoc( list key, list table )
{ if( null( table ))
    return NULL;
  if( eq(key, caar(table)))
    return cadar(table);
  else return assoc(key,cdr(table));
}


//env is a pointer to a pointer to an atom, so that def can extend it
list eval(  list expr, list local, list global )
{ switch( form( expr ))
    {
    case CEL_NIL:
      return expr;
    case CEL_ATOM:
      return expr;
    case CEL_SYMBOL:
      if( null(assoc(expr,local)))
	return ix( global, expr->string );
      else return assoc(expr,local);
    case CEL_QUOTE:
      return cdr( expr );
    case CEL_LAMBDA:
      return fn( cadr(expr), caddr(expr), global );
    case CEL_APPLY:
      return apply( eval(   car(expr), local, global),
  		    evlist( cdr(expr), local, global),
                    local,
		    global
  		  );
    case CEL_DEFINE:
      ins( global, cadr(expr)->string, eval( caddr(expr), local, global ));
      return cadr(expr);
      
    default:
      errv("cannot evaluate %l",
	   expr);
    }
}



list apply( list op, list args, list local, list global)
{ if( type(op) == OPERATOR )
    return op->operator.fp( args );
//two appends: arguments first priority, then original environment, then current environment
  if( type(op) == LAMBDA )
    return eval( op->lambda.body,
                 append( zip( op->lambda.params, args ), local ),//append newly substituted arguments to local arguments
                 global );
		
  errv("cannot apply %l: Expected an OPERATOR or LAMBDA, got %t",
       op,
       type(op));
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
