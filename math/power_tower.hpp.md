---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/factor.hpp
    title: Factor
  _extendedRequiredBy:
  - icon: ':warning:'
    path: test/tetration_mod.cpp
    title: test/tetration_mod.cpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/power_tower.test.cpp
    title: test/power_tower.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/power_tower.hpp\"\n\n\n\n#line 1 \"math/factor.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <numeric>\n#include <vector>\n\nunsigned\
    \ long long modmul(unsigned long long a, unsigned long long b,\n             \
    \             unsigned long long M) {\n    long long ret =\n        a * b - M\
    \ * static_cast<unsigned long long>(1.L / M * a * b);\n    return ret + M * (ret\
    \ < 0) - M * (ret >= static_cast<long long>(M));\n}\n\nunsigned long long modpow(unsigned\
    \ long long b, unsigned long long e,\n                          unsigned long\
    \ long mod) {\n    unsigned long long ans = 1;\n    for (; e; b = modmul(b, b,\
    \ mod), e /= 2) {\n        if (e & 1) {\n            ans = modmul(ans, b, mod);\n\
    \        }\n    }\n    return ans;\n}\n\nbool is_prime(unsigned long long n) {\n\
    \    if (n < 2 || n % 6 % 4 != 1) {\n        return (n | 1) == 3;\n    }\n   \
    \ unsigned long long A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},\n\
    \                       s = __builtin_ctzll(n - 1), d = n >> s;\n    for (unsigned\
    \ long long a : A) {\n        unsigned long long p = modpow(a % n, d, n), i =\
    \ s;\n        while (p != 1 && p != n - 1 && a % n && i--) {\n            p =\
    \ modmul(p, p, n);\n        }\n        if (p != n - 1 && i != s) {\n         \
    \   return 0;\n        }\n    }\n    return 1;\n}\n\nunsigned long long pollard(unsigned\
    \ long long n) {\n    auto f = [n](unsigned long long x) { return modmul(x, x,\
    \ n) + 1; };\n    unsigned long long x = 0, y = 0, t = 30, prd = 2, i = 1, q;\n\
    \    while (t++ % 40 || std::gcd(prd, n) == 1) {\n        if (x == y) {\n    \
    \        x = ++i, y = f(x);\n        }\n        if ((q = modmul(prd, std::max(x,\
    \ y) - std::min(x, y), n))) {\n            prd = q;\n        }\n        x = f(x),\
    \ y = f(f(y));\n    }\n    return std::gcd(prd, n);\n}\n\nstd::vector<unsigned\
    \ long long> factor(unsigned long long n) {\n    if (n == 1) {\n        return\
    \ {};\n    }\n    if (is_prime(n)) {\n        return {n};\n    }\n    unsigned\
    \ long long x = pollard(n);\n    auto l = factor(x), r = factor(n / x);\n    l.insert(l.end(),\
    \ r.begin(), r.end());\n    return l;\n}\n\nunsigned long long euler_phi(unsigned\
    \ long long n) {\n    auto f = factor(n);\n    std::sort(f.begin(), f.end());\n\
    \    f.erase(std::unique(f.begin(), f.end()), f.end());\n    for (auto p : f)\
    \ {\n        n -= n / p;\n    }\n    return n;\n}\n\n\n#line 5 \"math/power_tower.hpp\"\
    \n#include <cassert>\n#include <limits>\n#include <type_traits>\n#line 9 \"math/power_tower.hpp\"\
    \n\ntemplate <typename T, typename Promote = unsigned long long>\nT power_tower(const\
    \ std::vector<T> &a, T m) {\n    static_assert(std::is_integral_v<T>);\n    assert(m\
    \ > 0);\n    std::vector<unsigned long long> mod_chain{\n        static_cast<unsigned\
    \ long long>(m)};\n    while (mod_chain.back() > 1) {\n        const auto phi\
    \ = euler_phi(mod_chain.back());\n        mod_chain.push_back(phi);\n    }\n \
    \   const auto f = [](Promote x, Promote n, Promote mod) {\n        Promote r\
    \ = 1;\n        if (x > mod) {\n            x = x % mod + mod;\n        }\n  \
    \      while (n) {\n            if (n & 1) {\n                r *= x;\n      \
    \          if (r > mod) {\n                    r = r % mod + mod;\n          \
    \      }\n            }\n            x *= x;\n            if (x > mod) {\n   \
    \             x = x % mod + mod;\n            }\n            n >>= 1;\n      \
    \  }\n        return r;\n    };\n    Promote r = 1;\n    const auto k = static_cast<int>(std::min(a.size(),\
    \ mod_chain.size()));\n    for (auto i = k - 1; i >= 0; --i) {\n        assert(a[i]\
    \ > 0);\n        r = f(static_cast<Promote>(a[i]), r, mod_chain[i]);\n    }\n\
    \    return static_cast<T>(r % static_cast<Promote>(m));\n}\n\n\n"
  code: "#ifndef POWER_TOWER_HPP\n#define POWER_TOWER_HPP\n\n#include \"math/factor.hpp\"\
    \n#include <cassert>\n#include <limits>\n#include <type_traits>\n#include <vector>\n\
    \ntemplate <typename T, typename Promote = unsigned long long>\nT power_tower(const\
    \ std::vector<T> &a, T m) {\n    static_assert(std::is_integral_v<T>);\n    assert(m\
    \ > 0);\n    std::vector<unsigned long long> mod_chain{\n        static_cast<unsigned\
    \ long long>(m)};\n    while (mod_chain.back() > 1) {\n        const auto phi\
    \ = euler_phi(mod_chain.back());\n        mod_chain.push_back(phi);\n    }\n \
    \   const auto f = [](Promote x, Promote n, Promote mod) {\n        Promote r\
    \ = 1;\n        if (x > mod) {\n            x = x % mod + mod;\n        }\n  \
    \      while (n) {\n            if (n & 1) {\n                r *= x;\n      \
    \          if (r > mod) {\n                    r = r % mod + mod;\n          \
    \      }\n            }\n            x *= x;\n            if (x > mod) {\n   \
    \             x = x % mod + mod;\n            }\n            n >>= 1;\n      \
    \  }\n        return r;\n    };\n    Promote r = 1;\n    const auto k = static_cast<int>(std::min(a.size(),\
    \ mod_chain.size()));\n    for (auto i = k - 1; i >= 0; --i) {\n        assert(a[i]\
    \ > 0);\n        r = f(static_cast<Promote>(a[i]), r, mod_chain[i]);\n    }\n\
    \    return static_cast<T>(r % static_cast<Promote>(m));\n}\n\n#endif // POWER_TOWER_HPP\n"
  dependsOn:
  - math/factor.hpp
  isVerificationFile: false
  path: math/power_tower.hpp
  requiredBy:
  - test/tetration_mod.cpp
  timestamp: '2022-12-02 07:43:56+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/power_tower.test.cpp
documentation_of: math/power_tower.hpp
layout: document
redirect_from:
- /library/math/power_tower.hpp
- /library/math/power_tower.hpp.html
title: math/power_tower.hpp
---
