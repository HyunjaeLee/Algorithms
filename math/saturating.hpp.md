---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/saturating.hpp\"\n\n\n\n#include <concepts>\n#include\
    \ <iostream>\n#include <limits>\n\ntemplate <std::integral T> struct Saturating\
    \ {\n    static constexpr T MAX = std::numeric_limits<T>::max();\n    static constexpr\
    \ T MIN = std::numeric_limits<T>::min();\n    constexpr Saturating(T v = 0) :\
    \ val_(v) {}\n    auto operator<=>(const Saturating &) const = default;\n    constexpr\
    \ Saturating &operator+=(Saturating other) {\n        if (__builtin_add_overflow(val_,\
    \ other.val_, &val_)) {\n            val_ = (val_ < 0) ? MAX : MIN;\n        }\n\
    \        return *this;\n    }\n    constexpr Saturating &operator-=(Saturating\
    \ other) {\n        if (__builtin_sub_overflow(val_, other.val_, &val_)) {\n \
    \           val_ = (val_ < 0) ? MAX : MIN;\n        }\n        return *this;\n\
    \    }\n    constexpr Saturating &operator*=(Saturating other) {\n        auto\
    \ sign = val_ ^ other.val_;\n        if (__builtin_mul_overflow(val_, other.val_,\
    \ &val_)) {\n            val_ = (sign < 0) ? MIN : MAX;\n        }\n        return\
    \ *this;\n    }\n    constexpr Saturating &operator/=(Saturating other) {\n  \
    \      if (val_ == MIN && other.val_ == -1) {\n            val_ = MAX;\n     \
    \   } else {\n            val_ /= other.val_;\n        }\n        return *this;\n\
    \    }\n    friend constexpr Saturating operator+(Saturating a, Saturating b)\
    \ {\n        a += b;\n        return a;\n    }\n    friend constexpr Saturating\
    \ operator-(Saturating a, Saturating b) {\n        a -= b;\n        return a;\n\
    \    }\n    friend constexpr Saturating operator*(Saturating a, Saturating b)\
    \ {\n        a *= b;\n        return a;\n    }\n    friend constexpr Saturating\
    \ operator/(Saturating a, Saturating b) {\n        a /= b;\n        return a;\n\
    \    }\n    constexpr Saturating operator+() const { return *this; }\n    constexpr\
    \ Saturating operator-() const {\n        if (val_ == MIN) {\n            return\
    \ {MAX};\n        }\n        return {-val_};\n    }\n    constexpr Saturating\
    \ abs() const {\n        if (val_ == MIN) {\n            return {MAX};\n     \
    \   }\n        return (val_ < 0) ? Saturating(-val_) : *this;\n    }\n    constexpr\
    \ Saturating pow(unsigned long long exp) const {\n        Saturating res = 1;\n\
    \        Saturating base = *this;\n        while (exp) {\n            if (exp\
    \ & 1) {\n                res *= base;\n            }\n            base *= base;\n\
    \            exp >>= 1;\n        }\n        return res;\n    }\n    constexpr\
    \ T val() const { return val_; }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, Saturating s) { return os << s.val_; }\n    friend std::istream &operator>>(std::istream\
    \ &is, Saturating &s) { return is >> s.val_; }\n\nprivate:\n    T val_;\n};\n\n\
    \n"
  code: "#ifndef SATURATING_HPP\n#define SATURATING_HPP\n\n#include <concepts>\n#include\
    \ <iostream>\n#include <limits>\n\ntemplate <std::integral T> struct Saturating\
    \ {\n    static constexpr T MAX = std::numeric_limits<T>::max();\n    static constexpr\
    \ T MIN = std::numeric_limits<T>::min();\n    constexpr Saturating(T v = 0) :\
    \ val_(v) {}\n    auto operator<=>(const Saturating &) const = default;\n    constexpr\
    \ Saturating &operator+=(Saturating other) {\n        if (__builtin_add_overflow(val_,\
    \ other.val_, &val_)) {\n            val_ = (val_ < 0) ? MAX : MIN;\n        }\n\
    \        return *this;\n    }\n    constexpr Saturating &operator-=(Saturating\
    \ other) {\n        if (__builtin_sub_overflow(val_, other.val_, &val_)) {\n \
    \           val_ = (val_ < 0) ? MAX : MIN;\n        }\n        return *this;\n\
    \    }\n    constexpr Saturating &operator*=(Saturating other) {\n        auto\
    \ sign = val_ ^ other.val_;\n        if (__builtin_mul_overflow(val_, other.val_,\
    \ &val_)) {\n            val_ = (sign < 0) ? MIN : MAX;\n        }\n        return\
    \ *this;\n    }\n    constexpr Saturating &operator/=(Saturating other) {\n  \
    \      if (val_ == MIN && other.val_ == -1) {\n            val_ = MAX;\n     \
    \   } else {\n            val_ /= other.val_;\n        }\n        return *this;\n\
    \    }\n    friend constexpr Saturating operator+(Saturating a, Saturating b)\
    \ {\n        a += b;\n        return a;\n    }\n    friend constexpr Saturating\
    \ operator-(Saturating a, Saturating b) {\n        a -= b;\n        return a;\n\
    \    }\n    friend constexpr Saturating operator*(Saturating a, Saturating b)\
    \ {\n        a *= b;\n        return a;\n    }\n    friend constexpr Saturating\
    \ operator/(Saturating a, Saturating b) {\n        a /= b;\n        return a;\n\
    \    }\n    constexpr Saturating operator+() const { return *this; }\n    constexpr\
    \ Saturating operator-() const {\n        if (val_ == MIN) {\n            return\
    \ {MAX};\n        }\n        return {-val_};\n    }\n    constexpr Saturating\
    \ abs() const {\n        if (val_ == MIN) {\n            return {MAX};\n     \
    \   }\n        return (val_ < 0) ? Saturating(-val_) : *this;\n    }\n    constexpr\
    \ Saturating pow(unsigned long long exp) const {\n        Saturating res = 1;\n\
    \        Saturating base = *this;\n        while (exp) {\n            if (exp\
    \ & 1) {\n                res *= base;\n            }\n            base *= base;\n\
    \            exp >>= 1;\n        }\n        return res;\n    }\n    constexpr\
    \ T val() const { return val_; }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, Saturating s) { return os << s.val_; }\n    friend std::istream &operator>>(std::istream\
    \ &is, Saturating &s) { return is >> s.val_; }\n\nprivate:\n    T val_;\n};\n\n\
    #endif // SATURATING_HPP"
  dependsOn: []
  isVerificationFile: false
  path: math/saturating.hpp
  requiredBy: []
  timestamp: '2026-08-04 08:03:55+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/saturating.hpp
layout: document
title: Saturating
---

Provides saturating arithmetic on T.

### Related Problem
+ [Keep Fighting](https://www.acmicpc.net/problem/34742)
