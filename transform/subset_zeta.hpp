#ifndef SUBSET_ZETA_HPP
#define SUBSET_ZETA_HPP

#include <bit>
#include <cassert>
#include <vector>

template <typename T> void subset_zeta_transform(std::vector<T> &f) {
    assert(std::has_single_bit(f.size()));
    auto n = int(std::countr_zero(f.size()));
    for (auto i = 0; i < n; ++i) {
        for (auto t = 0; t < (1 << n); ++t) {
            if (t & (1 << i)) {
                f[t] += f[t ^ (1 << i)];
            }
        }
    }
}

#endif // SUBSET_ZETA_HPP
