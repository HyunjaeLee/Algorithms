#define PROBLEM "https://judge.yosupo.jp/problem/static_range_frequency"

#include "data_structures/static_range_frequency.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> A(N);
    for (auto &x : A) {
        std::cin >> x;
    }
    static_range_frequency<int> f(A);
    while (Q--) {
        int l, r, x;
        std::cin >> l >> r >> x;
        std::cout << f.query(l, r, x) << "\n";
    }
}
