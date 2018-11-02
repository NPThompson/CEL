/*CEL REPL*/
#define DEBUG

#include"cel.h"
#include<assert.h>




int main( int argc, char** argv )
{ list lib = cel_stdlib();
  list np;

  do{
    np = psf(stdin);
    printf("=> ");
    pr( eval(np,lib) );
    printf("\n");
  }while(1);
  
  return 0;
}
