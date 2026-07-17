#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/1404"

#include "graph/bipartite_coloring.hpp"
#include <atcoder/modint>
#include <bits/stdc++.h>
using Z = atcoder::modint1000000007;

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, M;
    std::cin >> N >> M;
    std::vector<int> A(N);
    for (auto i = 0; i < N; ++i) {
        std::cin >> A[i];
    }
    std::vector<std::vector<int>> G(N);
    for (auto i = 0; i < N - 1; ++i) {
        for (auto j = i + 1; j < N; ++j) {
            if (A[i] > A[j]) {
                G[i].push_back(j);
                G[j].push_back(i);
            }
        }
    }
    auto result = bipartite_coloring(G);
    if (!result) {
        std::cout << "0\n";
        return 0;
    }
    auto color = std::move(*result);
    std::vector<char> visited(N);
    std::vector<int> comp;
    for (auto i = 0; i < N; ++i) {
        if (visited[i]) {
            continue;
        }
        comp.push_back(0);
        auto dfs = [&](auto &&self, int u) -> void {
            visited[u] = true;
            comp.back() += (color[u] ? -1 : 1);
            for (auto v : G[u]) {
                if (!visited[v]) {
                    self(self, v);
                }
            }
        };
        dfs(dfs, i);
    }
    auto C = int(comp.size());
    std::vector<std::vector<Z>> dp(2, std::vector<Z>(2 * N + 1));
    for (auto d = -N; d <= N; ++d) {
        if (std::max(N + d, N - d) <= 2 * M) {
            dp[C & 1][N + d] = 1;
        }
    }
    for (auto i = C - 1; 0 <= i; --i) {
        for (auto d = -N; d <= N; ++d) {
            dp[i & 1][N + d] = 0;
            for (auto x : {d + comp[i], d - comp[i]}) {
                if (-N <= x && x <= N) {
                    dp[i & 1][N + d] += dp[(i + 1) & 1][N + x];
                }
            }
        }
    }
    std::cout << dp[0][N].val() << "\n";
}
