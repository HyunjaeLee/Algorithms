#define PROBLEM "https://judge.yosupo.jp/problem/static_range_inversions_query"

#include "mo/hilbert_mo.hpp"
#include <atcoder/fenwicktree>
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> A(N);
    for (auto &x : A) {
        std::cin >> x;
    }
    std::vector<int> c(A);
    std::sort(c.begin(), c.end());
    c.erase(std::unique(c.begin(), c.end()), c.end());
    for (auto &x : A) {
        auto it = std::lower_bound(c.begin(), c.end(), x);
        x = static_cast<int>(it - c.begin());
    }
    hilbert_mo mo(N);
    for (auto i = 0; i < Q; ++i) {
        int l, r;
        std::cin >> l >> r;
        mo.add(l, r);
    }
    auto s = 0LL;
    auto k = static_cast<int>(c.size());
    atcoder::fenwick_tree<int> ft(k);
    auto add_left = [&](auto i) {
        s += ft.sum(0, A[i]);
        ft.add(A[i], 1);
    };
    auto add_right = [&](auto i) {
        s += ft.sum(A[i] + 1, k);
        ft.add(A[i], 1);
    };
    auto remove_left = [&](auto i) {
        s -= ft.sum(0, A[i]);
        ft.add(A[i], -1);
    };
    auto remove_right = [&](auto i) {
        s -= ft.sum(A[i] + 1, k);
        ft.add(A[i], -1);
    };
    std::vector<long long> ans(Q);
    auto eval = [&](auto i) { ans[i] = s; };
    mo.run(add_left, add_right, remove_left, remove_right, eval);
    for (auto x : ans) {
        std::cout << x << '\n';
    }
}
