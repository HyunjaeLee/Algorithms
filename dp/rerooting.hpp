#ifndef REROOTING_HPP
#define REROOTING_HPP

#include <ranges>
#include <vector>

/*
    vector<vector<pair<int, EdgeWeight>>> g;
    struct Subtree {};
    struct Children {};
    auto rake = [&](Children l, Children r) -> Children {};
    auto add_edge = [&](Subtree d, EdgeWeight w) -> Children {};
    auto add_vertex = [&](Children d, int i) -> Subtree {};
    auto e = []() -> Children {};
*/

auto rerooting(const auto &g, auto rake, auto add_edge, auto add_vertex, auto e) {
    auto n = int(g.size());
    using Children = decltype(e());
    using Subtree = decltype(add_vertex(e(), 0));
    std::vector<Subtree> dp(n), dp_parent(n);
    std::vector<int> bfs_order, parent(n, -1);
    std::vector<Children> pref(n + 1);
    bfs_order.reserve(n);
    for (auto root = 0; root < n; ++root) {
        if (~parent[root]) {
            continue;
        }
        parent[root] = root;
        bfs_order.clear();
        bfs_order.push_back(root);
        auto q = bfs_order.cbegin();
        while (q != bfs_order.cend()) {
            auto u = *q++;
            for (auto [v, w] : g[u]) {
                if (v != parent[u]) {
                    parent[v] = u;
                    bfs_order.push_back(v);
                }
            }
        }
        for (auto u : bfs_order | std::views::reverse) {
            Children sum = e();
            for (auto [v, w] : g[u]) {
                if (v != parent[u]) {
                    sum = rake(sum, add_edge(dp[v], w));
                }
            }
            dp[u] = add_vertex(sum, u);
        }
        for (auto u : bfs_order) {
            auto i = 0;
            pref[0] = e();
            for (auto [v, w] : g[u]) {
                auto state = (v == parent[u]) ? dp_parent[u] : dp[v];
                pref[i + 1] = rake(pref[i], add_edge(state, w));
                ++i;
            }
            Children suff = e();
            for (auto [v, w] : g[u] | std::views::reverse) {
                if (v != parent[u]) {
                    Children except_child = rake(pref[i - 1], suff);
                    dp_parent[v] = add_vertex(except_child, u);
                }
                auto state = (v == parent[u]) ? dp_parent[u] : dp[v];
                suff = rake(add_edge(state, w), suff);
                --i;
            }
            dp[u] = add_vertex(suff, u);
        }
    }
    return dp;
}

#endif // REROOTING_HPP