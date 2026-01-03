---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/link_cut_tree/dynamic_tree_vertex_set_path_composite.test.cpp
    title: test/link_cut_tree/dynamic_tree_vertex_set_path_composite.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoids/reversible_monoid.hpp\"\n\n\n\ntemplate <typename\
    \ M> struct ReversibleMonoid {\n    ReversibleMonoid(M x) : val(x), rev(x) {}\n\
    \    ReversibleMonoid(M x, M y) : val(x), rev(y) {}\n    static ReversibleMonoid\
    \ op(ReversibleMonoid l, ReversibleMonoid r) {\n        return {M::op(l.val, r.val),\
    \ M::op(r.rev, l.rev)};\n    }\n    static ReversibleMonoid e() { return {M::e(),\
    \ M::e()}; }\n    static ReversibleMonoid toggle(ReversibleMonoid x) { return\
    \ {x.rev, x.val}; }\n    M val, rev;\n};\n\n\n"
  code: "#ifndef REVERSIBLE_MONOID_HPP\n#define REVERSIBLE_MONOID_HPP\n\ntemplate\
    \ <typename M> struct ReversibleMonoid {\n    ReversibleMonoid(M x) : val(x),\
    \ rev(x) {}\n    ReversibleMonoid(M x, M y) : val(x), rev(y) {}\n    static ReversibleMonoid\
    \ op(ReversibleMonoid l, ReversibleMonoid r) {\n        return {M::op(l.val, r.val),\
    \ M::op(r.rev, l.rev)};\n    }\n    static ReversibleMonoid e() { return {M::e(),\
    \ M::e()}; }\n    static ReversibleMonoid toggle(ReversibleMonoid x) { return\
    \ {x.rev, x.val}; }\n    M val, rev;\n};\n\n#endif // REVERSIBLE_MONOID_HPP"
  dependsOn: []
  isVerificationFile: false
  path: monoids/reversible_monoid.hpp
  requiredBy: []
  timestamp: '2026-01-04 02:17:36+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/link_cut_tree/dynamic_tree_vertex_set_path_composite.test.cpp
documentation_of: monoids/reversible_monoid.hpp
layout: document
redirect_from:
- /library/monoids/reversible_monoid.hpp
- /library/monoids/reversible_monoid.hpp.html
title: monoids/reversible_monoid.hpp
---
