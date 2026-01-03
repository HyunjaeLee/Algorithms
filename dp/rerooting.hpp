#ifndef REROOTING_HPP
#define REROOTING_HPP

#include <vector>

auto rerooting(const auto &g,   // Graph
               auto op,         // (PathState, PathState) -> PathState
               auto to_path,    // (TreeState, EdgeWeight) -> PathState
               auto to_subtree, // (PathState, NodeWeight) -> TreeState
               auto e           // PathState (Identity)
) {
    int n = g.size();
    using PathState = decltype(e);
    using TreeState = decltype(to_subtree(e, g.node_weight(0)));
    std::vector<TreeState> dp(n), dp_parent(n);
    std::vector<int> q, parent(n, -1);
    std::vector<PathState> pref(n + 1);
    q.reserve(n);
    for (int root = 0; root < n; ++root) {
        if (~parent[root]) {
            continue;
        }
        parent[root] = root;
        q.clear();
        q.push_back(root);
        auto it = q.cbegin();
        while (it != q.cend()) {
            int u = *it++;
            for (auto [v, w] : g[u]) {
                if (v != parent[u]) {
                    parent[v] = u;
                    q.push_back(v);
                }
            }
        }
        for (auto u : q | std::views::reverse) {
            PathState merged = e;
            for (auto [v, w] : g[u]) {
                if (v != parent[u]) {
                    merged = op(merged, to_path(dp[v], w));
                }
            }
            dp[u] = to_subtree(merged, g.node_weight(u));
        }
        for (auto u : q) {
            int i = 0;
            pref[0] = e;
            for (auto [v, w] : g[u]) {
                auto state = v == parent[u] ? dp_parent[u] : dp[v];
                pref[i + 1] = op(pref[i], to_path(state, w));
                ++i;
            }
            auto suff = e;
            for (auto [v, w] : g[u] | std::views::reverse) {
                if (v != parent[u]) {
                    PathState except_child = op(pref[i - 1], suff);
                    dp_parent[v] = to_subtree(except_child, g.node_weight(u));
                }
                auto state = v == parent[u] ? dp_parent[u] : dp[v];
                suff = op(to_path(state, w), suff);
                --i;
            }
            dp[u] = to_subtree(suff, g.node_weight(u));
        }
    }
    return dp;
}

#endif // REROOTING_HPP