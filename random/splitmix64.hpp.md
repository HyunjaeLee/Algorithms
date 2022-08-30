---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: random/xoshiro256starstar.hpp
    title: xoshiro256**
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/treap_set.test.cpp
    title: test/treap_set.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"random/splitmix64.hpp\"\n\n\n\n#include <cstdint>\n#include\
    \ <limits>\n\nstruct splitmix64 {\npublic:\n    using result_type = std::uint64_t;\n\
    \    splitmix64(std::uint64_t seed = 0) : x(seed) {}\n    std::uint64_t operator()()\
    \ {\n        std::uint64_t z = (x += 0x9e3779b97f4a7c15);\n        z = (z ^ (z\
    \ >> 30)) * 0xbf58476d1ce4e5b9;\n        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;\n\
    \        return z ^ (z >> 31);\n    }\n    static constexpr std::uint64_t min()\
    \ {\n        return std::numeric_limits<std::uint64_t>::min();\n    }\n    static\
    \ constexpr std::uint64_t max() {\n        return std::numeric_limits<std::uint64_t>::max();\n\
    \    }\n\nprivate:\n    std::uint64_t x; // The state can be seeded with any value.\n\
    };\n\n\n"
  code: "#ifndef SPLITMIX64_HPP\n#define SPLITMIX64_HPP\n\n#include <cstdint>\n#include\
    \ <limits>\n\nstruct splitmix64 {\npublic:\n    using result_type = std::uint64_t;\n\
    \    splitmix64(std::uint64_t seed = 0) : x(seed) {}\n    std::uint64_t operator()()\
    \ {\n        std::uint64_t z = (x += 0x9e3779b97f4a7c15);\n        z = (z ^ (z\
    \ >> 30)) * 0xbf58476d1ce4e5b9;\n        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;\n\
    \        return z ^ (z >> 31);\n    }\n    static constexpr std::uint64_t min()\
    \ {\n        return std::numeric_limits<std::uint64_t>::min();\n    }\n    static\
    \ constexpr std::uint64_t max() {\n        return std::numeric_limits<std::uint64_t>::max();\n\
    \    }\n\nprivate:\n    std::uint64_t x; // The state can be seeded with any value.\n\
    };\n\n#endif // SPLITMIX64_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: random/splitmix64.hpp
  requiredBy:
  - random/xoshiro256starstar.hpp
  timestamp: '2022-08-29 16:56:11+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/treap_set.test.cpp
documentation_of: random/splitmix64.hpp
layout: document
title: splitmix64
---

Source: [https://prng.di.unimi.it/splitmix64.c](https://prng.di.unimi.it/splitmix64.c)

[UniformRandomBitGenerator](https://en.cppreference.com/w/cpp/named_req/UniformRandomBitGenerator)를 만족한다.

`std::shuffle`, `std::uniform_int_distribution`과 같은 C++ 표준 라이브러리 함수와 함께 사용할 수 있다.
