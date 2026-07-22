#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/0009"

#include "math/linear_sieve.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    std::vector<int> A;
    for (int x; std::cin >> x;) {
        A.push_back(x);
    }
    linear_sieve sieve(std::ranges::max(A));
    for (auto x : A) {
        auto it = std::ranges::upper_bound(sieve.primes, x);
        auto ans = it - sieve.primes.begin();
        std::cout << ans << "\n";
    }
}
