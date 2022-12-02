#ifndef POWER_TOWER_HPP
#define POWER_TOWER_HPP

#include "math/factor.hpp"
#include <cassert>
#include <limits>
#include <type_traits>
#include <vector>

template <typename T, typename Promote = unsigned long long>
T power_tower(const std::vector<T> &a, T m) {
    static_assert(std::is_integral_v<T>);
    assert(m > 0);
    std::vector<unsigned long long> mod_chain{
        static_cast<unsigned long long>(m)};
    while (mod_chain.back() > 1) {
        const auto phi = euler_phi(mod_chain.back());
        mod_chain.push_back(phi);
    }
    const auto f = [](Promote x, Promote n, Promote mod) {
        Promote r = 1;
        if (x > mod) {
            x = x % mod + mod;
        }
        while (n) {
            if (n & 1) {
                r *= x;
                if (r > mod) {
                    r = r % mod + mod;
                }
            }
            x *= x;
            if (x > mod) {
                x = x % mod + mod;
            }
            n >>= 1;
        }
        return r;
    };
    Promote r = 1;
    const auto k = static_cast<int>(std::min(a.size(), mod_chain.size()));
    for (auto i = k - 1; i >= 0; --i) {
        assert(a[i] > 0);
        r = f(static_cast<Promote>(a[i]), r, mod_chain[i]);
    }
    return static_cast<T>(r % static_cast<Promote>(m));
}

#endif // POWER_TOWER_HPP
