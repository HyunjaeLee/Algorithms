#ifndef SEGTREE_BEATS_HPP
#define SEGTREE_BEATS_HPP

#include <algorithm>
#include <cassert>
#include <tuple>
#include <vector>

template <typename S, typename Op, typename E, typename F, typename Mapping,
          typename Composition, typename Id>
struct segtree_beats {
    segtree_beats(const std::vector<S> &data, Op op, E e, Mapping mapping,
                  Composition composition, Id id)
        : op_(op), e_(e), mapping_(mapping), composition_(composition), id_(id),
          n_(static_cast<int>(data.size())),
          log_(std::__lg(std::max(n_ - 1, 1)) + 1), size_(1 << log_),
          data_(2 * size_, e_()), lazy_(size_, id_()) {
        for (auto i = 0; i < n_; ++i) {
            data_[size_ + i] = data[i];
        }
        for (auto i = size_ - 1; i >= 1; --i) {
            update(i);
        }
    }
    void set(int pos, S x) {
        assert(0 <= pos && pos < n_);
        pos += size_;
        for (auto i = log_; i >= 1; --i) {
            push(pos >> i);
        }
        data_[pos] = x;
        for (auto i = 1; i <= log_; ++i) {
            update(pos >> i);
        }
    }
    S get(int pos) {
        assert(0 <= pos && pos < n_);
        pos += size_;
        for (auto i = log_; i >= 1; --i) {
            push(pos >> i);
        }
        return data_[pos];
    }
    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= n_);
        if (l == r)
            return e_();
        l += size_;
        r += size_;
        for (auto i = log_; i >= 1; --i) {
            if (((l >> i) << i) != l) {
                push(l >> i);
            }
            if (((r >> i) << i) != r) {
                push((r - 1) >> i);
            }
        }
        S sml = e_(), smr = e_();
        while (l < r) {
            if (l & 1) {
                sml = op_(sml, data_[l++]);
            }
            if (r & 1) {
                smr = op_(data_[--r], smr);
            }
            l >>= 1;
            r >>= 1;
        }
        return op_(sml, smr);
    }
    S all_prod() { return data_[1]; }
    void apply(int pos, F f) {
        assert(0 <= pos && pos < n_);
        pos += size_;
        for (auto i = log_; i >= 1; --i) {
            push(pos >> i);
        }
        auto ok = false;
        std::tie(data_[pos], ok) = mapping(f, data_[pos]);
        assert(ok);
        for (auto i = 1; i <= log_; ++i) {
            update(pos >> i);
        }
    }
    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= n_);
        if (l == r) {
            return;
        }
        l += size_;
        r += size_;
        for (auto i = log_; i >= 1; --i) {
            if (((l >> i) << i) != l) {
                push(l >> i);
            }
            if (((r >> i) << i) != r) {
                push((r - 1) >> i);
            }
        }
        int l2 = l, r2 = r;
        while (l < r) {
            if (l & 1) {
                all_apply(l++, f);
            }
            if (r & 1) {
                all_apply(--r, f);
            }
            l >>= 1;
            r >>= 1;
        }
        l = l2;
        r = r2;
        for (auto i = 1; i <= log_; ++i) {
            if (((l >> i) << i) != l) {
                update(l >> i);
            }
            if (((r >> i) << i) != r) {
                update((r - 1) >> i);
            }
        }
    }

private:
    void update(int node) {
        data_[node] = op_(data_[2 * node], data_[2 * node + 1]);
    }
    void all_apply(int node, F f) {
        auto ok = false;
        std::tie(data_[node], ok) = mapping_(f, data_[node]);
        if (node < size_) {
            lazy_[node] = composition_(f, lazy_[node]);
            if (!ok) {
                push(node);
                update(node);
            }
        }
    }
    void push(int node) {
        all_apply(2 * node, lazy_[node]);
        all_apply(2 * node + 1, lazy_[node]);
        lazy_[node] = id_();
    }
    Op op_;
    E e_;
    Mapping mapping_;
    Composition composition_;
    Id id_;
    const int n_, log_, size_;
    std::vector<S> data_;
    std::vector<F> lazy_;
};

template <typename S, typename Op, typename E, typename Mapping,
          typename Composition, typename Id>
segtree_beats(const std::vector<S> &data, Op op, E e, Mapping mapping,
              Composition composition, Id id)
    -> segtree_beats<S, Op, E, std::invoke_result_t<Id>, Mapping, Composition,
                     Id>;

#endif // SEGTREE_BEATS_HPP