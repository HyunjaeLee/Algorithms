#define PROBLEM "https://judge.yosupo.jp/problem/static_range_frequency"

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
    v.push_back(0); // Wavelet matrix requires non-empty vector
    wavelet_matrix<int> wm(std::move(v));
    while (Q--) {
        int l, r, x;
        std::cin >> l >> r >> x;
        std::cout << wm.rank(l, r, x) << '\n';
    }
}
