#ifndef REROOT_DFS_HPP
#define REROOT_DFS_HPP

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

auto reroot_dfs(const auto &g, auto rake, auto add_edge, auto add_vertex, auto e) {
    using Children = decltype(e());
    using Subtree = decltype(add_vertex(e(), 0));
    std::vector<Subtree> dp(g.size());
    auto dfs0 = [&](auto &&self, int u, int p) -> Subtree {
        Children sum = e();
        for (auto [v, w] : g[u]) {
            if (v != p) {
                sum = rake(sum, add_edge(self(self, v, u), w));
            }
        }
        return dp[u] = add_vertex(sum, u);
    };
    auto dfs1 = [&](auto &&self, int u, int p) -> void {
        std::vector<Children> pref{e()};
        for (auto [v, w] : g[u]) {
            pref.push_back(rake(pref.back(), add_edge(dp[v], w)));
        }
        Children suff = e();
        for (auto i = int(g[u].size()) - 1; 0 <= i; --i) {
            auto [v, w] = g[u][i];
            auto x = add_edge(dp[v], w);
            if (v != p) {
                dp[u] = add_vertex(rake(pref[i], suff), u);
                self(self, v, u);
            }
            suff = rake(x, suff);
        }
        dp[u] = add_vertex(suff, u);
    };
    dfs0(dfs0, 0, 0);
    dfs1(dfs1, 0, 0);
    return dp;
}

#endif // REROOT_DFS_HPP