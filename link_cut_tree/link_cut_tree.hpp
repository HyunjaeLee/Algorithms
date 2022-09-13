#ifndef LINK_CUT_TREE_HPP
#define LINK_CUT_TREE_HPP

#include <cassert>
#include <type_traits>
#include <utility>
#include <vector>

template <typename S, typename Op, typename E, typename F, typename Mapping,
          typename Composition, typename Id>
struct link_cut_tree {
    link_cut_tree(int n, Op op, E e, Mapping mapping, Composition composition,
                  Id id)
        : op_(op), e_(e), mapping_(mapping), composition_(composition), id_(id),
          n_(n), left_(n, -1), right_(n, -1), parent_(n, -1), data_(n, e_()),
          sum_(n, e_()), lazy_(n, id_()), reversed_(n, false) {}
    int access(int u) {
        assert(0 <= u && u < n_);
        auto result = -1;
        for (auto cur = u; ~cur; cur = parent_[cur]) {
            splay(cur);
            right_[cur] = result;
            update(cur);
            result = cur;
        }
        splay(u);
        return result;
    }
    void make_root(int u) {
        assert(0 <= u && u < n_);
        access(u);
        reverse(u);
        push(u);
    }
    void link(int u, int p) {
        assert(0 <= u && u < n_ && 0 <= p && p < n_);
        make_root(u);
        access(p);
        parent_[u] = p;
        right_[p] = u;
        update(p);
    }
    void cut(int u) {
        assert(0 <= u && u < n_);
        access(u);
        auto p = left_[u];
        left_[u] = -1;
        update(u);
        parent_[p] = -1;
    }
    void cut(int u, int v) {
        assert(0 <= u && u < n_ && 0 <= v && v < n_);
        make_root(u);
        cut(v);
    }
    int lca(int u, int v) {
        assert(0 <= u && u < n_ && 0 <= v && v < n_);
        access(u);
        return access(v);
    }
    void set(int u, S x) {
        assert(0 <= u && u < n_);
        access(u);
        data_[u] = x;
        update(u);
    }
    S get(int u) {
        assert(0 <= u && u < n_);
        access(u);
        return data_[u];
    }
    void apply(int u, int v, F f) {
        assert(0 <= u && u < n_ && 0 <= v && v < n_);
        make_root(u);
        access(v);
        all_apply(v, f);
        push(v);
    }
    S prod(int u, int v) {
        assert(0 <= u && u < n_ && 0 <= v && v < n_);
        make_root(u);
        access(v);
        return sum_[v];
    }
    bool connected(int u, int v) {
        assert(0 <= u && u < n_ && 0 <= v && v < n_);
        access(u);
        access(v);
        return u == v || ~parent_[u];
    }

private:
    bool is_root(int u) const {
        auto p = parent_[u];
        return !~p || (left_[p] != u && right_[p] != u);
    }
    void update(int u) {
        if (~u) {
            sum_[u] = data_[u];
            if (auto v = left_[u]; ~v) {
                sum_[u] = op_(sum_[v], sum_[u]);
            }
            if (auto v = right_[u]; ~v) {
                sum_[u] = op_(sum_[u], sum_[v]);
            }
        }
    }
    void all_apply(int u, F f) {
        if (~u) {
            data_[u] = mapping_(f, data_[u]);
            sum_[u] = mapping_(f, sum_[u]);
            lazy_[u] = composition_(f, lazy_[u]);
        }
    }
    void reverse(int u) {
        if (~u) {
            std::swap(left_[u], right_[u]);
            reversed_[u] = !reversed_[u];
        }
    }
    void push(int u) {
        if (~u) {
            all_apply(left_[u], lazy_[u]);
            all_apply(right_[u], lazy_[u]);
            lazy_[u] = id_();
            if (reversed_[u]) {
                reverse(left_[u]);
                reverse(right_[u]);
                reversed_[u] = false;
            }
        }
    }
    void rotate_right(int u) {
        auto p = parent_[u];
        auto g = parent_[p];
        if (left_[p] = right_[u]; ~left_[p]) {
            parent_[right_[u]] = p;
        }
        right_[u] = p;
        parent_[p] = u;
        update(p);
        update(u);
        if (parent_[u] = g; ~parent_[u]) {
            if (left_[g] == p) {
                left_[g] = u;
            }
            if (right_[g] == p) {
                right_[g] = u;
            }
            update(g);
        }
    }
    void rotate_left(int u) {
        auto p = parent_[u];
        auto g = parent_[p];
        if (right_[p] = left_[u]; ~right_[p]) {
            parent_[left_[u]] = p;
        }
        left_[u] = p;
        parent_[p] = u;
        update(p);
        update(u);
        if (parent_[u] = g; ~parent_[u]) {
            if (left_[g] == p) {
                left_[g] = u;
            }
            if (right_[g] == p) {
                right_[g] = u;
            }
            update(g);
        }
    }
    void splay(int u) {
        push(u);
        while (!is_root(u)) {
            auto p = parent_[u];
            if (is_root(p)) {
                push(p);
                push(u);
                if (left_[p] == u) {
                    rotate_right(u);
                } else {
                    rotate_left(u);
                }
            } else {
                auto g = parent_[p];
                push(g);
                push(p);
                push(u);
                if (left_[g] == p) {
                    if (left_[p] == u) {
                        rotate_right(p);
                        rotate_right(u);
                    } else {
                        rotate_left(u);
                        rotate_right(u);
                    }
                } else {
                    if (right_[p] == u) {
                        rotate_left(p);
                        rotate_left(u);
                    } else {
                        rotate_right(u);
                        rotate_left(u);
                    }
                }
            }
        }
    }
    Op op_;
    E e_;
    Mapping mapping_;
    Composition composition_;
    Id id_;
    int n_;
    std::vector<int> left_, right_, parent_;
    std::vector<S> data_, sum_;
    std::vector<F> lazy_;
    std::vector<char> reversed_;
};

template <typename Op, typename E, typename Mapping, typename Composition,
          typename Id>
link_cut_tree(int n, Op op, E e, Mapping mapping, Composition composition,
              Id id)
    -> link_cut_tree<std::invoke_result_t<E>, Op, E, std::invoke_result_t<Id>,
                     Mapping, Composition, Id>;

#endif // LINK_CUT_TREE_HPP