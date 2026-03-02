#define PROBLEM "https://judge.yosupo.jp/problem/tree_path_composite_sum"

#include "dp/rerooting.hpp"
#include "graph/csr_graph.hpp"
#include <atcoder/modint>
#include <bits/stdc++.h>

using Z = atcoder::modint998244353;

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N;
    std::cin >> N;
    using EdgeWeight = std::pair<int, int>;
    CSRGraph<EdgeWeight> g(N);
    std::vector<int> a(N);
    std::copy_n(std::istream_iterator<int>(std::cin), N, a.begin());
    for (auto i = 0; i < N - 1; ++i) {
        int u, v, b, c;
        std::cin >> u >> v >> b >> c;
        g.add_edge(u, v, {b, c});
    }
    g.build_undirected();
    using Subtree = std::pair<Z, int>;
    using Child = std::pair<Z, int>;
    auto rake = [&](Child l, Child r) -> Child { return {l.first + r.first, l.second + r.second}; };
    auto add_edge = [&](Subtree d, EdgeWeight w) -> Child {
        return {w.first * d.first + Z::raw(w.second) * d.second, d.second};
    };
    auto add_vertex = [&](Child d, int i) -> Subtree { return {d.first + a[i], d.second + 1}; };
    auto e = []() -> Child { return {0, 0}; };
    auto dp = rerooting(g, rake, add_edge, add_vertex, e);
    for (auto [sum, cnt] : dp) {
        std::cout << sum.val() << ' ';
    }
}
