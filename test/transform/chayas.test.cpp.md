---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/modint.hpp
    title: math/modint.hpp
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
    \n\n#line 1 \"math/modint.hpp\"\n\n\n\n#include <cassert>\n#include <concepts>\n\
    #include <iostream>\n#include <limits>\n#include <type_traits>\n#include <utility>\n\
    \ntemplate <std::signed_integral auto mod> struct modint {\n    using T = decltype(mod);\n\
    \    static_assert(0 < mod && mod <= std::numeric_limits<T>::max() / 2 + 1);\n\
    \    constexpr modint() : v(0) {}\n    constexpr modint(std::integral auto x)\
    \ : v(T((x % mod + mod) % mod)) {}\n    constexpr modint &operator+=(modint o)\
    \ {\n        v = (v + o.v) % mod;\n        return *this;\n    }\n    constexpr\
    \ modint &operator-=(modint o) {\n        v = (v - o.v + mod) % mod;\n       \
    \ return *this;\n    }\n    constexpr modint &operator*=(modint o) {\n       \
    \ static_assert(sizeof(T) <= sizeof(long long));\n        using U = std::conditional_t<sizeof(T)\
    \ <= sizeof(int), long long, __int128>;\n        v = T(U(v) * o.v % mod);\n  \
    \      return *this;\n    }\n    constexpr modint &operator/=(modint o) { return\
    \ *this *= o.inv(); }\n    constexpr modint operator-() const { return -v; }\n\
    \    constexpr modint operator+() const { return *this; }\n    friend constexpr\
    \ modint operator+(modint l, modint r) { return l += r; }\n    friend constexpr\
    \ modint operator-(modint l, modint r) { return l -= r; }\n    friend constexpr\
    \ modint operator*(modint l, modint r) { return l *= r; }\n    friend constexpr\
    \ modint operator/(modint l, modint r) { return l /= r; }\n    friend bool operator==(modint,\
    \ modint) = default;\n    constexpr modint pow(std::integral auto n) const {\n\
    \        assert(0 <= n);\n        modint x = *this, r = 1;\n        for (; n;\
    \ x *= x, n /= 2) {\n            if (n & 1) {\n                r *= x;\n     \
    \       }\n        }\n        return r;\n    }\n    constexpr modint inv() const\
    \ {\n        T a = v, b = mod, s = 1, t = 0;\n        while (b) {\n          \
    \  T q = a / b;\n            std::swap(a -= b * q, b);\n            std::swap(s\
    \ -= t * q, t);\n        }\n        assert(a == 1);\n        return s;\n    }\n\
    \    constexpr T val() const { return v; }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, modint a) { return os << a.v; }\n    friend std::istream &operator>>(std::istream\
    \ &is, modint &a) {\n        long long x;\n        is >> x;\n        a = x;\n\
    \        return is;\n    }\n\nprivate:\n    T v;\n};\n\nusing modint998244353\
    \ = modint<998244353>;\nusing modint1000000007 = modint<1000000007>;\n\n\n#line\
    \ 1 \"transform/subset_zeta.hpp\"\n\n\n\n#include <bit>\n#line 6 \"transform/subset_zeta.hpp\"\
    \n#include <vector>\n\ntemplate <typename T> void subset_zeta_transform(std::vector<T>\
    \ &f) {\n    assert(std::has_single_bit(f.size()));\n    auto n = int(std::countr_zero(f.size()));\n\
    \    for (auto i = 0; i < n; ++i) {\n        for (auto s = 0; s < (1 << n); ++s)\
    \ {\n            if (s & (1 << i)) {\n                f[s] += f[s ^ (1 << i)];\n\
    \            }\n        }\n    }\n}\n\n\n#line 5 \"test/transform/chayas.test.cpp\"\
    \n#include <bits/stdc++.h>\n\nusing Z = modint998244353;\n\nint main() {\n   \
    \ std::cin.tie(0)->sync_with_stdio(0);\n    int n, m;\n    std::cin >> n >> m;\n\
    \    std::vector<int> sos(1 << n);\n    for (auto i = 0; i < m; ++i) {\n     \
    \   int a, b, c;\n        std::cin >> a >> b >> c;\n        --a, --b, --c;\n \
    \       sos[(1 << a) | (1 << c)] += 1;\n        sos[(1 << b)] += 1;\n        sos[(1\
    \ << a) | (1 << b)] -= 1;\n        sos[(1 << b) | (1 << c)] -= 1;\n    }\n   \
    \ subset_zeta_transform(sos);\n    std::vector<Z> dp(1 << n);\n    dp[(1 << n)\
    \ - 1] = 1;\n    for (auto s = (1 << n) - 2; 0 <= s; --s) {\n        for (auto\
    \ i = 0; i < n; ++i) {\n            if (((s >> i) & 1) == 0 && sos[s] == 0 &&\
    \ sos[s | (1 << i)] == 0) {\n                dp[s] += dp[s | (1 << i)];\n    \
    \        }\n        }\n    }\n    std::cout << dp[0].val() << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/1448\"\n\n#include\
    \ \"math/modint.hpp\"\n#include \"transform/subset_zeta.hpp\"\n#include <bits/stdc++.h>\n\
    \nusing Z = modint998244353;\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
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
  - math/modint.hpp
  - transform/subset_zeta.hpp
  isVerificationFile: true
  path: test/transform/chayas.test.cpp
  requiredBy: []
  timestamp: '2026-11-06 14:29:39+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/transform/chayas.test.cpp
layout: document
redirect_from:
- /verify/test/transform/chayas.test.cpp
- /verify/test/transform/chayas.test.cpp.html
title: test/transform/chayas.test.cpp
---
