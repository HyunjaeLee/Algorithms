#define PROBLEM "https://judge.yosupo.jp/problem/dominatortree"

#include "graph/dominator_tree.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, M, S;
    std::cin >> N >> M >> S;
    dominator_tree dt(N);
    for (auto i = 0; i < M; ++i) {
        int a, b;
        std::cin >> a >> b;
        dt.add_edge(a, b);
    }
    dt.run(S);
    for (auto i = 0; i < N; ++i) {
        std::cout << dt[i] << ' ';
    }
}
