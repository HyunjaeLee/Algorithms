#ifndef ENUMERATE_TRIANGLES_HPP
#define ENUMERATE_TRIANGLES_HPP

#include <algorithm>
#include <utility>
#include <vector>

// O(n + m * sqrt(m))
void enumerate_triangles(int n, const std::vector<std::pair<int, int>> &edges, auto f) {
    std::vector<int> deg(n);
    for (auto [u, v] : edges) {
        ++deg[u];
        ++deg[v];
    }
    std::vector<std::vector<int>> g(n);
    for (auto [u, v] : edges) {
        if (std::pair(deg[u], u) < std::pair(deg[v], v)) {
            std::swap(u, v);
        }
        g[u].push_back(v);
    }
    std::vector<int> color(n, -1);
    for (auto i = 0; i < n; ++i) {
        for (auto j : g[i]) {
            color[j] = i;
        }
        for (auto j : g[i]) {
            for (auto k : g[j]) {
                if (color[k] == i) {
                    f(i, j, k);
                }
            }
        }
    }
}

#endif // ENUMERATE_TRIANGLES_HPP