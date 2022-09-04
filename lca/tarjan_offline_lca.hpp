#ifndef TARJAN_OFFLINE_LCA_HPP
#define TARJAN_OFFLINE_LCA_HPP

#include <utility>
#include <vector>

struct dsu {
    dsu(int n) : parent_or_size(n, -1) {}
    int find(int u) {
        return parent_or_size[u] < 0
                   ? u
                   : parent_or_size[u] = find(parent_or_size[u]);
    }
    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u != v) {
            if (-parent_or_size[u] < -parent_or_size[v]) {
                std::swap(u, v);
            }
            parent_or_size[u] += parent_or_size[v];
            parent_or_size[v] = u;
        }
    }

private:
    std::vector<int> parent_or_size;
};

struct tarjan_offline_lca {
    tarjan_offline_lca(const std::vector<std::vector<int>> &graph, int root,
                       const std::vector<std::pair<int, int>> &queries)
        : graph_(graph), root_(root), queries_(graph.size()),
          result_(queries.size()), ancestor_(graph.size()), color_(graph.size()),
          d_(graph.size()) {
        auto q = static_cast<int>(queries.size());
        for (auto i = 0; i < q; ++i) {
            auto [u, v] = queries[i];
            queries_[u].push_back({v, i});
            queries_[v].push_back({u, i});
        }
    }
    std::vector<int> lca() {
        lca(root_, root_);
        return result_;
    }

private:
    void lca(int u, int parent) {
        ancestor_[d_.find(u)] = u;
        for (auto v : graph_[u])
            if (v != parent) {
                lca(v, u);
                d_.merge(u, v);
                ancestor_[d_.find(u)] = u;
            }
        color_[u] = 1;
        for (auto [v, i] : queries_[u]) {
            if (color_[v]) {
                result_[i] = ancestor_[d_.find(v)];
            }
        }
    }
    std::vector<std::vector<int>> graph_;
    int root_;
    std::vector<std::vector<std::pair<int, int>>> queries_;
    std::vector<int> result_, ancestor_;
    std::vector<char> color_;
    dsu d_;
};

#endif // TARJAN_OFFLINE_LCA_HPP
