#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/0489"

#include "mo/mo_tree.hpp"
#include "mo/sqrt_freq_table.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, M;
    std::cin >> N >> M;
    std::vector<int> A(N);
    for (auto &x : A) {
        std::cin >> x;
    }
    std::vector<std::vector<int>> adj(N);
    for (auto i = 0; i < N - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    std::vector<std::tuple<int, int, int>> queries;
    for (auto i = 0; i < M; ++i) {
        int op;
        std::cin >> op;
        if (op == 1) {
            int u, w;
            std::cin >> u >> w;
            --u;
            auto v = int(adj.size());
            A.push_back(w);
            adj.emplace_back();
            adj[u].push_back(v);
            adj[v].push_back(u);
        } else {
            int u, v, k;
            std::cin >> u >> v >> k;
            --u, --v, --k;
            queries.emplace_back(u, v, k);
        }
    }
    auto C = A;
    std::ranges::sort(C);
    C.erase(unique(C.begin(), C.end()), C.end());
    for (auto &x : A) {
        auto it = std::ranges::lower_bound(C, x);
        x = int(it - C.begin());
    }
    MoTree mo(adj);
    for (auto [u, v, k] : queries) {
        mo.add(u, v);
    }
    SqrtFreqTable table(int(C.size()) - 1);
    std::vector<int> ans(queries.size());
    auto add = [&](int u) { table.insert(A[u]); };
    auto remove = [&](int u) { table.erase(A[u]); };
    auto eval = [&](int i) {
        auto [u, v, k] = queries[i];
        ans[i] = C[table.kth(k)];
    };
    mo.solve(add, remove, eval);
    std::ranges::copy(ans, std::ostream_iterator<int>(std::cout, "\n"));
}
