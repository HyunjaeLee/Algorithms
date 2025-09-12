#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include "../lca/lca_tree.hpp"
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
    lca_tree tree(adj, 0);
    for (int i = 0; i < Q; ++i) {
        int u, v;
        std::cin >> u >> v;
        std::cout << tree.lca(u, v) << '\n';
    }
}
