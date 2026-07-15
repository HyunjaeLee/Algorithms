#define PROBLEM "https://judge.yosupo.jp/problem/double_ended_priority_queue"

#include "data_structures/interval_heap.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    std::cin >> N >> Q;
    interval_heap<int> pq;
    for (auto i = 0; i < N; ++i) {
        int x;
        std::cin >> x;
        pq.push(x);
    }
    for (auto i = 0; i < Q; ++i) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int x;
            std::cin >> x;
            pq.push(x);
        } else if (t == 1) {
            std::cout << pq.min() << "\n";
            pq.pop_min();
        } else {
            std::cout << pq.max() << "\n";
            pq.pop_max();
        }
    }
}
