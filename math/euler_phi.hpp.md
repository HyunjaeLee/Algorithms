---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/math/euler_phi.test.cpp
    title: test/math/euler_phi.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/euler_phi.hpp\"\n\n\n\n#include <vector>\n#include\
    \ <cassert>\n\nstd::vector<int> euler_phi(int n) {\n    assert(0 < n);\n    std::vector<int>\
    \ prime, phi(n + 1);\n    std::vector<char> is_prime(n + 1, true);\n    is_prime[0]\
    \ = is_prime[1] = false;\n    phi[1] = 1;\n    for (auto i = 2; i <= n; ++i) {\n\
    \        if (is_prime[i]) {\n            prime.push_back(i);\n            phi[i]\
    \ = i - 1;\n        }\n        for (auto p : prime) {\n            if (i * p >\
    \ n) {\n                break;\n            }\n            is_prime[i * p] = false;\n\
    \            if (i % p == 0) {\n                phi[i * p] = phi[i] * p;\n   \
    \             break;\n            } else {\n                phi[i * p] = phi[i]\
    \ * phi[p];\n            }\n        }\n    }\n    return phi;\n}\n\n\n"
  code: "#ifndef EULER_PHI_HPP\n#define EULER_PHI_HPP\n\n#include <vector>\n#include\
    \ <cassert>\n\nstd::vector<int> euler_phi(int n) {\n    assert(0 < n);\n    std::vector<int>\
    \ prime, phi(n + 1);\n    std::vector<char> is_prime(n + 1, true);\n    is_prime[0]\
    \ = is_prime[1] = false;\n    phi[1] = 1;\n    for (auto i = 2; i <= n; ++i) {\n\
    \        if (is_prime[i]) {\n            prime.push_back(i);\n            phi[i]\
    \ = i - 1;\n        }\n        for (auto p : prime) {\n            if (i * p >\
    \ n) {\n                break;\n            }\n            is_prime[i * p] = false;\n\
    \            if (i % p == 0) {\n                phi[i * p] = phi[i] * p;\n   \
    \             break;\n            } else {\n                phi[i * p] = phi[i]\
    \ * phi[p];\n            }\n        }\n    }\n    return phi;\n}\n\n#endif //\
    \ EULER_PHI_HPP"
  dependsOn: []
  isVerificationFile: false
  path: math/euler_phi.hpp
  requiredBy: []
  timestamp: '2026-09-02 07:12:03+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/math/euler_phi.test.cpp
documentation_of: math/euler_phi.hpp
layout: document
title: Euler's totient function
---

### Complexity
+ $\mathcal{O}(n)$
