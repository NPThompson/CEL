/*cel_lib.c*/
#include"cel.h"





list cel_stdlib()
{	return parse(
        "(var somevariablevalue) (var2 someothervalue)"
        );
}
