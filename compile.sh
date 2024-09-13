#!/bin/bash

clear

ulimit -Sn 1048576 ; VAL=$( ulimit -Sn ) ; echo -e "MAX_FILENO: $VAL" 
LIST=( prxy ) ; Y="${#LIST[@]}" ; X=0

echo -e "\nKilling Services"
for item in "${LIST[@]}" ; do
    $( killall "$item" )
done

echo -e "\nCompiling Services"
for item in "${LIST[@]}" ; do

    tempfile=$(mktemp) ; (( X=$X+1 )) 

    if [ -f "$item" ] ; then 
       echo "-$item Compilled $X/$Y"
       continue 
    fi

    echo "-$item Compilling $X/$Y"

    if !( g++ -o $item ./Services/$item.cpp -I ./Modules -lssl -lcrypto -lz ) 2> "$tempfile"; then
         echo -e "\n" ; cat "$tempfile" >&2 ; exit
    fi

    rm "$tempfile"

done

echo -e "\nRunning Services"
for item in "${LIST[@]}" ; do
    ./"$item" & sleep 1s ;
done