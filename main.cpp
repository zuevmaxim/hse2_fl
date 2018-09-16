#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <unordered_map>

class minDFA {
private:
    std::vector<std::string> S;
	int q0;
	std::unordered_set<int> T, T2;	
	std::vector<std::vector<int>> G;
	std::vector<int> comp;
	std::vector<std::vector<int>> ans;
	std::vector<std::vector<std::vector<int>>> g;
    std::vector<bool> used;
    std::vector<std::vector<bool>> d;
    
    void dfs(int v) {
	    used[v] = true;
	    for (auto u : G[v])
		    if (!used[u])
			    dfs(u);
    }
    
    void graphInvert() {
	    int n = G.size();
	    used.assign(n, false);
	    dfs(q0);
	    g.resize(n);
	    std::for_each(g.begin(), g.end(), [this](auto& v) { v.resize(S.size()); });
	    for (int i = 0; i < n; ++i)
		    if (used[i])
			    for (int j = 0; j < (int)S.size(); ++j)
				    g[G[i][j]][j].push_back(i);
    }
    
    bool notEqual(int i, int j) {
	    return (T.find(i) != T.end()) != (T.find(j) != T.end());
    }
    
    void buildEqualTable() {
	    std::queue<std::pair<int, int>> Q;
	    int n = g.size();
	    d.resize(n);
	    std::for_each(d.begin(), d.end(), [n](auto& v) { v.resize(n, false); });
	    for (int i = 0; i < n; ++i)
	        if (used[i])
		        for (int j = 0; j < n; ++j)
			        if (used[j] && !d[i][j] && notEqual(i, j))
				        d[i][j] = d[j][i] = true, Q.push({i, j});

	    while (!Q.empty()) {
		    auto p = Q.front();
		    Q.pop();
		    for (int i = 0; i < (int)S.size(); ++i)
			    for (auto v : g[p.first][i])
				    for (auto u : g[p.second][i])
					    if (!d[v][u])
						    d[v][u] = d[u][v] = true, Q.push({v, u});
	    }
    }
    
    int findComponents() {
	    int n = used.size();
	    comp.resize(n, -1);
	    int compNum = 0;
	    for (int i = 0; i < n; ++i) {
		    if (used[i] && comp[i] == -1) {
			    ++compNum;
			    comp[i] = compNum;
			    for (int j = i + 1; j < n; ++j)
				    if (!d[i][j])
					    comp[j] = compNum;
		    }
	    }
	    return compNum;
    }
    
    void buildNewDFA(int compNum) {
	    int n = G.size();
	    ans.resize(compNum);
	    for_each(ans.begin(), ans.end(), [this](auto& v) { v.resize(S.size()); });
	    for (int v = 0; v < n; ++v)
	        if (used[v])
		        for (int i = 0; i < (int)S.size(); ++i)
			        ans[comp[v] - 1][i] = comp[G[v][i]];
	    std::for_each(T.begin(), T.end(),
	        [this](auto t) {
	            if (used[t])
	            T2.insert(comp[t]);
	        });
    }

public:
    void minimize() {
	    graphInvert();
	    buildEqualTable();
	    int compNum = findComponents();
	    buildNewDFA(compNum);
    }

    void writeDFA() {
        std::cout << ans.size() << '\n';
	    std::cout << S.size() << '\n';
	    std::for_each(S.begin(), S.end(), [](auto& p) { std:: cout << p << ' '; });
	    std::cout << '\n';
	    std::cout << comp[q0] << '\n';
	    std::cout << T2.size() << ' ';
	    std::for_each(T2.begin(), T2.end(), [](auto t) { std::cout << t << ' '; });
	    std::cout << '\n';
		
	    for (auto v : ans) {
		    for (auto u : v)
			    std::cout << u << ' ';
		    std::cout << '\n';
	    }
    }
    
    void readDFA() {
        int n;
        std::cin >> n;
        int aSize;
	    std::cin >> aSize;
	    std::string s;
	    for (int i = 0; i < aSize; ++i) {
		    std::cin >> s;
		    S.push_back(s);
	    }
	    std::cin >> q0; --q0;
	    int t;
	    std::cin >> t;
	    int c;
	    for (int i = 0; i < t; ++i) {
		    std::cin >> c;
		    T.insert(c - 1); 
	    }
	    G.resize(n);
	    std::for_each(G.begin(), G.end(), [this](auto& v) { v.resize(S.size()); });
	    for (int i = 0; i < n; ++i)
		    for (int j = 0; j < (int)S.size(); ++j)
			    std::cin >> G[i][j], --G[i][j];
    }
};

int main() {
    minDFA a;
	a.readDFA();
	a.minimize();
	a.writeDFA();
    return 0;
}
