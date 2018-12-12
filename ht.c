#include<stdio.h>
#include"cel.h"







unsigned int hashgen( const char* src )
{ unsigned int hash = 1;
  for( int i = 0; i < strlen(src); ++i )
    { hash = hash + src[i];
    }
  return hash % HASH_SIZE;
}



//insert
void _ins( list table, list k, list val )
{ if(type(k) != STRING)
    errv("Cannot insert %l, key %l has wrong type %t",
         val,
	 k,
	 type(k));
  if(type(table) != HASH)
    errv("Cannot insert %l into a non-hashtable (type %t)",
	 val,
	 type(table));

  list* hash = (table->array.records + hashgen( k->string ));

  while( !null(*hash) )
    { *hash = cdr(*hash);
    }
    *hash = cons( cons( k, val), NULL);
    
}


list ht( list recs )
{ list table = (list)malloc(sizeof(atom));
  table->type = HASH;
  table->array.records = (list*)malloc( HASH_SIZE * sizeof(list));

  for(int i = 0; i < HASH_SIZE; ++i )
    { table->array.records[i] = NULL;
    }
  
  while( !null(recs) )
    { _ins( table, caar(recs), cadar(recs));
      recs = cdr(recs);
    }
  
  return table;
}






void ins( list table, const char* k, list val )
{ return _ins(table, str(k), val);
}




list _assoc( list record, const char* _key )
{ list key = str( _key );
  while( !null(record) )
    { if( eq(caar(record), key ) )
    { return cdar( record );
    }
    record = cdr( record );
  }
  return NULL;
}


//index
list ix( list table, const char* key )
{ if(type(table) != HASH)
    errv("Attempt to index %l, which is a %t, not a hash-table",
	 table,
	 type(table));
  list result = _assoc( table->array.records[ hashgen( key ) ], key );

  if(null(result)){
    fprintf(stderr, "%s", key);
    errv(" has no matching value in the table");
  }
  return result;
}
	 
