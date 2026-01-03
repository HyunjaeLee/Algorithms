#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum"

#include "link_cut_tree/link_cut_tree.hpp"
#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    cin >> N >> Q;
    vector<long long> A(N);
    copy_n(istream_iterator<long long>(cin), N, begin(A));
    auto op = [](long long a, long long b) -> long long { return a + b; };
    auto e = []() -> long long { return 0LL; };
    auto mapping = [](long long f, long long x) -> long long { return f + x; };
    auto composition = [](long long f, long long g) -> long long { return f + g; };
    auto id = []() -> long long { return 0LL; };
    link_cut_tree<long long, op, e, long long, mapping, composition, id> lct(N);
    for (auto i = 0; i < N; ++i) {
        lct.set(i, A[i]);
    }
    for (auto i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        lct.link(u, v);
    }
    while (Q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int u, v, w, x;
            cin >> u >> v >> w >> x;
            lct.cut(u, v);
            lct.link(w, x);
        } else if (t == 1) {
            int p, x;
            cin >> p >> x;
            A[p] += x;
            lct.set(p, A[p]);
        } else {
            int u, v;
            cin >> u >> v;
            cout << lct.prod(u, v) << '\n';
        }
    }
}
