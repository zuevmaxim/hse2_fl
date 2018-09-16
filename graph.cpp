#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>
#include <algorithm>


int main() {
    int n;
    int aSize;
    int q0;
    int t;
    std::unordered_set<int> T;
    std::vector<std::string> S;
    std::vector<std::vector<int>> G;
    
	std::cin >> n;
	std::cin >> aSize;
	std::string s;
	for (int i = 0; i < aSize; ++i) {
		std::cin >> s;
		S.push_back(s);
	}
	std::cin >> q0;
	std::cin >> t;
	int c;
	for (int i = 0; i < t; ++i) {
		std::cin >> c;
		T.insert(c); 
	}
	G.resize(n);
	std::for_each(G.begin(), G.end(), [aSize](auto& v) { v.resize(aSize); });
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < aSize; ++j)
			std::cin >> G[i][j];
	std::cout << "digraph G {\n";
	std::cout << "node [shape=\"circle\"];\n";
	std::cout << "rankdir=\"LR\";\n";
	std::cout << "\"\" [shape=none];\n";
	
	for (auto v : T)
		std::cout << v << " [peripheries=2];\n";
	std::cout << "\"\" -> " << q0 << ";\n";
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < aSize; ++j)
			std::cout << i + 1 << "->" << G[i][j] << "[label=\"" << S[j] << "\"];\n";
	
	std::cout << "}\n";
    return 0;
}
