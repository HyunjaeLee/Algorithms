#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/challenges/sources/JAG/Regional/3354"

#include "graph/potentialized_offline_dynamic_connectivity.hpp"
#include "monoids/sum.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int M, N;
    std::cin >> M >> N;
    using A = Sum<long long>;
    PotentializedOfflineDynamicConnectivity<A> dc(N);
    dc.reserve(M);
    std::vector<std::tuple<int, int, A>> edges;
    edges.reserve(M);
    for (auto i = 0; i < M; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        --u, --v;
        dc.toggle_edge(u, v, A{w});
        edges.emplace_back(u, v, A{w});
    }
    for (auto [u, v, w] : edges) {
        dc.toggle_edge(u, v, A{w});
        dc.snapshot();
        dc.toggle_edge(u, v, A{w});
    }
    auto ans = -1;
    dc.solve([&](const auto &dsu, int i) {
        if (dsu.is_valid()) {
            ans = i + 1;
        }
    });
    std::cout << ans << "\n";
}
