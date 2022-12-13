---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/mobius.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <vector>\n\nstd::vector<int> mobius(int n) {\n    assert(n\
    \ > 0);\n    std::vector<int> prime, mu(n + 1);\n    std::vector<char> is_prime(n\
    \ + 1);\n    std::fill(is_prime.begin() + 2, is_prime.end(), true);\n    mu[1]\
    \ = 1;\n    for (auto i = 2; i <= n; ++i) {\n        if (is_prime[i]) {\n    \
    \        prime.push_back(i);\n            mu[i] = -1;\n        }\n        for\
    \ (auto p : prime) {\n            if (i * p > n) {\n                break;\n \
    \           }\n            is_prime[i * p] = false;\n            if (i % p ==\
    \ 0) {\n                mu[i * p] = 0;\n                break;\n            }\
    \ else {\n                mu[i * p] = -mu[i];\n            }\n        }\n    }\n\
    \    return mu;\n}\n\n\n"
  code: "#ifndef MOBIUS_HPP\n#define MOBIUS_HPP\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <vector>\n\nstd::vector<int> mobius(int n) {\n    assert(n\
    \ > 0);\n    std::vector<int> prime, mu(n + 1);\n    std::vector<char> is_prime(n\
    \ + 1);\n    std::fill(is_prime.begin() + 2, is_prime.end(), true);\n    mu[1]\
    \ = 1;\n    for (auto i = 2; i <= n; ++i) {\n        if (is_prime[i]) {\n    \
    \        prime.push_back(i);\n            mu[i] = -1;\n        }\n        for\
    \ (auto p : prime) {\n            if (i * p > n) {\n                break;\n \
    \           }\n            is_prime[i * p] = false;\n            if (i % p ==\
    \ 0) {\n                mu[i * p] = 0;\n                break;\n            }\
    \ else {\n                mu[i * p] = -mu[i];\n            }\n        }\n    }\n\
    \    return mu;\n}\n\n#endif // MOBIUS_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/mobius.hpp
  requiredBy: []
  timestamp: '2022-12-13 07:32:06+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/mobius.hpp
layout: document
title: "M\xF6bius function"
---

### Complexity
+ $\mathcal{O}\left(n\right)$
