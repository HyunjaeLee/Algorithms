#define PROBLEM "https://yukicoder.me/problems/no/901"

#include "graph/auxiliary_tree.hpp"
#include <bits/stdc++.h>
using i64 = long long;

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N;
    std::cin >> N;
    std::vector<std::vector<std::pair<int, i64>>> adj(N);
    std::vector<std::vector<int>> g(N);
    for (auto i = 0; i < N - 1; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    std::vector<i64> dist(N);
    auto dfs = [&](auto &&self, int u, int p) -> void {
        for (auto [v, w] : adj[u]) {
            if (v != p) {
                dist[v] = dist[u] + w;
                self(self, v, u);
            }
        }
    };
    dfs(dfs, 0, 0);
    AuxiliaryTree aux(g, 0);
    int Q;
    std::cin >> Q;
    while (Q--) {
        int k;
        std::cin >> k;
        std::vector<int> x(k);
        std::copy_n(std::istream_iterator<int>(std::cin), k, x.begin());
        i64 ans = 0;
        for (auto [u, p] : aux.get(move(x)) | std::views::drop(1)) {
            ans += dist[u] - dist[p];
        }
        std::cout << ans << '\n';
    }
}
