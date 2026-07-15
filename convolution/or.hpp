#ifndef OR_HPP
#define OR_HPP

#include "transform/subset_mobius.hpp"
#include "transform/subset_zeta.hpp"
#include <cassert>
#include <vector>

template <typename T> std::vector<T> or_convolution(std::vector<T> a, std::vector<T> b) {
    assert(a.size() == b.size());
    subset_zeta_transform(a);
    subset_zeta_transform(b);
    for (auto i = 0; i < int(a.size()); ++i) {
        a[i] *= b[i];
    }
    subset_mobius_transform(a);
    return a;
}

#endif // OR_HPP
