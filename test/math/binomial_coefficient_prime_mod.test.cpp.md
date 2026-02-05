---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/combinatorics.hpp
    title: math/combinatorics.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod
    links:
    - https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod
  bundledCode: "#line 1 \"test/math/binomial_coefficient_prime_mod.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod\"\n\
    \n#line 1 \"math/combinatorics.hpp\"\n\n\n\n#include <algorithm>\n#include <bit>\n\
    #include <cassert>\n#include <vector>\n\ntemplate <typename Z> struct Combinatorics\
    \ {\n    static void grow(int n) {\n        auto m = int(f_.size());\n       \
    \ if (n < m) {\n            return;\n        }\n        n = std::min<int>(std::bit_ceil(unsigned(n\
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
    \ f_{Z(1)}, finv_{Z(1)};\n};\n\n\n#line 4 \"test/math/binomial_coefficient_prime_mod.test.cpp\"\
    \n#include <atcoder/modint>\n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    using Z = atcoder::modint;\n    Combinatorics<Z> C;\n    int T, m;\n    std::cin\
    \ >> T >> m;\n    Z::set_mod(m);\n    for (auto i = 0; i < T; ++i) {\n       \
    \ int n, k;\n        std::cin >> n >> k;\n        std::cout << C(n, k).val() <<\
    \ \"\\n\";\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod\"\
    \n\n#include \"math/combinatorics.hpp\"\n#include <atcoder/modint>\n#include <bits/stdc++.h>\n\
    \nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n    using Z = atcoder::modint;\n\
    \    Combinatorics<Z> C;\n    int T, m;\n    std::cin >> T >> m;\n    Z::set_mod(m);\n\
    \    for (auto i = 0; i < T; ++i) {\n        int n, k;\n        std::cin >> n\
    \ >> k;\n        std::cout << C(n, k).val() << \"\\n\";\n    }\n}\n"
  dependsOn:
  - math/combinatorics.hpp
  isVerificationFile: true
  path: test/math/binomial_coefficient_prime_mod.test.cpp
  requiredBy: []
  timestamp: '2026-02-06 02:13:39+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/math/binomial_coefficient_prime_mod.test.cpp
layout: document
redirect_from:
- /verify/test/math/binomial_coefficient_prime_mod.test.cpp
- /verify/test/math/binomial_coefficient_prime_mod.test.cpp.html
title: test/math/binomial_coefficient_prime_mod.test.cpp
---
