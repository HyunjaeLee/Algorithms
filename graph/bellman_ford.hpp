#ifndef BELLMAN_FORD_HPP
#define BELLMAN_FORD_HPP

#include <algorithm>
#include <limits>
#include <tuple>
#include <vector>

template <typename T, T inf = std::numeric_limits<T>::max() / 2>
std::vector<T> bellman_ford(int n, const std::vector<std::tuple<int, int, T>> &edges, int src) {
    std::vector<T> dist(n, inf);
    dist[src] = 0;
    for (auto i = 0; i < n; ++i) {
        for (auto [u, v, w] : edges) {
            if (dist[u] < inf && dist[u] + w < dist[v]) {
                dist[v] = (i < n - 1) ? std::max(-inf, dist[u] + w) : -inf;
            }
        }
    }
    for (auto i = 0; i < n; ++i) {
        for (auto [u, v, w] : edges) {
            if (dist[u] == -inf) {
                dist[v] = -inf;
            }
        }
    }
    return dist;
}

#endif // BELLMAN_FORD_HPP