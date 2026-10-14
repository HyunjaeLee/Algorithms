#ifndef STATIC_RANGE_FREQUENCY_HPP
#define STATIC_RANGE_FREQUENCY_HPP

#include "data_structures/csr.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

template <typename T> struct static_range_frequency {
    explicit static_range_frequency(const std::vector<T> &a)
        : n(int(a.size())), v(compress(a)), f(int(v.size())) {
        for (auto i = 0; i < n; ++i) {
            auto c = int(std::ranges::lower_bound(v, a[i]) - v.begin());
            f.add(c, i);
        }
        f.build();
    }
    int query(int l, int r, T x) const { // [l, r)
        assert(0 <= l && l <= r && r <= n);
        if (l == r) {
            return 0;
        }
        auto it = std::ranges::lower_bound(v, x);
        if (it == v.end() || *it != x) {
            return 0;
        }
        auto c = int(it - v.begin());
        return int(std::ranges::lower_bound(f[c], r) - std::ranges::lower_bound(f[c], l));
    }

private:
    static std::vector<T> compress(std::vector<T> a) {
        std::ranges::sort(a);
        auto [l, r] = std::ranges::unique(a);
        a.erase(l, r);
        return a;
    }
    int n;
    std::vector<T> v;
    csr<int> f;
};

#endif // STATIC_RANGE_FREQUENCY_HPP