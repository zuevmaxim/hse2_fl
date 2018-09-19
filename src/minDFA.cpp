#include "minDFA.h"
#include <algorithm>
#include <queue>

void minDFA::dfs(int v) {
    used[v] = true;
    for (auto u : G[v])
	    if (!used[u])
		    dfs(u);
}

void minDFA::graphInvert() {
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

bool minDFA::notEqual(int i, int j) const {
    return (T.find(i) != T.end()) != (T.find(j) != T.end());
}

void minDFA::buildEqualTable() {
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

int minDFA::findComponents() {
    int n = used.size();
    comp.resize(n, -1);
    int compNum = 0;
    for (int i = 0; i < n; ++i) {
	    if (used[i] && comp[i] == -1) {
		    comp[i] = compNum;
		    for (int j = i + 1; j < n; ++j)
			    if (!d[i][j])
				    comp[j] = compNum;
		    ++compNum;
	    }
    }
    return compNum;
}

void minDFA::buildNewDFA(int compNum) {
    int n = G.size();
    std::vector<std::vector<int>> ans;
    ans.resize(compNum);
    for_each(ans.begin(), ans.end(), [this](auto& v) { v.resize(S.size()); });
    for (int v = 0; v < n; ++v)
        if (used[v])
	        for (int i = 0; i < (int)S.size(); ++i)
		        ans[comp[v]][i] = comp[G[v][i]];
    std::unordered_set<int> T2;
    std::for_each(T.begin(), T.end(),
        [this, &T2](auto t) {
            if (used[t])
            T2.insert(comp[t]);
        });
    std::swap(T, T2);
    std::swap(ans, G);
    q0 = comp[q0];
}

void minDFA::minimize() {
    graphInvert();
    buildEqualTable();
    int compNum = findComponents();
    buildNewDFA(compNum);
}

void minDFA::writeDFA(std::ofstream& out) const {
    out << G.size() << '\n';
    out << S.size() << '\n';
    std::for_each(S.begin(), S.end(), [&out](auto& p) { out << p << ' '; });
    out << '\n';
    out << q0 + 1 << '\n';
    out << T.size() << ' ';
    std::for_each(T.begin(), T.end(), [&out](auto t) { out << t + 1<< ' '; });
    out << '\n';
	
    for (auto v : G) {
	    for (auto u : v)
		    out << u + 1 << ' ';
	    out << '\n';
    }
}

void minDFA::readDFA(std::ifstream& in) {
    int n;
    in >> n;
    int aSize;
    in >> aSize;
    std::string s;
    for (int i = 0; i < aSize; ++i) {
	    in >> s;
	    S.push_back(s);
    }
    in >> q0; --q0;
    int t;
    in >> t;
    int c;
    for (int i = 0; i < t; ++i) {
	    in >> c;
	    T.insert(c - 1); 
    }
    G.resize(n);
    std::for_each(G.begin(), G.end(), [this](auto& v) { v.resize(S.size()); });
    for (int i = 0; i < n; ++i)
	    for (int j = 0; j < (int)S.size(); ++j)
		    in >> G[i][j], --G[i][j];
}
