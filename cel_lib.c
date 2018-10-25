/*cel_lib.c*/
#include"cel.h"
#include<stdarg.h>




list plus( list args )
{ return num( car(args)->number + car(cdr(args))->number );
}


list cel_stdlib()
{  return parsef(
     "(+ %) (bar 2) (quux 3)",
     op(plus)
   );
}

