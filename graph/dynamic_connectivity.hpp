#ifndef DYNAMIC_CONNECTIVITY_HPP
#define DYNAMIC_CONNECTIVITY_HPP

#include "../random/xoshiro256starstar.hpp"
#include <array>
#include <cassert>
#include <chrono>
#include <cstdint>
#include <initializer_list>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

template <typename Generator = xoshiro256starstar> struct treap {
    treap()
        : gen_(static_cast<typename Generator::result_type>(
              std::chrono::steady_clock::now().time_since_epoch().count())) {}
    std::array<int, 2> split(int u, int dir) {
        assert(~u);
        std::array<int, 2> result{-1, -1};
        result[dir] = update(nodes_[u].children[dir]);
        while (true) {
            auto p = nodes_[u].parent;
            nodes_[u].children[dir] = result[dir ^ 1];
            result[dir ^ 1] = update(u);
            if (!~p) {
                break;
            }
            dir = static_cast<int>(nodes_[p].children[1] == u);
            u = p;
        }
        return result;
    }
    int merge(int u, int v) {
        if (!~u || !~v) {
            return ~u ? u : v;
        }
        if (nodes_[u].priority < nodes_[v].priority) {
            nodes_[u].children[1] = merge(nodes_[u].children[1], v);
            return update(u);
        } else {
            nodes_[v].children[0] = merge(u, nodes_[v].children[0]);
            return update(v);
        }
    }
    int merge(std::initializer_list<int> ilist) {
        auto u = -1;
        for (auto v : ilist) {
            u = merge(u, v);
        }
        return u;
    }
    bool same(int u, int v) const { return get_root(u) == get_root(v); }
    void mark(int u, int idx, bool val) {
        assert(~u);
        nodes_[u].mark[idx] = val;
        while (~u) {
            auto p = nodes_[u].parent;
            update(u);
            u = p;
        }
    }
    int get_marked(int u, int idx) const {
        assert(~u);
        u = get_root(u);
        if (!nodes_[u].subtree_mark[idx]) {
            return -1;
        }
        while (!nodes_[u].mark[idx]) {
            for (auto v : nodes_[u].children) {
                if (~v && nodes_[v].subtree_mark[idx]) {
                    u = v;
                    break;
                }
            }
        }
        return u;
    }
    int new_node() {
        auto u = static_cast<int>(nodes_.size());
        nodes_.emplace_back(gen_());
        return u;
    }
    int get_root(int u) const {
        assert(~u);
        while (~nodes_[u].parent) {
            u = nodes_[u].parent;
        }
        return u;
    }
    int size(int u) const { return ~u ? nodes_[u].size : 0; }
    void reserve(int n) { nodes_.reserve(n); }

private:
    int update(int u) {
        if (~u) {
            nodes_[u].parent = -1;
            nodes_[u].size = 1;
            nodes_[u].subtree_mark = nodes_[u].mark;
            for (auto v : nodes_[u].children) {
                if (~v) {
                    nodes_[v].parent = u;
                    nodes_[u].size += nodes_[v].size;
                    for (auto i = 0; i < 2; ++i) {
                        nodes_[u].subtree_mark[i] |= nodes_[v].subtree_mark[i];
                    }
                }
            }
        }
        return u;
    }
    struct node {
        node(typename Generator::result_type priority) : priority(priority) {}
        typename Generator::result_type priority;
        int parent = -1, size = 1;
        std::array<int, 2> children{-1, -1};
        std::array<bool, 2> mark{}, subtree_mark{};
    };
    Generator gen_;
    std::vector<node> nodes_;
};

struct pair_hash {
    std::size_t operator()(std::pair<int, int> x) const {
        static const std::uint64_t fixed_random =
            std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x.first + fixed_random)() ^
               (splitmix64(x.second + fixed_random)() >> 1);
    }
};

struct int_hash {
    std::size_t operator()(int x) const {
        static const std::uint64_t fixed_random =
            std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + fixed_random)();
    }
};

struct euler_tour_tree {
    euler_tour_tree(int n) : n_(n) {
        treap_.reserve(3 * n_);
        edges_.reserve(2 * n_);
        edge_data_.reserve(2 * n_);
        for (auto i = 0; i < n_; ++i) {
            treap_.new_node();
        }
    }
    bool connected(int u, int v) const { return treap_.same(u, v); }
    void link(int u, int v) {
        auto uv = treap_.new_node();
        edges_[{u, v}] = uv;
        edge_data_.push_back({u, v});
        auto vu = treap_.new_node();
        edges_[{v, u}] = vu;
        edge_data_.push_back({v, u});
        auto [u1, u2] = treap_.split(u, 1);
        auto [v1, v2] = treap_.split(v, 1);
        treap_.merge({u2, u1, uv, v2, v1, vu});
    }
    void cut(int u, int v) {
        auto uv_it = edges_.find({u, v});
        auto vu_it = edges_.find({v, u});
        auto uv = uv_it->second;
        auto vu = vu_it->second;
        auto uv_left = treap_.split(uv, 0)[0];
        bool is_uv_before_vu = treap_.same(uv, vu);
        auto uv_right = treap_.split(uv, 1)[1];
        auto vu_left = treap_.split(vu, 0)[0];
        auto vu_right = treap_.split(vu, 1)[1];
        if (is_uv_before_vu) {
            treap_.merge(uv_left, vu_right);
        } else {
            treap_.merge(vu_left, uv_right);
        }
        edges_.erase(uv_it);
        edges_.erase(vu_it);
    }
    void mark_node(int u, bool mark) { treap_.mark(u, 0, mark); }
    void mark_edge(int u, int v, bool mark) {
        auto uv = edges_[{u, v}];
        treap_.mark(uv, 1, mark);
        auto vu = edges_[{v, u}];
        treap_.mark(vu, 1, mark);
    }
    int get_marked_node(int u) const { return treap_.get_marked(u, 0); }
    std::pair<int, int> get_marked_edge(int u) const {
        auto edge = treap_.get_marked(u, 1);
        return ~edge ? edge_data_[edge - n_] : std::pair(-1, -1);
    }
    int tree_size(int u) const {
        u = treap_.get_root(u);
        return treap_.size(u);
    }

private:
    int n_;
    treap<> treap_;
    std::unordered_map<std::pair<int, int>, int, pair_hash> edges_;
    std::vector<std::pair<int, int>> edge_data_;
};

