#include "hash.h"
#include <stdlib.h>
void main(){
     int i = 20;
     hashtable h = hashtable_new(i);
     char *key="a";
     char *val="a";
     hashtable_put(h,key,val);
     hashtable_foreach(h);
}
