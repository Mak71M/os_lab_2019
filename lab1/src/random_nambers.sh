#!/bin/bash 
filename="numbers.txt"
exec 3<> "$filename" 
for ((i=1; i<=150; i++))
do 
	number=$(od -An -N2 -i /dev/random | awk '{print $1}')
	echo "$number" >&3 
done 
exec 3>&-