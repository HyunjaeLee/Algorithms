#ifndef COMMUTATIVE_DUAL_SEGTREE_HPP
#define COMMUTATIVE_DUAL_SEGTREE_HPP

#include <bit>
#include <cassert>
#include <utility>
#include <vector>

// https://suisen-cp.github.io/cp-library-cpp/library/datastructure/segment_tree/commutative_dual_segment_tree.hpp
template <typename S, typename F, auto mapping, auto composition, auto id>
struct commutative_dual_segtree {
    commutative_dual_segtree() = default;
    commutative_dual_segtree(std::vector<S> &&a)
        : n(a.size()), m(std::bit_ceil(a.size())), data(std::move(a)), lazy(m, id()) {}
    commutative_dual_segtree(const std::vector<S> &a)
        : commutative_dual_segtree(std::vector<S>(a)) {}
    commutative_dual_segtree(int n, const S &fill_value)
        : commutative_dual_segtree(std::vector<S>(n, fill_value)) {}

    S get(int i) const {
        assert(0 <= i && i < n);
        S res = data[i];
        for (i = (i + m) >> 1; i; i >>= 1) {
            res = mapping(lazy[i], res);
        }
        return res;
    }
    S operator[](int i) const { return get(i); }
    void apply(int l, int r, const F &f) {
        assert(0 <= l && l <= r && r <= n);
        for (l += m, r += m; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                apply(l++, f);
            }
            if (r & 1) {
                apply(--r, f);
            }
        }
    }

private:
    void apply(int k, const F &f) {
        if (k < m) {
            lazy[k] = composition(f, lazy[k]);
        } else {
            data[k - m] = mapping(f, data[k - m]);
        }
    }

    int n, m;
    std::vector<S> data;
    std::vector<F> lazy;
};

#endif // COMMUTATIVE_DUAL_SEGTREE_HPP