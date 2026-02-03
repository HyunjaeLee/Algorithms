---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/graph/jag_regional_2022_i.test.cpp
    title: test/graph/jag_regional_2022_i.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoids/sum.hpp\"\n\n\n\n// Additive Abelian Group\ntemplate\
    \ <typename T> struct Sum {\n    T val;\n    static Sum op(Sum a, Sum b) { return\
    \ {a.val + b.val}; }\n    static Sum e() { return {0}; }\n    static Sum inv(Sum\
    \ x) { return {-x.val}; }\n    friend bool operator==(const Sum &a, const Sum\
    \ &b) { return a.val == b.val; }\n};\n\n\n"
  code: "#ifndef SUM_HPP\n#define SUM_HPP\n\n// Additive Abelian Group\ntemplate <typename\
    \ T> struct Sum {\n    T val;\n    static Sum op(Sum a, Sum b) { return {a.val\
    \ + b.val}; }\n    static Sum e() { return {0}; }\n    static Sum inv(Sum x) {\
    \ return {-x.val}; }\n    friend bool operator==(const Sum &a, const Sum &b) {\
    \ return a.val == b.val; }\n};\n\n#endif // SUM_HPP"
  dependsOn: []
  isVerificationFile: false
  path: monoids/sum.hpp
  requiredBy: []
  timestamp: '2026-02-03 20:57:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/graph/jag_regional_2022_i.test.cpp
documentation_of: monoids/sum.hpp
layout: document
redirect_from:
- /library/monoids/sum.hpp
- /library/monoids/sum.hpp.html
title: monoids/sum.hpp
---
