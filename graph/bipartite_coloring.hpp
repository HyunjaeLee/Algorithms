#ifndef BIPARTITE_COLORING_HPP
#define BIPARTITE_COLORING_HPP

#include <optional>
#include <queue>
#include <vector>

std::optional<std::vector<int>> bipartite_coloring(const std::vector<std::vector<int>> &g) {
    auto n = int(g.size());
    std::vector<int> color(n, -1);
    for (auto i = 0; i < n; ++i) {
        if (color[i] != -1) {
            continue;
        }
        std::queue<int> q;
        q.push(i);
        color[i] = 0;
        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            for (auto v : g[u]) {
                if (color[v] == -1) {
                    q.push(v);
                    color[v] = color[u] ^ 1;
                } else if (color[v] == color[u]) {
                    return std::nullopt;
                }
            }
        }
    }
    return color;
}

#endif // BIPARTITE_COLORING_HPP