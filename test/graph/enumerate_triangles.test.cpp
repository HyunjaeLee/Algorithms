#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_triangles"

#include "graph/enumerate_triangles.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, M;
    std::cin >> N >> M;
    std::vector<int> A(N);
    for (auto &x : A) {
        std::cin >> x;
    }
    std::vector<std::pair<int, int>> E(M);
    for (auto &[u, v] : E) {
        std::cin >> u >> v;
    }
    __int128 sum = 0;
    auto f = [&](int i, int j, int k) { sum += __int128(A[i]) * A[j] * A[k]; };
    enumerate_triangles(N, E, f);
    auto ans = int(sum % 998244353);
    std::cout << ans << "\n";
}
