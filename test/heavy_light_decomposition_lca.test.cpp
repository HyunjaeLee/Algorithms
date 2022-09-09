#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include "../heavy_light_decomposition/heavy_light_decomposition.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    std::cin >> N >> Q;
    std::vector<std::vector<int>> adj(N);
    for (auto i = 1; i < N; ++i) {
        int p;
        std::cin >> p;
        adj[p].push_back(i);
    }
    heavy_light_decomposition hld(adj, 0);
    while (Q--) {
        int u, v;
        std::cin >> u >> v;
        std::cout << hld.lca(u, v) << '\n';
    }
}
