#define PROBLEM "https://judge.yosupo.jp/problem/factorize"

#include "math/factor.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int Q;
    std::cin >> Q;
    for (auto i = 0; i < Q; ++i) {
        unsigned long long a;
        std::cin >> a;
        auto f = factor(a);
        std::sort(f.begin(), f.end());
        std::cout << f.size() << ' ';
        std::copy(f.begin(), f.end(),
                  std::ostream_iterator<unsigned long long>(std::cout, " "));
        std::cout << '\n';
    }
}
