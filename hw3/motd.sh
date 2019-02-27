#!/bin/sh
# print message x number of times
# ./motd.sh [String] [number]

printBorder()
{
    i="0"
    let "size = $1+4"
    while [ $i -lt $size ]
    do
        echo -n "*"
        i=$[$i+1]
    done
}

if [ -z "$1" ]; then
    echo "Please enter a message"
    exit
fi

if [ -z "$2" ]; then
    echo "how many times do you want to print?"
    exit
fi

message=$1
number=$2

# build border for top/bottom
mleen=$(echo -n $message | wc -c)
border=`printBorder $mleen`

echo "$border"
# loop output
i="0"
while [ $i -lt $number ]
do
    echo "* $message *"
    i=$[$i+1]
done
echo "$border"
