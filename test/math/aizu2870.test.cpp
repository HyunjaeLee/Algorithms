#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/2870"

#include "math/linear_sieve.hpp"
#include <atcoder/modint>
#include <bits/stdc++.h>
using Z = atcoder::modint1000000007;

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N;
    std::cin >> N;
    std::vector<int> A(N);
    for (auto &x : A) {
        std::cin >> x;
    }
    linear_sieve sieve(std::ranges::max(A));
    std::vector<Z> dp(N + 1);
    dp[N] = 1;
    for (auto i = N - 1; 0 <= i; --i) {
        if (!sieve.is_prime(A[i])) {
            continue;
        }
        for (auto j = 1; j <= 2; ++j) {
            if (i + j <= N && (i + j == N || A[i] < A[i + j])) {
                dp[i] += dp[i + j];
            }
        }
    }
    std::cout << dp[0].val() << "\n";
}
