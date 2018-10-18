/*CEL REPL*/
#include"cel.h"



int main( int argc, char** argv )
{   list global = cel_stdlib();
    printlist( lookup(parse("var"), global), stdout);	
    printf("\n");
    printlist( lookup(parse("var2"), global), stdout );
    list result;
	
    do{
        result = parsefile( stdin );
	printlist( eval( result, global ), stdout); 
    }while( type( result ) != SXPR_EMPTY );
	
    freelist(result);
		
    return 0;
}
