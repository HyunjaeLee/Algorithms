#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_B"

#include "graph/bellman_ford.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, M, S;
    std::cin >> N >> M >> S;
    constexpr auto inf = std::numeric_limits<int>::max() / 2;
    std::vector<std::tuple<int, int, int>> edges(M);
    for (auto &[u, v, w] : edges) {
        std::cin >> u >> v >> w;
    }
    auto dist = bellman_ford(N, edges, S);
    for (auto i = 0; i < N; ++i) {
        if (dist[i] == -inf) {
            std::cout << "NEGATIVE CYCLE\n";
            return 0;
        }
    }
    for (auto i = 0; i < N; ++i) {
        if (dist[i] == inf) {
            std::cout << "INF\n";
        } else {
            std::cout << dist[i] << "\n";
        }
    }
}
