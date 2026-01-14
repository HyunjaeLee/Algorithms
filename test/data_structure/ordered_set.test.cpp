#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"

#include "data_structure/ordered_set.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    std::cin >> N >> Q;
    ordered_set<int> s;
    for (auto i = 0; i < N; ++i) {
        int a;
        std::cin >> a;
        s.insert(a);
    }
    for (auto i = 0; i < Q; ++i) {
        int t, x;
        std::cin >> t >> x;
        if (t == 0) {
            s.insert(x);
        } else if (t == 1) {
            s.erase(x);
        } else if (t == 2) {
            auto it = s.find_by_order(x - 1);
            std::cout << (it != s.end() ? *it : -1) << "\n";
        } else if (t == 3) {
            std::cout << s.order_of_key(x + 1) << "\n";
        } else if (t == 4) {
            auto it = s.upper_bound(x);
            std::cout << (it != s.begin() ? *std::prev(it) : -1) << "\n";
        } else if (t == 5) {
            auto it = s.lower_bound(x);
            std::cout << (it != s.end() ? *it : -1) << "\n";
        }
    }
}
