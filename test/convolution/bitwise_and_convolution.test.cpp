#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_and_convolution"

#include "convolution/and.hpp"
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
    auto C = and_convolution(A, B);
    for (auto i = 0; i < (1 << N); ++i) {
        std::cout << C[i].val() << " ";
    }
}
