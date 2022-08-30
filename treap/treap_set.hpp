#ifndef TREAP_SET_HPP
#define TREAP_SET_HPP

#include <array>
#include <vector>

template <typename T, typename Generator> struct treap_set {
    bool insert(T key) {
        if (contains(key)) {
            return false;
        }
        auto [left, right] = split(root_, key);
        auto u = static_cast<int>(nodes_.size());
        nodes_.emplace_back(key, gen_());
        root_ = merge(merge(left, u), right);
        return true;
    }
    bool erase(T key) {
        if (!contains(key)) {
            return false;
        }
        root_ = erase(root_, key);
        return true;
    }
    void reserve(int n) {
        nodes_.reserve(static_cast<std::vector<int>::size_type>(n));
    }
    // T find_by_order(int order) const {
    //     assert(0 <= order && order < size());

    // }
    int order_of_key(T key) const {
        return order_of_key(root_, key);
    }
    bool contains(T key) const { return ~find(root_, key); }
    int size() const { return size(root_); }
    template <typename Function> void for_each(Function f) const {
        for_each(root_, f);
    }

private:
    // for all x in left tree: x < key
    // for all x in right tree: x >= key
    std::array<int, 2> split(int u, T key) {
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
    int find(int u, T key) const {
        if (!~u) {
            return -1;
        }
        if (nodes_[u].key < key) {
            return find(nodes_[u].children[1], key);
        } else if (key < nodes_[u].key) {
            return find(nodes_[u].children[0], key);
        } else {
            return u;
        }
    }
    int erase(int u, T key) {
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
    int order_of_key(int u, T key) const {
        if (!~u) {
            return 0;
        }
        if (nodes_[u].key < key) {
            return size(nodes_[u].children[0]) + 1 + order_of_key(nodes_[u].children[1], key);
        } else {
            return order_of_key(nodes_[u].children[0], key);
        }
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
        node(T key, typename Generator::result_type priority)
            : key(key), priority(priority) {}
        T key;
        typename Generator::result_type priority;
        std::array<int, 2> children{-1, -1};
        int subtree_size = 1;
    };
    Generator gen_;
    std::vector<node> nodes_;
    int root_ = -1;
};

#endif // TREAP_SET_HPP
