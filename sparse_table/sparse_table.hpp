#ifndef SPARSE_TABLE_HPP
#define SPARSE_TABLE_HPP

#include <bit>
#include <cassert>
#include <type_traits>
#include <vector>

template <typename S, auto op, auto e> struct sparse_table {
    static_assert(std::is_invocable_r_v<S, decltype(op), S, S>,
                  "op must be a function of type S(S, S)");
    static_assert(std::is_invocable_r_v<S, decltype(e)>,
                  "e must be a function of type S()");
    sparse_table(const std::vector<S> &v)
        : n_((int)v.size()), width_(std::bit_width(v.size())),
          table_(width_, std::vector<S>(v.size())) {
        table_[0] = v;
        for (auto i = 1; i < width_; ++i) {
            for (auto j = 0; j + (1 << i) <= n_; ++j) {
                table_[i][j] =
                    op(table_[i - 1][j], table_[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= n_);
        auto sum = e();
        for (auto i = width_ - 1; 0 <= i; --i) {
            if ((1 << i) <= r - l) {
                sum = op(sum, table_[i][l]);
                l += (1 << i);
            }
        }
        return sum;
    }
    S prod_idempotent(int l, int r) {
        assert(0 <= l && l <= r && r <= n_);
        if (l == r) {
            return e();
        }
        auto i = std::bit_width(unsigned(r - l)) - 1;
        return op(table_[i][l], table_[i][r - (1 << i)]);
    }

private:
    int n_, width_;
    std::vector<std::vector<S>> table_;
};

#endif // SPARSE_TABLE_HPP