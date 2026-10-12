#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"

#include "graph/goldberg_radzik.hpp"
#include "graph/csr_graph.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, M, S, T;
    std::cin >> N >> M >> S >> T;
    csr_graph<int> g(N);
    for (auto i = 0; i < M; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        g.add_edge(u, v, w);
    }
    g.build();
    constexpr auto inf = std::numeric_limits<long long>::max() / 2;
    auto [ok, dist, parent] = goldberg_radzik<long long, inf>(g, S);
    std::vector<int> path;
    for (auto x = T; x != -1; x = parent[x]) {
        path.push_back(x);
    }
    if (inf <= dist[T]) {
        std::cout << "-1\n";
    } else {
        auto X = dist[T];
        auto Y = int(path.size()) - 1;
        std::cout << X << " " << Y << "\n";
        for (auto i = Y; 0 < i; --i) {
            std::cout << path[i] << " " << path[i - 1] << "\n";
        }
    }
}
