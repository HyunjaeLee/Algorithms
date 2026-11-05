---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: game/ordinal_sum.hpp
    title: game/ordinal_sum.hpp
  - icon: ':heavy_check_mark:'
    path: game/surreal.hpp
    title: game/surreal.hpp
  - icon: ':heavy_check_mark:'
    path: game/surreal.hpp
    title: game/surreal.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/1377
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/1377
  bundledCode: "#line 1 \"test/game/2016_tsukuba_k.test.cpp\"\n#define PROBLEM \"\
    https://onlinejudge.u-aizu.ac.jp/problems/1377\"\n\n#line 1 \"game/ordinal_sum.hpp\"\
    \n\n\n\n#line 1 \"game/surreal.hpp\"\n\n\n\n#include <algorithm>\n#include <bit>\n\
    #include <cassert>\n#include <compare>\n#include <limits>\n#include <ostream>\n\
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
    \ m + q + 1);\n        }\n    }\n}\n\n\n#line 5 \"test/game/2016_tsukuba_k.test.cpp\"\
    \n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    using S = Surreal;\n    int N;\n    std::cin >> N;\n    std::vector<std::string>\
    \ A(N);\n    for (auto i = 0; i < N; ++i) {\n        std::cin >> A[i];\n    }\n\
    \    std::vector<S> G(N);\n    for (auto i = 0; i < N; ++i) {\n        for (auto\
    \ c : A[i]) {\n            G[i] = ordinal_sum(G[i], c == 'B' ? 1 : -1);\n    \
    \    }\n    }\n    auto ans = 0;\n    auto X = N / 2;\n    auto Y = N - N / 2;\n\
    \    std::map<S, int> mp;\n    for (auto s = 0; s < (1 << X); ++s) {\n       \
    \ S sum = 0;\n        auto sz = 0;\n        for (auto i = 0; i < X; ++i) {\n \
    \           if ((s >> i) & 1) {\n                sum += G[i];\n              \
    \  sz += int(A[i].size());\n            }\n        }\n        mp[sum] = std::max(mp[sum],\
    \ sz);\n    }\n    for (auto s = 0; s < (1 << Y); ++s) {\n        S sum = 0;\n\
    \        auto sz = 0;\n        for (auto i = 0; i < Y; ++i) {\n            if\
    \ ((s >> i) & 1) {\n                sum += G[X + i];\n                sz += int(A[X\
    \ + i].size());\n            }\n        }\n        if (auto it = mp.find(-sum);\
    \ it != mp.end()) {\n            ans = std::max(ans, it->second + sz);\n     \
    \   }\n    }\n    std::cout << ans << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/1377\"\n\n#include\
    \ \"game/ordinal_sum.hpp\"\n#include \"game/surreal.hpp\"\n#include <bits/stdc++.h>\n\
    \nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n    using S = Surreal;\n\
    \    int N;\n    std::cin >> N;\n    std::vector<std::string> A(N);\n    for (auto\
    \ i = 0; i < N; ++i) {\n        std::cin >> A[i];\n    }\n    std::vector<S> G(N);\n\
    \    for (auto i = 0; i < N; ++i) {\n        for (auto c : A[i]) {\n         \
    \   G[i] = ordinal_sum(G[i], c == 'B' ? 1 : -1);\n        }\n    }\n    auto ans\
    \ = 0;\n    auto X = N / 2;\n    auto Y = N - N / 2;\n    std::map<S, int> mp;\n\
    \    for (auto s = 0; s < (1 << X); ++s) {\n        S sum = 0;\n        auto sz\
    \ = 0;\n        for (auto i = 0; i < X; ++i) {\n            if ((s >> i) & 1)\
    \ {\n                sum += G[i];\n                sz += int(A[i].size());\n \
    \           }\n        }\n        mp[sum] = std::max(mp[sum], sz);\n    }\n  \
    \  for (auto s = 0; s < (1 << Y); ++s) {\n        S sum = 0;\n        auto sz\
    \ = 0;\n        for (auto i = 0; i < Y; ++i) {\n            if ((s >> i) & 1)\
    \ {\n                sum += G[X + i];\n                sz += int(A[X + i].size());\n\
    \            }\n        }\n        if (auto it = mp.find(-sum); it != mp.end())\
    \ {\n            ans = std::max(ans, it->second + sz);\n        }\n    }\n   \
    \ std::cout << ans << \"\\n\";\n}\n"
  dependsOn:
  - game/ordinal_sum.hpp
  - game/surreal.hpp
  - game/surreal.hpp
  isVerificationFile: true
  path: test/game/2016_tsukuba_k.test.cpp
  requiredBy: []
  timestamp: '2026-11-05 13:44:03+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/game/2016_tsukuba_k.test.cpp
layout: document
redirect_from:
- /verify/test/game/2016_tsukuba_k.test.cpp
- /verify/test/game/2016_tsukuba_k.test.cpp.html
title: test/game/2016_tsukuba_k.test.cpp
---
