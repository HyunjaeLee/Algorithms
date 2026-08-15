#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/2069"

#include "optimization/canonical_coin_system.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    for (int t = 1, N; (std::cin >> N) && N; ++t) {
        std::cout << "Case #" << t << ": ";
        std::vector<int> A(N);
        for (auto &x : A) {
            std::cin >> x;
        }
        if (A[0] != 1) {
            std::cout << "Cannot pay some amount\n";
            continue;
        }
        auto [canonical, w, mw] = greedy_optimality(A);
        if (canonical) {
            std::cout << "OK\n";
        } else {
            std::cout << "Cannot use greedy algorithm\n";
        }
    }
}
