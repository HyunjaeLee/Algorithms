---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/euler_phi.hpp
    title: Euler's totient function
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/2249
    links:
    - https://yukicoder.me/problems/no/2249
  bundledCode: "#line 1 \"test/math/euler_phi.test.cpp\"\n#define PROBLEM \"https://yukicoder.me/problems/no/2249\"\
    \n\n#line 1 \"math/euler_phi.hpp\"\n\n\n\n#include <vector>\n#include <cassert>\n\
    \nstd::vector<int> euler_phi(int n) {\n    assert(0 < n);\n    std::vector<int>\
    \ prime, phi(n + 1);\n    std::vector<char> is_prime(n + 1, true);\n    is_prime[0]\
    \ = is_prime[1] = false;\n    phi[1] = 1;\n    for (auto i = 2; i <= n; ++i) {\n\
    \        if (is_prime[i]) {\n            prime.push_back(i);\n            phi[i]\
    \ = i - 1;\n        }\n        for (auto p : prime) {\n            if (i * p >\
    \ n) {\n                break;\n            }\n            is_prime[i * p] = false;\n\
    \            if (i % p == 0) {\n                phi[i * p] = phi[i] * p;\n   \
    \             break;\n            } else {\n                phi[i * p] = phi[i]\
    \ * phi[p];\n            }\n        }\n    }\n    return phi;\n}\n\n\n#line 4\
    \ \"test/math/euler_phi.test.cpp\"\n#include <bits/stdc++.h>\n\nint main() {\n\
    \    std::cin.tie(0)->sync_with_stdio(0);\n    constexpr auto NMAX = 10'000'000;\n\
    \    auto phi = euler_phi(NMAX);\n    std::vector<long long> pref(NMAX + 1);\n\
    \    for (auto i = 2; i <= NMAX; ++i) {\n        pref[i] = 2 * i - 2 - phi[i];\n\
    \    }\n    for (auto i = 2; i < NMAX; ++i) {\n        pref[i + 1] += pref[i];\n\
    \    }\n    int T;\n    std::cin >> T;\n    while (T--) {\n        int N;\n  \
    \      std::cin >> N;\n        std::cout << pref[N] << \"\\n\";\n    }\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/2249\"\n\n#include \"\
    math/euler_phi.hpp\"\n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    constexpr auto NMAX = 10'000'000;\n    auto phi = euler_phi(NMAX);\n    std::vector<long\
    \ long> pref(NMAX + 1);\n    for (auto i = 2; i <= NMAX; ++i) {\n        pref[i]\
    \ = 2 * i - 2 - phi[i];\n    }\n    for (auto i = 2; i < NMAX; ++i) {\n      \
    \  pref[i + 1] += pref[i];\n    }\n    int T;\n    std::cin >> T;\n    while (T--)\
    \ {\n        int N;\n        std::cin >> N;\n        std::cout << pref[N] << \"\
    \\n\";\n    }\n}\n"
  dependsOn:
  - math/euler_phi.hpp
  isVerificationFile: true
  path: test/math/euler_phi.test.cpp
  requiredBy: []
  timestamp: '2026-09-02 07:12:03+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/math/euler_phi.test.cpp
layout: document
redirect_from:
- /verify/test/math/euler_phi.test.cpp
- /verify/test/math/euler_phi.test.cpp.html
title: test/math/euler_phi.test.cpp
---
