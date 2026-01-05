#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/1068"

#include "segment_tree/segtree_2d.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    while (true) {
        int N, M, Q;
        std::cin >> N >> M >> Q;
        if (N == 0 && M == 0 && Q == 0) {
            break;
        }
        using S = int;
        auto op = [](S a, S b) -> S { return std::min(a, b); };
        auto e = []() -> S { return std::numeric_limits<int>::max(); };
        segtree_2d<S, op, e> seg(N, M);
        for (auto i = 0; i < N; ++i) {
            for (auto j = 0; j < M; ++j) {
                int x;
                std::cin >> x;
                seg.set(i, j, x);
            }
        }
        while (Q--) {
            int r1, c1, r2, c2;
            std::cin >> r1 >> c1 >> r2 >> c2;
            auto ans = seg.prod(r1, r2 + 1, c1, c2 + 1);
            std::cout << ans << '\n';
        }
    }
}
