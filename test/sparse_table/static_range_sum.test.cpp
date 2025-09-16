#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"

#include "sparse_table/sparse_table.hpp"
#include <bits/stdc++.h>

long long op(long long a, long long b) {
    return a + b;
}

long long e() {
    return 0LL;
}

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    std::cin >> N >> Q;
    std::vector<long long> A(N);
    for (auto &x : A) {
        std::cin >> x;
    }
    sparse_table<long long, op, e> S(A);
    while (Q--) {
        int l, r;
        std::cin >> l >> r;
        auto ans = S.prod(l, r);
        std::cout << ans << '\n';
    }
}
