---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convolution/or.hpp
    title: convolution/or.hpp
  - icon: ':question:'
    path: math/modint.hpp
    title: math/modint.hpp
  - icon: ':heavy_check_mark:'
    path: transform/subset_mobius.hpp
    title: transform/subset_mobius.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/bitwise_and_convolution
    links:
    - https://judge.yosupo.jp/problem/bitwise_and_convolution
  bundledCode: "#line 1 \"test/convolution/bitwise_or_convolution.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/bitwise_and_convolution\"\n\n#line\
    \ 1 \"convolution/or.hpp\"\n\n\n\n#line 1 \"transform/subset_mobius.hpp\"\n\n\n\
    \n#include <bit>\n#include <cassert>\n#include <vector>\n\ntemplate <typename\
    \ T> void subset_mobius_transform(std::vector<T> &g) {\n    assert(std::has_single_bit(g.size()));\n\
    \    auto n = int(std::countr_zero(g.size()));\n    for (auto i = 0; i < n; ++i)\
    \ {\n        for (auto s = 0; s < (1 << n); ++s) {\n            if (s & (1 <<\
    \ i)) {\n                g[s] -= g[s ^ (1 << i)];\n            }\n        }\n\
    \    }\n}\n\n\n#line 1 \"transform/subset_zeta.hpp\"\n\n\n\n#line 7 \"transform/subset_zeta.hpp\"\
    \n\ntemplate <typename T> void subset_zeta_transform(std::vector<T> &f) {\n  \
    \  assert(std::has_single_bit(f.size()));\n    auto n = int(std::countr_zero(f.size()));\n\
    \    for (auto i = 0; i < n; ++i) {\n        for (auto s = 0; s < (1 << n); ++s)\
    \ {\n            if (s & (1 << i)) {\n                f[s] += f[s ^ (1 << i)];\n\
    \            }\n        }\n    }\n}\n\n\n#line 8 \"convolution/or.hpp\"\n\ntemplate\
    \ <typename T> std::vector<T> or_convolution(std::vector<T> a, std::vector<T>\
    \ b) {\n    assert(a.size() == b.size());\n    subset_zeta_transform(a);\n   \
    \ subset_zeta_transform(b);\n    for (auto i = 0; i < int(a.size()); ++i) {\n\
    \        a[i] *= b[i];\n    }\n    subset_mobius_transform(a);\n    return a;\n\
    }\n\n\n#line 1 \"math/modint.hpp\"\n\n\n\n#line 5 \"math/modint.hpp\"\n#include\
    \ <concepts>\n#include <iostream>\n#include <limits>\n#include <type_traits>\n\
    #include <utility>\n\ntemplate <std::signed_integral auto mod> struct modint {\n\
    \    using T = decltype(mod);\n    static_assert(0 < mod && mod <= std::numeric_limits<T>::max()\
    \ / 2 + 1);\n    constexpr modint() : v(0) {}\n    constexpr modint(std::integral\
    \ auto x) : v(T((x % mod + mod) % mod)) {}\n    constexpr modint &operator+=(modint\
    \ o) {\n        v = (v + o.v) % mod;\n        return *this;\n    }\n    constexpr\
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
    \ 5 \"test/convolution/bitwise_or_convolution.test.cpp\"\n#include <bits/stdc++.h>\n\
    \nusing Z = modint998244353;\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N;\n    std::cin >> N;\n    std::vector<Z> A(1 << N);\n    for (auto\
    \ i = 0; i < (1 << N); ++i) {\n        int x;\n        std::cin >> x;\n      \
    \  A[i] = x;\n    }\n    std::vector<Z> B(1 << N);\n    for (auto i = 0; i < (1\
    \ << N); ++i) {\n        int x;\n        std::cin >> x;\n        B[i] = x;\n \
    \   }\n    std::ranges::reverse(A);\n    std::ranges::reverse(B);\n    auto C\
    \ = or_convolution(A, B);\n    std::ranges::reverse(C);\n    for (auto i = 0;\
    \ i < (1 << N); ++i) {\n        std::cout << C[i].val() << \" \";\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/bitwise_and_convolution\"\
    \n\n#include \"convolution/or.hpp\"\n#include \"math/modint.hpp\"\n#include <bits/stdc++.h>\n\
    \nusing Z = modint998244353;\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N;\n    std::cin >> N;\n    std::vector<Z> A(1 << N);\n    for (auto\
    \ i = 0; i < (1 << N); ++i) {\n        int x;\n        std::cin >> x;\n      \
    \  A[i] = x;\n    }\n    std::vector<Z> B(1 << N);\n    for (auto i = 0; i < (1\
    \ << N); ++i) {\n        int x;\n        std::cin >> x;\n        B[i] = x;\n \
    \   }\n    std::ranges::reverse(A);\n    std::ranges::reverse(B);\n    auto C\
    \ = or_convolution(A, B);\n    std::ranges::reverse(C);\n    for (auto i = 0;\
    \ i < (1 << N); ++i) {\n        std::cout << C[i].val() << \" \";\n    }\n}\n"
  dependsOn:
  - convolution/or.hpp
  - transform/subset_mobius.hpp
  - transform/subset_zeta.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: test/convolution/bitwise_or_convolution.test.cpp
  requiredBy: []
  timestamp: '2026-11-06 14:29:39+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/convolution/bitwise_or_convolution.test.cpp
layout: document
redirect_from:
- /verify/test/convolution/bitwise_or_convolution.test.cpp
- /verify/test/convolution/bitwise_or_convolution.test.cpp.html
title: test/convolution/bitwise_or_convolution.test.cpp
---
