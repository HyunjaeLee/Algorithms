#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/2963"

#include "optimization/canonical_coin_system.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    long long A, B;
    std::cin >> A >> B;
    auto [canonical, w, mw] = greedy_optimality(std::vector{1LL, A, B});
    std::cout << w << "\n";
}
