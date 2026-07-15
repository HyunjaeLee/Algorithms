#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_and_convolution"

#include "convolution/or.hpp"
#include <atcoder/modint>
#include <bits/stdc++.h>
using Z = atcoder::modint998244353;

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N;
    std::cin >> N;
    std::vector<Z> A(1 << N);
    for (auto i = 0; i < (1 << N); ++i) {
        int x;
        std::cin >> x;
        A[i] = x;
    }
    std::vector<Z> B(1 << N);
    for (auto i = 0; i < (1 << N); ++i) {
        int x;
        std::cin >> x;
        B[i] = x;
    }
    std::ranges::reverse(A);
    std::ranges::reverse(B);
    auto C = or_convolution(A, B);
    std::ranges::reverse(C);
    for (auto i = 0; i < (1 << N); ++i) {
        std::cout << C[i].val() << " ";
    }
}
