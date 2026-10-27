#define PROBLEM "https://judge.yosupo.jp/problem/tree_diameter"

#include "dp/rerooting.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N;
    std::cin >> N;
    std::vector<std::vector<std::pair<int, int>>> g(N);
    for (auto i = 0; i < N - 1; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    auto rake = [&](long long l, long long r) -> long long { return std::max(l, r); };
    auto add_edge = [&](long long d, int w) -> long long { return d + w; };
    auto add_vertex = [&](long long d, int) -> long long { return d; };
    auto e = []() -> long long { return 0; };
    auto dp = rerooting(g, rake, add_edge, add_vertex, e);
    auto root = 0;
    for (auto i = 0; i < N; ++i) {
        if (dp[root] < dp[i]) {
            root = i;
        }
    }
    std::vector<int> parent(N, -1);
    std::vector<long long> depth(N);
    auto dfs = [&](auto &&self, int u) -> void {
        for (auto [v, w] : g[u]) {
            if (v == parent[u]) {
                continue;
            }
            parent[v] = u;
            depth[v] = depth[u] + w;
            self(self, v);
        }
    };
    dfs(dfs, root);
    auto u = 0;
    for (auto i = 0; i < N; ++i) {
        if (depth[u] < depth[i]) {
            u = i;
        }
    }
    std::vector<int> path;
    while (u != -1) {
        path.push_back(u);
        u = parent[u];
    }
    std::cout << dp[root] << " " << path.size() << "\n";
    for (auto v : path) {
        std::cout << v << " ";
    }
}
