#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_A"

#include "../random/xoshiro256starstar.hpp"
#include "../treap/treap_set.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int q;
    std::cin >> q;
    treap_set<int, xoshiro256starstar> s;
    while (q--) {
        int t, x;
        std::cin >> t >> x;
        if (t == 0) {
            s.insert(x);
            std::cout << s.size() << '\n';
        } else {
            std::cout << (s.contains(x) ? 1 : 0) << '\n';
        }
    }
}
