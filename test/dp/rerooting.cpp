#define PROBLEM "https://judge.yosupo.jp/problem/static_range_inversions_query"

#include "dp/rerooting.hpp"
#include "graph/csr_graph.hpp"
#include <atcoder/modint>
#include <bits/stdc++.h>

using mint = atcoder::modint998244353;

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N;
    std::cin >> N;
    CSRGraph<int, std::pair<int, int>> g(N);
    for (auto i = 0; i < N; ++i) {
        int a;
        std::cin >> a;
        g.set_node(i, a);
    }
    for (auto i = 0; i < N - 1; ++i) {
        int u, v, b, c;
        std::cin >> u >> v >> b >> c;
        g.add_edge(u, v, {b, c});
    }
    g.build_undirected();
    using State = std::pair<mint, int>;
    auto op = [](State a, State b) -> State { return {a.first + b.first, a.second + b.second}; };
    auto to_path = [](State x, auto e) -> State {
        return {e.first * x.first + mint::raw(e.second) * x.second, x.second};
    };
    auto to_subtree = [](State x, int v) -> State { return {x.first + v, x.second + 1}; };
    State e{0, 0};
    auto dp = rerooting(g, op, to_path, to_subtree, e);
    for (auto [sum, cnt] : dp) {
        std::cout << sum.val() << ' ';
    }
}
