---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: game/numnim.hpp
    title: game/numnim.hpp
  - icon: ':heavy_check_mark:'
    path: game/ordinal_sum.hpp
    title: game/ordinal_sum.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/game/2016_tsukuba_k.test.cpp
    title: test/game/2016_tsukuba_k.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/game/2016_tsukuba_k.test.cpp
    title: test/game/2016_tsukuba_k.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://nyaannyaan.github.io/library/game/surreal-number.hpp
  bundledCode: "#line 1 \"game/surreal.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <bit>\n#include <cassert>\n#include <compare>\n#include <limits>\n#include <ostream>\n\
    #include <vector>\n\n// g > 0: L wins\n// g < 0: R wins\n// g = 0: second wins\n\
    // https://nyaannyaan.github.io/library/game/surreal-number.hpp\nstruct Surreal\
    \ {\n    using S = Surreal;\n    using i64 = long long;\n    using u64 = unsigned\
    \ long long;\n    using i128 = __int128;\n    i64 p, q; // p / 2^q\n\n    Surreal(i64\
    \ p_ = 0, i64 q_ = 0) : p(p_), q(q_) {\n        // normalize\n        if (p) {\n\
    \            auto k = std::min<i64>(std::countr_zero(u64(p)), q);\n          \
    \  p >>= k;\n            q -= k;\n        } else {\n            q = 0;\n     \
    \   }\n    }\n    Surreal(const std::vector<S> &l, const std::vector<S> &r) {\n\
    \        constexpr auto inf = std::numeric_limits<i64>::max();\n        S lmax\
    \ = l.empty() ? -inf : std::ranges::max(l);\n        S rmin = r.empty() ? inf\
    \ : std::ranges::min(r);\n        assert(lmax < rmin);\n        S u = 0;\n   \
    \     while (!(lmax < u && u < rmin)) {\n            u = lmax < u ? u.left() :\
    \ u.right();\n        }\n        *this = u;\n    }\n\n    friend S operator+(S\
    \ l, S r) {\n        auto cq = std::max(l.q, r.q);\n        auto cp = (l.p <<\
    \ (cq - l.q)) + (r.p << (cq - r.q));\n        return {cp, cq};\n    }\n    friend\
    \ S operator-(S l, S r) {\n        auto cq = std::max(l.q, r.q);\n        auto\
    \ cp = (l.p << (cq - l.q)) - (r.p << (cq - r.q));\n        return {cp, cq};\n\
    \    }\n    S &operator+=(S r) { return *this = *this + r; }\n    S &operator-=(S\
    \ r) { return *this = *this - r; }\n\n    S operator-() const { return {-p, q};\
    \ }\n    S operator+() const { return *this; }\n\n    friend std::strong_ordering\
    \ operator<=>(S l, S r) {\n        return l.p * (i128(1) << r.q) <=> r.p * (i128(1)\
    \ << l.q);\n    }\n    friend bool operator==(S l, S r) { return l.p * (i128(1)\
    \ << r.q) == r.p * (i128(1) << l.q); }\n\n    S left() const { return *this -\
    \ (p <= 0 && q == 0 ? 1 : S{1, q + 1}); }\n    S right() const { return *this\
    \ + (0 <= p && q == 0 ? 1 : S{1, q + 1}); }\n\n    friend std::ostream &operator<<(std::ostream\
    \ &os, S r) {\n        os << r.p;\n        if (r.q) {\n            os << \"/\"\
    \ << (1LL << r.q);\n        }\n        return os;\n    }\n};\n\n\n"
  code: "#ifndef SURREAL_HPP\n#define SURREAL_HPP\n\n#include <algorithm>\n#include\
    \ <bit>\n#include <cassert>\n#include <compare>\n#include <limits>\n#include <ostream>\n\
    #include <vector>\n\n// g > 0: L wins\n// g < 0: R wins\n// g = 0: second wins\n\
    // https://nyaannyaan.github.io/library/game/surreal-number.hpp\nstruct Surreal\
    \ {\n    using S = Surreal;\n    using i64 = long long;\n    using u64 = unsigned\
    \ long long;\n    using i128 = __int128;\n    i64 p, q; // p / 2^q\n\n    Surreal(i64\
    \ p_ = 0, i64 q_ = 0) : p(p_), q(q_) {\n        // normalize\n        if (p) {\n\
    \            auto k = std::min<i64>(std::countr_zero(u64(p)), q);\n          \
    \  p >>= k;\n            q -= k;\n        } else {\n            q = 0;\n     \
    \   }\n    }\n    Surreal(const std::vector<S> &l, const std::vector<S> &r) {\n\
    \        constexpr auto inf = std::numeric_limits<i64>::max();\n        S lmax\
    \ = l.empty() ? -inf : std::ranges::max(l);\n        S rmin = r.empty() ? inf\
    \ : std::ranges::min(r);\n        assert(lmax < rmin);\n        S u = 0;\n   \
    \     while (!(lmax < u && u < rmin)) {\n            u = lmax < u ? u.left() :\
    \ u.right();\n        }\n        *this = u;\n    }\n\n    friend S operator+(S\
    \ l, S r) {\n        auto cq = std::max(l.q, r.q);\n        auto cp = (l.p <<\
    \ (cq - l.q)) + (r.p << (cq - r.q));\n        return {cp, cq};\n    }\n    friend\
    \ S operator-(S l, S r) {\n        auto cq = std::max(l.q, r.q);\n        auto\
    \ cp = (l.p << (cq - l.q)) - (r.p << (cq - r.q));\n        return {cp, cq};\n\
    \    }\n    S &operator+=(S r) { return *this = *this + r; }\n    S &operator-=(S\
    \ r) { return *this = *this - r; }\n\n    S operator-() const { return {-p, q};\
    \ }\n    S operator+() const { return *this; }\n\n    friend std::strong_ordering\
    \ operator<=>(S l, S r) {\n        return l.p * (i128(1) << r.q) <=> r.p * (i128(1)\
    \ << l.q);\n    }\n    friend bool operator==(S l, S r) { return l.p * (i128(1)\
    \ << r.q) == r.p * (i128(1) << l.q); }\n\n    S left() const { return *this -\
    \ (p <= 0 && q == 0 ? 1 : S{1, q + 1}); }\n    S right() const { return *this\
    \ + (0 <= p && q == 0 ? 1 : S{1, q + 1}); }\n\n    friend std::ostream &operator<<(std::ostream\
    \ &os, S r) {\n        os << r.p;\n        if (r.q) {\n            os << \"/\"\
    \ << (1LL << r.q);\n        }\n        return os;\n    }\n};\n\n#endif // SURREAL_HPP"
  dependsOn: []
  isVerificationFile: false
  path: game/surreal.hpp
  requiredBy:
  - game/ordinal_sum.hpp
  - game/numnim.hpp
  timestamp: '2026-11-05 13:44:03+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/game/2016_tsukuba_k.test.cpp
  - test/game/2016_tsukuba_k.test.cpp
documentation_of: game/surreal.hpp
layout: document
redirect_from:
- /library/game/surreal.hpp
- /library/game/surreal.hpp.html
title: game/surreal.hpp
---
