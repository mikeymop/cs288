#!/bin/bash

getDate() {
    echo `date +'%Y-%m-%d-%H-%M-%S'`
}

doStuff() {
    fname=`getDate`.html
    sname=`getDate`.xhtml
    echo "Downloading ${fname}"
    `wget ${url} -O ${fname} &> /dev/null`
    if [ ! -f "tagsoup-1.2.1.jar" ]
    then
        echo "Getting tagsoup..."
        `wget http://vrici.lojban.org/~cowan/XML/tagsoup/tagsoup-1.2.1.jar &> /dev/null`
    fi
    `java -jar tagsoup-1.2.1.jar --files ${fname} &> /dev/null`
    `rm ${fname}`
    echo "Writing data to .csv"
    `python3 parseHTML.py ${sname}`
    `rm ${sname}`
}

url="http://wsj.com/mdc/public/page/2_3021-activnnm-actives.html"

i=1
while [ $i -le 60 ]
do
    doStuff
    i=$(( $i + 1 ))
    echo "I'll check again in a minute..."
    sleep 1m
done
