---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/math/extgcd.test.cpp
    title: test/math/extgcd.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/extgcd.hpp\"\n\n\n\ntemplate <typename T> T extgcd(T\
    \ a, T b, T &x, T &y) {\n    if (b == 0) {\n        x = 1, y = 0;\n        return\
    \ a;\n    }\n    T d = extgcd(b, a % b, y, x);\n    y -= a / b * x;\n    return\
    \ d;\n}\n\n\n"
  code: "#ifndef EXTGCD_HPP\n#define EXTGCD_HPP\n\ntemplate <typename T> T extgcd(T\
    \ a, T b, T &x, T &y) {\n    if (b == 0) {\n        x = 1, y = 0;\n        return\
    \ a;\n    }\n    T d = extgcd(b, a % b, y, x);\n    y -= a / b * x;\n    return\
    \ d;\n}\n\n#endif // EXTGCD_HPP"
  dependsOn: []
  isVerificationFile: false
  path: math/extgcd.hpp
  requiredBy: []
  timestamp: '2026-01-09 14:45:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/math/extgcd.test.cpp
documentation_of: math/extgcd.hpp
layout: document
title: Extended Euclidean Algorithm
---

Computes $g = \gcd(a,b)$ and find integers $x$ and $y$ such that $ax+by=g$.
+ $g$ may be negative.
+ $|x| \le \left| \frac{b}{g} \right|$
+ $|y| \le \left| \frac{a}{g} \right|$

> **Bézout's identity**—Let $a$ and $b$ be integers with greatest common divisor $g$. Then there exist integers $x$ and $y$ such that $ax + by = g$. Moreover, the integers of the form $az + bt$ are exactly the multiples of $g$.

### Complexity

+ $ \mathcal{O(\log(\min(a, b)))} $

### References
+ [euclid.h - KACTL](https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/euclid.h)
+ [Extended Euclidean Algorithm - CP Algorithms](https://cp-algorithms.com/algebra/extended-euclid-algorithm.html)
+ [Extended Euclidean algorithm - Wikipedia](https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm)
+ [Bézout's identity - Wikipedia](https://en.wikipedia.org/wiki/B%C3%A9zout%27s_identity)
+ [Proof of Bounds for the Extended Euclidean Algorithm - Jeffrey Hurchalla](https://jeffhurchalla.com/2018/10/09/analysis-of-bounds-in-the-extended-euclidean-algorithm/)
