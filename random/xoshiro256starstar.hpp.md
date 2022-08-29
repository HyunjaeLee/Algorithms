---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: random/splitmix64.hpp
    title: splitmix64
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"random/xoshiro256starstar.hpp\"\n\n\n\n#line 1 \"random/splitmix64.hpp\"\
    \n\n\n\n#include <cstdint>\n\nstruct splitmix64 {\npublic:\n    using result_type\
    \ = std::uint64_t;\n    splitmix64(std::uint64_t seed = 0) : x(seed) {}\n    std::uint64_t\
    \ operator()() { return next(); }\n\nprivate:\n    std::uint64_t next() {\n  \
    \      std::uint64_t z = (x += 0x9e3779b97f4a7c15);\n        z = (z ^ (z >> 30))\
    \ * 0xbf58476d1ce4e5b9;\n        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;\n \
    \       return z ^ (z >> 31);\n    }\n    std::uint64_t x; // The state can be\
    \ seeded with any value.\n};\n\n\n#line 5 \"random/xoshiro256starstar.hpp\"\n\
    #include <array>\n#line 7 \"random/xoshiro256starstar.hpp\"\n\nstruct xoshiro256starstar\
    \ {\npublic:\n    using result_type = std::uint64_t;\n    xoshiro256starstar(std::uint64_t\
    \ seed = 0) {\n        splitmix64 g(seed);\n        for (auto &x : s) {\n    \
    \        x = g();\n        }\n    }\n    std::uint64_t operator()() { return next();\
    \ }\n\nprivate:\n    static std::uint64_t rotl(const std::uint64_t x, int k) {\n\
    \        return (x << k) | (x >> (64 - k));\n    }\n    std::uint64_t next() {\n\
    \        const std::uint64_t result = rotl(s[1] * 5, 7) * 9;\n        const std::uint64_t\
    \ t = s[1] << 17;\n        s[2] ^= s[0];\n        s[3] ^= s[1];\n        s[1]\
    \ ^= s[2];\n        s[0] ^= s[3];\n        s[2] ^= t;\n        s[3] = rotl(s[3],\
    \ 45);\n        return result;\n    }\n    std::array<std::uint64_t, 4> s;\n};\n\
    \n\n"
  code: "#ifndef XOSHIRO256STARSTAR_HPP\n#define XOSHIRO256STARSTAR_HPP\n\n#include\
    \ \"splitmix64.hpp\"\n#include <array>\n#include <cstdint>\n\nstruct xoshiro256starstar\
    \ {\npublic:\n    using result_type = std::uint64_t;\n    xoshiro256starstar(std::uint64_t\
    \ seed = 0) {\n        splitmix64 g(seed);\n        for (auto &x : s) {\n    \
    \        x = g();\n        }\n    }\n    std::uint64_t operator()() { return next();\
    \ }\n\nprivate:\n    static std::uint64_t rotl(const std::uint64_t x, int k) {\n\
    \        return (x << k) | (x >> (64 - k));\n    }\n    std::uint64_t next() {\n\
    \        const std::uint64_t result = rotl(s[1] * 5, 7) * 9;\n        const std::uint64_t\
    \ t = s[1] << 17;\n        s[2] ^= s[0];\n        s[3] ^= s[1];\n        s[1]\
    \ ^= s[2];\n        s[0] ^= s[3];\n        s[2] ^= t;\n        s[3] = rotl(s[3],\
    \ 45);\n        return result;\n    }\n    std::array<std::uint64_t, 4> s;\n};\n\
    \n#endif // XOSHIRO256STARSTAR_HPP\n"
  dependsOn:
  - random/splitmix64.hpp
  isVerificationFile: false
  path: random/xoshiro256starstar.hpp
  requiredBy: []
  timestamp: '2022-08-29 15:08:35+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: random/xoshiro256starstar.hpp
layout: document
title: xoshiro256**
---

Source: [https://prng.di.unimi.it/xoshiro256starstar.c](https://prng.di.unimi.it/xoshiro256starstar.c)