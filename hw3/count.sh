#!/bin/sh

for i in {0..9}
do
    echo -n "$i"
    echo -n " "
    echo `ls | grep "^$i" | wc -l`
done
