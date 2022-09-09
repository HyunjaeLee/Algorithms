#ifndef OFFLINE_DYNAMIC_CONNECTIVITY_HPP
#define OFFLINE_DYNAMIC_CONNECTIVITY_HPP

#include <algorithm>
#include <array>
#include <cassert>
#include <type_traits>
#include <utility>
#include <vector>

template <typename DisjointSet> struct offline_dynamic_connectivity {
    explicit offline_dynamic_connectivity(int n) : n_(n), timer_(0) {}
    void toggle_edge(int u, int v) {
        assert(0 <= u && u < n_ && 0 <= v && v < n_);
        if (u > v) {
            std::swap(u, v);
        }
        edges_.push_back({u, v, timer_});
    }
    int snapshot() { return timer_++; }
    void reserve(int n) { edges_.reserve(n); }
    template <typename Function>
    std::vector<std::invoke_result_t<Function, DisjointSet, int>>
    solve(Function f) {
        auto k = timer_;
        if (k == 0) {
            return {};
        }
        std::sort(edges_.begin(), edges_.end());
        std::vector<std::vector<std::pair<int, int>>> segment(2 * k);
        auto edges_size = static_cast<int>(edges_.size());
        for (auto i = 0; i < edges_size; ++i) {
            auto [u, v, l] = edges_[i];
            auto r = k;
            if (i + 1 < edges_size && u == edges_[i + 1][0] &&
                v == edges_[i + 1][1]) {
                r = edges_[++i][2];
            }
            l += k;
            r += k;
            while (l < r) {
                if (l & 1) {
                    segment[l++].push_back({u, v});
                }
                if (r & 1) {
                    segment[--r].push_back({u, v});
                }
                l >>= 1;
                r >>= 1;
            }
        }
        DisjointSet dsu(n_);
        std::vector<std::invoke_result_t<Function, DisjointSet, int>> result(k);
        auto dfs = [&](auto self, int node) -> void {
            auto count = 0;
            for (auto [u, v] : segment[node]) {
                if (dsu.merge(u, v)) {
                    ++count;
                }
            }
            if (node < k) {
                self(self, 2 * node);
                self(self, 2 * node + 1);
            } else {
                result[node - k] = f(dsu, node - k);
            }
            dsu.rollback(count);
        };
        dfs(dfs, 1);
        return result;
    }

private:
    int n_, timer_;
    std::vector<std::array<int, 3>> edges_;
};

#endif // OFFLINE_DYNAMIC_CONNECTIVITY_HPP
