#ifndef SPLAY_SET_HPP
#define SPLAY_SET_HPP

#include <functional>
#include <vector>

template <typename Key, typename Compare = std::less<Key>> struct splay_set {
    splay_set() : root_(-1), comp_(Compare()) {}
    bool insert(const Key &key) {
        if (!~root_) {
            root_ = new_node(key);
            return true;
        }
        auto u = root_, p = -1;
        while (~u) {
            if (comp_(key, key_[u])) {
                p = u;
                u = left_[u];
            } else if (comp_(key_[u], key)) {
                p = u;
                u = right_[u];
            } else {
                break;
            }
        }
        bool created = false;
        if (!~u) {
            created = true;
            u = new_node(key);
            parent_[u] = p;
            (comp_(key, key_[p]) ? left_[p] : right_[p]) = u;
        }
        splay(u);
        return created;
    }
    bool erase(const Key &key) {
        if (!~find(key)) {
            return false;
        }
        auto l = left_[root_];
        auto r = right_[root_];
        if (~l && ~r) {
            root_ = l;
            parent_[l] = -1;
            auto u = l;
            while (~right_[u]) {
                u = right_[u];
            }
            right_[u] = r;
            parent_[r] = u;
            update(u);
            splay(u);
        } else if (~l) {
            parent_[l] = -1;
            root_ = l;
        } else if (~r) {
            parent_[r] = -1;
            root_ = r;
        } else {
            root_ = -1;
        }
        return true;
    }
    bool contains(const Key &key) { return static_cast<bool>(~find(key)); }
    int size() const { return size(root_); }
    template <typename Function> void for_each(Function f) const {
        for_each(root_, f);
    }

private:
    void rotate(int u) {
        auto p = parent_[u];
        auto b = -1;
        if (u == left_[p]) {
            left_[p] = b = right_[u];
            right_[u] = p;
        } else {
            right_[p] = b = left_[u];
            left_[u] = p;
        }
        parent_[u] = parent_[p];
        parent_[p] = u;
        if (~b) {
            parent_[b] = p;
        }
        (~parent_[u]
             ? (p == left_[parent_[u]] ? left_[parent_[u]] : right_[parent_[u]])
             : root_) = u;
        update(p);
        update(u);
    }
    void splay(int u) {
        if (!~u) {
            return;
        }
        while (~parent_[u]) {
            auto p = parent_[u];
            auto g = parent_[p];
            if (~g) {
                rotate(((u == left_[p]) == (p == left_[g])) ? p : u);
            }
            rotate(u);
        }
        return;
    }
    void update(int u) {
        if (~u) {
            size_[u] = 1 + size(left_[u]) + size(right_[u]);
        }
    }
    int new_node(const Key &key) {
        auto u = static_cast<int>(key_.size());
        key_.push_back(key);
        size_.push_back(1);
        left_.push_back(-1);
        right_.push_back(-1);
        parent_.push_back(-1);
        return u;
    }
    int find(const Key &key) {
        auto u = root_, p = -1;
        while (~u) {
            if (comp_(key, key_[u])) {
                p = u;
                u = left_[u];
            } else if (comp_(key_[u], key)) {
                p = u;
                u = right_[u];
            } else {
                break;
            }
        }
        splay(~u ? u : p);
        return u;
    }
    template <typename Function> void for_each(int u, Function f) const {
        if (~u) {
            for_each(left_[u], f);
            f(key_[u]);
            for_each(right_[u], f);
        }
    }
    int size(int u) const { return ~u ? size_[u] : 0; }
    std::vector<Key> key_;
    std::vector<int> size_, left_, right_, parent_;
    int root_;
    Compare comp_;
};

#endif // SPLAY_SET_HPP