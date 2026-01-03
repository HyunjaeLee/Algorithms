#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum"

#include "link_cut_tree/lazy_link_cut_tree.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    std::cin >> N >> Q;
    std::vector<long long> A(N);
    std::copy_n(std::istream_iterator<long long>(std::cin), N, std::begin(A));
    auto op = [](long long a, long long b) -> long long { return a + b; };
    auto e = []() -> long long { return 0LL; };
    auto mapping = [](long long f, long long x) -> long long { return f + x; };
    auto composition = [](long long f, long long g) -> long long { return f + g; };
    auto id = []() -> long long { return 0LL; };
    link_cut_tree<long long, op, e, long long, mapping, composition, id> lct(N);
    for (auto i = 0; i < N; ++i) {
        lct.set(i, A[i]);
    }
    for (auto i = 0; i < N - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        lct.link(u, v);
    }
    while (Q--) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int u, v, w, x;
            std::cin >> u >> v >> w >> x;
            lct.cut(u, v);
            lct.link(w, x);
        } else if (t == 1) {
            int p, x;
            std::cin >> p >> x;
            A[p] += x;
            lct.set(p, A[p]);
        } else {
            int u, v;
            std::cin >> u >> v;
            std::cout << lct.prod(u, v) << '\n';
        }
    }
}
