#! /bin/bash
f=$1
k=$2
touch out.txt
if [ "$k" = "-o" ]; then
    cat $f | ./graph > diag.txt
    dot -Tpng diag.txt -o DFA.png
fi
cat $f | ./main | tee out.txt | ./graph > diag.txt
dot -Tpng diag.txt -o minDFA.png
rm diag.txt
