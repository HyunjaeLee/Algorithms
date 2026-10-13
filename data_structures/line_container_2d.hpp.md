---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structures/line_container.hpp
    title: data_structures/line_container.hpp
  - icon: ':heavy_check_mark:'
    path: math/ceil_div.hpp
    title: math/ceil_div.hpp
  - icon: ':heavy_check_mark:'
    path: math/floor_div.hpp
    title: math/floor_div.hpp
  - icon: ':heavy_check_mark:'
    path: math/rational.hpp
    title: math/rational.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/data_structures/yuki2012.test.cpp
    title: test/data_structures/yuki2012.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structures/line_container_2d.hpp\"\n\n\n\n#line 1 \"\
    data_structures/line_container.hpp\"\n\n\n\n#line 1 \"math/rational.hpp\"\n\n\n\
    \n#line 1 \"math/ceil_div.hpp\"\n\n\n\ntemplate <typename T> T ceil_div(T a, T\
    \ b) {\n    return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0);\n}\n\n\n\
    #line 1 \"math/floor_div.hpp\"\n\n\n\ntemplate <typename T> T floor_div(T a, T\
    \ b) {\n    return a / b - static_cast<T>((a ^ b) < 0 && a % b != 0);\n}\n\n\n\
    #line 6 \"math/rational.hpp\"\n#include <algorithm>\n#include <cassert>\n#include\
    \ <compare>\n#include <type_traits>\n\n// https://github.com/hitonanode/cplib-cpp/blob/master/rational/rational_number.hpp\n\
    template <typename T, bool reduce = false> struct rational {\n    constexpr rational(T\
    \ num = 0, T den = 1) : p(num), q(den) { normalize(); }\n\n    constexpr bool\
    \ is_finite() const { return q != 0; }\n    constexpr bool is_infinite() const\
    \ { return p != 0 && q == 0; }\n    constexpr bool is_nan() const { return p ==\
    \ 0 && q == 0; }\n\n    constexpr rational &operator+=(const rational &o) {\n\
    \        if (is_nan() || o.is_nan())\n            return *this = rational(0, 0);\n\
    \        if (is_infinite() && o.is_infinite())\n            return *this = rational(p\
    \ + o.p, 0);\n        return *this = rational(p * o.q + q * o.p, q * o.q);\n \
    \   }\n    constexpr rational &operator-=(const rational &o) {\n        if (is_nan()\
    \ || o.is_nan())\n            return *this = rational(0, 0);\n        if (is_infinite()\
    \ && o.is_infinite())\n            return *this = rational(p - o.p, 0);\n    \
    \    return *this = rational(p * o.q - q * o.p, q * o.q);\n    }\n    constexpr\
    \ rational &operator*=(const rational &o) { return *this = rational(p * o.p, q\
    \ * o.q); }\n    constexpr rational &operator/=(const rational &o) {\n       \
    \ if (o.p < 0)\n            return *this = rational(p * -o.q, -q * o.p);\n   \
    \     return *this = rational(p * o.q, q * o.p);\n    }\n\n    friend constexpr\
    \ rational operator+(rational a, const rational &b) { return a += b; }\n    friend\
    \ constexpr rational operator-(rational a, const rational &b) { return a -= b;\
    \ }\n    friend constexpr rational operator*(rational a, const rational &b) {\
    \ return a *= b; }\n    friend constexpr rational operator/(rational a, const\
    \ rational &b) { return a /= b; }\n\n    constexpr rational operator-() const\
    \ { return rational(-p, q); }\n    constexpr rational abs() const { return rational(0\
    \ < p ? p : -p, q); }\n    constexpr T floor() const {\n        assert(is_finite());\n\
    \        return floor_div(p, q);\n    }\n    constexpr T ceil() const {\n    \
    \    assert(is_finite());\n        return ceil_div(p, q);\n    }\n\n    constexpr\
    \ std::partial_ordering operator<=>(const rational &r) const {\n        if (is_nan()\
    \ || r.is_nan()) {\n            return std::partial_ordering::unordered;\n   \
    \     }\n        if (is_infinite() && r.is_infinite()) {\n            return p\
    \ <=> r.p;\n        }\n        if (is_infinite()) {\n            return p < 0\
    \ ? std::partial_ordering::less : std::partial_ordering::greater;\n        }\n\
    \        if (r.is_infinite()) {\n            return r.p < 0 ? std::partial_ordering::greater\
    \ : std::partial_ordering::less;\n        }\n        using W = std::conditional_t<sizeof(T)\
    \ <= sizeof(int), long long, __int128_t>;\n        return (W(p) * r.q) <=> (W(r.p)\
    \ * q);\n    }\n    constexpr bool operator==(const rational &r) const { return\
    \ (*this <=> r) == 0; }\n\n    constexpr explicit operator double() const { return\
    \ (double)p / (double)q; }\n    constexpr explicit operator long double() const\
    \ { return (long double)p / (long double)q; }\n\n    constexpr T numerator() const\
    \ { return p; }\n    constexpr T denominator() const { return q; }\n\nprivate:\n\
    \    constexpr void normalize() {\n        if (q == 0) {\n            p = (p >\
    \ 0) - (p < 0);\n            return;\n        }\n        if constexpr (reduce)\
    \ {\n            T g = std::__gcd(p, q);\n            if (g) {\n             \
    \   p /= g;\n                q /= g;\n            }\n        }\n        if (q\
    \ < 0) {\n            p = -p;\n            q = -q;\n        }\n    }\n\n    T\
    \ p, q; // 0 <= q\n};\n\n\n#line 6 \"data_structures/line_container.hpp\"\n#include\
    \ <functional>\n#include <set>\n#include <utility>\n\n// https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h\n\
    template <typename T, bool maximize = true> struct line_container {\n    struct\
    \ line {\n        T a, b;\n        mutable rational<T> p;\n        bool operator<(const\
    \ line &o) const { return a < o.a; }\n        bool operator<(auto x) const { return\
    \ p < x; }\n    };\n    static constexpr auto inf = rational<T>(1, 0);\n    bool\
    \ isect(auto x, auto y) {\n        if (y == lines.end()) {\n            x->p =\
    \ inf;\n            return false;\n        }\n        if (x->a == y->a) {\n  \
    \          x->p = (y->b < x->b) ? inf : -inf;\n        } else {\n            x->p\
    \ = rational<T>(y->b - x->b, x->a - y->a);\n        }\n        return x->p >=\
    \ y->p;\n    }\n    void add(T a, T b) {\n        if constexpr (!maximize) {\n\
    \            a = -a;\n            b = -b;\n        }\n        auto z = lines.emplace(a,\
    \ b, 0);\n        auto y = z++;\n        auto x = y;\n        while (isect(y,\
    \ z)) {\n            z = lines.erase(z);\n        }\n        if (x != lines.begin()\
    \ && isect(--x, y)) {\n            y = lines.erase(y);\n            isect(x, y);\n\
    \        }\n        while ((y = x) != lines.begin() && (--x)->p >= y->p) {\n \
    \           isect(x, lines.erase(y));\n        }\n    }\n    std::pair<T, T> query_line(auto\
    \ x) const {\n        assert(!lines.empty());\n        auto l = lines.lower_bound(x);\n\
    \        if constexpr (maximize) {\n            return {l->a, l->b};\n       \
    \ } else {\n            return {-l->a, -l->b};\n        }\n    }\n    T query(T\
    \ x) const {\n        auto [a, b] = query_line(x);\n        return a * x + b;\n\
    \    }\n\nprivate:\n    std::multiset<line, std::less<>> lines;\n};\n\n\n#line\
    \ 7 \"data_structures/line_container_2d.hpp\"\n#include <limits>\n\ntemplate <typename\
    \ T> struct line_container_2d {\n    void add(T a, T b) {\n        min_a = std::min(min_a,\
    \ a);\n        max_a = std::max(max_a, a);\n        min_lc.add(a, b);\n      \
    \  max_lc.add(a, b);\n    }\n    T max(T x, T y) const {\n        if (y == 0)\
    \ {\n            return x < 0 ? x * min_a : x * max_a;\n        }\n        rational<T>\
    \ r(x, y);\n        auto [a, b] = (y < 0 ? min_lc.query_line(r) : max_lc.query_line(r));\n\
    \        return a * x + b * y;\n    }\n    T min(T x, T y) const { return -max(-x,\
    \ -y); }\n\nprivate:\n    static constexpr auto inf = std::numeric_limits<T>::max();\n\
    \    T min_a = inf, max_a = -inf;\n    line_container<T, false> min_lc;\n    line_container<T>\
    \ max_lc;\n};\n\n\n"
  code: "#ifndef LINE_CONTAINER_2D_HPP\n#define LINE_CONTAINER_2D_HPP\n\n#include\
    \ \"data_structures/line_container.hpp\"\n#include \"math/rational.hpp\"\n#include\
    \ <algorithm>\n#include <limits>\n\ntemplate <typename T> struct line_container_2d\
    \ {\n    void add(T a, T b) {\n        min_a = std::min(min_a, a);\n        max_a\
    \ = std::max(max_a, a);\n        min_lc.add(a, b);\n        max_lc.add(a, b);\n\
    \    }\n    T max(T x, T y) const {\n        if (y == 0) {\n            return\
    \ x < 0 ? x * min_a : x * max_a;\n        }\n        rational<T> r(x, y);\n  \
    \      auto [a, b] = (y < 0 ? min_lc.query_line(r) : max_lc.query_line(r));\n\
    \        return a * x + b * y;\n    }\n    T min(T x, T y) const { return -max(-x,\
    \ -y); }\n\nprivate:\n    static constexpr auto inf = std::numeric_limits<T>::max();\n\
    \    T min_a = inf, max_a = -inf;\n    line_container<T, false> min_lc;\n    line_container<T>\
    \ max_lc;\n};\n\n#endif // LINE_CONTAINER_2D_HPP"
  dependsOn:
  - data_structures/line_container.hpp
  - math/rational.hpp
  - math/ceil_div.hpp
  - math/floor_div.hpp
  isVerificationFile: false
  path: data_structures/line_container_2d.hpp
  requiredBy: []
  timestamp: '2026-10-13 08:16:35+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/data_structures/yuki2012.test.cpp
documentation_of: data_structures/line_container_2d.hpp
layout: document
redirect_from:
- /library/data_structures/line_container_2d.hpp
- /library/data_structures/line_container_2d.hpp.html
title: data_structures/line_container_2d.hpp
---
