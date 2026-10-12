#ifndef GOLDBERG_RADZIK_HPP
#define GOLDBERG_RADZIK_HPP

#include <limits>
#include <ranges>
#include <tuple>
#include <utility>
#include <vector>

template <typename T, T inf = std::numeric_limits<T>::max() / 2>
std::tuple<bool, std::vector<T>, std::vector<int>> goldberg_radzik(const auto &g, int src) {
    auto n = int(g.size());
    std::vector<T> dist(n, inf);
    dist[src] = 0;
    std::vector<int> cur{src}, nxt, order, parent(n, -1);
    std::vector<int> state(n); // -t: in stack/labeled, t: visited
    for (auto t = 1; !cur.empty(); ++t) {
        order.clear();
        auto dfs = [&](auto &&self, int u) {
            if (state[u] == t || state[u] == -t)
                return state[u] == t;
            state[u] = -t;
            for (auto [v, w] : g[u]) {
                if (dist[v] <= dist[u] + w)
                    continue;
                dist[v] = dist[u] + w;
                parent[v] = u;
                if (!self(self, v))
                    return false;
            }
            state[u] = t;
            order.push_back(u);
            return true;
        };
        for (auto u : cur) {
            if (state[u] == t)
                continue;
            auto can_relax = false;
            for (auto [v, w] : g[u]) {
                if (dist[u] + w < dist[v]) {
                    can_relax = true;
                    break;
                }
            }
            if (can_relax && !dfs(dfs, u)) {
                return {false, {}, {}};
            }
        }
        nxt.clear();
        for (auto u : order | std::views::reverse) {
            for (auto [v, w] : g[u]) {
                if (dist[v] <= dist[u] + w)
                    continue;
                dist[v] = dist[u] + w;
                parent[v] = u;
                if (state[v] != -t) {
                    state[v] = -t;
                    nxt.push_back(v);
                }
            }
        }
        std::swap(cur, nxt);
    }
    return {true, std::move(dist), std::move(parent)};
}

#endif // GOLDBERG_RADZIK_HPP