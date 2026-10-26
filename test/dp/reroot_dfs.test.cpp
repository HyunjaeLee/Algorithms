#define PROBLEM "https://judge.yosupo.jp/problem/tree_path_composite_sum"

#include "dp/reroot_dfs.hpp"
#include <atcoder/modint>
#include <bits/stdc++.h>
using Z = atcoder::modint998244353;

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N;
    std::cin >> N;
    using EdgeWeight = std::pair<int, int>;
    std::vector<std::vector<std::pair<int, EdgeWeight>>> g(N);
    std::vector<int> a(N);
    for (auto i = 0; i < N; ++i) {
        std::cin >> a[i];
    }
    for (auto i = 0; i < N - 1; ++i) {
        int u, v, b, c;
        std::cin >> u >> v >> b >> c;
        g[u].push_back({v, {b, c}});
        g[v].push_back({u, {b, c}});
    }
    using Subtree = std::pair<Z, int>;
    using Children = std::pair<Z, int>;
    auto rake = [&](Children l, Children r) -> Children {
        return {l.first + r.first, l.second + r.second};
    };
    auto add_edge = [&](Subtree d, EdgeWeight w) -> Children {
        return {w.first * d.first + Z::raw(w.second) * d.second, d.second};
    };
    auto add_vertex = [&](Children d, int i) -> Subtree { return {d.first + a[i], d.second + 1}; };
    auto e = []() -> Children { return {0, 0}; };
    auto dp = reroot_dfs(g, rake, add_edge, add_vertex, e);
    for (auto [sum, cnt] : dp) {
        std::cout << sum.val() << ' ';
    }
}
