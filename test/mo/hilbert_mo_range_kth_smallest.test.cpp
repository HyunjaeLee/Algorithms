#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include "mo/hilbert_mo.hpp"
#include "mo/sqrt_freq_table.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> A(N);
    for (auto &a : A) {
        std::cin >> a;
    }
    auto C = A;
    std::ranges::sort(C);
    C.erase(unique(C.begin(), C.end()), C.end());
    for (auto &a : A) {
        auto it = std::ranges::lower_bound(C, a);
        a = int(it - C.begin());
    }
    std::vector<int> K(Q);
    HilbertMo mo(N);
    for (auto &k : K) {
        int l, r;
        std::cin >> l >> r >> k;
        mo.add(l, r);
    }
    SqrtFreqTable table(int(C.size()));
    std::vector<int> ans(Q);
    auto add = [&](int i) { table.insert(A[i]); };
    auto remove = [&](int i) { table.erase(A[i]); };
    auto eval = [&](int i) { ans[i] = C[table.kth(K[i])]; };
    mo.solve(add, remove, eval);
    std::ranges::copy(ans, std::ostream_iterator<int>(std::cout, "\n"));
}
