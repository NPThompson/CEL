#include"cel.h"
#include<string.h>
#include<assert.h>




list cons( list lhs, list rhs)
{  list l = makels();
    l->type = PAIR;
    l->pair.car = lhs;
    l->pair.cdr = rhs;
  return l;
}

 

list car(list L)
{ crashif( (null(L) || atomic(L)), (null(L) ? "car( nil ) undefined" : "car( <atom> ) undefined"));
  return L->pair.car;
}



list cdr(list L)
{ crashif( (null(L) || atomic(L)), (null(L) ? "cdr( nil ) undefined" : "cdr( <atom> ) undefined"));
  return L->pair.cdr;
}



list append( list l0, list l1 )
{ if( null( l0 ))
    return l1;
  else return cons( car(l0), append( cdr(l0), l1));
}



list zip( list l0, list l1 )
{ if( null(l0) || null(l1) )
    return NULL;
  else return cons( cons(car(l0), cons(car(l1), NULL)), zip( cdr(l0), cdr(l1)));
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



list op(list(*f)(list), const char* printname)
{  list l = (list)malloc(sizeof(atom));
  l->type = OPERATOR;
  l->operator.fp = f;
  l->operator.name = printname;
  return l;
}



list fn(list _params, list _body, list _env )
{ return cons( cons( str("'"), str("fn")),
	       cons( _params, cons( _body, cons( _env, NULL))));
}



int type( list L )
{  return L->type;
}



int atomic( list l )
{ return ( !null(l) && type(l) != PAIR );
}



int _eqstring( char* s1, char* s2 )
{ int len = strlen(s1);
  if(len != strlen(s2)) return 0;
  for(int i = 0; i < len; ++i )
    { if(s1[i] != s2[i]) return 0;
    }
  return 1;
}



int _eqatom(list l1, list l2)
{ if( type(l1) != type(l2))       return 0;
  switch(type(l1))
    {case NUMBER : return l1->number == l2->number;
    case STRING : return _eqstring(l1->string, l2->string );
    default : break;
    }
 return l1 == l2;//pointer comparison
}



int eq( list e0, list e1 )
{  if(atomic(e0) && atomic(e1)) return _eqatom(e0,e1);
  else return eq(car(e0),car(e1)) && eq(cdr(e0), cdr(e1));
}



int null( list exp )
{ return exp == NULL;
}



list map( list ls, list(*fn)(list) )
{ if( null( ls ))
    return NULL;
  else return cons( fn(car(ls)), fn(cdr(ls)) );
}
