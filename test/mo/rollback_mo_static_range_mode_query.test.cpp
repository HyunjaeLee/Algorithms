#define PROBLEM "https://judge.yosupo.jp/problem/static_range_mode_query"

#include "mo/rollback_mo.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> A(N);
    std::copy_n(std::istream_iterator<int>(std::cin), N, A.begin());
    auto C = A;
    std::ranges::sort(C);
    C.erase(std::unique(C.begin(), C.end()), C.end());
    for (auto &a : A) {
        a = int(std::ranges::lower_bound(C, a) - C.begin());
    }
    RollbackMo mo(N);
    for (auto i = 0; i < Q; ++i) {
        int l, r;
        std::cin >> l >> r;
        mo.add(l, r);
    }
    auto best = 0, val = 0;
    std::vector<int> freq(C.size());
    std::vector<std::tuple<int, int, int>> history;
    std::vector<std::pair<int, int>> ans(Q);
    auto add = [&](int i) {
        auto a = A[i];
        history.emplace_back(best, val, a);
        ++freq[a];
        if (val < freq[a]) {
            best = a;
            val = freq[a];
        }
    };
    auto rollback = [&] {
        auto [b, v, a] = history.back();
        history.pop_back();
        best = b;
        val = v;
        --freq[a];
    };
    auto eval = [&](int i) { ans[i] = {C[best], val}; };
    mo.solve(add, rollback, eval);
    for (auto [mode, cnt] : ans) {
        std::cout << mode << " " << cnt << "\n";
    }
}
