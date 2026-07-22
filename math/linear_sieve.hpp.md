---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/math/aizu0009.test.cpp
    title: test/math/aizu0009.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/math/aizu2870.test.cpp
    title: test/math/aizu2870.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/math/yuki106.test.cpp
    title: test/math/yuki106.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/linear_sieve.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <map>\n#include <vector>\n\nstruct linear_sieve {\n    explicit linear_sieve(int\
    \ n) : lpf(n + 1) {\n        for (auto i = 2; i <= n; ++i) {\n            if (lpf[i]\
    \ == 0) {\n                lpf[i] = i;\n                primes.push_back(i);\n\
    \            }\n            for (auto p : primes) {\n                if (lpf[i]\
    \ < p || n < 1LL * i * p) {\n                    break;\n                }\n \
    \               lpf[i * p] = p;\n            }\n        }\n    }\n    std::map<int,\
    \ int> factorize(int x) const { // O(log x)\n        assert(1 <= x && x < int(lpf.size()));\n\
    \        std::map<int, int> f;\n        while (1 < x) {\n            ++f[lpf[x]];\n\
    \            x /= lpf[x];\n        }\n        return f;\n    }\n    bool is_prime(int\
    \ x) const { // O(1)\n        assert(1 <= x && x < int(lpf.size()));\n       \
    \ return lpf[x] == x;\n    }\n    std::vector<int> lpf;\n    std::vector<int>\
    \ primes;\n};\n\n\n"
  code: "#ifndef LINEAR_SIEVE_HPP\n#define LINEAR_SIEVE_HPP\n\n#include <cassert>\n\
    #include <map>\n#include <vector>\n\nstruct linear_sieve {\n    explicit linear_sieve(int\
    \ n) : lpf(n + 1) {\n        for (auto i = 2; i <= n; ++i) {\n            if (lpf[i]\
    \ == 0) {\n                lpf[i] = i;\n                primes.push_back(i);\n\
    \            }\n            for (auto p : primes) {\n                if (lpf[i]\
    \ < p || n < 1LL * i * p) {\n                    break;\n                }\n \
    \               lpf[i * p] = p;\n            }\n        }\n    }\n    std::map<int,\
    \ int> factorize(int x) const { // O(log x)\n        assert(1 <= x && x < int(lpf.size()));\n\
    \        std::map<int, int> f;\n        while (1 < x) {\n            ++f[lpf[x]];\n\
    \            x /= lpf[x];\n        }\n        return f;\n    }\n    bool is_prime(int\
    \ x) const { // O(1)\n        assert(1 <= x && x < int(lpf.size()));\n       \
    \ return lpf[x] == x;\n    }\n    std::vector<int> lpf;\n    std::vector<int>\
    \ primes;\n};\n\n#endif // LINEAR_SIEVE_HPP"
  dependsOn: []
  isVerificationFile: false
  path: math/linear_sieve.hpp
  requiredBy: []
  timestamp: '2026-07-22 17:15:56+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/math/aizu2870.test.cpp
  - test/math/aizu0009.test.cpp
  - test/math/yuki106.test.cpp
documentation_of: math/linear_sieve.hpp
layout: document
redirect_from:
- /library/math/linear_sieve.hpp
- /library/math/linear_sieve.hpp.html
title: math/linear_sieve.hpp
---
