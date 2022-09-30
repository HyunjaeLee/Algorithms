#ifndef ROLLBACK_DISJOINT_SET_HPP
#define ROLLBACK_DISJOINT_SET_HPP

#include <cassert>
#include <stack>
#include <utility>
#include <vector>

struct rollback_disjoint_set {
    explicit rollback_disjoint_set(int n) : n_(n), parent_or_size_(n, -1) {}
    int find(int u) const {
        return parent_or_size_[u] < 0 ? u : find(parent_or_size_[u]);
    }
    bool merge(int u, int v) {
        assert(0 <= u && u < n_ && 0 <= v && v < n_);
        u = find(u);
        v = find(v);
        if (u == v) {
            return false;
        }
        if (-parent_or_size_[u] < -parent_or_size_[v]) {
            std::swap(u, v);
        }
        history_.emplace(v, parent_or_size_[v]);
        parent_or_size_[u] += parent_or_size_[v];
        parent_or_size_[v] = u;
        return true;
    }
    bool same(int u, int v) const {
        assert(0 <= u && u < n_ && 0 <= v && v < n_);
        return find(u) == find(v);
    }
    int size(int u) const {
        assert(0 <= u && u < n_);
        return -parent_or_size_[find(u)];
    }
    void rollback() {
        assert(!history_.empty());
        auto [v, val] = history_.top();
        auto u = parent_or_size_[v];
        parent_or_size_[v] = val;
        parent_or_size_[u] -= val;
        history_.pop();
    }
    void rollback(int count) {
        for (auto i = 0; i < count; ++i) {
            rollback();
        }
    }

private:
    int n_;
    std::vector<int> parent_or_size_;
    std::stack<std::pair<int, int>> history_;
};

#endif // ROLLBACK_DISJOINT_SET_HPP