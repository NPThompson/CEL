/*cel_lib.c*/
#include"celdebug.h"
#include"cel.h"
#include<stdarg.h>
#include<assert.h>



#define binop( CN, FD, OP ) CN( car(args)->FD OP car(cdr(args))->FD )
#define binargtest( FLAG, NAME) crashif( type(car(args)) != FLAG || type(car(cdr(args))) != FLAG, "%s", "wrong argument types for " #NAME)
#define arithfp( PRIMOP, SIG ) list SIG( list args ){ crashif( null(args), "%s", #SIG " undefined on nil"); binargtest( NUMBER, SIG ); return binop( num, number, PRIMOP ); }



arithfp( +, plus );
arithfp( /, divide );
arithfp( *, times);



list cel_stdlib()
{  list table = ht(psv(
     "((+ %) (* %) (/ %))",
     op(plus,   "+\\2"),
     op(times,  "*\\2"),
     op(divide, "/\\2")
		       ));
}

