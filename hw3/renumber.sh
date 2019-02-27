#!/bin/sh
# sequentially rename all files in a directory
# ./rename.sh [FILES] [EXTENSION]
# printf idea from:
# https://ubuntuforums.org/showthread.php?t=926752
mkFileName() 
{
    filename=$1
    newfilenum=$(printf "%03d" $2)
    newfilename="$1$newfilenum$3"
    echo $newfilename
}

if [ -z "$1" ]; then
    echo "Please enter a filename"
    exit
    fi
if [ -z "$2" ]; then
    echo "Please enter a file extension"
    exit
    fi

fname=$1
fext=$2

# iteratea across all files in pwd
let "n = 1"
for i in `ls`
do
    newfn=`mkFileName $fname $n`
    # if file exists
    if [ -f "$newfn.$2" ]; then
        echo "$newfn taken, skipping"
        (( n += 1 ))
        newfn=`mkFileName $fname $n`
        mv $i "$newfn.$2"
        continue
    else
        mv $i "$newfn.$2"
        echo "mv to $newfn"
        (( n += 1 ))
        continue
    fi
done
