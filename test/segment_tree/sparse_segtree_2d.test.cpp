#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"

#include "segment_tree/sparse_segtree_2d.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    std::cin >> N >> Q;
    std::vector<std::tuple<int, int, long long>> points(N);
    for (auto &[x, y, w] : points) {
        std::cin >> x >> y >> w;
    }
    std::vector<std::array<int, 5>> query;
    query.reserve(Q);
    for (auto i = 0; i < Q; ++i) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int x, y, w;
            std::cin >> x >> y >> w;
            query.push_back({t, x, y, w, int(points.size())});
            points.emplace_back(x, y, 0);
        } else {
            int l, d, r, u;
            std::cin >> l >> d >> r >> u;
            query.push_back({t, l, d, r, u});
        }
    }
    auto op = [](long long a, long long b) { return a + b; };
    auto e = [] { return 0LL; };
    sparse_segtree_2d<int, long long, op, e> seg(int(points.size()),
                                                 [&](int i) { return points[i]; });
    for (const auto &q : query) {
        if (q[0] == 0) {
            auto [t, x, y, w, id] = q;
            seg.multiply(id, w);
        } else {
            auto [t, l, d, r, u] = q;
            auto ans = seg.prod(l, r, d, u);
            std::cout << ans << "\n";
        }
    }
}
