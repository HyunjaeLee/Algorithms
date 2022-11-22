#ifndef DOMINATOR_TREE_HPP
#define DOMINATOR_TREE_HPP

#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>

struct dominator_tree {
    explicit dominator_tree(int n)
        : n_(n), parent_(n), idom_(n, -1), sdom_(n, -1), dsu_(n), label_(n),
          graph_(n), rev_graph_(n) {
        order_.reserve(n);
        std::iota(dsu_.begin(), dsu_.end(), 0);
        std::iota(label_.begin(), label_.end(), 0);
    }
    void add_edge(int from, int to) {
        assert(0 <= from && from < n_ && 0 <= to && to < n_);
        graph_[from].push_back(to);
        rev_graph_[to].push_back(from);
    }
    void run(int root) {
        assert(0 <= root && root < n_);
        dfs(root);
        std::vector<std::vector<int>> bucket(n_);
        std::vector<int> x(n_);
        for (auto i = static_cast<int>(order_.size()) - 1; i >= 0; --i) {
            auto u = order_[i];
            for (auto v : rev_graph_[u]) {
                if (~sdom_[v]) {
                    sdom_[u] = std::min(sdom_[u], sdom_[eval(v)]);
                }
            }
            bucket[order_[sdom_[u]]].push_back(u);
            for (auto v : bucket[parent_[u]]) {
                x[v] = eval(v);
            }
            bucket[parent_[u]].clear();
            link(parent_[u], u);
        }
        for (auto i = 1; i < static_cast<int>(order_.size()); ++i) {
            auto u = order_[i], v = x[u];
            idom_[u] = (sdom_[u] == sdom_[v] ? sdom_[u] : idom_[v]);
        }
        for (auto i = 1; i < static_cast<int>(order_.size()); ++i) {
            auto u = order_[i];
            idom_[u] = order_[idom_[u]];
        }
        idom_[root] = root;
    }
    int operator[](int u) const {
        assert(0 <= u && u < n_);
        return idom_[u];
    }

private:
    void dfs(int u) {
        sdom_[u] = static_cast<int>(order_.size());
        order_.push_back(u);
        for (auto v : graph_[u]) {
            if (!~sdom_[v]) {
                parent_[v] = u;
                dfs(v);
            }
        }
    }
    int find(int u) {
        if (dsu_[u] == u) {
            return u;
        }
        auto root = find(dsu_[u]);
        if (sdom_[label_[u]] > sdom_[label_[dsu_[u]]]) {
            label_[u] = label_[dsu_[u]];
        }
        return dsu_[u] = root;
    }
    int eval(int u) {
        find(u);
        return label_[u];
    }
    void link(int u, int v) { dsu_[v] = u; }
    int n_;
    std::vector<int> order_, parent_, idom_, sdom_, dsu_, label_;
    std::vector<std::vector<int>> graph_, rev_graph_;
};

#endif // DOMINATOR_TREE_HPP