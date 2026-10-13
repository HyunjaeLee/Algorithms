#define PROBLEM "https://yukicoder.me/problems/no/2012"

#include "data_structures/line_container_2d.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N;
    std::cin >> N;
    std::vector<std::pair<int, int>> P(N);
    line_container_2d<long long> lc;
    for (auto &[x, y] : P) {
        std::cin >> x >> y;
        lc.add(x, y);
    }
    auto ans = 0LL;
    for (auto [x, y] : P) {
        ans = std::max({ans, lc.max(y, -x), lc.max(-y, x)});
    }
    std::cout << ans << "\n";
}
