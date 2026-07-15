#ifndef SUPERSET_ZETA_HPP
#define SUPERSET_ZETA_HPP

#include <bit>
#include <cassert>
#include <vector>

template <typename T> void superset_zeta_transform(std::vector<T> &f) {
    assert(std::has_single_bit(f.size()));
    auto n = int(std::countr_zero(f.size()));
    for (auto i = 0; i < n; ++i) {
        for (auto s = 0; s < (1 << n); ++s) {
            if (s & (1 << i)) {
                f[s ^ (1 << i)] += f[s];
            }
        }
    }
}

#endif // SUPERSET_ZETA_HPP
