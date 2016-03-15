#include <stdio.h>
#include <stdlib.h>
typedef struct hashnode_struct{
   struct hashnode_struct *next;
   const char *key;
   void *val;
}*hashnode,_hashnode;

typedef struct hashtable_struct{
   int size;
   int count;
   struct hashnode_struct *z;
}*hashtable,_hashtable;

void hashtable_put(hashtable h,const char *key,void *val);

void *hashtable_get(hashtable h,const char *key);

void hashtable_free(hashtable h);

void hashtable_delete_node(hashtable h,const char *key);

void hashtable_foreach(hashtable h);

hashtable hashtable_new(int size);
