#ifndef HILBERT_MO_HPP
#define HILBERT_MO_HPP

#include <algorithm>
#include <array>
#include <cassert>
#include <vector>

struct hilbert_mo {
    hilbert_mo(int n) : n_(n), log_(std::__lg(std::max(1, n_)) + 1) {}
    void add(int l, int r) {
        assert(0 <= l && l <= r && r <= n_);
        auto index = static_cast<int>(queries_.size());
        auto order = hilbert_order(l, r, log_, 0);
        queries_.push_back({l, r, index, order});
    }
    template <typename Add, typename Remove, typename Eval>
    void run(Add add, Remove remove, Eval eval) {
        run(add, add, remove, remove, eval);
    }
    template <typename AddLeft, typename AddRight, typename RemoveLeft,
              typename RemoveRight, typename Eval>
    void run(AddLeft add_left, AddRight add_right, RemoveLeft remove_left,
             RemoveRight remove_right, Eval eval) {
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
    long long hilbert_order(int x, int y, int pow, int rotate) const {
        if (pow == 0) {
            return 0;
        }
        auto hpow = 1 << (pow - 1);
        auto seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
        seg = (seg + rotate) & 3;
        const std::array<int, 4> rotate_delta{3, 0, 0, 1};
        auto nx = x & (x ^ hpow), ny = y & (y ^ hpow);
        auto nrot = (rotate + rotate_delta[seg]) & 3;
        auto subsquare_size = static_cast<long long>(1) << (2 * pow - 2);
        auto ans = seg * subsquare_size;
        auto add = hilbert_order(nx, ny, pow - 1, nrot);
        ans += (seg == 1 || seg == 2) ? add : (subsquare_size - add - 1);
        return ans;
    }
    std::vector<query> queries_;
    const int n_, log_;
};

#endif // HILBERT_MO_HPP