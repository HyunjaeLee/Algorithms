#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/challenges/sources/JAG/Summer/2971"

#include "data_structures/potentialized_rollback_dsu.hpp"
#include <bits/stdc++.h>

using i64 = long long;
using i128 = __int128;

struct A {
    static A op(A a, A b) { return {modmul(a.val, b.val)}; }
    static A e() { return {1}; }
    static A inv(A x) { return {modpow(x.val, mod - 2)}; }
    static i64 modmul(i64 a, i64 b) { return i64(i128(a) * b % mod); }
    static i64 modpow(i64 x, i64 n) {
        i64 r = 1;
        while (n) {
            if (n & 1) {
                r = modmul(r, x);
            }
            x = modmul(x, x);
            n >>= 1;
        }
        return r;
    }
    bool operator==(const A &other) const { return val == other.val; }
    i64 val;
    inline static i64 mod = (1LL << 61) - 1;
};

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, M;
    std::cin >> N >> M;
    PotentializedRollbackDSU<A> dsu(N);
    for (auto i = 0; i < M; ++i) {
        int v, u, x;
        std::cin >> v >> u >> x;
        --u, --v;
        dsu.merge(u, v, A{x});
    }
    auto ans = dsu.is_valid() ? "Yes" : "No";
    std::cout << ans << "\n";
}
