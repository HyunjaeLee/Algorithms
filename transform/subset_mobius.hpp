#ifndef SUBSET_MOBIUS_HPP
#define SUBSET_MOBIUS_HPP

#include <bit>
#include <cassert>
#include <vector>

template <typename T> void subset_mobius_transform(std::vector<T> &g) {
    assert(std::has_single_bit(g.size()));
    auto n = int(std::countr_zero(g.size()));
    for (auto i = 0; i < n; ++i) {
        for (auto s = 0; s < (1 << n); ++s) {
            if (s & (1 << i)) {
                g[s] -= g[s ^ (1 << i)];
            }
        }
    }
}

#endif // SUBSET_MOBIUS_HPP
