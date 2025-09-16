#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"

#include "heavy_light_decomposition/heavy_light_decomposition.hpp"
#include <atcoder/fenwicktree>
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> a(N);
    for (auto &x : a) {
        std::cin >> x;
    }
    std::vector<std::vector<int>> adj(N);
    for (auto i = 1; i < N; ++i) {
        int p;
        std::cin >> p;
        adj[p].push_back(i);
    }
    heavy_light_decomposition hld(adj, 0);
    atcoder::fenwick_tree<long long> ft(N);
    for (auto i = 0; i < N; ++i) {
        hld.access_node(i, [&](auto x) { ft.add(x, a[i]); });
    }
    for (auto i = 0; i < Q; ++i) {
        int t, u;
        std::cin >> t >> u;
        if (t == 0) {
            long long val;
            std::cin >> val;
            hld.access_node(u, [&](auto x) { ft.add(x, val); });
        } else {
            auto ans = 0LL;
            hld.access_subtree(u, true,
                               [&](auto l, auto r) { ans = ft.sum(l, r); });
            std::cout << ans << '\n';
        }
    }
}
