#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_B"

#include "graph/bridges.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> g(n);
    for (auto i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    auto bridges = find_bridges(g);
    for (auto &[u, v] : bridges) {
        if (u > v) {
            std::swap(u, v);
        }
    }
    std::ranges::sort(bridges);
    for (auto [u, v] : bridges) {
        std::cout << u << ' ' << v << '\n';
    }
}
