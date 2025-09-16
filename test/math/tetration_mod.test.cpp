#define PROBLEM "https://judge.yosupo.jp/problem/tetration_mod"

#include "math/power_tower.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int T;
    std::cin >> T;
    for (auto i = 0; i < T; ++i) {
        int A, B, M;
        std::cin >> A >> B >> M;
        if (A == 0) {
            std::cout << ((B & 1) ^ 1) % M;
        } else {
            const auto n = std::min(B, 64);
            std::vector<int> a(n, A);
            std::cout << power_tower(a, M);
        }
        std::cout << '\n';
    }
}
