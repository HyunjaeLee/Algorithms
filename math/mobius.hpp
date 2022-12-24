#ifndef MOBIUS_HPP
#define MOBIUS_HPP

#include <algorithm>
#include <cassert>
#include <vector>

std::vector<int> mobius(int n) {
    assert(n > 0);
    std::vector<int> prime, mu(n + 1);
    std::vector<char> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    mu[1] = 1;
    for (auto i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            prime.push_back(i);
            mu[i] = -1;
        }
        for (auto p : prime) {
            if (i * p > n) {
                break;
            }
            is_prime[i * p] = false;
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            } else {
                mu[i * p] = -mu[i];
            }
        }
    }
    return mu;
}

#endif // MOBIUS_HPP
