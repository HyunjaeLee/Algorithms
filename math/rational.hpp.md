---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/ceil_div.hpp
    title: math/ceil_div.hpp
  - icon: ':heavy_check_mark:'
    path: math/floor_div.hpp
    title: math/floor_div.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: data_structures/line_container.hpp
    title: data_structures/line_container.hpp
  - icon: ':heavy_check_mark:'
    path: data_structures/line_container_2d.hpp
    title: data_structures/line_container_2d.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/data_structures/line_container.test.cpp
    title: test/data_structures/line_container.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/data_structures/yuki2012.test.cpp
    title: test/data_structures/yuki2012.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://github.com/hitonanode/cplib-cpp/blob/master/rational/rational_number.hpp
  bundledCode: "#line 1 \"math/rational.hpp\"\n\n\n\n#line 1 \"math/ceil_div.hpp\"\
    \n\n\n\ntemplate <typename T> T ceil_div(T a, T b) {\n    return a / b + static_cast<T>((a\
    \ ^ b) > 0 && a % b != 0);\n}\n\n\n#line 1 \"math/floor_div.hpp\"\n\n\n\ntemplate\
    \ <typename T> T floor_div(T a, T b) {\n    return a / b - static_cast<T>((a ^\
    \ b) < 0 && a % b != 0);\n}\n\n\n#line 6 \"math/rational.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <compare>\n#include <type_traits>\n\n// https://github.com/hitonanode/cplib-cpp/blob/master/rational/rational_number.hpp\n\
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
    \ p, q; // 0 <= q\n};\n\n\n"
  code: "#ifndef RATIONAL_HPP\n#define RATIONAL_HPP\n\n#include \"math/ceil_div.hpp\"\
    \n#include \"math/floor_div.hpp\"\n#include <algorithm>\n#include <cassert>\n\
    #include <compare>\n#include <type_traits>\n\n// https://github.com/hitonanode/cplib-cpp/blob/master/rational/rational_number.hpp\n\
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
    \ p, q; // 0 <= q\n};\n\n#endif // RATIONAL_HPP"
  dependsOn:
  - math/ceil_div.hpp
  - math/floor_div.hpp
  isVerificationFile: false
  path: math/rational.hpp
  requiredBy:
  - data_structures/line_container.hpp
  - data_structures/line_container_2d.hpp
  timestamp: '2026-10-13 08:10:16+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/data_structures/yuki2012.test.cpp
  - test/data_structures/line_container.test.cpp
documentation_of: math/rational.hpp
layout: document
redirect_from:
- /library/math/rational.hpp
- /library/math/rational.hpp.html
title: math/rational.hpp
---
