#!/bin/bash

g++ -o main prog2.cpp;
filename="Wrap test answers.txt"

unset one
declare -i int 
int=0

#!for FILE in home/sharvilpr23/prog2/*.txt;
for i in {0..11};
do
	echo "Running test $i ...";
	./main < test$i.txt
done;
rm main;
