#ifndef AND_HPP
#define AND_HPP

#include "transform/superset_mobius.hpp"
#include "transform/superset_zeta.hpp"
#include <cassert>
#include <vector>

template <typename T> std::vector<T> and_convolution(std::vector<T> a, std::vector<T> b) {
    assert(a.size() == b.size());
    superset_zeta_transform(a);
    superset_zeta_transform(b);
    for (auto i = 0; i < int(a.size()); ++i) {
        a[i] *= b[i];
    }
    superset_mobius_transform(a);
    return a;
}

#endif // AND_HPP
