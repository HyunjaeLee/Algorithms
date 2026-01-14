#define PROBLEM "https://judge.yosupo.jp/problem/matrix_rank_mod_2"

#include "linear_algebra/gf2_matrix.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int n, m;
    std::cin >> n >> m;
    if (n < m) {
        GF2Matrix mat(n, m);
        for (auto i = 0; i < n; ++i) {
            std::string row;
            std::cin >> row;
            mat.set_row(i, row);
        }
        std::cout << mat.gaussian_elimination() << "\n";
    } else {
        GF2Matrix mat(m, n);
        for (auto i = 0; i < n; ++i) {
            for (auto j = 0; j < m; ++j) {
                char c;
                std::cin >> c;
                if (c == '1') {
                    mat.set(j, i);
                }
            }
        }
        std::cout << mat.gaussian_elimination() << "\n";
    }
}
