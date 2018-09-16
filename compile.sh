#! /bin/bash
g++ -std=c++17 -Wall -pedantic -Iinclude -Wextra main.cpp -o main
g++ -std=c++17 -Wall -pedantic -Iinclude -Wextra graph.cpp -o graph
sudo apt-get install graphviz >/dev/null
