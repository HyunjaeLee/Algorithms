#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include "../wavelet/wavelet_matrix.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> v(N);
    for (auto &x : v) {
        std::cin >> x;
    }
    wavelet_matrix<int> wm(std::move(v));
    while (Q--) {
        int l, r, k;
        std::cin >> l >> r >> k;
        std::cout << wm.quantile(l, r, k) << '\n';
    }
}
