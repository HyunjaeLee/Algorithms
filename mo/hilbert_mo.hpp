#ifndef HILBERT_MO_HPP
#define HILBERT_MO_HPP

#include <algorithm>
#include <array>
#include <cassert>
#include <vector>

struct HilbertMo {
    HilbertMo(int n) : n_(n), log_(std::bit_width(unsigned(n))) {}
    void add(int l, int r) {
        assert(0 <= l && l <= r && r <= n_);
        auto index = int(queries_.size());
        auto order = hilbert_order(l, r);
        queries_.push_back({l, r, index, order});
    }
    void solve(auto add, auto remove, auto eval) { solve(add, add, remove, remove, eval); }
    void solve(auto add_left, auto add_right, auto remove_left, auto remove_right, auto eval) {
        sort(queries_.begin(), queries_.end());
        auto l = 0, r = 0;
        for (auto [left, right, index, order] : queries_) {
            while (left < l) {
                add_left(--l);
            }
            while (r < right) {
                add_right(r++);
            }
            while (l < left) {
                remove_left(l++);
            }
            while (right < r) {
                remove_right(--r);
            }
            eval(index);
        }
    }

private:
    struct query {
        int left, right, index;
        long long order;
        bool operator<(const query &other) const { return order < other.order; }
    };
    long long hilbert_order(int x, int y) const {
        auto d = 0LL;
        for (auto s = 1 << log_; s > 0; s >>= 1) {
            bool rx = x & s, ry = y & s;
            d = (d << 2) | ((rx * 3) ^ ry);
            if (!ry) {
                if (rx) {
                    x = ~x;
                    y = ~y;
                }
                std::swap(x, y);
            }
        }
        return d;
    }
    std::vector<query> queries_;
    const int n_, log_;
};

#endif // HILBERT_MO_HPP