---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: game/surreal.hpp
    title: game/surreal.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/game/2016_tsukuba_k.test.cpp
    title: test/game/2016_tsukuba_k.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://arxiv.org/pdf/2305.16516
  bundledCode: "#line 1 \"game/ordinal_sum.hpp\"\n\n\n\n#line 1 \"game/surreal.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <bit>\n#include <cassert>\n#include <compare>\n\
    #include <limits>\n#include <ostream>\n#include <vector>\n\n// g > 0: L wins\n\
    // g < 0: R wins\n// g = 0: second wins\n// https://nyaannyaan.github.io/library/game/surreal-number.hpp\n\
    struct Surreal {\n    using S = Surreal;\n    using i64 = long long;\n    using\
    \ u64 = unsigned long long;\n    using i128 = __int128;\n    i64 p, q; // p /\
    \ 2^q\n\n    Surreal(i64 p_ = 0, i64 q_ = 0) : p(p_), q(q_) {\n        // normalize\n\
    \        if (p) {\n            auto k = std::min<i64>(std::countr_zero(u64(p)),\
    \ q);\n            p >>= k;\n            q -= k;\n        } else {\n         \
    \   q = 0;\n        }\n    }\n    Surreal(const std::vector<S> &l, const std::vector<S>\
    \ &r) {\n        constexpr auto inf = std::numeric_limits<i64>::max();\n     \
    \   S lmax = l.empty() ? -inf : std::ranges::max(l);\n        S rmin = r.empty()\
    \ ? inf : std::ranges::min(r);\n        assert(lmax < rmin);\n        S u = 0;\n\
    \        while (!(lmax < u && u < rmin)) {\n            u = lmax < u ? u.left()\
    \ : u.right();\n        }\n        *this = u;\n    }\n\n    friend S operator+(S\
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
    \ << (1LL << r.q);\n        }\n        return os;\n    }\n};\n\n\n#line 5 \"game/ordinal_sum.hpp\"\
    \n#include <cstdlib>\n\n// G : 0 = G and 0 : G = G\n// Ordinal sum is associative:\
    \ (G : H) : J = G : (H : J)\n// https://arxiv.org/pdf/2305.16516\n// ordinal sum\
    \ of numbers where the base is in canonical form\nSurreal ordinal_sum(Surreal\
    \ g, Surreal h) {\n    using S = Surreal;\n    if (h == 0) {\n        return g;\n\
    \    }\n    if (g == 0) {\n        return h;\n    }\n    if (g < 0) {\n      \
    \  // If G and H are positions, \u2212(G : H) = (\u2212G) : (\u2212H).\n     \
    \   return -ordinal_sum(-g, -h);\n    }\n    auto n = std::abs(g.p) >> g.q;\n\
    \    auto a = std::abs(g.p) & ((1LL << g.q) - 1);\n    auto p = g.q;\n    auto\
    \ m = std::abs(h.p) >> h.q;\n    auto b = std::abs(h.p) & ((1LL << h.q) - 1);\n\
    \    auto q = h.q;\n    if (a == 0) {\n        if (0 <= h) {\n            return\
    \ S(n) + S(m) + S(b, q);\n        } else {\n            return S(n) - S(1) + S(1,\
    \ m) - S(b, m + q + 1);\n        }\n    } else {\n        if (0 <= h) {\n    \
    \        return S(n) + S(a + 1, p) - S(1, p + m) + S(b, p + m + q + 1);\n    \
    \    } else {\n            return S(n) + S(a - 1, p) + S(1, p + m) - S(b, p +\
    \ m + q + 1);\n        }\n    }\n}\n\n\n"
  code: "#ifndef ORDINAL_SUM_HPP\n#define ORDINAL_SUM_HPP\n\n#include \"surreal.hpp\"\
    \n#include <cstdlib>\n\n// G : 0 = G and 0 : G = G\n// Ordinal sum is associative:\
    \ (G : H) : J = G : (H : J)\n// https://arxiv.org/pdf/2305.16516\n// ordinal sum\
    \ of numbers where the base is in canonical form\nSurreal ordinal_sum(Surreal\
    \ g, Surreal h) {\n    using S = Surreal;\n    if (h == 0) {\n        return g;\n\
    \    }\n    if (g == 0) {\n        return h;\n    }\n    if (g < 0) {\n      \
    \  // If G and H are positions, \u2212(G : H) = (\u2212G) : (\u2212H).\n     \
    \   return -ordinal_sum(-g, -h);\n    }\n    auto n = std::abs(g.p) >> g.q;\n\
    \    auto a = std::abs(g.p) & ((1LL << g.q) - 1);\n    auto p = g.q;\n    auto\
    \ m = std::abs(h.p) >> h.q;\n    auto b = std::abs(h.p) & ((1LL << h.q) - 1);\n\
    \    auto q = h.q;\n    if (a == 0) {\n        if (0 <= h) {\n            return\
    \ S(n) + S(m) + S(b, q);\n        } else {\n            return S(n) - S(1) + S(1,\
    \ m) - S(b, m + q + 1);\n        }\n    } else {\n        if (0 <= h) {\n    \
    \        return S(n) + S(a + 1, p) - S(1, p + m) + S(b, p + m + q + 1);\n    \
    \    } else {\n            return S(n) + S(a - 1, p) + S(1, p + m) - S(b, p +\
    \ m + q + 1);\n        }\n    }\n}\n\n#endif // ORDINAL_SUM_HPP"
  dependsOn:
  - game/surreal.hpp
  isVerificationFile: false
  path: game/ordinal_sum.hpp
  requiredBy: []
  timestamp: '2026-11-05 13:44:03+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/game/2016_tsukuba_k.test.cpp
documentation_of: game/ordinal_sum.hpp
layout: document
redirect_from:
- /library/game/ordinal_sum.hpp
- /library/game/ordinal_sum.hpp.html
title: game/ordinal_sum.hpp
---
