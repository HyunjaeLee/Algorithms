#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"

#include "data_structures/hash_map.hpp"
#include <bits/stdc++.h>

hash_map<long long, long long, 1 << 20> mp;

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int Q;
    std::cin >> Q;
    while (Q--) {
        int t;
        std::cin >> t;
        if (t == 0) {
            long long k, v;
            std::cin >> k >> v;
            mp.set(k, v);
        } else {
            long long k;
            std::cin >> k;
            std::cout << mp.get(k).value_or(0) << "\n";
        }
    }
}
