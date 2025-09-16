#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include "matching/stable_matching.hpp"
#include <bits/stdc++.h>

void assert_unique(std::vector<int> v, int n) {
    assert(static_cast<int>(v.size()) == n);
    std::sort(v.begin(), v.end());
    for (auto i = 0; i < n; ++i) {
        assert(v[i] == i);
    }
}

void test() {
    for (auto n = 1; n <= 100; ++n) {
        std::vector<std::vector<int>> a(n, std::vector<int>(n)),
            b(n, std::vector<int>(n));
        std::mt19937 g(0);
        for (auto i = 0; i < n; ++i) {
            std::iota(a[i].begin(), a[i].end(), 0);
            std::shuffle(a[i].begin(), a[i].end(), g);
        }
        for (auto i = 0; i < n; ++i) {
            std::iota(b[i].begin(), b[i].end(), 0);
            std::shuffle(b[i].begin(), b[i].end(), g);
        }
        std::vector<std::vector<int>> a_priority(n, std::vector<int>(n)),
            b_priority(n, std::vector<int>(n));
        for (auto i = 0; i < n; ++i) {
            for (auto j = 0; j < n; ++j) {
                a_priority[i][a[i][j]] = j;
            }
        }
        for (auto i = 0; i < n; ++i) {
            for (auto j = 0; j < n; ++j) {
                b_priority[i][b[i][j]] = j;
            }
        }
        auto a_match = stable_matching(a, b);
        assert_unique(a_match, n);
        std::vector<int> b_match(n);
        for (auto i = 0; i < n; ++i) {
            b_match[a_match[i]] = i;
        }
        for (auto i = 0; i < n; ++i) {
            for (auto j = 0; j < n; ++j) {
                assert(!(a_priority[i][j] < a_priority[i][a_match[i]] &&
                         b_priority[j][i] < b_priority[j][b_match[j]]));
            }
        }
    }
}

int main() {
    test();
    std::cout << "Hello World\n";
}
