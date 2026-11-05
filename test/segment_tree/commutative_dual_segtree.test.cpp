#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_E"

#include "segment_tree/commutative_dual_segtree.hpp"
#include <bits/stdc++.h>

using S = int;
using F = int;
S mapping(F f, S x) { return f + x; }
F composition(F f, F g) { return f + g; }
F id() { return 0; }

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    std::cin >> N >> Q;
    commutative_dual_segtree<S, F, mapping, composition, id> seg(N, 0);
    while (Q--) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int l, r, x;
            std::cin >> l >> r >> x;
            --l;
            seg.apply(l, r, x);
        } else {
            int i;
            std::cin >> i;
            --i;
            std::cout << seg.get(i) << "\n";
        }
    }
}
