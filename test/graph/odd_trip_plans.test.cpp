#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/challenges/sources/JAG/Summer/3622"

#include "graph/potentialized_offline_dynamic_connectivity.hpp"
#include "monoids/xor.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, M, Q;
    std::cin >> N >> M >> Q;
    using A = Xor<int>;
    PotentializedOfflineDynamicConnectivity<A> dc(N);
    for (auto i = 0; i < M; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        dc.toggle_edge(u, v, A{1});
    }
    std::vector<std::pair<int, int>> query;
    for (auto i = 0; i < Q; ++i) {
        int t, u, v;
        std::cin >> t >> u >> v;
        --u, --v;
        if (t == 1) {
            dc.toggle_edge(u, v, A{1});
        } else {
            dc.snapshot();
            query.emplace_back(u, v);
        }
    }
    std::vector<char> ans(query.size());
    dc.solve([&](const auto &dsu, int i) {
        auto [u, v] = query[i];
        auto is_bipartite = dsu.is_valid();
        auto ok = dsu.size(0) == N && (!is_bipartite || dsu.diff(u, v) == A{(N ^ 1) & 1});
        ans[i] = ok;
    });
    for (auto ok : ans) {
        std::cout << (ok ? "Yes" : "No") << "\n";
    }
}
