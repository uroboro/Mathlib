#!/bin/sh
# for each header file in ./Classes, it searches for function declarations.

function_list() {
for i in `ls Classes/ | grep [.]h`; do
#	echo Classes/$i
	cat Classes/$i | grep ");"
done
}

echo ptr:
ptr=`function_list | grep ptr`
echo -e "$ptr"
echo mtx:
mtx=`function_list | grep mtx`
echo -e "$mtx"
echo mn:
mn=`function_list | grep mn`
echo -e "$mn"
echo mf:
mf=`function_list | grep mf`
echo -e "$mf"
