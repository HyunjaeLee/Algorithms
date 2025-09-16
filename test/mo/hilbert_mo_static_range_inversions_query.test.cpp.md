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
    #include <cassert>\n#include <vector>\n\nstruct hilbert_mo {\n    hilbert_mo(int\
    \ n) : n_(n), log_(std::__lg(std::max(1, n_)) + 1) {}\n    void add(int l, int\
    \ r) {\n        assert(0 <= l && l <= r && r <= n_);\n        auto index = static_cast<int>(queries_.size());\n\
    \        auto order = hilbert_order(l, r, log_, 0);\n        queries_.push_back({l,\
    \ r, index, order});\n    }\n    template <typename Add, typename Remove, typename\
    \ Eval>\n    void run(Add add, Remove remove, Eval eval) {\n        run(add, add,\
    \ remove, remove, eval);\n    }\n    template <typename AddLeft, typename AddRight,\
    \ typename RemoveLeft,\n              typename RemoveRight, typename Eval>\n \
    \   void run(AddLeft add_left, AddRight add_right, RemoveLeft remove_left,\n \
    \            RemoveRight remove_right, Eval eval) {\n        sort(queries_.begin(),\
    \ queries_.end());\n        auto l = 0, r = 0;\n        for (auto [left, right,\
    \ index, order] : queries_) {\n            while (left < l) {\n              \
    \  add_left(--l);\n            }\n            while (r < right) {\n          \
    \      add_right(r++);\n            }\n            while (l < left) {\n      \
    \          remove_left(l++);\n            }\n            while (right < r) {\n\
    \                remove_right(--r);\n            }\n            eval(index);\n\
    \        }\n    }\n\nprivate:\n    struct query {\n        int left, right, index;\n\
    \        long long order;\n        bool operator<(const query &other) const {\
    \ return order < other.order; }\n    };\n    long long hilbert_order(int x, int\
    \ y, int pow, int rotate) const {\n        if (pow == 0) {\n            return\
    \ 0;\n        }\n        auto hpow = 1 << (pow - 1);\n        auto seg = (x <\
    \ hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);\n        seg = (seg + rotate)\
    \ & 3;\n        const std::array<int, 4> rotate_delta{3, 0, 0, 1};\n        auto\
    \ nx = x & (x ^ hpow), ny = y & (y ^ hpow);\n        auto nrot = (rotate + rotate_delta[seg])\
    \ & 3;\n        auto subsquare_size = static_cast<long long>(1) << (2 * pow -\
    \ 2);\n        auto ans = seg * subsquare_size;\n        auto add = hilbert_order(nx,\
    \ ny, pow - 1, nrot);\n        ans += (seg == 1 || seg == 2) ? add : (subsquare_size\
    \ - add - 1);\n        return ans;\n    }\n    std::vector<query> queries_;\n\
    \    const int n_, log_;\n};\n\n\n#line 4 \"test/mo/hilbert_mo_static_range_inversions_query.test.cpp\"\
    \n#include <atcoder/fenwicktree>\n#include <bits/stdc++.h>\n\nint main() {\n \
    \   std::cin.tie(0)->sync_with_stdio(0);\n    int N, Q;\n    std::cin >> N >>\
    \ Q;\n    std::vector<int> A(N);\n    for (auto &x : A) {\n        std::cin >>\
    \ x;\n    }\n    std::vector<int> c(A);\n    std::sort(c.begin(), c.end());\n\
    \    c.erase(std::unique(c.begin(), c.end()), c.end());\n    for (auto &x : A)\
    \ {\n        auto it = std::lower_bound(c.begin(), c.end(), x);\n        x = static_cast<int>(it\
    \ - c.begin());\n    }\n    hilbert_mo mo(N);\n    for (auto i = 0; i < Q; ++i)\
    \ {\n        int l, r;\n        std::cin >> l >> r;\n        mo.add(l, r);\n \
    \   }\n    auto s = 0LL;\n    auto k = static_cast<int>(c.size());\n    atcoder::fenwick_tree<int>\
    \ ft(k);\n    auto add_left = [&](auto i) {\n        s += ft.sum(0, A[i]);\n \
    \       ft.add(A[i], 1);\n    };\n    auto add_right = [&](auto i) {\n       \
    \ s += ft.sum(A[i] + 1, k);\n        ft.add(A[i], 1);\n    };\n    auto remove_left\
    \ = [&](auto i) {\n        s -= ft.sum(0, A[i]);\n        ft.add(A[i], -1);\n\
    \    };\n    auto remove_right = [&](auto i) {\n        s -= ft.sum(A[i] + 1,\
    \ k);\n        ft.add(A[i], -1);\n    };\n    std::vector<long long> ans(Q);\n\
    \    auto eval = [&](auto i) { ans[i] = s; };\n    mo.run(add_left, add_right,\
    \ remove_left, remove_right, eval);\n    for (auto x : ans) {\n        std::cout\
    \ << x << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_inversions_query\"\
    \n\n#include \"mo/hilbert_mo.hpp\"\n#include <atcoder/fenwicktree>\n#include <bits/stdc++.h>\n\
    \nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int N, Q;\n    std::cin\
    \ >> N >> Q;\n    std::vector<int> A(N);\n    for (auto &x : A) {\n        std::cin\
    \ >> x;\n    }\n    std::vector<int> c(A);\n    std::sort(c.begin(), c.end());\n\
    \    c.erase(std::unique(c.begin(), c.end()), c.end());\n    for (auto &x : A)\
    \ {\n        auto it = std::lower_bound(c.begin(), c.end(), x);\n        x = static_cast<int>(it\
    \ - c.begin());\n    }\n    hilbert_mo mo(N);\n    for (auto i = 0; i < Q; ++i)\
    \ {\n        int l, r;\n        std::cin >> l >> r;\n        mo.add(l, r);\n \
    \   }\n    auto s = 0LL;\n    auto k = static_cast<int>(c.size());\n    atcoder::fenwick_tree<int>\
    \ ft(k);\n    auto add_left = [&](auto i) {\n        s += ft.sum(0, A[i]);\n \
    \       ft.add(A[i], 1);\n    };\n    auto add_right = [&](auto i) {\n       \
    \ s += ft.sum(A[i] + 1, k);\n        ft.add(A[i], 1);\n    };\n    auto remove_left\
    \ = [&](auto i) {\n        s -= ft.sum(0, A[i]);\n        ft.add(A[i], -1);\n\
    \    };\n    auto remove_right = [&](auto i) {\n        s -= ft.sum(A[i] + 1,\
    \ k);\n        ft.add(A[i], -1);\n    };\n    std::vector<long long> ans(Q);\n\
    \    auto eval = [&](auto i) { ans[i] = s; };\n    mo.run(add_left, add_right,\
    \ remove_left, remove_right, eval);\n    for (auto x : ans) {\n        std::cout\
    \ << x << '\\n';\n    }\n}\n"
  dependsOn:
  - mo/hilbert_mo.hpp
  isVerificationFile: true
  path: test/mo/hilbert_mo_static_range_inversions_query.test.cpp
  requiredBy: []
  timestamp: '2025-09-16 22:59:29+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/mo/hilbert_mo_static_range_inversions_query.test.cpp
layout: document
redirect_from:
- /verify/test/mo/hilbert_mo_static_range_inversions_query.test.cpp
- /verify/test/mo/hilbert_mo_static_range_inversions_query.test.cpp.html
title: test/mo/hilbert_mo_static_range_inversions_query.test.cpp
---
