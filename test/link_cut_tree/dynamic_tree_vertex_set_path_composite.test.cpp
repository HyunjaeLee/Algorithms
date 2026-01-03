#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite"

#include "link_cut_tree/link_cut_tree.hpp"
#include "monoids/affine_monoid.hpp"
#include "monoids/reversible_monoid.hpp"
#include <atcoder/modint>
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    std::cin >> N >> Q;
    using mint = atcoder::modint998244353;
    using M = AffineMonoid<mint>;
    using S = ReversibleMonoid<M>;
    link_cut_tree<S, S::op, S::e, S::toggle> lct(N);
    for (auto i = 0; i < N; ++i) {
        int a, b;
        std::cin >> a >> b;
        lct.set(i, M{a, b});
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
            int p, c, d;
            std::cin >> p >> c >> d;
            lct.set(p, M{c, d});
        } else {
            int u, v, x;
            std::cin >> u >> v >> x;
            auto [a, b] = lct.prod(u, v).val;
            auto ans = a * x + b;
            std::cout << ans.val() << '\n';
        }
    }
}
