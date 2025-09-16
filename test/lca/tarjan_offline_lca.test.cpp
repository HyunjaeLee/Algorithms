#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include "../lca/tarjan_offline_lca.hpp"
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
    std::vector<std::pair<int, int>> queries(Q);
    for (auto &[u, v] : queries) {
        std::cin >> u >> v;
    }
    tarjan_offline_lca lca(adj, 0, queries);
    auto result = lca.lca();
    for (auto x : result) {
        std::cout << x << '\n';
    }
}
