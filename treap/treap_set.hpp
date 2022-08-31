#ifndef TREAP_SET_HPP
#define TREAP_SET_HPP

#include <array>
#include <cassert>
#include <vector>

template <typename Key, typename Generator> struct treap_set {
    treap_set() = default;
    explicit treap_set(typename Generator::result_type seed) : gen_(seed) {}
    bool insert(const Key &key) {
        if (contains(key)) {
            return false;
        }
        auto [left, right] = split(root_, key);
        auto u = static_cast<int>(nodes_.size());
        nodes_.emplace_back(key, gen_());
        root_ = merge(merge(left, u), right);
        return true;
    }
    bool erase(const Key &key) {
        if (!contains(key)) {
            return false;
        }
        root_ = erase(root_, key);
        return true;
    }
    void reserve(int n) {
        nodes_.reserve(static_cast<std::vector<int>::size_type>(n));
    }
    const Key &find_by_order(int order) const {
        assert(0 <= order && order < size());
        auto u = find_by_order(root_, order);
        assert(~u);
        return nodes_[u].key;
    }
    int order_of_key(const Key &key) const { return order_of_key(root_, key); }
    bool contains(const Key &key) const { return ~find(root_, key); }
    int size() const { return size(root_); }
    template <typename Function> void for_each(Function f) const {
        for_each(root_, f);
    }

private:
    // for all x in left tree: x < key
    // for all x in right tree: x >= key
    std::array<int, 2> split(int u, const Key &key) {
        if (!~u) {
            return {-1, -1};
        }
        if (nodes_[u].key < key) {
            auto [left, right] = split(nodes_[u].children[1], key);
            nodes_[u].children[1] = left;
            return {update(u), right};
        } else {
            auto [left, right] = split(nodes_[u].children[0], key);
            nodes_[u].children[0] = right;
            return {left, update(u)};
        }
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
    int update(int u) {
        if (!~u) {
            return u;
        }
        nodes_[u].subtree_size = 1;
        for (auto v : nodes_[u].children) {
            if (~v) {
                nodes_[u].subtree_size += nodes_[v].subtree_size;
            }
        }
        return u;
    }
    int find(int u, const Key &key) const {
        while (~u) {
            if (nodes_[u].key < key) {
                u = nodes_[u].children[1];
            } else if (key < nodes_[u].key) {
                u = nodes_[u].children[0];
            } else {
                break;
            }
        }
        return u;
    }
    int erase(int u, const Key &key) {
        if (!~u) {
            return -1;
        }
        if (nodes_[u].key < key) {
            nodes_[u].children[1] = erase(nodes_[u].children[1], key);
            return update(u);
        } else if (key < nodes_[u].key) {
            nodes_[u].children[0] = erase(nodes_[u].children[0], key);
            return update(u);
        } else {
            return merge(nodes_[u].children[0], nodes_[u].children[1]);
        }
    }
    int find_by_order(int u, int order) const {
        while (~u) {
            if (size(nodes_[u].children[0]) < order) {
                order -= size(nodes_[u].children[0]) + 1;
                u = nodes_[u].children[1];
            } else if (order < size(nodes_[u].children[0])) {
                u = nodes_[u].children[0];
            } else {
                break;
            }
        }
        return u;
    }
    int order_of_key(int u, const Key &key) const {
        auto order = 0;
        while (~u) {
            if (nodes_[u].key < key) {
                order += size(nodes_[u].children[0]) + 1;
                u = nodes_[u].children[1];
            } else {
                u = nodes_[u].children[0];
            }
        }
        return order;
    }
    int size(int u) const { return ~u ? nodes_[u].subtree_size : 0; }
    template <typename Function> void for_each(int u, Function f) const {
        if (~u) {
            for_each(nodes_[u].children[0], f);
            f(nodes_[u].key);
            for_each(nodes_[u].children[1], f);
        }
    }
    struct node {
        node(const Key &key, typename Generator::result_type priority)
            : key(key), priority(priority) {}
        Key key;
        typename Generator::result_type priority;
        std::array<int, 2> children{-1, -1};
        int subtree_size = 1;
    };
    Generator gen_;
    std::vector<node> nodes_;
    int root_ = -1;
};

#endif // TREAP_SET_HPP
