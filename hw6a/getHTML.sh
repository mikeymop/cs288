#!/bin/bash

url="http://wsj.com/mdc/public/page/2_3021-activnnm-actives.html"

getDate() {
    echo `date +'%Y-%m-%d-%h-%m-%S'`
}

fname=`getDate`.html
echo $fname

echo "Downloading ${fname}"
`wget ${url} -O ${fname}`

`java -jar tagsoup-1.2.1.jar --files ${fname}`
