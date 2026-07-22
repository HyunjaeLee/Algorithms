#define PROBLEM "https://yukicoder.me/problems/no/106"

#include "math/linear_sieve.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, K;
    std::cin >> N >> K;
    linear_sieve sieve(N);
    auto ans = 0;
    for (auto i = 2; i <= N; ++i) {
        if (K <= int(sieve.factorize(i).size())) {
            ans += 1;
        }
    }
    std::cout << ans << "\n";
}
