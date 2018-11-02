/*CEL REPL*/
#define DEBUG

#include"cel.h"
#include<assert.h>

void carandcdrtest( list input )
{   printf("\n");
    pr(input);
    printf("\ncar => ");
    pr(car(input));
    printf("\ncdr => ");
    pr(cdr(input));
}



int main( int argc, char** argv )
{ list lib = cel_stdlib();
  do{
    pr(eval(psf(stdin),lib));
  }while(1);
  
  return 0;
}
