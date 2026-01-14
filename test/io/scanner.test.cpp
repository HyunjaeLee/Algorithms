#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include "../io/scanner.hpp"
#include <bits/stdc++.h>

scanner scan;

int main() {
    int T;
    scan(T);
    while (T--) {
        long long A, B;
        scan(A, B);
        std::cout << A + B << '\n';
    }
}
