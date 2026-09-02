#ifndef EULER_PHI_HPP
#define EULER_PHI_HPP

#include <vector>
#include <cassert>

std::vector<int> euler_phi(int n) {
    assert(0 < n);
    std::vector<int> prime, phi(n + 1);
    std::vector<char> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    phi[1] = 1;
    for (auto i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            prime.push_back(i);
            phi[i] = i - 1;
        }
        for (auto p : prime) {
            if (i * p > n) {
                break;
            }
            is_prime[i * p] = false;
            if (i % p == 0) {
                phi[i * p] = phi[i] * p;
                break;
            } else {
                phi[i * p] = phi[i] * phi[p];
            }
        }
    }
    return phi;
}

#endif // EULER_PHI_HPP