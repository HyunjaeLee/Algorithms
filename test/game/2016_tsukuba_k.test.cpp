#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/1377"

#include "game/ordinal_sum.hpp"
#include "game/surreal.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    using S = Surreal;
    int N;
    std::cin >> N;
    std::vector<std::string> A(N);
    for (auto i = 0; i < N; ++i) {
        std::cin >> A[i];
    }
    std::vector<S> G(N);
    for (auto i = 0; i < N; ++i) {
        for (auto c : A[i]) {
            G[i] = ordinal_sum(G[i], c == 'B' ? 1 : -1);
        }
    }
    auto ans = 0;
    auto X = N / 2;
    auto Y = N - N / 2;
    std::map<S, int> mp;
    for (auto s = 0; s < (1 << X); ++s) {
        S sum = 0;
        auto sz = 0;
        for (auto i = 0; i < X; ++i) {
            if ((s >> i) & 1) {
                sum += G[i];
                sz += int(A[i].size());
            }
        }
        mp[sum] = std::max(mp[sum], sz);
    }
    for (auto s = 0; s < (1 << Y); ++s) {
        S sum = 0;
        auto sz = 0;
        for (auto i = 0; i < Y; ++i) {
            if ((s >> i) & 1) {
                sum += G[X + i];
                sz += int(A[X + i].size());
            }
        }
        if (auto it = mp.find(-sum); it != mp.end()) {
            ans = std::max(ans, it->second + sz);
        }
    }
    std::cout << ans << "\n";
}
