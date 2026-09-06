#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/challenges/sources/JAG/Summer/3614"

#include "math/combinatorics.hpp"
#include "math/p_recursive.hpp"
#include <atcoder/modint>
#include <bits/stdc++.h>
using Z = atcoder::modint998244353;

Z small(int n, int m) {
    Combinatorics<Z> C;
    auto ans = Z(m).pow(2 * n);
    for (auto i = 0; i < n; ++i) {
        ans -= m * C(2 * n, i) * Z(m - 1).pow(i);
    }
    return ans;
}

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int m;
    std::cin >> m;
    std::vector<Z> ans;
    for (auto i = 1; i <= std::min(100, m); ++i) {
        ans.push_back(small(i, m));
    }
    if (100 < m) {
        auto coeffs = find_recurrence_relation(ans, 1);
        ans = extended(m, coeffs, ans);
    }
    for (auto i = 0; i < m; ++i) {
        std::cout << ans[i].val() << "\n";
    }
}
