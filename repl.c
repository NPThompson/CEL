/*CEL REPL*/
#include"cel.h"


void carandcdrtest( list input )
{   printf("\n");
    printlist(input,stdout);
    printf("\ncar => ");
    printlist(car(input),stdout);
    printf("\ncdr => ");
    printlist(cdr(input),stdout);
}



int main( int argc, char** argv )
{ list global = cel_stdlib();

  list input;


  do{
    input = eval(parsefile(stdin),global);
    printlist(input,stdout);
  }while(1);
 
  

  return 0;
}
