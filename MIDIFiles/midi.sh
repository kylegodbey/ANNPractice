!#/bin/bash

a=1
b=0

for i in *.mid; do

 # new=$(printf "%0d.mid" ${a})
 
 ./midicsv ${i} ~${b}
 #let a=a+1 
 let b=b+1

done