#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include "sparse_table/sparse_table.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> A(N);
    for (auto &x : A) {
        std::cin >> x;
    }
    auto op = [](auto a, auto b) { return std::min(a, b); };
    auto e = []() { return std::numeric_limits<int>::max(); };
    sparse_table<int, op, e> S(A);
    while (Q--) {
        int l, r;
        std::cin >> l >> r;
        auto ans = S.prod_idempotent(l, r);
        std::cout << ans << '\n';
    }
}
