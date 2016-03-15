#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

void hashtable_put(hashtable h,const char *key,void *val){
   if( h == NULL || key == NULL ){
	return;
   }
   hashnode node = malloc(sizeof(hashnode));
   node->key=key;  
   node->val=val;
   if( h->z == NULL ){
      h->z=node;
   }else{
      hashnode last_node = h->z;
      do{
	  if( last_node->next == NULL ){
              last_node->next=node;
	      break;
          }else{
 	      last_node = last_node->next;
          }
      }while(1);
   }
}

hashtable hashtable_new(int size){
    hashtable h = malloc(sizeof(hashtable));
    h->size=size;
    h->count=10;
    return h;
}

void hashtable_foreach(hashtable h){
    if( h == NULL || h->z == NULL ){
	return;
    }
    hashnode node = h->z;
    do{
	printf("%s=>%s\n",node->key,node->val);
        if( node->next == NULL ){
	   return;
        }else{
            node = node->next;
        }
    }while(1);
}

void hashtable_delete_node(hashtable h,const char *key){
   if( h == NULL || key == NULL || h->z == NULL ){
       return;
   }
   hashnode node = h->z;
   if( node->key == key ){
       if( node->next != NULL ){
	   h->z = node->next;
       }else{
	   h->z = NULL;
       }
       free(node);
       return ;
   }

   hashnode last_node = node;
   node = node->next;

   do{
       if( node->key == key ){
	  last_node->next = node->next;
          free(node);
          return ;
       }else{
	  last_node = node;
          if( node->next == NULL ){
	     return ;
          }else{
	     node = node->next;
          }
       }
   }while(1);

}

void *hashtable_get(hashtable h,const char *key){
   if(h == NULL || key == NULL || h->z == NULL){
	return NULL;
   }
   hashnode node = h->z;
   do{
	if( node->key == key ){
	    return node->val;
        }else{
	    if( node->next == NULL ){
		return NULL;
            }else{
		node = node->next;
	    }
        }
   }while(1);
}

void hashtable_free(hashtable h){
   if( h == NULL ){
	return ;
   }
   if( h->z == NULL ){
	free(h);
   }
   hashnode node = h->z;
   hashnode next_node = h->z;
   do{
      if( node->next != NULL ){
	  next_node = node->next;
	  free(node);
          node = next_node;
      }else{
         free(node);
	 return;
      }
 
   }while(1);
}

