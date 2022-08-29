#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include "../io/scanner.hpp"
#include <iostream>

scanner scan;

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int T;
    scan(T);
    while (T--) {
        long long A, B;
        scan(A, B);
        std::cout << A + B << '\n';
    }
}
