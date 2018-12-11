/*CEL REPL*/
#define DEBUG

#include"cel.h"
#include<assert.h>




int main( int argc, char** argv )
{ list lib = cel_corelib();
  list np;
    
  do{
    printf("\n  ");
    np = psf(stdin);
    printf("=> ");
    pr( eval(np, NULL, lib) );
  }while(1);
  
  return 0;
}
