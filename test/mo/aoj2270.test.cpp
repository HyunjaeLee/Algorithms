#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/2270"

#include "mo/mo_tree.hpp"
#include "mo/sqrt_freq_table.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> A(N);
    for (auto &x : A) {
        std::cin >> x;
    }
    auto C = A;
    std::ranges::sort(C);
    C.erase(std::unique(C.begin(), C.end()), C.end());
    for (auto &x : A) {
        auto it = std::ranges::lower_bound(C, x);
        x = int(it - C.begin());
    }
    std::vector<std::vector<int>> adj(N);
    for (auto i = 0; i < N - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    std::vector<int> K(Q);
    MoTree mo(adj);
    for (auto &k : K) {
        int u, v;
        std::cin >> u >> v >> k;
        --u, --v, --k;
        mo.add(u, v);
    }
    SqrtFreqTable table(int(C.size()) - 1);
    std::vector<int> ans(Q);
    auto add = [&](int u) { table.insert(A[u]); };
    auto remove = [&](int u) { table.erase(A[u]); };
    auto eval = [&](int i) { ans[i] = C[table.kth(K[i])]; };
    mo.solve(add, remove, eval);
    std::ranges::copy(ans, std::ostream_iterator<int>(std::cout, "\n"));
}
