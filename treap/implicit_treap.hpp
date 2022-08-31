#ifndef IMPLICIT_TREAP_HPP
#define IMPLICIT_TREAP_HPP

#include <array>
#include <cassert>
#include <initializer_list>
#include <vector>

template <typename T, typename Generator> struct implicit_treap {
    implicit_treap() = default;
    explicit implicit_treap(typename Generator::result_type seed)
        : gen_(seed) {}
    // Split into [0, pos), [pos, inf)
    std::array<int, 2> split(int u, int pos) {
        if (!~u) {
            return {-1, -1};
        }
        if (size(nodes_[u].children[0]) < pos) {
            auto [left, right] = split(nodes_[u].children[1],
                                       pos - size(nodes_[u].children[0]) - 1);
            nodes_[u].children[1] = left;
            return {update(u), right};
        } else {
            auto [left, right] = split(nodes_[u].children[0], pos);
            nodes_[u].children[0] = right;
            return {left, update(u)};
        }
    }
    // Split into [0, pos[0]), [pos[0], pos[1]),
    // ..., [pos[n-2], pos[n-1]), [pos[n-1], inf)
    std::vector<int> split(int u, std::initializer_list<int> ilist) {
        auto n = static_cast<int>(ilist.size());
        assert(n > 0);
        assert(~u);
        std::vector<int> result(n + 1), pos(ilist);
        result[0] = u;
        for (auto i = n - 1; i >= 1; --i) {
            pos[i] -= pos[i - 1];
        }
        for (auto i = 0; i < n; ++i) {
            auto [left, right] = split(result[i], pos[i]);
            result[i] = left;
            result[i + 1] = right;
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
    // Inserts value before pos
    int insert(int u, int pos, const T &value) {
        assert(0 <= pos && pos <= size(u));
        auto v = static_cast<int>(nodes_.size());
        nodes_.emplace_back(value, gen_());
        auto [left, right] = split(u, pos);
        return merge({left, v, right});
    }
    int push_back(int u, const T &value) {
        auto v = static_cast<int>(nodes_.size());
        nodes_.emplace_back(value, gen_());
        return merge(u, v);
    }
    T &get(int u, int pos) {
        assert(!~nodes_[u].parent);
        assert(0 <= pos && pos < size(u));
        while (~u) {
            if (size(nodes_[u].children[0]) < pos) {
                pos -= size(nodes_[u].children[0]) + 1;
                u = nodes_[u].children[1];
            } else if (pos < size(nodes_[u].children[0])) {
                u = nodes_[u].children[0];
            } else {
                break;
            }
        }
        assert(~u);
        return nodes_[u].value;
    }
    void reserve(std::vector<int>::size_type n) { nodes_.reserve(n); }
    int size(int u) const { return ~u ? nodes_[u].subtree_size : 0; }
    template <typename Function> void for_each(int u, Function f) const {
        if (~u) {
            for_each(nodes_[u].children[0], f);
            f(nodes_[u].value);
            for_each(nodes_[u].children[1], f);
        }
    }

private:
    int update(int u) {
        if (!~u) {
            return u;
        }
        nodes_[u].parent = -1;
        nodes_[u].subtree_size = 1;
        for (auto v : nodes_[u].children) {
            if (~v) {
                nodes_[v].parent = u;
                nodes_[u].subtree_size += nodes_[v].subtree_size;
            }
        }
        return u;
    }
    struct node {
        node(const T &value, typename Generator::result_type priority)
            : value(value), priority(priority) {}
        T value;
        typename Generator::result_type priority;
        int parent = -1;
        int subtree_size = 1;
        std::array<int, 2> children{-1, -1};
    };
    Generator gen_;
    std::vector<node> nodes_;
};

#endif // IMPLICIT_TREAP_HPP
