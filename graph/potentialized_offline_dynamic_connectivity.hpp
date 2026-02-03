#ifndef POTENTIALIZED_OFFLINE_DYNAMIC_CONNECTIVITY_HPP
#define POTENTIALIZED_OFFLINE_DYNAMIC_CONNECTIVITY_HPP

#include "data_structures/potentialized_rollback_dsu.hpp"
#include <algorithm>
#include <cassert>
#include <ranges>
#include <tuple>
#include <vector>

// A is an abelian group
template <typename A> struct PotentializedOfflineDynamicConnectivity {
    explicit PotentializedOfflineDynamicConnectivity(int n) : n_(n), timer_(0) {}
    void toggle_edge(int u, int v, A w) {
        assert(0 <= u && u < n_ && 0 <= v && v < n_);
        if (u > v) {
            std::swap(u, v);
            w = A::inv(w);
        }
        edges_.emplace_back(u, v, timer_, w);
    }
    int snapshot() { return timer_++; }
    void reserve(int n) { edges_.reserve(n); }
    void solve(auto f) {
        auto k = timer_;
        if (k == 0) {
            return;
        }
        auto comp = [](const auto &a, const auto &b) {
            const auto &[u1, v1, t1, w1] = a;
            const auto &[u2, v2, t2, w2] = b;
            return std::tie(u1, v1, t1) < std::tie(u2, v2, t2);
        };
        std::ranges::sort(edges_, comp);
        std::vector<std::vector<int>> segment(2 * k);
        const auto E = int(edges_.size());
        for (auto i = 0; i < E; ++i) {
            auto [u, v, l, w] = edges_[i];
            auto r = k;
            if (i + 1 < E && u == std::get<0>(edges_[i + 1]) && v == std::get<1>(edges_[i + 1])) {
                r = std::get<2>(edges_[++i]);
            }
            l += k;
            r += k;
            while (l < r) {
                if (l & 1) {
                    segment[l++].emplace_back(i);
                }
                if (r & 1) {
                    segment[--r].emplace_back(i);
                }
                l >>= 1;
                r >>= 1;
            }
        }
        PotentializedRollbackDSU<A> dsu(n_);
        auto dfs = [&](auto self, int node) -> void {
            auto count = 0;
            for (auto i : segment[node]) {
                auto &&[u, v, _, w] = edges_[i];
                count += dsu.merge(u, v, w);
            }
            if (node < k) {
                self(self, 2 * node);
                self(self, 2 * node + 1);
            } else {
                f(dsu, node - k);
            }
            dsu.rollback(count);
        };
        dfs(dfs, 1);
    }

private:
    int n_, timer_;
    std::vector<std::tuple<int, int, int, A>> edges_;
};

#endif // POTENTIALIZED_OFFLINE_DYNAMIC_CONNECTIVITY_HPP