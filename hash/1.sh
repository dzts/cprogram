#!/bin/sh
gcc hash.c
./a.out
read -p "click y to edit hash.c?" sure
if [ "$sure"a == "ya" ];then
  vim hash.c
fi
