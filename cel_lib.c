/*cel_lib.c*/
#include"cel.h"
#include<stdarg.h>
#include<assert.h>




list plus( list args )
{ assert( args != NULL && type(car(args)) == NUMBER && type(car(cdr(args))) == NUMBER );
  return num( car(args)->number + car(cdr(args))->number );
}


list cel_stdlib()
{  return psv(
     "((+ %) (foo 4) (bar 2) (quux 3))",
     op(plus, "+\\2")
   );
}

