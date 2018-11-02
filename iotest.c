#include"cel.h"
#include<stdio.h>
#include<stdlib.h>


void test( int(*fp)(void), const char* testname)
{ printf( "%s: %s\n", testname, (fp() ? "OK" : "FAIL"));
}


	   
int parse_equals_print()
{  FILE* fp = fopen( "testfile", "rw" );
  fprintf(fp, "Hello, world!");

  char buf[256];
  fscanf(fp, "%s", buf );

  printf("hw");
  
  fprintf(fp, "Goodbeye!");

  printf("%s", buf );
  
  /* list list1 = parsefile( fp ); */

  /* pr( list1, fp ); */

  /* list list2 = parsefile( fp ); */

  /* return eq( list1, list2 ); */
  
}




int main(int argc, char** argv )
{ //test(parse_equals_print, "parse == print");
  parse_equals_print();

}
