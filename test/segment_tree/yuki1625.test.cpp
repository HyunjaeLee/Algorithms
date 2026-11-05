#define PROBLEM "https://yukicoder.me/problems/no/1625"

#include "segment_tree/sparse_segtree_2d.hpp"
#include <bits/stdc++.h>

using S = long long;

S op(S a, S b) { return std::max(a, b); }

S e() { return -1; }

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    std::cin >> N >> Q;
    std::vector<long long> X, Y;
    std::vector<long long> W;
    for (auto i = 0; i < N; ++i) {
        long long x1, y1, x2, y2, x3, y3;
        std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        auto x = std::min({x1, x2, x3});
        auto y = std::max({x1, x2, x3});
        auto w = std::abs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1));
        X.push_back(x);
        Y.push_back(y);
        W.push_back(w);
    }
    std::vector<std::array<long long, 3>> query(Q);
    for (auto i = 0; i < Q; ++i) {
        int t;
        std::cin >> t;
        if (t == 1) {
            long long x1, y1, x2, y2, x3, y3;
            std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
            auto x = std::min({x1, x2, x3});
            auto y = std::max({x1, x2, x3});
            auto w = std::abs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1));
            query[i] = {t, std::ssize(X), w};
            X.push_back(x);
            Y.push_back(y);
            W.push_back(-1);
        } else {
            long long l, r;
            std::cin >> l >> r;
            query[i] = {t, l, r};
        }
    }
    sparse_segtree_2d<long long, S, op, e> seg(X, Y, W);
    for (auto i = 0; i < Q; ++i) {
        auto t = query[i][0];
        if (t == 1) {
            auto id = int(query[i][1]);
            auto w = query[i][2];
            seg.set(id, w);
        } else {
            auto l = query[i][1];
            auto r = query[i][2];
            auto ans = seg.prod(l, r + 1, l, r + 1);
            std::cout << ans << "\n";
        }
    }
}
