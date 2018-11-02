/*CEL REPL*/
#define DEBUG

#include"cel.h"
#include<assert.h>




int main( int argc, char** argv )
{ list lib = cel_stdlib();
  do{
    pr(eval(psf(stdin),lib));
  }while(1);
  
  return 0;
}
