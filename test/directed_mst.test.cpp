#define PROBLEM "https://judge.yosupo.jp/problem/directedmst"

#include "graph/directed_mst.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, M, S;
    std::cin >> N >> M >> S;
    directed_mst<long long> dmst(N);
    for (auto i = 0; i < M; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;
        dmst.add_edge(a, b, c);
    }
    auto [X, parent] = dmst.run(S);
    parent[S] = S;
    std::cout << X << '\n';
    for (auto p : parent) {
        std::cout << p << ' ';
    }
}
