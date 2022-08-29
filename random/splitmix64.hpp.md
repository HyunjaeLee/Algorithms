---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: random/xoshiro256starstar.hpp
    title: xoshiro256**
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"random/splitmix64.hpp\"\n\n\n\n#include <cstdint>\n\nstruct\
    \ splitmix64 {\npublic:\n    using result_type = std::uint64_t;\n    splitmix64(std::uint64_t\
    \ seed = 0) : x(seed) {}\n    std::uint64_t operator()() { return next(); }\n\n\
    private:\n    std::uint64_t next() {\n        std::uint64_t z = (x += 0x9e3779b97f4a7c15);\n\
    \        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;\n        z = (z ^ (z >> 27))\
    \ * 0x94d049bb133111eb;\n        return z ^ (z >> 31);\n    }\n    std::uint64_t\
    \ x; // The state can be seeded with any value.\n};\n\n\n"
  code: "#ifndef SPLITMIX64_HPP\n#define SPLITMIX64_HPP\n\n#include <cstdint>\n\n\
    struct splitmix64 {\npublic:\n    using result_type = std::uint64_t;\n    splitmix64(std::uint64_t\
    \ seed = 0) : x(seed) {}\n    std::uint64_t operator()() { return next(); }\n\n\
    private:\n    std::uint64_t next() {\n        std::uint64_t z = (x += 0x9e3779b97f4a7c15);\n\
    \        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;\n        z = (z ^ (z >> 27))\
    \ * 0x94d049bb133111eb;\n        return z ^ (z >> 31);\n    }\n    std::uint64_t\
    \ x; // The state can be seeded with any value.\n};\n\n#endif // SPLITMIX64_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: random/splitmix64.hpp
  requiredBy:
  - random/xoshiro256starstar.hpp
  timestamp: '2022-08-29 15:08:35+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: random/splitmix64.hpp
layout: document
title: splitmix64
---

Source: [https://prng.di.unimi.it/splitmix64.c](https://prng.di.unimi.it/splitmix64.c)
