#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2235"

#include "../graph/dynamic_connectivity.hpp"
#include <bits/stdc++.h>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int n, k;
    std::cin >> n >> k;
    dynamic_connectivity dc(n);
    for (auto i = 0; i < k; ++i) {
        int q, u, v;
        std::cin >> q >> u >> v;
        switch (q) {
        case 1:
            dc.link(u, v);
            break;
        case 2:
            dc.cut(u, v);
            break;
        case 3:
            std::cout << (dc.connected(u, v) ? "YES\n" : "NO\n");
            break;
        }
    }
}
