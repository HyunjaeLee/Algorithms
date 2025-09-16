#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"

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
    for (auto i = 0; i < N - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    heavy_light_decomposition hld(adj, 0);
    atcoder::fenwick_tree<long long> ft(N);
    for (auto i = 0; i < N; ++i) {
        hld.access_node(i, [&](auto x) { ft.add(x, a[i]); });
    }
    for (auto i = 0; i < Q; ++i) {
        int t, a, b;
        std::cin >> t >> a >> b;
        if (t == 0) {
            hld.access_node(a, [&](auto x) { ft.add(x, b); });
        } else {
            auto sum = 0LL;
            hld.access_path(a, b, true,
                            [&](auto l, auto r) { sum += ft.sum(l, r); });
            std::cout << sum << '\n';
        }
    }
}
