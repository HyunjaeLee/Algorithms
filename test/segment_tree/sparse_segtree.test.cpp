#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite_large_array"

#include "segment_tree/sparse_segtree.hpp"
#include "monoids/affine_monoid.hpp"
#include <atcoder/modint>
#include <bits/stdc++.h>
using Z = atcoder::modint998244353;

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    std::cin >> N >> Q;
    using S = AffineMonoid<Z>;
    sparse_segtree<int, S, S::op, S::e> seg(N);
    while (Q--) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int p, c, d;
            std::cin >> p >> c >> d;
            seg.set(p, {c, d});
        } else {
            int l, r, x;
            std::cin >> l >> r >> x;
            auto [a, b] = seg.prod(l, r);
            auto ans = a * x + b;
            std::cout << ans.val() << "\n";
        }
    }
}