struct dynamic_connectivity {
    dynamic_connectivity(int n)
        : n_(n), log_(std::__lg(n_) + 1),
          spanning_forest_(log_, euler_tour_tree(n_)),
          nontree_adj_(log_,
                       std::vector<std::unordered_set<int, int_hash>>(n_)) {
        edge_level_.reserve(n_);
        is_tree_edge_.reserve(n_);
    }
    bool connected(int u, int v) const {
        return spanning_forest_[0].connected(u, v);
    }
    void link(int u, int v) {
        edge_level(u, v) = 0;
        if (connected(u, v)) {
            is_tree_edge(u, v) = false;
            add_edge_to_adj(u, v, 0);
        } else {
            is_tree_edge(u, v) = true;
            spanning_forest_[0].link(u, v);
            spanning_forest_[0].mark_edge(u, v, true);
        }
    }
    void cut(int u, int v) {
        auto level = edge_level(u, v);
        if (is_tree_edge(u, v)) {
            for (auto i = level; i >= 0; --i) {
                spanning_forest_[i].cut(u, v);
            }
            replace(u, v, level);
        } else {
            delete_edge_from_adj(u, v, level);
        }
    }

private:
    void replace(int u, int v, int level) {
        if (spanning_forest_[level].tree_size(u) >
            spanning_forest_[level].tree_size(v)) {
            std::swap(u, v);
        }
        for (auto [x, y] = spanning_forest_[level].get_marked_edge(u); ~x;
             std::tie(x, y) = spanning_forest_[level].get_marked_edge(u)) {
            ++edge_level(x, y);
            spanning_forest_[level].mark_edge(x, y, false);
            spanning_forest_[level + 1].link(x, y);
            spanning_forest_[level + 1].mark_edge(x, y, true);
        }
        for (auto x = spanning_forest_[level].get_marked_node(u); ~x;
             x = spanning_forest_[level].get_marked_node(u)) {
            while (!nontree_adj_[level][x].empty()) {
                auto y = *nontree_adj_[level][x].begin();
                if (spanning_forest_[level].connected(x, y)) {
                    ++edge_level(x, y);
                    delete_edge_from_adj(x, y, level);
                    add_edge_to_adj(x, y, level + 1);
                } else {
                    is_tree_edge(x, y) = true;
                    delete_edge_from_adj(x, y, level);
                    for (auto i = level; i >= 0; --i) {
                        spanning_forest_[i].link(x, y);
                    }
                    spanning_forest_[level].mark_edge(x, y, true);
                    return;
                }
            }
        }
        if (level > 0) {
            replace(u, v, level - 1);
        }
    }
    void add_edge_to_adj(int u, int v, int level) {
        if (nontree_adj_[level][u].empty()) {
            spanning_forest_[level].mark_node(u, true);
        }
        nontree_adj_[level][u].insert(v);
        if (nontree_adj_[level][v].empty()) {
            spanning_forest_[level].mark_node(v, true);
        }
        nontree_adj_[level][v].insert(u);
    }
    void delete_edge_from_adj(int u, int v, int level) {
        nontree_adj_[level][u].erase(v);
        if (nontree_adj_[level][u].empty()) {
            spanning_forest_[level].mark_node(u, false);
        }
        nontree_adj_[level][v].erase(u);
        if (nontree_adj_[level][v].empty()) {
            spanning_forest_[level].mark_node(v, false);
        }
    }
    int &edge_level(int u, int v) {
        if (u > v) {
            std::swap(u, v);
        }
        return edge_level_[{u, v}];
    }
    bool &is_tree_edge(int u, int v) {
        if (u > v) {
            std::swap(u, v);
        }
        return is_tree_edge_[{u, v}];
    }
    int n_, log_;
    std::vector<euler_tour_tree> spanning_forest_;
    std::vector<std::vector<std::unordered_set<int, int_hash>>> nontree_adj_;
    std::unordered_map<std::pair<int, int>, int, pair_hash> edge_level_;
    std::unordered_map<std::pair<int, int>, bool, pair_hash> is_tree_edge_;
};

#endif // DYNAMIC_CONNECTIVITY_HPP