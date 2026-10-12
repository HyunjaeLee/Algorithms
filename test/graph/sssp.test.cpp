#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_B"

#include "graph/goldberg_radzik.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, M, S;
    std::cin >> N >> M >> S;
    constexpr auto inf = std::numeric_limits<int>::max() / 2;
    std::vector<std::vector<std::pair<int, int>>> g(N);
    for (auto i = 0; i < M; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        g[u].emplace_back(v, w);
    }
    auto [ok, dist, parent] = goldberg_radzik<int, inf>(g, S);
    if (!ok) {
        std::cout << "NEGATIVE CYCLE\n";
        return 0;
    }
    for (auto i = 0; i < N; ++i) {
        if (dist[i] == inf) {
            std::cout << "INF\n";
        } else {
            std::cout << dist[i] << "\n";
        }
    }
}
