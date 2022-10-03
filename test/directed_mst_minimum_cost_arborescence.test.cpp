#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_B"

#include "graph/directed_mst.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int V, E, r;
    std::cin >> V >> E >> r;
    directed_mst<int> dmst(V);
    for (auto i = 0; i < E; ++i) {
        int s, t, w;
        std::cin >> s >> t >> w;
        dmst.add_edge(s, t, w);
    }
    auto [ans, p] = dmst.run(r);
    std::cout << ans << '\n';
}
