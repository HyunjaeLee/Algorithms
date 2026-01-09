#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_E"

#include "math/extgcd.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int a, b;
    std::cin >> a >> b;
    int x, y;
    extgcd(a, b, x, y);
    std::cout << x << " " << y << "\n";
}
