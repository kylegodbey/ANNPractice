!#/bin/bash

a=1
for i in *.mid; do
    new=$(printf "%02d.mid" ${a})
    mv ${i} ${new}
    let a=a+1
done