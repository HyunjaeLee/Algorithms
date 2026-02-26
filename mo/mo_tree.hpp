#ifndef MO_TREE_HPP
#define MO_TREE_HPP

#include "mo/hilbert_mo.hpp"
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

struct MoTree {
    explicit MoTree(const std::vector<std::vector<int>> &adj)
        : n_(int(adj.size())), in_(n_), tour_(2 * n_), top_(n_), parent_(n_), mo_(2 * n_) {
        auto timer = 0;
        std::vector<int> size(n_, 1), heavy(n_, -1);
        auto dfs = [&](auto &&self, int u) -> void {
            for (auto v : adj[u]) {
                if (v != parent_[u]) {
                    parent_[v] = u;
                    self(self, v);
                    size[u] += size[v];
                    if (heavy[u] == -1 || size[heavy[u]] < size[v]) {
                        heavy[u] = v;
                    }
                }
            }
        };
        auto hld = [&](auto &&self, int u) -> void {
            in_[u] = timer;
            tour_[timer++] = u;
            for (auto v : adj[u]) {
                if (v != parent_[u]) {
                    top_[v] = (v == heavy[u]) ? top_[u] : v;
                    self(self, v);
                }
            }
            tour_[timer++] = u;
        };
        dfs(dfs, 0);
        hld(hld, 0);
    }
    int lca(int u, int v) const {
        assert(0 <= u && u < n_ && 0 <= v && v <= n_);
        while (top_[u] != top_[v]) {
            if (in_[top_[u]] < in_[top_[v]]) {
                std::swap(u, v);
            }
            u = parent_[top_[u]];
        }
        return (in_[u] < in_[v]) ? u : v;
    }
    void add(int u, int v) {
        assert(0 <= u && u < n_ && 0 <= v && v <= n_);
        lca_.push_back(lca(u, v));
        auto [l, r] = std::minmax(in_[u], in_[v]);
        mo_.add(l + 1, r + 1);
    }
    void solve(auto add, auto remove, auto eval) {
        std::vector<bool> contains(n_);
        auto toggle = [&](int i) {
            auto u = tour_[i];
            if (contains[u]) {
                remove(u);
            } else {
                add(u);
            }
            contains[u].flip();
        };
        auto eval_lca = [&](int i) {
            toggle(in_[lca_[i]]);
            eval(i);
            toggle(in_[lca_[i]]);
        };
        mo_.solve(toggle, toggle, eval_lca);
    }

private:
    int n_;
    std::vector<int> in_, tour_, top_, parent_, lca_;
    HilbertMo mo_;
};

#endif // MO_TREE_HPP