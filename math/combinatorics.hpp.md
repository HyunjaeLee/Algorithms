---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/math/binomial_coefficient_prime_mod.test.cpp
    title: test/math/binomial_coefficient_prime_mod.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/combinatorics.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <bit>\n#include <cassert>\n#include <vector>\n\ntemplate <typename Z> struct\
    \ Combinatorics {\n    static void grow(int n) {\n        auto m = int(f_.size());\n\
    \        if (n < m) {\n            return;\n        }\n        n = std::min<int>(std::bit_ceil(unsigned(n\
    \ + 1)), Z::mod());\n        f_.resize(n);\n        finv_.resize(n);\n       \
    \ for (auto i = m; i < n; ++i) {\n            f_[i] = f_[i - 1] * Z(i);\n    \
    \    }\n        finv_[n - 1] = f_[n - 1].inv();\n        for (auto i = n - 1;\
    \ m < i; --i) {\n            finv_[i - 1] = finv_[i] * Z(i);\n        }\n    }\n\
    \    static Z f(int n) { // O(1)\n        assert(0 <= n);\n        grow(n);\n\
    \        return f_[n];\n    }\n    static Z finv(int n) { // O(1)\n        assert(0\
    \ <= n);\n        grow(n);\n        return finv_[n];\n    }\n    static Z binom(int\
    \ n, int k) { // O(1)\n        if (0 <= k && k <= n) {\n            return f(n)\
    \ * finv(k) * finv(n - k);\n        } else {\n            return Z(0);\n     \
    \   }\n    }\n    static Z binom2(long long n, long long k) { // O(min(k, n -\
    \ k))\n        if (k < 0 || n < k) {\n            return Z(0);\n        }\n  \
    \      if (n - k < k) {\n            return binom2(n, n - k);\n        }\n   \
    \     auto ret = finv(int(k));\n        for (auto i = 0; i < k; ++i) {\n     \
    \       ret *= Z(n - i);\n        }\n        return ret;\n    }\n    Z operator()(int\
    \ n, int k) { return binom(n, k); }\n\nprivate:\n    inline static std::vector<Z>\
    \ f_{Z(1)}, finv_{Z(1)};\n};\n\n\n"
  code: "#ifndef COMBINATORICS_HPP\n#define COMBINATORICS_HPP\n\n#include <algorithm>\n\
    #include <bit>\n#include <cassert>\n#include <vector>\n\ntemplate <typename Z>\
    \ struct Combinatorics {\n    static void grow(int n) {\n        auto m = int(f_.size());\n\
    \        if (n < m) {\n            return;\n        }\n        n = std::min<int>(std::bit_ceil(unsigned(n\
    \ + 1)), Z::mod());\n        f_.resize(n);\n        finv_.resize(n);\n       \
    \ for (auto i = m; i < n; ++i) {\n            f_[i] = f_[i - 1] * Z(i);\n    \
    \    }\n        finv_[n - 1] = f_[n - 1].inv();\n        for (auto i = n - 1;\
    \ m < i; --i) {\n            finv_[i - 1] = finv_[i] * Z(i);\n        }\n    }\n\
    \    static Z f(int n) { // O(1)\n        assert(0 <= n);\n        grow(n);\n\
    \        return f_[n];\n    }\n    static Z finv(int n) { // O(1)\n        assert(0\
    \ <= n);\n        grow(n);\n        return finv_[n];\n    }\n    static Z binom(int\
    \ n, int k) { // O(1)\n        if (0 <= k && k <= n) {\n            return f(n)\
    \ * finv(k) * finv(n - k);\n        } else {\n            return Z(0);\n     \
    \   }\n    }\n    static Z binom2(long long n, long long k) { // O(min(k, n -\
    \ k))\n        if (k < 0 || n < k) {\n            return Z(0);\n        }\n  \
    \      if (n - k < k) {\n            return binom2(n, n - k);\n        }\n   \
    \     auto ret = finv(int(k));\n        for (auto i = 0; i < k; ++i) {\n     \
    \       ret *= Z(n - i);\n        }\n        return ret;\n    }\n    Z operator()(int\
    \ n, int k) { return binom(n, k); }\n\nprivate:\n    inline static std::vector<Z>\
    \ f_{Z(1)}, finv_{Z(1)};\n};\n\n#endif // COMBINATORICS_HPP"
  dependsOn: []
  isVerificationFile: false
  path: math/combinatorics.hpp
  requiredBy: []
  timestamp: '2026-02-06 02:13:39+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/math/binomial_coefficient_prime_mod.test.cpp
documentation_of: math/combinatorics.hpp
layout: document
redirect_from:
- /library/math/combinatorics.hpp
- /library/math/combinatorics.hpp.html
title: math/combinatorics.hpp
---
