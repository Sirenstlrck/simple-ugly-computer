#!/usr/bin/sh

root=$(dirname $0)/..

# such a shame
cd ${root}
objs=$(find . -name "*.o" -not -path "./tests/*" -not -name "*main*")
tests=$(find ./tests/ -name "*.c")

echo ================================================
for test in ${tests}
do
    gcc -I./include/ ${test} ${objs} -o ${test}.out
    echo ${test}.out
    ${test}.out
    echo
done
