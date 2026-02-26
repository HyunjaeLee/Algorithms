---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: mo/hilbert_mo.hpp
    title: mo/hilbert_mo.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/static_range_inversions_query
    links:
    - https://judge.yosupo.jp/problem/static_range_inversions_query
  bundledCode: "#line 1 \"test/mo/hilbert_mo_static_range_inversions_query.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_inversions_query\"\
    \n\n#line 1 \"mo/hilbert_mo.hpp\"\n\n\n\n#include <algorithm>\n#include <array>\n\
    #include <cassert>\n#include <vector>\n\nstruct HilbertMo {\n    HilbertMo(int\
    \ n) : n_(n), log_(std::bit_width(unsigned(n))) {}\n    void add(int l, int r)\
    \ {\n        assert(0 <= l && l <= r && r <= n_);\n        auto index = int(queries_.size());\n\
    \        auto order = hilbert_order(l, r);\n        queries_.push_back({l, r,\
    \ index, order});\n    }\n    void solve(auto add, auto remove, auto eval) { solve(add,\
    \ add, remove, remove, eval); }\n    void solve(auto add_left, auto add_right,\
    \ auto remove_left, auto remove_right, auto eval) {\n        sort(queries_.begin(),\
    \ queries_.end());\n        auto l = 0, r = 0;\n        for (auto [left, right,\
    \ index, order] : queries_) {\n            while (left < l) {\n              \
    \  add_left(--l);\n            }\n            while (r < right) {\n          \
    \      add_right(r++);\n            }\n            while (l < left) {\n      \
    \          remove_left(l++);\n            }\n            while (right < r) {\n\
    \                remove_right(--r);\n            }\n            eval(index);\n\
    \        }\n    }\n\nprivate:\n    struct query {\n        int left, right, index;\n\
    \        long long order;\n        bool operator<(const query &other) const {\
    \ return order < other.order; }\n    };\n    long long hilbert_order(int x, int\
    \ y) const {\n        long long d = 0;\n        for (int s = 1 << log_; s > 0;\
    \ s >>= 1) {\n            bool rx = x & s, ry = y & s;\n            d = (d <<\
    \ 2) | ((rx * 3) ^ ry);\n            if (!ry) {\n                if (rx) {\n \
    \                   x = ~x;\n                    y = ~y;\n                }\n\
    \                std::swap(x, y);\n            }\n        }\n        return d;\n\
    \    }\n    std::vector<query> queries_;\n    const int n_, log_;\n};\n\n\n#line\
    \ 4 \"test/mo/hilbert_mo_static_range_inversions_query.test.cpp\"\n#include <atcoder/fenwicktree>\n\
    #include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N, Q;\n    std::cin >> N >> Q;\n    std::vector<int> A(N);\n    for (auto\
    \ &x : A) {\n        std::cin >> x;\n    }\n    std::vector<int> c(A);\n    std::sort(c.begin(),\
    \ c.end());\n    c.erase(std::unique(c.begin(), c.end()), c.end());\n    for (auto\
    \ &x : A) {\n        auto it = std::lower_bound(c.begin(), c.end(), x);\n    \
    \    x = static_cast<int>(it - c.begin());\n    }\n    HilbertMo mo(N);\n    for\
    \ (auto i = 0; i < Q; ++i) {\n        int l, r;\n        std::cin >> l >> r;\n\
    \        mo.add(l, r);\n    }\n    auto s = 0LL;\n    auto k = static_cast<int>(c.size());\n\
    \    atcoder::fenwick_tree<int> ft(k);\n    auto add_left = [&](auto i) {\n  \
    \      s += ft.sum(0, A[i]);\n        ft.add(A[i], 1);\n    };\n    auto add_right\
    \ = [&](auto i) {\n        s += ft.sum(A[i] + 1, k);\n        ft.add(A[i], 1);\n\
    \    };\n    auto remove_left = [&](auto i) {\n        s -= ft.sum(0, A[i]);\n\
    \        ft.add(A[i], -1);\n    };\n    auto remove_right = [&](auto i) {\n  \
    \      s -= ft.sum(A[i] + 1, k);\n        ft.add(A[i], -1);\n    };\n    std::vector<long\
    \ long> ans(Q);\n    auto eval = [&](auto i) { ans[i] = s; };\n    mo.solve(add_left,\
    \ add_right, remove_left, remove_right, eval);\n    for (auto x : ans) {\n   \
    \     std::cout << x << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_inversions_query\"\
    \n\n#include \"mo/hilbert_mo.hpp\"\n#include <atcoder/fenwicktree>\n#include <bits/stdc++.h>\n\
    \nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int N, Q;\n    std::cin\
    \ >> N >> Q;\n    std::vector<int> A(N);\n    for (auto &x : A) {\n        std::cin\
    \ >> x;\n    }\n    std::vector<int> c(A);\n    std::sort(c.begin(), c.end());\n\
    \    c.erase(std::unique(c.begin(), c.end()), c.end());\n    for (auto &x : A)\
    \ {\n        auto it = std::lower_bound(c.begin(), c.end(), x);\n        x = static_cast<int>(it\
    \ - c.begin());\n    }\n    HilbertMo mo(N);\n    for (auto i = 0; i < Q; ++i)\
    \ {\n        int l, r;\n        std::cin >> l >> r;\n        mo.add(l, r);\n \
    \   }\n    auto s = 0LL;\n    auto k = static_cast<int>(c.size());\n    atcoder::fenwick_tree<int>\
    \ ft(k);\n    auto add_left = [&](auto i) {\n        s += ft.sum(0, A[i]);\n \
    \       ft.add(A[i], 1);\n    };\n    auto add_right = [&](auto i) {\n       \
    \ s += ft.sum(A[i] + 1, k);\n        ft.add(A[i], 1);\n    };\n    auto remove_left\
    \ = [&](auto i) {\n        s -= ft.sum(0, A[i]);\n        ft.add(A[i], -1);\n\
    \    };\n    auto remove_right = [&](auto i) {\n        s -= ft.sum(A[i] + 1,\
    \ k);\n        ft.add(A[i], -1);\n    };\n    std::vector<long long> ans(Q);\n\
    \    auto eval = [&](auto i) { ans[i] = s; };\n    mo.solve(add_left, add_right,\
    \ remove_left, remove_right, eval);\n    for (auto x : ans) {\n        std::cout\
    \ << x << '\\n';\n    }\n}\n"
  dependsOn:
  - mo/hilbert_mo.hpp
  isVerificationFile: true
  path: test/mo/hilbert_mo_static_range_inversions_query.test.cpp
  requiredBy: []
  timestamp: '2026-02-26 17:06:24+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/mo/hilbert_mo_static_range_inversions_query.test.cpp
layout: document
redirect_from:
- /verify/test/mo/hilbert_mo_static_range_inversions_query.test.cpp
- /verify/test/mo/hilbert_mo_static_range_inversions_query.test.cpp.html
title: test/mo/hilbert_mo_static_range_inversions_query.test.cpp
---
