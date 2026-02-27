#define PROBLEM "https://judge.yosupo.jp/problem/static_range_inversions_query"

#include "mo/hilbert_mo.hpp"
#include "segment_tree/simd_segtree.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> A(N);
    for (auto &x : A) {
        std::cin >> x;
    }
    auto c = A;
    std::ranges::sort(c);
    c.erase(std::unique(c.begin(), c.end()), c.end());
    for (auto &x : A) {
        auto it = std::ranges::lower_bound(c, x);
        x = int(it - c.begin());
    }
    HilbertMo mo(N);
    for (auto i = 0; i < Q; ++i) {
        int l, r;
        std::cin >> l >> r;
        mo.add(l, r);
    }
    auto val = 0LL;
    auto k = int(c.size());
    simd_segtree<int, 100000> seg;
    std::vector<long long> ans(Q);
    auto add_left = [&](auto i) {
        val += seg.sum(A[i]);
        seg.add(A[i], 1);
    };
    auto add_right = [&](auto i) {
        val += seg.sum(A[i] + 1, k);
        seg.add(A[i], 1);
    };
    auto remove_left = [&](auto i) {
        val -= seg.sum(A[i]);
        seg.add(A[i], -1);
    };
    auto remove_right = [&](auto i) {
        val -= seg.sum(A[i] + 1, k);
        seg.add(A[i], -1);
    };
    auto eval = [&](auto i) { ans[i] = val; };
    mo.solve(add_left, add_right, remove_left, remove_right, eval);
    std::ranges::copy(ans, std::ostream_iterator<long long>(std::cout, "\n"));
}
