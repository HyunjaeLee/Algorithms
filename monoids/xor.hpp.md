---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/graph/odd_trip_plans.test.cpp
    title: test/graph/odd_trip_plans.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoids/xor.hpp\"\n\n\n\n// Xor Abelian Group\ntemplate\
    \ <typename T> struct Xor {\n    T val;\n    static Xor op(Xor a, Xor b) { return\
    \ {a.val ^ b.val}; }\n    static Xor e() { return {0}; }\n    static Xor inv(Xor\
    \ x) { return x; }\n    friend bool operator==(const Xor &a, const Xor &b) { return\
    \ a.val == b.val; }\n};\n\n\n"
  code: "#ifndef XOR_HPP\n#define XOR_HPP\n\n// Xor Abelian Group\ntemplate <typename\
    \ T> struct Xor {\n    T val;\n    static Xor op(Xor a, Xor b) { return {a.val\
    \ ^ b.val}; }\n    static Xor e() { return {0}; }\n    static Xor inv(Xor x) {\
    \ return x; }\n    friend bool operator==(const Xor &a, const Xor &b) { return\
    \ a.val == b.val; }\n};\n\n#endif // XOR_HPP"
  dependsOn: []
  isVerificationFile: false
  path: monoids/xor.hpp
  requiredBy: []
  timestamp: '2026-02-03 20:57:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/graph/odd_trip_plans.test.cpp
documentation_of: monoids/xor.hpp
layout: document
redirect_from:
- /library/monoids/xor.hpp
- /library/monoids/xor.hpp.html
title: monoids/xor.hpp
---
