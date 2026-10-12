#define PROBLEM "https://judge.yosupo.jp/problem/tree_diameter"

#include <graph/csr_graph.hpp>
#include <tree/tree_diameter.hpp>

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    csr_graph<long long> g(N);
    for (auto i = 0; i < N - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g.add_edge(u, v, w);
        g.add_edge(v, u, w);
    }
    g.build();
    auto [d, path] = tree_diameter<long long>(g);
    cout << d << " " << path.size() << "\n";
    for (auto u : path) {
        cout << u << " ";
    }
}
