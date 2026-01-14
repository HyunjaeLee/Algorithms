#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det_mod_2"

#include "linear_algebra/gf2_matrix.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int n;
    std::cin >> n;
    GF2Matrix mat(n, n);
    for (auto i = 0; i < n; ++i) {
        std::string row;
        std::cin >> row;
        mat.set_row(i, row);
    }
    std::cout << (mat.gaussian_elimination() == n) << "\n";
}
