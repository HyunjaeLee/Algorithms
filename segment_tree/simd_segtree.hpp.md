---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/mo/hilbert_mo_static_range_inversions_query.test.cpp
    title: test/mo/hilbert_mo_static_range_inversions_query.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"segment_tree/simd_segtree.hpp\"\n\n\n\n#include <array>\n\
    #include <utility>\n#include <cstddef>\n#include <algorithm>\n\n#pragma GCC optimize(\"\
    O3,unroll-loops\")\n#ifdef __x86_64__\n#pragma GCC target(\"avx2,bmi,bmi2,popcnt,lzcnt\"\
    )\n#endif\n\ntemplate <typename T, int N> struct simd_segtree {\n    static constexpr\
    \ int cache_size = 64;\n    static constexpr int reg_size = 32;\n    static constexpr\
    \ int reg_count = cache_size / reg_size;\n    static constexpr int branching =\
    \ cache_size / sizeof(T);\n    static constexpr int branching_bits = std::__lg(branching);\n\
    \    typedef T __attribute__((vector_size(reg_size))) vec;\n    struct Precalc\
    \ {\n        alignas(cache_size) T mask[branching][branching];\n        constexpr\
    \ Precalc() : mask{} {\n            for (int i = 0; i < branching; ++i)\n    \
    \            for (int j = 0; j < branching; ++j)\n                    mask[i][j]\
    \ = (i < j ? -1 : 0);\n        }\n    };\n    static constexpr Precalc precalc{};\n\
    \    static constexpr int calc_height(int n) {\n        return (n <= branching\
    \ ? 1 : calc_height(n / branching) + 1);\n    }\n    static constexpr int calc_offset(int\
    \ h) {\n        int s = 0, n = N;\n        while (h--) {\n            n = (n +\
    \ branching - 1) / branching;\n            s += n * branching + branching;\n \
    \       }\n        return s;\n    }\n    static constexpr int round(int k) { return\
    \ k & ~(branching - 1); }\n    static constexpr int H = calc_height(N);\n    template\
    \ <std::size_t... indices>\n    static constexpr std::array<int, H + 1> calc_offsets(std::index_sequence<indices...>)\
    \ {\n        return {calc_offset(indices)...};\n    }\n    static constexpr auto\
    \ offset = calc_offsets(std::make_index_sequence<H + 1>());\n    alignas(cache_size)\
    \ T values[offset[H]]{};\n    void add(int k, T x) {\n        vec v = x + vec{};\n\
    \        for (int h = 0; h != H; ++h) {\n            auto a = (vec *)&values[offset[h]\
    \ + round(k)];\n            const auto m = (const vec *)&precalc.mask[k % branching];\n\
    \            for (int i = 0; i != reg_count; ++i)\n                a[i] += v &\
    \ m[i];\n            k >>= branching_bits;\n        }\n    }\n    T sum(int i)\
    \ {\n        T s = 0;\n        for (int h = 0; h != H; ++h) {\n            s +=\
    \ values[offset[h] + i];\n            i >>= branching_bits;\n        }\n     \
    \   return s;\n    }\n    T sum(int i, int j) {\n        T s = 0;\n        for\
    \ (int h = 0; h != H; ++h) {\n            s -= values[offset[h] + i];\n      \
    \      s += values[offset[h] + j];\n            i >>= branching_bits;\n      \
    \      j >>= branching_bits;\n        }\n        return s;\n    }\n};\n\n\n"
  code: "#ifndef SIMD_SEGTREE_HPP\n#define SIMD_SEGTREE_HPP\n\n#include <array>\n\
    #include <utility>\n#include <cstddef>\n#include <algorithm>\n\n#pragma GCC optimize(\"\
    O3,unroll-loops\")\n#ifdef __x86_64__\n#pragma GCC target(\"avx2,bmi,bmi2,popcnt,lzcnt\"\
    )\n#endif\n\ntemplate <typename T, int N> struct simd_segtree {\n    static constexpr\
    \ int cache_size = 64;\n    static constexpr int reg_size = 32;\n    static constexpr\
    \ int reg_count = cache_size / reg_size;\n    static constexpr int branching =\
    \ cache_size / sizeof(T);\n    static constexpr int branching_bits = std::__lg(branching);\n\
    \    typedef T __attribute__((vector_size(reg_size))) vec;\n    struct Precalc\
    \ {\n        alignas(cache_size) T mask[branching][branching];\n        constexpr\
    \ Precalc() : mask{} {\n            for (int i = 0; i < branching; ++i)\n    \
    \            for (int j = 0; j < branching; ++j)\n                    mask[i][j]\
    \ = (i < j ? -1 : 0);\n        }\n    };\n    static constexpr Precalc precalc{};\n\
    \    static constexpr int calc_height(int n) {\n        return (n <= branching\
    \ ? 1 : calc_height(n / branching) + 1);\n    }\n    static constexpr int calc_offset(int\
    \ h) {\n        int s = 0, n = N;\n        while (h--) {\n            n = (n +\
    \ branching - 1) / branching;\n            s += n * branching + branching;\n \
    \       }\n        return s;\n    }\n    static constexpr int round(int k) { return\
    \ k & ~(branching - 1); }\n    static constexpr int H = calc_height(N);\n    template\
    \ <std::size_t... indices>\n    static constexpr std::array<int, H + 1> calc_offsets(std::index_sequence<indices...>)\
    \ {\n        return {calc_offset(indices)...};\n    }\n    static constexpr auto\
    \ offset = calc_offsets(std::make_index_sequence<H + 1>());\n    alignas(cache_size)\
    \ T values[offset[H]]{};\n    void add(int k, T x) {\n        vec v = x + vec{};\n\
    \        for (int h = 0; h != H; ++h) {\n            auto a = (vec *)&values[offset[h]\
    \ + round(k)];\n            const auto m = (const vec *)&precalc.mask[k % branching];\n\
    \            for (int i = 0; i != reg_count; ++i)\n                a[i] += v &\
    \ m[i];\n            k >>= branching_bits;\n        }\n    }\n    T sum(int i)\
    \ {\n        T s = 0;\n        for (int h = 0; h != H; ++h) {\n            s +=\
    \ values[offset[h] + i];\n            i >>= branching_bits;\n        }\n     \
    \   return s;\n    }\n    T sum(int i, int j) {\n        T s = 0;\n        for\
    \ (int h = 0; h != H; ++h) {\n            s -= values[offset[h] + i];\n      \
    \      s += values[offset[h] + j];\n            i >>= branching_bits;\n      \
    \      j >>= branching_bits;\n        }\n        return s;\n    }\n};\n\n#endif\
    \ // SIMD_SEGTREE_HPP"
  dependsOn: []
  isVerificationFile: false
  path: segment_tree/simd_segtree.hpp
  requiredBy: []
  timestamp: '2026-02-27 15:20:30+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/mo/hilbert_mo_static_range_inversions_query.test.cpp
documentation_of: segment_tree/simd_segtree.hpp
layout: document
redirect_from:
- /library/segment_tree/simd_segtree.hpp
- /library/segment_tree/simd_segtree.hpp.html
title: segment_tree/simd_segtree.hpp
---
