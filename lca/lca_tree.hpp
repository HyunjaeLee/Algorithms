#ifndef LCA_TREE_HPP
#define LCA_TREE_HPP

#include <algorithm>
#include <bit>
#include <cassert>
#include <queue>
#include <vector>

struct lca_tree {
    lca_tree(const std::vector<std::vector<int>> &adj, int root)
        : n_(static_cast<int>(adj.size())), root_(root),
          lg_(std::bit_width(static_cast<unsigned>(n_)) - 1),
          table_((lg_ + 1) * n_), depth_(n_) {
        depth_[root_] = 0;
        table_[root_] = root_;
        std::queue<int> q;
        q.emplace(root_);
        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            for (auto v : adj[u]) {
                if (v != table_[u]) {
                    depth_[v] = depth_[u] + 1;
                    table_[v] = u;
                    q.emplace(v);
                }
            }
        }
        for (auto i = 1; i <= lg_; ++i) {
            for (auto u = 0; u < n_; ++u) {
                auto parent = table_[(i - 1) * n_ + u];
                table_[i * n_ + u] = table_[(i - 1) * n_ + parent];
            }
        }
    }
    int kth_parent(int u, int k) const {
        assert(0 <= u && u < n_ && 0 <= k);
        for (auto i = 0; i <= lg_; ++i) {
            if ((k >> i) & 1) {
                u = table_[i * n_ + u];
            }
        }
        return u;
    }
    int lca(int u, int v) const {
        assert(0 <= u && u < n_ && 0 <= v && v < n_);
        if (depth_[u] < depth_[v]) {
            std::swap(u, v);
        }
        u = kth_parent(u, depth_[u] - depth_[v]);
        if (u == v) {
            return u;
        }
        for (auto i = lg_; i >= 0; i--) {
            if (table_[i * n_ + u] != table_[i * n_ + v]) {
                u = table_[i * n_ + u];
                v = table_[i * n_ + v];
            }
        }
        return table_[u];
    }
    int distance(int u, int v) const {
        assert(0 <= u && u < n_ && 0 <= v && v < n_);
        return depth_[u] + depth_[v] - 2 * depth_[lca(u, v)];
    }
    int jump(int u, int v, int k) const {
        assert(0 <= u && u < n_ && 0 <= v && v < n_ && 0 <= k);
        auto l = lca(u, v);
        auto ul = depth_[u] - depth_[l];
        auto vl = depth_[v] - depth_[l];
        if (ul + vl < k) {
            return -1;
        }
        if (k <= ul) {
            return kth_parent(u, k);
        } else {
            return kth_parent(v, ul + vl - k);
        }
    }
    const int n_, root_, lg_;
    std::vector<int> table_, depth_;
};

#endif // LCA_TREE_HPP
