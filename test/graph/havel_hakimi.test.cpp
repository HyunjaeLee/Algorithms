#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/4003"

#include "graph/havel_hakimi.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N;
    std::cin >> N;
    std::vector<int> deg(N);
    for (auto &d : deg) {
        std::cin >> d;
    }
    std::cout << (havel_hakimi(deg) ? "Yes\n" : "No\n");
}
