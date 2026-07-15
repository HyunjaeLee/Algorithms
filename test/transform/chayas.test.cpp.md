---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: transform/subset_zeta.hpp
    title: transform/subset_zeta.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/1448
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/1448
  bundledCode: "#line 1 \"test/transform/chayas.test.cpp\"\n#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/1448\"\
    \n\n#line 1 \"transform/subset_zeta.hpp\"\n\n\n\n#include <bit>\n#include <cassert>\n\
    #include <vector>\n\ntemplate <typename T> void subset_zeta_transform(std::vector<T>\
    \ &f) {\n    assert(std::has_single_bit(f.size()));\n    auto n = int(std::countr_zero(f.size()));\n\
    \    for (auto i = 0; i < n; ++i) {\n        for (auto s = 0; s < (1 << n); ++s)\
    \ {\n            if (s & (1 << i)) {\n                f[s] += f[s ^ (1 << i)];\n\
    \            }\n        }\n    }\n}\n\n\n#line 4 \"test/transform/chayas.test.cpp\"\
    \n#include <atcoder/modint>\n#include <bits/stdc++.h>\nusing Z = atcoder::modint998244353;\n\
    \nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int n, m;\n    std::cin\
    \ >> n >> m;\n    std::vector<int> sos(1 << n);\n    for (auto i = 0; i < m; ++i)\
    \ {\n        int a, b, c;\n        std::cin >> a >> b >> c;\n        --a, --b,\
    \ --c;\n        sos[(1 << a) | (1 << c)] += 1;\n        sos[(1 << b)] += 1;\n\
    \        sos[(1 << a) | (1 << b)] -= 1;\n        sos[(1 << b) | (1 << c)] -= 1;\n\
    \    }\n    subset_zeta_transform(sos);\n    std::vector<Z> dp(1 << n);\n    dp[(1\
    \ << n) - 1] = 1;\n    for (auto s = (1 << n) - 2; 0 <= s; --s) {\n        for\
    \ (auto i = 0; i < n; ++i) {\n            if (((s >> i) & 1) == 0 && sos[s] ==\
    \ 0 && sos[s | (1 << i)] == 0) {\n                dp[s] += dp[s | (1 << i)];\n\
    \            }\n        }\n    }\n    std::cout << dp[0].val() << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/1448\"\n\n#include\
    \ \"transform/subset_zeta.hpp\"\n#include <atcoder/modint>\n#include <bits/stdc++.h>\n\
    using Z = atcoder::modint998244353;\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int n, m;\n    std::cin >> n >> m;\n    std::vector<int> sos(1 << n);\n \
    \   for (auto i = 0; i < m; ++i) {\n        int a, b, c;\n        std::cin >>\
    \ a >> b >> c;\n        --a, --b, --c;\n        sos[(1 << a) | (1 << c)] += 1;\n\
    \        sos[(1 << b)] += 1;\n        sos[(1 << a) | (1 << b)] -= 1;\n       \
    \ sos[(1 << b) | (1 << c)] -= 1;\n    }\n    subset_zeta_transform(sos);\n   \
    \ std::vector<Z> dp(1 << n);\n    dp[(1 << n) - 1] = 1;\n    for (auto s = (1\
    \ << n) - 2; 0 <= s; --s) {\n        for (auto i = 0; i < n; ++i) {\n        \
    \    if (((s >> i) & 1) == 0 && sos[s] == 0 && sos[s | (1 << i)] == 0) {\n   \
    \             dp[s] += dp[s | (1 << i)];\n            }\n        }\n    }\n  \
    \  std::cout << dp[0].val() << \"\\n\";\n}\n"
  dependsOn:
  - transform/subset_zeta.hpp
  isVerificationFile: true
  path: test/transform/chayas.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 17:42:48+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/transform/chayas.test.cpp
layout: document
redirect_from:
- /verify/test/transform/chayas.test.cpp
- /verify/test/transform/chayas.test.cpp.html
title: test/transform/chayas.test.cpp
---
