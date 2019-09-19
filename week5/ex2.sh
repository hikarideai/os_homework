#!/bin/bash

while true
do
    tail -1 "file" > num
    num=$((num+1))
    echo $num >> file
done
