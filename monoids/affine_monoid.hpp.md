---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/link_cut_tree/dynamic_tree_vertex_set_path_composite.test.cpp
    title: test/link_cut_tree/dynamic_tree_vertex_set_path_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/segment_tree/sparse_segtree.test.cpp
    title: test/segment_tree/sparse_segtree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoids/affine_monoid.hpp\"\n\n\n\ntemplate <typename Z>\
    \ struct AffineMonoid {\n    static AffineMonoid op(AffineMonoid f, AffineMonoid\
    \ g) {\n        auto [a, b] = f;\n        auto [c, d] = g;\n        return {c\
    \ * a, c * b + d};\n    }\n    static AffineMonoid e() { return {1, 0}; }\n  \
    \  Z a, b;\n};\n\n\n"
  code: "#ifndef AFFINE_MONOID_HPP\n#define AFFINE_MONOID_HPP\n\ntemplate <typename\
    \ Z> struct AffineMonoid {\n    static AffineMonoid op(AffineMonoid f, AffineMonoid\
    \ g) {\n        auto [a, b] = f;\n        auto [c, d] = g;\n        return {c\
    \ * a, c * b + d};\n    }\n    static AffineMonoid e() { return {1, 0}; }\n  \
    \  Z a, b;\n};\n\n#endif // AFFINE_MONOID_HPP"
  dependsOn: []
  isVerificationFile: false
  path: monoids/affine_monoid.hpp
  requiredBy: []
  timestamp: '2026-08-12 17:52:00+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/link_cut_tree/dynamic_tree_vertex_set_path_composite.test.cpp
  - test/segment_tree/sparse_segtree.test.cpp
documentation_of: monoids/affine_monoid.hpp
layout: document
redirect_from:
- /library/monoids/affine_monoid.hpp
- /library/monoids/affine_monoid.hpp.html
title: monoids/affine_monoid.hpp
---
