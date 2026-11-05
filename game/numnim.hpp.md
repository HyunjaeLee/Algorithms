---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: game/mex.hpp
    title: game/mex.hpp
  - icon: ':heavy_check_mark:'
    path: game/surreal.hpp
    title: game/surreal.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://codeforces.com/gym/105484/problem/D
    - https://maspypy.github.io/library/game/number_and_star.hpp
  bundledCode: "#line 1 \"game/numnim.hpp\"\n\n\n\n#line 1 \"game/mex.hpp\"\n\n\n\n\
    #include <vector>\n\nint mex(const auto &a) {\n    auto n = int(a.size());\n \
    \   std::vector<bool> f(n);\n    for (auto x : a) {\n        if (x < n) {\n  \
    \          f[x] = true;\n        }\n    }\n    for (auto i = 0; i < n; ++i) {\n\
    \        if (!f[i]) {\n            return i;\n        }\n    }\n    return n;\n\
    }\n\n\n#line 1 \"game/surreal.hpp\"\n\n\n\n#include <algorithm>\n#include <bit>\n\
    #include <cassert>\n#include <compare>\n#include <limits>\n#include <ostream>\n\
    #line 11 \"game/surreal.hpp\"\n\n// g > 0: L wins\n// g < 0: R wins\n// g = 0:\
    \ second wins\n// https://nyaannyaan.github.io/library/game/surreal-number.hpp\n\
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
    \ << (1LL << r.q);\n        }\n        return os;\n    }\n};\n\n\n#line 6 \"game/numnim.hpp\"\
    \n\n// a + *b (number + nimber)\n// a > 0: L wins\n// a < 0: R wins\n// a = 0\
    \ and b != 0: first wins\n// a = 0 and b = 0: second wins\n// https://codeforces.com/gym/105484/problem/D\n\
    // https://maspypy.github.io/library/game/number_and_star.hpp\nstruct NumNim {\n\
    \    Surreal num;\n    int nim;\n\n    NumNim(Surreal num_ = 0, int nim_ = 0)\
    \ : num(num_), nim(nim_) {}\n    NumNim(const std::vector<NumNim> &l, const std::vector<NumNim>\
    \ &r) {\n        constexpr auto inf = std::numeric_limits<long long>::max() /\
    \ 2;\n        Surreal max_num_l = -inf;\n        for (auto x : l) {\n        \
    \    max_num_l = std::max(max_num_l, x.num);\n        }\n        Surreal min_num_r\
    \ = inf;\n        for (auto x : r) {\n            min_num_r = std::min(min_num_r,\
    \ x.num);\n        }\n        std::vector<int> nim_l;\n        for (auto x : l)\
    \ {\n            if (x.num == max_num_l) {\n                nim_l.push_back(x.nim);\n\
    \            }\n        }\n        auto mex_l = mex(nim_l);\n        std::vector<int>\
    \ nim_r;\n        for (auto x : r) {\n            if (x.num == min_num_r) {\n\
    \                nim_r.push_back(x.nim);\n            }\n        }\n        auto\
    \ mex_r = mex(nim_r);\n        assert(max_num_l <= min_num_r);\n        if (max_num_l\
    \ < min_num_r) {\n            Surreal u = 0;\n            while (!((mex_l ? max_num_l\
    \ < u : max_num_l <= u) &&\n                     (mex_r ? u < min_num_r : u <=\
    \ min_num_r))) {\n                u = (mex_l ? max_num_l < u : max_num_l <= u)\
    \ ? u.left() : u.right();\n            }\n            num = u;\n            nim\
    \ = 0;\n        } else {\n            assert(mex_l == mex_r);\n            num\
    \ = max_num_l;\n            nim = mex_l;\n        }\n    }\n\n    NumNim &operator+=(NumNim\
    \ o) {\n        num += o.num;\n        nim ^= o.nim;\n        return *this;\n\
    \    }\n    NumNim &operator-=(NumNim o) {\n        num -= o.num;\n        nim\
    \ ^= o.nim;\n        return *this;\n    }\n    friend NumNim operator+(NumNim\
    \ l, NumNim r) { return l += r; }\n    friend NumNim operator-(NumNim l, NumNim\
    \ r) { return l -= r; }\n\n    friend std::ostream &operator<<(std::ostream &os,\
    \ NumNim r) {\n        os << r.num;\n        if (r.nim) {\n            os << \"\
    \ + *\" << r.nim;\n        }\n        return os;\n    }\n};\n\n\n"
  code: "#ifndef NUMNIM_HPP\n#define NUMNIM_HPP\n\n#include \"mex.hpp\"\n#include\
    \ \"surreal.hpp\"\n\n// a + *b (number + nimber)\n// a > 0: L wins\n// a < 0:\
    \ R wins\n// a = 0 and b != 0: first wins\n// a = 0 and b = 0: second wins\n//\
    \ https://codeforces.com/gym/105484/problem/D\n// https://maspypy.github.io/library/game/number_and_star.hpp\n\
    struct NumNim {\n    Surreal num;\n    int nim;\n\n    NumNim(Surreal num_ = 0,\
    \ int nim_ = 0) : num(num_), nim(nim_) {}\n    NumNim(const std::vector<NumNim>\
    \ &l, const std::vector<NumNim> &r) {\n        constexpr auto inf = std::numeric_limits<long\
    \ long>::max() / 2;\n        Surreal max_num_l = -inf;\n        for (auto x :\
    \ l) {\n            max_num_l = std::max(max_num_l, x.num);\n        }\n     \
    \   Surreal min_num_r = inf;\n        for (auto x : r) {\n            min_num_r\
    \ = std::min(min_num_r, x.num);\n        }\n        std::vector<int> nim_l;\n\
    \        for (auto x : l) {\n            if (x.num == max_num_l) {\n         \
    \       nim_l.push_back(x.nim);\n            }\n        }\n        auto mex_l\
    \ = mex(nim_l);\n        std::vector<int> nim_r;\n        for (auto x : r) {\n\
    \            if (x.num == min_num_r) {\n                nim_r.push_back(x.nim);\n\
    \            }\n        }\n        auto mex_r = mex(nim_r);\n        assert(max_num_l\
    \ <= min_num_r);\n        if (max_num_l < min_num_r) {\n            Surreal u\
    \ = 0;\n            while (!((mex_l ? max_num_l < u : max_num_l <= u) &&\n   \
    \                  (mex_r ? u < min_num_r : u <= min_num_r))) {\n            \
    \    u = (mex_l ? max_num_l < u : max_num_l <= u) ? u.left() : u.right();\n  \
    \          }\n            num = u;\n            nim = 0;\n        } else {\n \
    \           assert(mex_l == mex_r);\n            num = max_num_l;\n          \
    \  nim = mex_l;\n        }\n    }\n\n    NumNim &operator+=(NumNim o) {\n    \
    \    num += o.num;\n        nim ^= o.nim;\n        return *this;\n    }\n    NumNim\
    \ &operator-=(NumNim o) {\n        num -= o.num;\n        nim ^= o.nim;\n    \
    \    return *this;\n    }\n    friend NumNim operator+(NumNim l, NumNim r) { return\
    \ l += r; }\n    friend NumNim operator-(NumNim l, NumNim r) { return l -= r;\
    \ }\n\n    friend std::ostream &operator<<(std::ostream &os, NumNim r) {\n   \
    \     os << r.num;\n        if (r.nim) {\n            os << \" + *\" << r.nim;\n\
    \        }\n        return os;\n    }\n};\n\n#endif // NUMNIM_HPP"
  dependsOn:
  - game/mex.hpp
  - game/surreal.hpp
  isVerificationFile: false
  path: game/numnim.hpp
  requiredBy: []
  timestamp: '2026-11-05 13:44:03+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: game/numnim.hpp
layout: document
redirect_from:
- /library/game/numnim.hpp
- /library/game/numnim.hpp.html
title: game/numnim.hpp
---
