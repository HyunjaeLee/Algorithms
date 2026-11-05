---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: segment_tree/commutative_dual_segtree.hpp
    title: segment_tree/commutative_dual_segtree.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_E
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_E
  bundledCode: "#line 1 \"test/segment_tree/commutative_dual_segtree.test.cpp\"\n\
    #define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_E\"\n\n#line\
    \ 1 \"segment_tree/commutative_dual_segtree.hpp\"\n\n\n\n#include <bit>\n#include\
    \ <cassert>\n#include <utility>\n#include <vector>\n\n// https://suisen-cp.github.io/cp-library-cpp/library/datastructure/segment_tree/commutative_dual_segment_tree.hpp\n\
    template <typename S, typename F, auto mapping, auto composition, auto id>\nstruct\
    \ commutative_dual_segtree {\n    commutative_dual_segtree() = default;\n    commutative_dual_segtree(std::vector<S>\
    \ &&a)\n        : n(a.size()), m(std::bit_ceil(a.size())), data(std::move(a)),\
    \ lazy(m, id()) {}\n    commutative_dual_segtree(const std::vector<S> &a)\n  \
    \      : commutative_dual_segtree(std::vector<S>(a)) {}\n    commutative_dual_segtree(int\
    \ n, const S &fill_value)\n        : commutative_dual_segtree(std::vector<S>(n,\
    \ fill_value)) {}\n\n    S get(int i) const {\n        assert(0 <= i && i < n);\n\
    \        S res = data[i];\n        for (i = (i + m) >> 1; i; i >>= 1) {\n    \
    \        res = mapping(lazy[i], res);\n        }\n        return res;\n    }\n\
    \    S operator[](int i) const { return get(i); }\n    void apply(int l, int r,\
    \ const F &f) {\n        assert(0 <= l && l <= r && r <= n);\n        for (l +=\
    \ m, r += m; l < r; l >>= 1, r >>= 1) {\n            if (l & 1) {\n          \
    \      apply(l++, f);\n            }\n            if (r & 1) {\n             \
    \   apply(--r, f);\n            }\n        }\n    }\n\nprivate:\n    void apply(int\
    \ k, const F &f) {\n        if (k < m) {\n            lazy[k] = composition(f,\
    \ lazy[k]);\n        } else {\n            data[k - m] = mapping(f, data[k - m]);\n\
    \        }\n    }\n\n    int n, m;\n    std::vector<S> data;\n    std::vector<F>\
    \ lazy;\n};\n\n\n#line 4 \"test/segment_tree/commutative_dual_segtree.test.cpp\"\
    \n#include <bits/stdc++.h>\n\nusing S = int;\nusing F = int;\nS mapping(F f, S\
    \ x) { return f + x; }\nF composition(F f, F g) { return f + g; }\nF id() { return\
    \ 0; }\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int N, Q;\n\
    \    std::cin >> N >> Q;\n    commutative_dual_segtree<S, F, mapping, composition,\
    \ id> seg(N, 0);\n    while (Q--) {\n        int t;\n        std::cin >> t;\n\
    \        if (t == 0) {\n            int l, r, x;\n            std::cin >> l >>\
    \ r >> x;\n            --l;\n            seg.apply(l, r, x);\n        } else {\n\
    \            int i;\n            std::cin >> i;\n            --i;\n          \
    \  std::cout << seg.get(i) << \"\\n\";\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_E\"\n\n\
    #include \"segment_tree/commutative_dual_segtree.hpp\"\n#include <bits/stdc++.h>\n\
    \nusing S = int;\nusing F = int;\nS mapping(F f, S x) { return f + x; }\nF composition(F\
    \ f, F g) { return f + g; }\nF id() { return 0; }\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N, Q;\n    std::cin >> N >> Q;\n    commutative_dual_segtree<S, F, mapping,\
    \ composition, id> seg(N, 0);\n    while (Q--) {\n        int t;\n        std::cin\
    \ >> t;\n        if (t == 0) {\n            int l, r, x;\n            std::cin\
    \ >> l >> r >> x;\n            --l;\n            seg.apply(l, r, x);\n       \
    \ } else {\n            int i;\n            std::cin >> i;\n            --i;\n\
    \            std::cout << seg.get(i) << \"\\n\";\n        }\n    }\n}\n"
  dependsOn:
  - segment_tree/commutative_dual_segtree.hpp
  isVerificationFile: true
  path: test/segment_tree/commutative_dual_segtree.test.cpp
  requiredBy: []
  timestamp: '2026-11-05 06:06:56+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/segment_tree/commutative_dual_segtree.test.cpp
layout: document
redirect_from:
- /verify/test/segment_tree/commutative_dual_segtree.test.cpp
- /verify/test/segment_tree/commutative_dual_segtree.test.cpp.html
title: test/segment_tree/commutative_dual_segtree.test.cpp
---
