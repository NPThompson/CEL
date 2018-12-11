/*cel_lib.c*/
#include"celdebug.h"
#include"cel.h"
#include<stdarg.h>
#include<assert.h>



#define binop( CN, FD, OP ) CN( car(args)->FD OP car(cdr(args))->FD )

#define binargtest( FLAG, NAME) do{\
    if(type(car(args)) != FLAG) errv("Cannot compute (" #NAME "%l %l), first argument has wrong type %t", car(args), car(cdr(args)), type(car(args)));\
    if(type(car(cdr(args))) != FLAG) errv("Cannot compute (" #NAME "%l %l), second argument has wrong type %t", car(args), car(cdr(args)), type(car(cdr(args)))); \
}while(0);

#define arithfp( PRIMOP, SIG )\
list SIG( list args ){ \
  if(null(args)) errv( #SIG "undefined on nil");\
  binargtest( NUMBER, SIG );\
  return binop( num, number, PRIMOP );\
}



arithfp( +, plus  );
arithfp( /, divide);
arithfp( *, times );
arithfp( -, minus );

list ls( list args ){ return args; }

//car not behaving as it should
list fixcar( list args ){ return caar( args ); }
list fixcdr( list args ){ return cdar( args ); }

list cel_corelib()
{  list table = ht(psv(
     "((+ %) (* %) (/ %) (- %) (car %) (cdr %) (ls %))",
     op(plus,   "+\\2"),
     op(times,  "*\\2"),
     op(divide, "/\\2"),
     op(minus,  "-\\2"),
     op(fixcar,    "car\\1"),
     op(fixcdr,    "cdr\\1"),
     op(ls,     "ls\\n")
     
   ));
}

