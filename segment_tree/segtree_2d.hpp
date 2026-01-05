#ifndef SEGTREE_2D_HPP
#define SEGTREE_2D_HPP

#include <cassert>
#include <vector>

// S op(S, S) - commutative monoid operation
// S e() - commutative monoid identity
template <typename S, auto op, auto e> struct segtree_2d {
    // O(n * m)
    segtree_2d(int n, int m) : n_(n), m_(m), data_(n << 1, std::vector<S>(m << 1, e())) {}
    // O(n * m)
    segtree_2d(int n, int m, S x)
        : segtree_2d(std::vector<std::vector<S>>(n, std::vector<S>(m, x))) {}
    // O(n * m)
    segtree_2d(const std::vector<std::vector<S>> &a)
        : n_((int)a.size()), m_((int)a[0].size()),
          data_((n_ << 1), std::vector<S>((m_ << 1), e())) {
        for (auto i = 0; i < n_; ++i) {
            for (auto j = 0; j < m_; ++j) {
                data_[i + n_][j + m_] = a[i][j];
            }
        }
        for (auto i = n_ - 1; i >= 1; --i) {
            for (auto j = 0; j < m_; ++j) {
                data_[i][j + m_] = op(data_[i << 1][j + m_], data_[i << 1 | 1][j + m_]);
            }
        }
        for (auto i = 1; i < (n_ << 1); ++i) {
            for (auto j = m_ - 1; 0 < j; --j) {
                data_[i][j] = op(data_[i][j << 1], data_[i][j << 1 | 1]);
            }
        }
    }
    // a[r][c] := x
    // O(log(n) * log(m))
    void set(int r, int c, S x) {
        assert(0 <= r && r < n_);
        assert(0 <= c && c < m_);
        data_[r += n_][c += m_] = x;
        for (auto j = c; j >>= 1;) {
            data_[r][j] = op(data_[r][j << 1], data_[r][j << 1 | 1]);
        }
        for (auto i = r; i >>= 1;) {
            data_[i][c] = op(data_[i << 1][c], data_[i << 1 | 1][c]);
            for (auto j = c; j >>= 1;) {
                data_[i][j] = op(data_[i][j << 1], data_[i][j << 1 | 1]);
            }
        }
    }
    // Returns a[r][c]
    // O(1)
    S get(int r, int c) {
        assert(0 <= r && r < n_);
        assert(0 <= c && c < m_);
        return data_[r + n_][c + m_];
    }
    // Returns the sum of a[i][j] on [r1, r2) X [c1, c2)
    // O(log n * log m)
    S prod(int r1, int r2, int c1, int c2) {
        assert(0 <= r1 && r1 <= r2 && r2 <= n_);
        assert(0 <= c1 && c1 <= c2 && c2 <= m_);
        if (r1 >= r2 || c1 >= c2)
            return e();
        S res = e();
        r1 += n_, r2 += n_, c1 += m_, c2 += m_;
        for (auto il = r1, ir = r2; il < ir; il >>= 1, ir >>= 1) {
            if (il & 1) {
                for (auto jl = c1, jr = c2; jl < jr; jl >>= 1, jr >>= 1) {
                    if (jl & 1) {
                        res = op(res, data_[il][jl++]);
                    }
                    if (jr & 1) {
                        res = op(res, data_[il][--jr]);
                    }
                }
                ++il;
            }
            if (ir & 1) {
                --ir;
                for (auto jl = c1, jr = c2; jl < jr; jl >>= 1, jr >>= 1) {
                    if (jl & 1) {
                        res = op(res, data_[ir][jl++]);
                    }
                    if (jr & 1) {
                        res = op(res, data_[ir][--jr]);
                    }
                }
            }
        }
        return res;
    }
    int n_, m_;
    std::vector<std::vector<S>> data_;
};

#endif // SEGTREE_2D_HPP