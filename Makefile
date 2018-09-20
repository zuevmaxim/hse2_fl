.PHONY: clean all
CXX = g++
CXXFLAGS = -std=c++14 -Wall -pedantic -Iinclude -Wextra

all: bin main

bin:
	mkdir -p bin
	if ( ! dpkg -s graphviz | grep -iE "status" | grep -oiE "installed"); then sudo apt-get install graphviz; fi

main: bin/main.o bin/minDFA.o bin/DFAdraw.o
	$(CXX) $(CXXFLAGS) bin/main.o bin/minDFA.o bin/DFAdraw.o -o main

bin/main.o: src/main.cpp include/*.h 
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o bin/main.o

bin/minDFA.o: src/minDFA.cpp include/*.h 
	$(CXX) $(CXXFLAGS) -c src/minDFA.cpp -o bin/minDFA.o

bin/DFAdraw.o: src/DFAdraw.cpp include/*.h 
	$(CXX) $(CXXFLAGS) -c src/DFAdraw.cpp -o bin/DFAdraw.o

clean:
	rm -rf bin main
