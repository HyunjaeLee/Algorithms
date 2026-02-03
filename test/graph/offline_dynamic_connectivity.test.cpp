#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2235"

#include "data_structures/rollback_disjoint_set.hpp"
#include "graph/offline_dynamic_connectivity.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int n, k;
    std::cin >> n >> k;
    offline_dynamic_connectivity<rollback_disjoint_set> dc(n);
    std::vector<std::pair<int, int>> q;
    dc.reserve(k);
    q.reserve(k);
    while (k--) {
        int t, u, v;
        std::cin >> t >> u >> v;
        switch (t) {
        case 1:
        case 2:
            dc.toggle_edge(u, v);
            break;
        case 3:
            q.emplace_back(u, v);
            dc.snapshot();
            break;
        }
    }
    auto result = dc.solve([&](const auto &dsu, int i) {
        auto [u, v] = q[i];
        return dsu.same(u, v);
    });
    for (auto b : result) {
        std::cout << (b ? "YES\n" : "NO\n");
    }
}
