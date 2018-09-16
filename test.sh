#! /bin/bash
bash compile.sh
for d in $(ls tests); do
    touch tests/$d/out.txt
    cat tests/$d/in.txt | ./graph > diag.txt
    dot -Tpng diag.txt -o tests/$d/DFA.png
    cat tests/$d/in.txt | ./main | tee tests/$d/out.txt | ./graph > diag.txt
    dot -Tpng diag.txt -o tests/$d/minDFA.png
done
rm diag.txt
