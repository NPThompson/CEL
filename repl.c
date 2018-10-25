/*CEL REPL*/
#include"cel.h"




int main( int argc, char** argv )
{ list global = cel_stdlib();

  //testing primitive operators
  /* list sum = assoc(str("+"),global)->operator(cons(num(1),cons(num(2),NULL))); */

  /* list sum2 = apply(assoc(str("+"),global), parse("3 1 2"), global); */
  
  /* printlist(sum,stdout); */
  /* printf("\n"); */
  /* printlist(sum2,stdout); */
  
  do{
    printlist(eval(parsefile(stdin),global),stdout);
    printf("\n");
  }while(1 );

  return 0;
}
