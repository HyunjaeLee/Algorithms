---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: sparse_table/sparse_table.hpp
    title: Sparse Table
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/staticrmq
    links:
    - https://judge.yosupo.jp/problem/staticrmq
  bundledCode: "#line 1 \"test/sparse_table/static_rmq.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/staticrmq\"\n\n#line 1 \"sparse_table/sparse_table.hpp\"\
    \n\n\n\n#include <bit>\n#include <cassert>\n#include <type_traits>\n#include <vector>\n\
    \ntemplate <typename S, auto op, auto e> struct sparse_table {\n    static_assert(std::is_invocable_r_v<S,\
    \ decltype(op), S, S>,\n                  \"op must be a function of type S(S,\
    \ S)\");\n    static_assert(std::is_invocable_r_v<S, decltype(e)>,\n         \
    \         \"e must be a function of type S()\");\n    sparse_table(const std::vector<S>\
    \ &v)\n        : n_((int)v.size()), width_(std::bit_width(v.size())),\n      \
    \    table_(width_, std::vector<S>(v.size())) {\n        table_[0] = v;\n    \
    \    for (auto i = 1; i < width_; ++i) {\n            for (auto j = 0; j + (1\
    \ << i) <= n_; ++j) {\n                table_[i][j] =\n                    op(table_[i\
    \ - 1][j], table_[i - 1][j + (1 << (i - 1))]);\n            }\n        }\n   \
    \ }\n    S prod(int l, int r) {\n        assert(0 <= l && l <= r && r <= n_);\n\
    \        auto sum = e();\n        for (auto i = width_ - 1; 0 <= i; --i) {\n \
    \           if ((1 << i) <= r - l) {\n                sum = op(sum, table_[i][l]);\n\
    \                l += (1 << i);\n            }\n        }\n        return sum;\n\
    \    }\n    S prod_idempotent(int l, int r) {\n        assert(0 <= l && l <= r\
    \ && r <= n_);\n        if (l == r) {\n            return e();\n        }\n  \
    \      auto i = std::bit_width(unsigned(r - l)) - 1;\n        return op(table_[i][l],\
    \ table_[i][r - (1 << i)]);\n    }\n\nprivate:\n    int n_, width_;\n    std::vector<std::vector<S>>\
    \ table_;\n};\n\n\n#line 4 \"test/sparse_table/static_rmq.test.cpp\"\n#include\
    \ <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N, Q;\n    std::cin >> N >> Q;\n    std::vector<int> A(N);\n    for (auto\
    \ &x : A) {\n        std::cin >> x;\n    }\n    auto op = [](auto a, auto b) {\
    \ return std::min(a, b); };\n    auto e = []() { return std::numeric_limits<int>::max();\
    \ };\n    sparse_table<int, op, e> S(A);\n    while (Q--) {\n        int l, r;\n\
    \        std::cin >> l >> r;\n        auto ans = S.prod_idempotent(l, r);\n  \
    \      std::cout << ans << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\n\n#include\
    \ \"sparse_table/sparse_table.hpp\"\n#include <bits/stdc++.h>\n\nint main() {\n\
    \    std::cin.tie(0)->sync_with_stdio(0);\n    int N, Q;\n    std::cin >> N >>\
    \ Q;\n    std::vector<int> A(N);\n    for (auto &x : A) {\n        std::cin >>\
    \ x;\n    }\n    auto op = [](auto a, auto b) { return std::min(a, b); };\n  \
    \  auto e = []() { return std::numeric_limits<int>::max(); };\n    sparse_table<int,\
    \ op, e> S(A);\n    while (Q--) {\n        int l, r;\n        std::cin >> l >>\
    \ r;\n        auto ans = S.prod_idempotent(l, r);\n        std::cout << ans <<\
    \ '\\n';\n    }\n}\n"
  dependsOn:
  - sparse_table/sparse_table.hpp
  isVerificationFile: true
  path: test/sparse_table/static_rmq.test.cpp
  requiredBy: []
  timestamp: '2025-09-16 22:59:29+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/sparse_table/static_rmq.test.cpp
layout: document
redirect_from:
- /verify/test/sparse_table/static_rmq.test.cpp
- /verify/test/sparse_table/static_rmq.test.cpp.html
title: test/sparse_table/static_rmq.test.cpp
---
