#define PROBLEM "https://judge.yosupo.jp/problem/static_range_count_distinct"

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
    HilbertMo mo(N);
    for (auto i = 0; i < Q; ++i) {
        int l, r;
        std::cin >> l >> r;
        mo.add(l, r);
    }
    SqrtFreqTable table(int(C.size()) - 1);
    std::vector<int> ans(Q);
    auto add = [&](int i) { table.insert(A[i]); };
    auto remove = [&](int i) { table.erase(A[i]); };
    auto eval = [&](int i) { ans[i] = table.count_distinct(); };
    mo.solve(add, remove, eval);
    std::ranges::copy(ans, std::ostream_iterator<int>(std::cout, "\n"));
}
