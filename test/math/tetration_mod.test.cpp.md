---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/power_tower.hpp
    title: Power tower
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/tetration_mod
    links:
    - https://judge.yosupo.jp/problem/tetration_mod
  bundledCode: "#line 1 \"test/math/tetration_mod.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/tetration_mod\"\
    \n\n#line 1 \"math/power_tower.hpp\"\n\n\n\n#include <cassert>\n#include <limits>\n\
    #include <type_traits>\n#include <vector>\n\ntemplate <typename T> T euler_phi(T\
    \ n) {\n    T phi = n;\n    for (T i = 2; i * i <= n; i++) {\n        if (n %\
    \ i == 0) {\n            phi -= phi / i;\n            while (n % i == 0) {\n \
    \               n /= i;\n            }\n        }\n    }\n    if (n != 1) {\n\
    \        phi -= phi / n;\n    }\n    return phi;\n}\n\ntemplate <typename T, typename\
    \ Promote = unsigned long long>\nT power_tower(const std::vector<T> &a, T m) {\n\
    \    static_assert(std::is_integral_v<T>);\n    assert(m > 0);\n    std::vector<unsigned\
    \ long long> mod_chain{\n        static_cast<unsigned long long>(m)};\n    while\
    \ (mod_chain.back() > 1) {\n        const auto phi = euler_phi(mod_chain.back());\n\
    \        mod_chain.push_back(phi);\n    }\n    const auto f = [](Promote x, Promote\
    \ n, Promote mod) {\n        Promote r = 1;\n        if (x > mod) {\n        \
    \    x = x % mod + mod;\n        }\n        while (n) {\n            if (n & 1)\
    \ {\n                r *= x;\n                if (r > mod) {\n               \
    \     r = r % mod + mod;\n                }\n            }\n            x *= x;\n\
    \            if (x > mod) {\n                x = x % mod + mod;\n            }\n\
    \            n >>= 1;\n        }\n        return r;\n    };\n    Promote r = 1;\n\
    \    const auto k = static_cast<int>(std::min(a.size(), mod_chain.size()));\n\
    \    for (auto i = k - 1; i >= 0; --i) {\n        assert(a[i] > 0);\n        r\
    \ = f(static_cast<Promote>(a[i]), r, mod_chain[i]);\n    }\n    return static_cast<T>(r\
    \ % static_cast<Promote>(m));\n}\n\n\n#line 4 \"test/math/tetration_mod.test.cpp\"\
    \n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int T;\n    std::cin >> T;\n    for (auto i = 0; i < T; ++i) {\n        int\
    \ A, B, M;\n        std::cin >> A >> B >> M;\n        if (A == 0) {\n        \
    \    std::cout << ((B & 1) ^ 1) % M;\n        } else {\n            const auto\
    \ n = std::min(B, 64);\n            std::vector<int> a(n, A);\n            std::cout\
    \ << power_tower(a, M);\n        }\n        std::cout << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/tetration_mod\"\n\n#include\
    \ \"math/power_tower.hpp\"\n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int T;\n    std::cin >> T;\n    for (auto i = 0; i < T; ++i) {\n        int\
    \ A, B, M;\n        std::cin >> A >> B >> M;\n        if (A == 0) {\n        \
    \    std::cout << ((B & 1) ^ 1) % M;\n        } else {\n            const auto\
    \ n = std::min(B, 64);\n            std::vector<int> a(n, A);\n            std::cout\
    \ << power_tower(a, M);\n        }\n        std::cout << '\\n';\n    }\n}\n"
  dependsOn:
  - math/power_tower.hpp
  isVerificationFile: true
  path: test/math/tetration_mod.test.cpp
  requiredBy: []
  timestamp: '2025-09-16 22:59:29+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/math/tetration_mod.test.cpp
layout: document
redirect_from:
- /verify/test/math/tetration_mod.test.cpp
- /verify/test/math/tetration_mod.test.cpp.html
title: test/math/tetration_mod.test.cpp
---
