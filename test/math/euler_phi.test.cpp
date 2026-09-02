#define PROBLEM "https://yukicoder.me/problems/no/2249"

#include "math/euler_phi.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    constexpr auto NMAX = 10'000'000;
    auto phi = euler_phi(NMAX);
    std::vector<long long> pref(NMAX + 1);
    for (auto i = 2; i <= NMAX; ++i) {
        pref[i] = 2 * i - 2 - phi[i];
    }
    for (auto i = 2; i < NMAX; ++i) {
        pref[i + 1] += pref[i];
    }
    int T;
    std::cin >> T;
    while (T--) {
        int N;
        std::cin >> N;
        std::cout << pref[N] << "\n";
    }
}
