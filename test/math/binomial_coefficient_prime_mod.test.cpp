#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod"

#include "math/combinatorics.hpp"
#include <atcoder/modint>
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    using Z = atcoder::modint;
    Combinatorics<Z> C;
    int T, m;
    std::cin >> T >> m;
    Z::set_mod(m);
    for (auto i = 0; i < T; ++i) {
        int n, k;
        std::cin >> n >> k;
        std::cout << C(n, k).val() << "\n";
    }
}
