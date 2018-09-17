#include "minDFA.h"
#include "DFAdraw.h"
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>

int main(int argc, char* argv[]) {
    std::string inFile = argv[1];
    
    std::ifstream in(inFile);
    
    minDFA dfa;
	dfa.readDFA(in);
	
	if (argc > 1 && strcmp(argv[2], "-o") == 0) {
	    DFAdraw dd(dfa);
	    dd.draw("DFA.png");
	}
	
	dfa.minimize();
	
	std::ofstream out("out.txt");
	dfa.writeDFA(out);
	
	DFAdraw dd(dfa);
	dd.draw("minDFA.png");
    return 0;
}
