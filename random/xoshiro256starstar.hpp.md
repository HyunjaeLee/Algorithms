---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: random/splitmix64.hpp
    title: splitmix64
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/dynamic_connectivity.hpp
    title: graph/dynamic_connectivity.hpp
  - icon: ':warning:'
    path: treap/lazy_implicit_treap.hpp
    title: treap/lazy_implicit_treap.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/dynamic_connectivity.test.cpp
    title: test/dynamic_connectivity.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/treap_set.test.cpp
    title: test/treap_set.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"random/xoshiro256starstar.hpp\"\n\n\n\n#line 1 \"random/splitmix64.hpp\"\
    \n\n\n\n#include <cstdint>\n#include <limits>\n\nstruct splitmix64 {\npublic:\n\
    \    using result_type = std::uint64_t;\n    splitmix64(std::uint64_t seed = 0)\
    \ : x(seed) {}\n    std::uint64_t operator()() {\n        std::uint64_t z = (x\
    \ += 0x9e3779b97f4a7c15);\n        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;\n\
    \        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;\n        return z ^ (z >> 31);\n\
    \    }\n    static constexpr std::uint64_t min() {\n        return std::numeric_limits<std::uint64_t>::min();\n\
    \    }\n    static constexpr std::uint64_t max() {\n        return std::numeric_limits<std::uint64_t>::max();\n\
    \    }\n\nprivate:\n    std::uint64_t x; // The state can be seeded with any value.\n\
    };\n\n\n#line 5 \"random/xoshiro256starstar.hpp\"\n#include <array>\n#line 8 \"\
    random/xoshiro256starstar.hpp\"\n\nstruct xoshiro256starstar {\npublic:\n    using\
    \ result_type = std::uint64_t;\n    xoshiro256starstar(std::uint64_t seed = 0)\
    \ {\n        splitmix64 g(seed);\n        for (auto &x : s) {\n            x =\
    \ g();\n        }\n    }\n    std::uint64_t operator()() {\n        const std::uint64_t\
    \ result = rotl(s[1] * 5, 7) * 9;\n        const std::uint64_t t = s[1] << 17;\n\
    \        s[2] ^= s[0];\n        s[3] ^= s[1];\n        s[1] ^= s[2];\n       \
    \ s[0] ^= s[3];\n        s[2] ^= t;\n        s[3] = rotl(s[3], 45);\n        return\
    \ result;\n    }\n    static constexpr std::uint64_t min() {\n        return std::numeric_limits<std::uint64_t>::min();\n\
    \    }\n    static constexpr std::uint64_t max() {\n        return std::numeric_limits<std::uint64_t>::max();\n\
    \    }\n\nprivate:\n    static std::uint64_t rotl(const std::uint64_t x, int k)\
    \ {\n        return (x << k) | (x >> (64 - k));\n    }\n    std::array<std::uint64_t,\
    \ 4> s;\n};\n\n\n"
  code: "#ifndef XOSHIRO256STARSTAR_HPP\n#define XOSHIRO256STARSTAR_HPP\n\n#include\
    \ \"splitmix64.hpp\"\n#include <array>\n#include <cstdint>\n#include <limits>\n\
    \nstruct xoshiro256starstar {\npublic:\n    using result_type = std::uint64_t;\n\
    \    xoshiro256starstar(std::uint64_t seed = 0) {\n        splitmix64 g(seed);\n\
    \        for (auto &x : s) {\n            x = g();\n        }\n    }\n    std::uint64_t\
    \ operator()() {\n        const std::uint64_t result = rotl(s[1] * 5, 7) * 9;\n\
    \        const std::uint64_t t = s[1] << 17;\n        s[2] ^= s[0];\n        s[3]\
    \ ^= s[1];\n        s[1] ^= s[2];\n        s[0] ^= s[3];\n        s[2] ^= t;\n\
    \        s[3] = rotl(s[3], 45);\n        return result;\n    }\n    static constexpr\
    \ std::uint64_t min() {\n        return std::numeric_limits<std::uint64_t>::min();\n\
    \    }\n    static constexpr std::uint64_t max() {\n        return std::numeric_limits<std::uint64_t>::max();\n\
    \    }\n\nprivate:\n    static std::uint64_t rotl(const std::uint64_t x, int k)\
    \ {\n        return (x << k) | (x >> (64 - k));\n    }\n    std::array<std::uint64_t,\
    \ 4> s;\n};\n\n#endif // XOSHIRO256STARSTAR_HPP\n"
  dependsOn:
  - random/splitmix64.hpp
  isVerificationFile: false
  path: random/xoshiro256starstar.hpp
  requiredBy:
  - graph/dynamic_connectivity.hpp
  - treap/lazy_implicit_treap.hpp
  timestamp: '2022-08-29 16:56:11+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/treap_set.test.cpp
  - test/dynamic_connectivity.test.cpp
documentation_of: random/xoshiro256starstar.hpp
layout: document
title: xoshiro256**
---

Source: [https://prng.di.unimi.it/xoshiro256starstar.c](https://prng.di.unimi.it/xoshiro256starstar.c)

[UniformRandomBitGenerator](https://en.cppreference.com/w/cpp/named_req/UniformRandomBitGenerator)를 만족한다.

`std::shuffle`, `std::uniform_int_distribution`과 같은 C++ 표준 라이브러리 함수와 함께 사용할 수 있다.
