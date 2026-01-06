#ifndef BRIDGES_HPP
#define BRIDGES_HPP

#include <algorithm>
#include <utility>
#include <vector>

std::vector<std::pair<int, int>> find_bridges(const auto &g) {
    auto n = (int)g.size();
    auto timer = 0;
    std::vector<int> visited(n, false), tin(n, -1), low(n, -1);
    std::vector<std::pair<int, int>> bridges;
    auto dfs = [&](auto self, int u, int p) -> void {
        visited[u] = true;
        tin[u] = low[u] = timer++;
        bool parent_skipped = false;
        for (int v : g[u]) {
            if (v == p && !parent_skipped) {
                parent_skipped = true;
                continue;
            }
            if (visited[v]) {
                low[u] = std::min(low[u], tin[v]);
            } else {
                self(self, v, u);
                low[u] = std::min(low[u], low[v]);
                if (tin[u] < low[v]) {
                    bridges.emplace_back(u, v);
                }
            }
        }
    };
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(dfs, i, -1);
        }
    }
    return bridges;
}

#endif // BRIDGES_HPP