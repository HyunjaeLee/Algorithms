#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum_large_array"

#include "segment_tree/sparse_lazy_segtree.hpp"
#include <atcoder/modint>
#include <bits/stdc++.h>
using Z = atcoder::modint998244353;

using S = Z;

S op(S a, S b) { return a + b; }

S e() { return 0; }

using F = std::pair<Z, Z>;

S mapping(F f, S x, int l, int r) {
    auto [a, b] = f;
    return a * x + b * (r - l);
}

F composition(F f, F g) {
    auto [a, b] = f;
    auto [c, d] = g;
    return {a * c, a * d + b};
}

F id() { return {1, 0}; }

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    std::cin >> N >> Q;
    sparse_lazy_segtree<int, S, op, e, F, mapping, composition, id> seg(N);
    while (Q--) {
        int t, l, r;
        std::cin >> t >> l >> r;
        if (t == 0) {
            int b, c;
            std::cin >> b >> c;
            seg.apply(l, r, {b, c});
        } else {
            auto ans = seg.prod(l, r);
            std::cout << ans.val() << "\n";
        }
    }
}
