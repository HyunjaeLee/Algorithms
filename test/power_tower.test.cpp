#define PROBLEM "https://yukicoder.me/problems/no/181"

#include "math/power_tower.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int A, N, M;
    std::cin >> A >> N >> M;
    std::vector<int> a(std::min(N, 24), A);
    std::cout << power_tower(a, M) << '\n';
}
