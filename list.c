#include"cel.h"
#include<string.h>
#include<assert.h>




list cons( list lhs, list rhs)
{  list l = (list)malloc(sizeof(atom));
    l->type = PAIR;
    l->pair.car = lhs;
    l->pair.cdr = rhs;
  return l;
}



list car(list L)
{  if(L != NULL && !atomic(L))
     return L->pair.car;
  else return NULL;
}



list cdr(list L)
{  if(L != NULL && !atomic(L))
    return L->pair.cdr;
  else return NULL;
}



char* copystr( const char* src, unsigned int sz )
{ char*  str = (char*)malloc(sizeof(sz));

  for(int i = 0; i < sz; ++i )
    { str[i] = src[i];
    }
  return str;
}



list str(const char* cstr)
{  list l = (list)malloc(sizeof(atom));
  l->type = STRING;
  l->string = copystr( cstr, strlen(cstr)+1 );
  return l;
}



list num(double val)
{  list l = (list)malloc(sizeof(atom));
  l->type = NUMBER;
  l->number = val;
  return l;
}



list op(list(*f)(list))
{  list l = (list)malloc(sizeof(atom));
  l->type = OPERATOR;
  l->operator = f;
  return l;
}



int type( list L )
{  return L->type;
}



int form( list l )
{ if( l == NULL ){
    return NIL;
  }
  if( atomic(l)){
    return ATOM;
  }
  if( atomic(car(l)) && atomic(cdr(l)) ){
    return TUPLE;
  }
  if( atomic(car(l)) ){
    return LIST;
  }
  else return COMPOUND;
}



int atomic( list L )
{ return ( L != NULL ) && ( type(L) != PAIR );
}



int _eqstring( char* s1, char* s2 )
{ int len = strlen(s1);
  if(len != strlen(s2)) return 0;
  for(int i = 0; i < len; ++i )
    { if(s1[i] != s2[i]) return 0;
    }
  return 1;
}



int eqatom(list l1, list l2)
{ if( type(l1) != type(l2))       return 0;
  switch(type(l1))
    {case NUMBER : return l1->number == l2->number;
    case STRING : return _eqstring(l1->string, l2->string );
    default : break;
    }
 return l1 == l2;//pointer comparison
}



int eqlist( list l1, list l2 )
{  if(atomic(l1) && atomic(l2)) return eqatom(l1,l2);
  else return eqlist(car(l1),car(l2)) && eqlist(cdr(l1), cdr(l2));
}



void freelist(list l)
{
}
