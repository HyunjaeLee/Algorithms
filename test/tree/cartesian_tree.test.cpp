#define PROBLEM "https://judge.yosupo.jp/problem/cartesian_tree"

#include "tree/cartesian_tree.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N;
    std::cin >> N;
    std::vector<int> A(N);
    copy_n(std::istream_iterator<int>(std::cin), N, A.begin());
    auto parent = cartesian_tree(A);
    for (auto i = 0; i < N; ++i) {
        std::cout << (~parent[i] ? parent[i] : i) << " ";
    }
}
