#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_A"

#include "graph/articulation_points.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> g(n);
    for (auto i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    auto cutpoints = find_cutpoints(g);
    std::ranges::sort(cutpoints);
    std::ranges::copy(cutpoints, std::ostream_iterator<int>(std::cout, "\n"));
}
