#ifndef _MIN_DFA_H
#define _MIN_DFA_H

#include <unordered_set>
#include <vector>
#include <string>
#include <fstream>

class minDFA {
private:
    friend class DFAdraw;
    std::vector<std::string> S;
	int q0;
	std::unordered_set<int> T;	
	std::vector<std::vector<int>> G;
	std::vector<int> comp;
	std::vector<std::vector<std::vector<int>>> g;
    std::vector<bool> used;
    std::vector<std::vector<bool>> d;
    
    void dfs(int v);
    void graphInvert();
    bool notEqual(int i, int j) const;
    void buildEqualTable();
    int findComponents();
    void buildNewDFA(int compNum);

public:
    void minimize();
    void writeDFA(std::ofstream& out) const;
    void readDFA(std::ifstream& in);
};


#endif
