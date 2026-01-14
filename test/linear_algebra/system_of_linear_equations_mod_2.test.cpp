#define PROBLEM "https://judge.yosupo.jp/problem/system_of_linear_equations_mod_2"

#include "linear_algebra/gf2_matrix.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int n, m;
    std::cin >> n >> m;
    GF2Matrix mat(n, m + 1);
    for (auto i = 0; i < n; ++i) {
        std::string row;
        std::cin >> row;
        mat.set_row(i, row);
    }
    for (auto i = 0; i < n; ++i) {
        char c;
        std::cin >> c;
        if (c == '1') {
            mat.set(i, m);
        }
    }
    auto ans = mat.solve();
    if (ans.empty()) {
        std::cout << "-1\n";
    } else {
        std::cout << ans.size() - 1 << "\n";
        for (const auto &v : ans) {
            for (auto i = 0; i < m; ++i) {
                std::cout << v[i];
            }
            std::cout << "\n";
        }
    }
}
