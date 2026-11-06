---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/convolution/bitwise_and_convolution.test.cpp
    title: test/convolution/bitwise_and_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/convolution/bitwise_or_convolution.test.cpp
    title: test/convolution/bitwise_or_convolution.test.cpp
  - icon: ':x:'
    path: test/dp/reroot_dfs.test.cpp
    title: test/dp/reroot_dfs.test.cpp
  - icon: ':x:'
    path: test/dp/rerooting.test.cpp
    title: test/dp/rerooting.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/graph/aizu1404.test.cpp
    title: test/graph/aizu1404.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/math/aizu2870.test.cpp
    title: test/math/aizu2870.test.cpp
  - icon: ':x:'
    path: test/math/aizu3614.test.cpp
    title: test/math/aizu3614.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/segment_tree/sparse_lazy_segtree.test.cpp
    title: test/segment_tree/sparse_lazy_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/segment_tree/sparse_segtree.test.cpp
    title: test/segment_tree/sparse_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/transform/chayas.test.cpp
    title: test/transform/chayas.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/modint.hpp\"\n\n\n\n#include <cassert>\n#include <concepts>\n\
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
    \ = modint<998244353>;\nusing modint1000000007 = modint<1000000007>;\n\n\n"
  code: "#ifndef MODINT_HPP\n#define MODINT_HPP\n\n#include <cassert>\n#include <concepts>\n\
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
    \ = modint<998244353>;\nusing modint1000000007 = modint<1000000007>;\n\n#endif\
    \ // MODINT_HPP"
  dependsOn: []
  isVerificationFile: false
  path: math/modint.hpp
  requiredBy: []
  timestamp: '2026-11-06 14:29:39+00:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/dp/rerooting.test.cpp
  - test/dp/reroot_dfs.test.cpp
  - test/segment_tree/sparse_segtree.test.cpp
  - test/segment_tree/sparse_lazy_segtree.test.cpp
  - test/transform/chayas.test.cpp
  - test/graph/aizu1404.test.cpp
  - test/math/aizu3614.test.cpp
  - test/math/aizu2870.test.cpp
  - test/convolution/bitwise_or_convolution.test.cpp
  - test/convolution/bitwise_and_convolution.test.cpp
documentation_of: math/modint.hpp
layout: document
redirect_from:
- /library/math/modint.hpp
- /library/math/modint.hpp.html
title: math/modint.hpp
---
