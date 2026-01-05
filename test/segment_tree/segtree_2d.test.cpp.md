---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: segment_tree/segtree_2d.hpp
    title: 2D Segment Tree
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/1068
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/1068
  bundledCode: "#line 1 \"test/segment_tree/segtree_2d.test.cpp\"\n#define PROBLEM\
    \ \"https://onlinejudge.u-aizu.ac.jp/problems/1068\"\n\n#line 1 \"segment_tree/segtree_2d.hpp\"\
    \n\n\n\n#include <cassert>\n#include <vector>\n\n// S op(S, S) - commutative monoid\
    \ operation\n// S e() - commutative monoid identity\ntemplate <typename S, auto\
    \ op, auto e> struct segtree_2d {\n    // O(n * m)\n    segtree_2d(int n, int\
    \ m) : n_(n), m_(m), data_(n << 1, std::vector<S>(m << 1, e())) {}\n    // O(n\
    \ * m)\n    segtree_2d(int n, int m, S x)\n        : segtree_2d(std::vector<std::vector<S>>(n,\
    \ std::vector<S>(m, x))) {}\n    // O(n * m)\n    segtree_2d(const std::vector<std::vector<S>>\
    \ &a)\n        : n_((int)a.size()), m_((int)a[0].size()),\n          data_((n_\
    \ << 1), std::vector<S>((m_ << 1), e())) {\n        for (auto i = 0; i < n_; ++i)\
    \ {\n            for (auto j = 0; j < m_; ++j) {\n                data_[i + n_][j\
    \ + m_] = a[i][j];\n            }\n        }\n        for (auto i = n_ - 1; i\
    \ >= 1; --i) {\n            for (auto j = 0; j < m_; ++j) {\n                data_[i][j\
    \ + m_] = op(data_[i << 1][j + m_], data_[i << 1 | 1][j + m_]);\n            }\n\
    \        }\n        for (auto i = 1; i < (n_ << 1); ++i) {\n            for (auto\
    \ j = m_ - 1; 0 < j; --j) {\n                data_[i][j] = op(data_[i][j << 1],\
    \ data_[i][j << 1 | 1]);\n            }\n        }\n    }\n    // a[r][c] := x\n\
    \    // O(log(n) * log(m))\n    void set(int r, int c, S x) {\n        assert(0\
    \ <= r && r < n_);\n        assert(0 <= c && c < m_);\n        data_[r += n_][c\
    \ += m_] = x;\n        for (auto j = c; j >>= 1;) {\n            data_[r][j] =\
    \ op(data_[r][j << 1], data_[r][j << 1 | 1]);\n        }\n        for (auto i\
    \ = r; i >>= 1;) {\n            data_[i][c] = op(data_[i << 1][c], data_[i <<\
    \ 1 | 1][c]);\n            for (auto j = c; j >>= 1;) {\n                data_[i][j]\
    \ = op(data_[i][j << 1], data_[i][j << 1 | 1]);\n            }\n        }\n  \
    \  }\n    // Returns a[r][c]\n    // O(1)\n    S get(int r, int c) {\n       \
    \ assert(0 <= r && r < n_);\n        assert(0 <= c && c < m_);\n        return\
    \ data_[r + n_][c + m_];\n    }\n    // Returns the sum of a[i][j] on [r1, r2)\
    \ X [c1, c2)\n    // O(log n * log m)\n    S prod(int r1, int r2, int c1, int\
    \ c2) {\n        assert(0 <= r1 && r1 <= r2 && r2 <= n_);\n        assert(0 <=\
    \ c1 && c1 <= c2 && c2 <= m_);\n        if (r1 >= r2 || c1 >= c2)\n          \
    \  return e();\n        S res = e();\n        r1 += n_, r2 += n_, c1 += m_, c2\
    \ += m_;\n        for (auto il = r1, ir = r2; il < ir; il >>= 1, ir >>= 1) {\n\
    \            if (il & 1) {\n                for (auto jl = c1, jr = c2; jl < jr;\
    \ jl >>= 1, jr >>= 1) {\n                    if (jl & 1) {\n                 \
    \       res = op(res, data_[il][jl++]);\n                    }\n             \
    \       if (jr & 1) {\n                        res = op(res, data_[il][--jr]);\n\
    \                    }\n                }\n                ++il;\n           \
    \ }\n            if (ir & 1) {\n                --ir;\n                for (auto\
    \ jl = c1, jr = c2; jl < jr; jl >>= 1, jr >>= 1) {\n                    if (jl\
    \ & 1) {\n                        res = op(res, data_[ir][jl++]);\n          \
    \          }\n                    if (jr & 1) {\n                        res =\
    \ op(res, data_[ir][--jr]);\n                    }\n                }\n      \
    \      }\n        }\n        return res;\n    }\n    int n_, m_;\n    std::vector<std::vector<S>>\
    \ data_;\n};\n\n\n#line 4 \"test/segment_tree/segtree_2d.test.cpp\"\n#include\
    \ <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    while (true) {\n        int N, M, Q;\n        std::cin >> N >> M >> Q;\n\
    \        if (N == 0 && M == 0 && Q == 0) {\n            break;\n        }\n  \
    \      using S = int;\n        auto op = [](S a, S b) -> S { return std::min(a,\
    \ b); };\n        auto e = []() -> S { return std::numeric_limits<int>::max();\
    \ };\n        segtree_2d<S, op, e> seg(N, M);\n        for (auto i = 0; i < N;\
    \ ++i) {\n            for (auto j = 0; j < M; ++j) {\n                int x;\n\
    \                std::cin >> x;\n                seg.set(i, j, x);\n         \
    \   }\n        }\n        while (Q--) {\n            int r1, c1, r2, c2;\n   \
    \         std::cin >> r1 >> c1 >> r2 >> c2;\n            auto ans = seg.prod(r1,\
    \ r2 + 1, c1, c2 + 1);\n            std::cout << ans << '\\n';\n        }\n  \
    \  }\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/1068\"\n\n#include\
    \ \"segment_tree/segtree_2d.hpp\"\n#include <bits/stdc++.h>\n\nint main() {\n\
    \    std::cin.tie(0)->sync_with_stdio(0);\n    while (true) {\n        int N,\
    \ M, Q;\n        std::cin >> N >> M >> Q;\n        if (N == 0 && M == 0 && Q ==\
    \ 0) {\n            break;\n        }\n        using S = int;\n        auto op\
    \ = [](S a, S b) -> S { return std::min(a, b); };\n        auto e = []() -> S\
    \ { return std::numeric_limits<int>::max(); };\n        segtree_2d<S, op, e> seg(N,\
    \ M);\n        for (auto i = 0; i < N; ++i) {\n            for (auto j = 0; j\
    \ < M; ++j) {\n                int x;\n                std::cin >> x;\n      \
    \          seg.set(i, j, x);\n            }\n        }\n        while (Q--) {\n\
    \            int r1, c1, r2, c2;\n            std::cin >> r1 >> c1 >> r2 >> c2;\n\
    \            auto ans = seg.prod(r1, r2 + 1, c1, c2 + 1);\n            std::cout\
    \ << ans << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - segment_tree/segtree_2d.hpp
  isVerificationFile: true
  path: test/segment_tree/segtree_2d.test.cpp
  requiredBy: []
  timestamp: '2026-01-05 19:28:19+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/segment_tree/segtree_2d.test.cpp
layout: document
redirect_from:
- /verify/test/segment_tree/segtree_2d.test.cpp
- /verify/test/segment_tree/segtree_2d.test.cpp.html
title: test/segment_tree/segtree_2d.test.cpp
---
