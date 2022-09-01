#ifndef LAZY_IMPLICIT_TREAP
#define LAZY_IMPLICIT_TREAP

#include <array>
#include <cassert>
#include <initializer_list>
#include <utility>
#include <vector>

template <typename S, S (*op)(S, S), S (*e)(), typename F, S (*mapping)(F, S),
          F (*composition)(F, F), F (*id)(), typename Generator>
struct lazy_implicit_treap {
    lazy_implicit_treap() = default;
    explicit lazy_implicit_treap(typename Generator::result_type seed)
        : gen_(seed) {}
    // Split into [0, pos), [pos, inf)
    std::array<int, 2> split(int u, int pos) {
        if (!~u) {
            return {-1, -1};
        }
        push(u);
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
            push(u);
            nodes_[u].children[1] = merge(nodes_[u].children[1], v);
            return update(u);
        } else {
            push(v);
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
    int insert(int u, int pos, const S &value) {
        assert(0 <= pos && pos <= size(u));
        auto v = static_cast<int>(nodes_.size());
        nodes_.emplace_back(value, gen_());
        auto [left, right] = split(u, pos);
        return merge({left, v, right});
    }
    int push_back(int u, const S &value) {
        auto v = static_cast<int>(nodes_.size());
        nodes_.emplace_back(value, gen_());
        return merge(u, v);
    }
    int erase(int u, int pos) {
        assert(0 <= pos && pos < size(u));
        auto v = split(u, {pos, pos+1});
        return merge(v[0], v[2]);
    }
    S get(int u, int pos) {
        assert(~u && !~nodes_[u].parent);
        assert(0 <= pos && pos < size(u));
        while (~u) {
            push(u);
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
    int set(int u, int pos, S value) {
        assert(0 <= pos && pos < size(u));
        auto v = split(u, {pos, pos + 1});
        nodes_[v[1]].value = value;
        nodes_[v[1]].subtree_sum = value;
        return merge({v[0], v[1], v[2]});
    }
    int apply(int u, int pos, F f) { return apply(u, pos, pos + 1, f); }
    int apply(int u, int l, int r, F f) {
        assert(0 <= l && l <= r && r <= size(u));
        auto v = split(u, {l, r});
        all_apply(v[1], f);
        return merge({v[0], v[1], v[2]});
    }
    S all_prod(int u) const { return ~u ? nodes_[u].subtree_sum : e(); }
    std::pair<int, S> prod(int u, int l, int r) {
        auto v = split(u, {l, r});
        auto result = all_prod(v[1]);
        return {merge({v[0], v[1], v[2]}), result};
    }
    int reverse(int u) {
        if (~u) {
            nodes_[u].reversed ^= true;
        }
        return u;
    }
    int reverse(int u, int l, int r) {
        assert(0 <= l && l <= r && r <= size(u));
        auto v = split(u, {l, r});
        reverse(v[1]);
        return merge({v[0], v[1], v[2]});
    }
    void reserve(std::vector<int>::size_type n) { nodes_.reserve(n); }
    int size(int u) const { return ~u ? nodes_[u].subtree_size : 0; }
    template <typename Function> void for_each(int u, Function f) {
        if (~u) {
            push(u);
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
        nodes_[u].subtree_sum =
                ~nodes_[u].children[0]
                ? op(nodes_[nodes_[u].children[0]].subtree_sum, nodes_[u].value)
                : nodes_[u].value;
        nodes_[u].subtree_sum =
                ~nodes_[u].children[1]
                ? op(nodes_[u].subtree_sum, nodes_[nodes_[u].children[1]].subtree_sum)
                : nodes_[u].subtree_sum;
        return u;
    }
    void push(int u) {
        if (!~u) {
            return;
        }
        all_apply(nodes_[u].children[0], nodes_[u].lazy);
        all_apply(nodes_[u].children[1], nodes_[u].lazy);
        nodes_[u].lazy = id();
        if (nodes_[u].reversed) {
            for (auto v : nodes_[u].children) {
                if (~v) {
                    nodes_[v].reversed ^= true;
                }
            }
            std::swap(nodes_[u].children[0], nodes_[u].children[1]);
            nodes_[u].reversed = false;
        }
    }
    void all_apply(int u, F f) {
        if (~u) {
            nodes_[u].value = mapping(f, nodes_[u].value);
            nodes_[u].subtree_sum = mapping(f, nodes_[u].subtree_sum);
            nodes_[u].lazy = composition(f, nodes_[u].lazy);
        }
    }
    struct node {
        node(const S &value_, typename Generator::result_type priority_)
            : value(value_), subtree_sum(value_), priority(priority_) {}
        S value;
        S subtree_sum;
        F lazy = id();
        typename Generator::result_type priority;
        bool reversed = false;
        int parent = -1;
        int subtree_size = 1;
        std::array<int, 2> children{-1, -1};
    };
    Generator gen_;
    std::vector<node> nodes_;
};

#endif // LAZY_IMPLICIT_TREAP