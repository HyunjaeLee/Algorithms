#ifndef ARTICULATION_POINTS_HPP
#define ARTICULATION_POINTS_HPP

#include <algorithm>
#include <vector>

std::vector<int> find_cutpoints(const auto &g) {
    auto n = (int)g.size();
    auto timer = 0;
    std::vector<int> visited(n), tin(n, -1), low(n, -1);
    std::vector<int> cutpoints;
    auto dfs = [&](auto self, int u, int p) -> void {
        visited[u] = true;
        tin[u] = low[u] = timer++;
        auto children = 0;
        auto is_cutpoint = false;
        for (auto v : g[u]) {
            if (v == p) {
                continue;
            }
            if (visited[v]) {
                low[u] = std::min(low[u], tin[v]);
            } else {
                self(self, v, u);
                low[u] = std::min(low[u], low[v]);
                is_cutpoint |= (tin[u] <= low[v] && p != -1);
                ++children;
            }
        }
        is_cutpoint |= (p == -1 && 1 < children);
        if (is_cutpoint) {
            cutpoints.push_back(u);
        }
    };
    for (auto i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(dfs, i, -1);
        }
    }
    return cutpoints;
}

#endif // ARTICULATION_POINTS_HPP