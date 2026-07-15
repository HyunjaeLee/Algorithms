#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/1448"

#include "transform/subset_zeta.hpp"
#include <atcoder/modint>
#include <bits/stdc++.h>
using Z = atcoder::modint998244353;

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int n, m;
    std::cin >> n >> m;
    std::vector<int> sos(1 << n);
    for (auto i = 0; i < m; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;
        --a, --b, --c;
        sos[(1 << a) | (1 << c)] += 1;
        sos[(1 << b)] += 1;
        sos[(1 << a) | (1 << b)] -= 1;
        sos[(1 << b) | (1 << c)] -= 1;
    }
    subset_zeta_transform(sos);
    std::vector<Z> dp(1 << n);
    dp[(1 << n) - 1] = 1;
    for (auto s = (1 << n) - 2; 0 <= s; --s) {
        for (auto i = 0; i < n; ++i) {
            if (((s >> i) & 1) == 0 && sos[s] == 0 && sos[s | (1 << i)] == 0) {
                dp[s] += dp[s | (1 << i)];
            }
        }
    }
    std::cout << dp[0].val() << "\n";
}
