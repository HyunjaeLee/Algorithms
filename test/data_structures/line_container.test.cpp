#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"

#include "data_structures/line_container.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    std::cin >> N >> Q;
    line_container<long long, false> lc;
    for (auto i = 0; i < N; ++i) {
        long long a, b;
        std::cin >> a >> b;
        lc.add(a, b);
    }
    while (Q--) {
        int t;
        std::cin >> t;
        if (t == 0) {
            long long a, b;
            std::cin >> a >> b;
            lc.add(a, b);
        } else {
            int x;
            std::cin >> x;
            std::cout << lc.query(x) << "\n";
        }
    }
}
