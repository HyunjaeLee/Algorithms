---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/linear_sieve.hpp
    title: math/linear_sieve.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/106
    links:
    - https://yukicoder.me/problems/no/106
  bundledCode: "#line 1 \"test/math/yuki106.test.cpp\"\n#define PROBLEM \"https://yukicoder.me/problems/no/106\"\
    \n\n#line 1 \"math/linear_sieve.hpp\"\n\n\n\n#include <cassert>\n#include <map>\n\
    #include <vector>\n\nstruct linear_sieve {\n    explicit linear_sieve(int n) :\
    \ lpf(n + 1) {\n        for (auto i = 2; i <= n; ++i) {\n            if (lpf[i]\
    \ == 0) {\n                lpf[i] = i;\n                primes.push_back(i);\n\
    \            }\n            for (auto p : primes) {\n                if (lpf[i]\
    \ < p || n < 1LL * i * p) {\n                    break;\n                }\n \
    \               lpf[i * p] = p;\n            }\n        }\n    }\n    std::map<int,\
    \ int> factorize(int x) const { // O(log x)\n        assert(1 <= x && x < int(lpf.size()));\n\
    \        std::map<int, int> f;\n        while (1 < x) {\n            ++f[lpf[x]];\n\
    \            x /= lpf[x];\n        }\n        return f;\n    }\n    bool is_prime(int\
    \ x) const { // O(1)\n        assert(1 <= x && x < int(lpf.size()));\n       \
    \ return lpf[x] == x;\n    }\n    std::vector<int> lpf;\n    std::vector<int>\
    \ primes;\n};\n\n\n#line 4 \"test/math/yuki106.test.cpp\"\n#include <bits/stdc++.h>\n\
    \nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int N, K;\n    std::cin\
    \ >> N >> K;\n    linear_sieve sieve(N);\n    auto ans = 0;\n    for (auto i =\
    \ 2; i <= N; ++i) {\n        if (K <= int(sieve.factorize(i).size())) {\n    \
    \        ans += 1;\n        }\n    }\n    std::cout << ans << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/106\"\n\n#include \"math/linear_sieve.hpp\"\
    \n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N, K;\n    std::cin >> N >> K;\n    linear_sieve sieve(N);\n    auto\
    \ ans = 0;\n    for (auto i = 2; i <= N; ++i) {\n        if (K <= int(sieve.factorize(i).size()))\
    \ {\n            ans += 1;\n        }\n    }\n    std::cout << ans << \"\\n\"\
    ;\n}\n"
  dependsOn:
  - math/linear_sieve.hpp
  isVerificationFile: true
  path: test/math/yuki106.test.cpp
  requiredBy: []
  timestamp: '2026-07-22 17:15:56+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/math/yuki106.test.cpp
layout: document
redirect_from:
- /verify/test/math/yuki106.test.cpp
- /verify/test/math/yuki106.test.cpp.html
title: test/math/yuki106.test.cpp
---
