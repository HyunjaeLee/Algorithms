---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/factor.hpp
    title: Factor
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/factorize
    links:
    - https://judge.yosupo.jp/problem/factorize
  bundledCode: "#line 1 \"test/factor.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/factorize\"\
    \n\n#line 1 \"math/factor.hpp\"\n\n\n\n#include <algorithm>\n#include <numeric>\n\
    #include <vector>\n\nunsigned long long modmul(unsigned long long a, unsigned\
    \ long long b,\n                          unsigned long long M) {\n    long long\
    \ ret =\n        a * b - M * static_cast<unsigned long long>(1.L / M * a * b);\n\
    \    return ret + M * (ret < 0) - M * (ret >= static_cast<long long>(M));\n}\n\
    \nunsigned long long modpow(unsigned long long b, unsigned long long e,\n    \
    \                      unsigned long long mod) {\n    unsigned long long ans =\
    \ 1;\n    for (; e; b = modmul(b, b, mod), e /= 2) {\n        if (e & 1) {\n \
    \           ans = modmul(ans, b, mod);\n        }\n    }\n    return ans;\n}\n\
    \nbool is_prime(unsigned long long n) {\n    if (n < 2 || n % 6 % 4 != 1) {\n\
    \        return (n | 1) == 3;\n    }\n    unsigned long long A[] = {2, 325, 9375,\
    \ 28178, 450775, 9780504, 1795265022},\n                       s = __builtin_ctzll(n\
    \ - 1), d = n >> s;\n    for (unsigned long long a : A) {\n        unsigned long\
    \ long p = modpow(a % n, d, n), i = s;\n        while (p != 1 && p != n - 1 &&\
    \ a % n && i--) {\n            p = modmul(p, p, n);\n        }\n        if (p\
    \ != n - 1 && i != s) {\n            return 0;\n        }\n    }\n    return 1;\n\
    }\n\nunsigned long long pollard(unsigned long long n) {\n    auto f = [n](unsigned\
    \ long long x) { return modmul(x, x, n) + 1; };\n    unsigned long long x = 0,\
    \ y = 0, t = 30, prd = 2, i = 1, q;\n    while (t++ % 40 || std::gcd(prd, n) ==\
    \ 1) {\n        if (x == y) {\n            x = ++i, y = f(x);\n        }\n   \
    \     if ((q = modmul(prd, std::max(x, y) - std::min(x, y), n))) {\n         \
    \   prd = q;\n        }\n        x = f(x), y = f(f(y));\n    }\n    return std::gcd(prd,\
    \ n);\n}\n\nstd::vector<unsigned long long> factor(unsigned long long n) {\n \
    \   if (n == 1) {\n        return {};\n    }\n    if (is_prime(n)) {\n       \
    \ return {n};\n    }\n    unsigned long long x = pollard(n);\n    auto l = factor(x),\
    \ r = factor(n / x);\n    l.insert(l.end(), r.begin(), r.end());\n    return l;\n\
    }\n\nunsigned long long euler_phi(unsigned long long n) {\n    auto f = factor(n);\n\
    \    std::sort(f.begin(), f.end());\n    f.erase(std::unique(f.begin(), f.end()),\
    \ f.end());\n    for (auto p : f) {\n        n -= n / p;\n    }\n    return n;\n\
    }\n\n\n#line 4 \"test/factor.test.cpp\"\n#include <bits/stdc++.h>\n\nint main()\
    \ {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int Q;\n    std::cin >> Q;\n\
    \    for (auto i = 0; i < Q; ++i) {\n        unsigned long long a;\n        std::cin\
    \ >> a;\n        auto f = factor(a);\n        std::sort(f.begin(), f.end());\n\
    \        std::cout << f.size() << ' ';\n        std::copy(f.begin(), f.end(),\n\
    \                  std::ostream_iterator<unsigned long long>(std::cout, \" \"\
    ));\n        std::cout << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/factorize\"\n\n#include\
    \ \"math/factor.hpp\"\n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int Q;\n    std::cin >> Q;\n    for (auto i = 0; i < Q; ++i) {\n        unsigned\
    \ long long a;\n        std::cin >> a;\n        auto f = factor(a);\n        std::sort(f.begin(),\
    \ f.end());\n        std::cout << f.size() << ' ';\n        std::copy(f.begin(),\
    \ f.end(),\n                  std::ostream_iterator<unsigned long long>(std::cout,\
    \ \" \"));\n        std::cout << '\\n';\n    }\n}\n"
  dependsOn:
  - math/factor.hpp
  isVerificationFile: true
  path: test/factor.test.cpp
  requiredBy: []
  timestamp: '2022-12-02 07:43:56+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/factor.test.cpp
layout: document
redirect_from:
- /verify/test/factor.test.cpp
- /verify/test/factor.test.cpp.html
title: test/factor.test.cpp
---
