#! /bin/bash
cd tests
if [ "$1" = "clean" ]; then
    for d in $(ls); do
        rm -f $d/DFA.png $d/out.txt $d/minDFA.png
    done
else
    for d in $(ls); do
        cp ../main $d/
        cd $d
        ./main in.txt -o
        cd ..
        rm -f $d/main
    done
fi

