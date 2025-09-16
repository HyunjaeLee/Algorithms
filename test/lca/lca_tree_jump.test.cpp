#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"

#include "../lca/lca_tree.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    std::cin >> N >> Q;
    std::vector<std::vector<int>> adj(N);
    for (auto i = 0; i < N - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    lca_tree tree(adj, 0);
    for (auto i = 0; i < Q; ++i) {
        int u, v, k;
        std::cin >> u >> v >> k;
        std::cout << tree.jump(u, v, k) << '\n';
    }
}
