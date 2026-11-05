---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/segment_tree/commutative_dual_segtree.test.cpp
    title: test/segment_tree/commutative_dual_segtree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://suisen-cp.github.io/cp-library-cpp/library/datastructure/segment_tree/commutative_dual_segment_tree.hpp
  bundledCode: "#line 1 \"segment_tree/commutative_dual_segtree.hpp\"\n\n\n\n#include\
    \ <bit>\n#include <cassert>\n#include <utility>\n#include <vector>\n\n// https://suisen-cp.github.io/cp-library-cpp/library/datastructure/segment_tree/commutative_dual_segment_tree.hpp\n\
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
    \ lazy;\n};\n\n\n"
  code: "#ifndef COMMUTATIVE_DUAL_SEGTREE_HPP\n#define COMMUTATIVE_DUAL_SEGTREE_HPP\n\
    \n#include <bit>\n#include <cassert>\n#include <utility>\n#include <vector>\n\n\
    // https://suisen-cp.github.io/cp-library-cpp/library/datastructure/segment_tree/commutative_dual_segment_tree.hpp\n\
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
    \ lazy;\n};\n\n#endif // COMMUTATIVE_DUAL_SEGTREE_HPP"
  dependsOn: []
  isVerificationFile: false
  path: segment_tree/commutative_dual_segtree.hpp
  requiredBy: []
  timestamp: '2026-11-05 06:06:56+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/segment_tree/commutative_dual_segtree.test.cpp
documentation_of: segment_tree/commutative_dual_segtree.hpp
layout: document
redirect_from:
- /library/segment_tree/commutative_dual_segtree.hpp
- /library/segment_tree/commutative_dual_segtree.hpp.html
title: segment_tree/commutative_dual_segtree.hpp
---
