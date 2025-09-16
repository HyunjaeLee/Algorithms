#define PROBLEM                                                                \
    "https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum"

#include "../segment_tree/segtree_beats.hpp"
#include <bits/stdc++.h>

struct S {
    long long max, max2, min, min2, sum;
    int max_count, min_count, size;
};

struct F {
    long long upper, lower, sum;
};

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    std::cin >> N >> Q;
    std::vector<S> v(N);
    constexpr auto inf = static_cast<long long>(1e18);
    for (auto &s : v) {
        long long x;
        std::cin >> x;
        s.max = s.min = s.sum = x;
        s.max_count = s.min_count = s.size = 1;
        s.max2 = -inf;
        s.min2 = inf;
    }
    auto op = [](S a, S b) -> S {
        S ret{};
        if (a.max < b.max) {
            ret.max = b.max;
            ret.max2 = std::max(a.max, b.max2);
            ret.max_count = b.max_count;
        } else if (b.max < a.max) {
            ret.max = a.max;
            ret.max2 = std::max(a.max2, b.max);
            ret.max_count = a.max_count;
        } else {
            ret.max = a.max;
            ret.max2 = std::max(a.max2, b.max2);
            ret.max_count = a.max_count + b.max_count;
        }
        if (a.min < b.min) {
            ret.min = a.min;
            ret.min2 = std::min(a.min2, b.min);
            ret.min_count = a.min_count;
        } else if (b.min < a.min) {
            ret.min = b.min;
            ret.min2 = std::min(a.min, b.min2);
            ret.min_count = b.min_count;
        } else {
            ret.min = a.min;
            ret.min2 = std::min(a.min2, b.min2);
            ret.min_count = a.min_count + b.min_count;
        }
        ret.sum = a.sum + b.sum;
        ret.size = a.size + b.size;
        return ret;
    };
    auto e = []() -> S { return {-inf, -inf, inf, inf, 0, 0, 0, 0}; };
    auto mapping = [](F f, S x) -> std::pair<S, bool> {
        x.max += f.sum;
        x.max2 += f.sum;
        x.min += f.sum;
        x.min2 += f.sum;
        x.sum += f.sum * x.size;
        if (x.max <= f.lower) {
            return {{f.lower, -1, f.lower, -1, f.lower * x.size, x.size, x.size,
                     x.size},
                    true};
        }
        if (f.upper <= x.min) {
            return {{f.upper, -1, f.upper, -1, f.upper * x.size, x.size, x.size,
                     x.size},
                    true};
        }
        if (x.max2 < f.upper && f.upper < x.max) {
            x.sum -= (x.max - f.upper) * x.max_count;
            x.max = f.upper;
        } else if (f.upper <= x.max2) {
            return {x, false};
        }
        if (x.max < x.min) {
            x.min = x.max;
        } else if (x.max < x.min2) {
            x.min2 = x.max;
        }
        if (x.min < f.lower && f.lower < x.min2) {
            x.sum += (f.lower - x.min) * x.min_count;
            x.min = f.lower;
        } else if (x.min2 <= f.lower) {
            return {x, false};
        }
        if (x.max < x.min) {
            x.max = x.min;
        } else if (x.max2 < x.min) {
            x.max2 = x.min;
        }
        return {x, true};
    };
    auto composition = [](F f, F g) -> F {
        g.upper += f.sum;
        g.lower += f.sum;
        g.sum += f.sum;
        g.upper = std::min(f.upper, g.upper);
        if (g.upper < g.lower) {
            g.lower = g.upper;
        }
        g.lower = std::max(f.lower, g.lower);
        if (g.upper < g.lower) {
            g.upper = g.lower;
        }
        return g;
    };
    auto id = []() -> F { return {inf, -inf, 0}; };
    segtree_beats seg(v, op, e, mapping, composition, id);
    for (auto i = 0; i < Q; ++i) {
        int q, l, r;
        std::cin >> q >> l >> r;
        auto b = 0LL;
        if (q != 3)
            std::cin >> b;
        switch (q) {
        case 0:
            seg.apply(l, r, {b, -inf, 0});
            break;
        case 1:
            seg.apply(l, r, {inf, b, 0});
            break;
        case 2:
            seg.apply(l, r, {inf, -inf, b});
            break;
        case 3:
            std::cout << seg.prod(l, r).sum << '\n';
            break;
        }
    }
}
