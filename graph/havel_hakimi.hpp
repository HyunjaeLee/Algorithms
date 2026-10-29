#ifndef HAVEL_HAKIMI_HPP
#define HAVEL_HAKIMI_HPP

#include <cassert>
#include <optional>
#include <queue>
#include <span>
#include <utility>
#include <vector>

// https://en.wikipedia.org/wiki/Havel–Hakimi_algorithm
// O(N + M log N)
std::optional<std::vector<std::pair<int, int>>> havel_hakimi(std::vector<int> deg) {
    auto n = int(deg.size());
    std::priority_queue<std::pair<int, int>> pq;
    for (auto i = 0; i < n; ++i) {
        assert(0 <= deg[i]);
        if (0 < deg[i]) {
            pq.emplace(deg[i], i);
        }
    }
    std::vector<std::pair<int, int>> edges;
    while (!pq.empty()) {
        auto [k, u] = pq.top();
        pq.pop();
        if (int(pq.size()) < k) {
            return std::nullopt;
        }
        for (auto i = 0; i < k; ++i) {
            auto [d, v] = pq.top();
            pq.pop();
            --deg[v];
            edges.emplace_back(u, v);
        }
        for (auto [_, v] : std::span(edges).last(k)) {
            if (0 < deg[v]) {
                pq.emplace(deg[v], v);
            }
        }
    }
    return edges;
}

#endif // HAVEL_HAKIMI_HPP