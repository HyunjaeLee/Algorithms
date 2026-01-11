#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"

#include "graph/csr_graph.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    CSRGraph<std::monostate, long long> g(n);
    for (auto i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        g.add_edge(u, v, w);
    }
    g.build_directed();
    using S = std::pair<long long, int>;
    std::vector<int> parent(n, -1);
    std::vector<long long> dist(n, std::numeric_limits<long long>::max());
    std::priority_queue<S, std::vector<S>, std::greater<>> pq;
    dist[s] = 0;
    pq.emplace(dist[s], s);
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) {
            continue;
        }
        for (auto [v, w] : g[u]) {
            if (d + w < dist[v]) {
                parent[v] = u;
                dist[v] = d + w;
                pq.emplace(dist[v], v);
            }
        }
    }
    if (dist[t] == std::numeric_limits<long long>::max()) {
        std::cout << -1;
    } else {
        std::vector<int> ans;
        for (auto u = t; u != s; u = parent[u]) {
            ans.push_back(u);
        }
        auto X = dist[t];
        auto Y = (int)ans.size();
        ans.push_back(s);
        std::cout << X << " " << Y << "\n";
        for (auto i = Y; 0 < i; --i) {
            std::cout << ans[i] << " " << ans[i - 1] << "\n";
        }
    }
}
