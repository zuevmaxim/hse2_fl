#include "DFAdraw.h"
#include <fstream>
#include <cstdlib>
#include <string>

DFAdraw::DFAdraw(const minDFA& dfa) : dfa(dfa) { }

void DFAdraw::draw(const char* s) {
    std::ofstream out("graph.txt");
    out << "digraph G {\n";
	out << "node [shape=\"circle\"];\n";
	out << "rankdir=\"LR\";\n";
	out << "\"\" [shape=none];\n";
	for (auto v : dfa.T)
		out << v + 1 << " [peripheries=2];\n";
	out << "\"\" -> " << dfa.q0 + 1 << ";\n";
	for (int i = 0; i < (int)dfa.G.size(); ++i)
		for (int j = 0; j < (int)dfa.S.size(); ++j)
			out << i + 1 << "->" << dfa.G[i][j] + 1 << "[label=\"" << dfa.S[j] << "\"];\n";
	out << "}" << std::endl;
	std::string command = "dot -Tpng graph.txt -o";
	command += s;
    std::system(command.c_str());	
    std::system("rm -f graph.txt");
}

