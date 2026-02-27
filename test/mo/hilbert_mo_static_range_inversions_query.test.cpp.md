---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: mo/hilbert_mo.hpp
    title: mo/hilbert_mo.hpp
  - icon: ':heavy_check_mark:'
    path: segment_tree/simd_segtree.hpp
    title: segment_tree/simd_segtree.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/static_range_inversions_query
    links:
    - https://judge.yosupo.jp/problem/static_range_inversions_query
  bundledCode: "#line 1 \"test/mo/hilbert_mo_static_range_inversions_query.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_inversions_query\"\
    \n\n#line 1 \"mo/hilbert_mo.hpp\"\n\n\n\n#include <algorithm>\n#include <array>\n\
    #include <cassert>\n#include <vector>\n\nstruct HilbertMo {\n    HilbertMo(int\
    \ n) : n_(n), log_(std::bit_width(unsigned(n))) {}\n    void add(int l, int r)\
    \ {\n        assert(0 <= l && l <= r && r <= n_);\n        auto index = int(queries_.size());\n\
    \        auto order = hilbert_order(l, r);\n        queries_.push_back({l, r,\
    \ index, order});\n    }\n    void solve(auto add, auto remove, auto eval) { solve(add,\
    \ add, remove, remove, eval); }\n    void solve(auto add_left, auto add_right,\
    \ auto remove_left, auto remove_right, auto eval) {\n        sort(queries_.begin(),\
    \ queries_.end());\n        auto l = 0, r = 0;\n        for (auto [left, right,\
    \ index, order] : queries_) {\n            while (left < l) {\n              \
    \  add_left(--l);\n            }\n            while (r < right) {\n          \
    \      add_right(r++);\n            }\n            while (l < left) {\n      \
    \          remove_left(l++);\n            }\n            while (right < r) {\n\
    \                remove_right(--r);\n            }\n            eval(index);\n\
    \        }\n    }\n\nprivate:\n    struct query {\n        int left, right, index;\n\
    \        long long order;\n        bool operator<(const query &other) const {\
    \ return order < other.order; }\n    };\n    long long hilbert_order(int x, int\
    \ y) const {\n        auto d = 0LL;\n        for (auto s = 1 << log_; s > 0; s\
    \ >>= 1) {\n            bool rx = x & s, ry = y & s;\n            d = (d << 2)\
    \ | ((rx * 3) ^ ry);\n            if (!ry) {\n                if (rx) {\n    \
    \                x = ~x;\n                    y = ~y;\n                }\n   \
    \             std::swap(x, y);\n            }\n        }\n        return d;\n\
    \    }\n    std::vector<query> queries_;\n    const int n_, log_;\n};\n\n\n#line\
    \ 1 \"segment_tree/simd_segtree.hpp\"\n\n\n\n#line 5 \"segment_tree/simd_segtree.hpp\"\
    \n#include <utility>\n#include <cstddef>\n#line 8 \"segment_tree/simd_segtree.hpp\"\
    \n\n#pragma GCC optimize(\"O3,unroll-loops\")\n#ifdef __x86_64__\n#pragma GCC\
    \ target(\"avx2,bmi,bmi2,popcnt,lzcnt\")\n#endif\n\ntemplate <typename T, int\
    \ N> struct simd_segtree {\n    static constexpr int cache_size = 64;\n    static\
    \ constexpr int reg_size = 32;\n    static constexpr int reg_count = cache_size\
    \ / reg_size;\n    static constexpr int branching = cache_size / sizeof(T);\n\
    \    static constexpr int branching_bits = std::__lg(branching);\n    typedef\
    \ T __attribute__((vector_size(reg_size))) vec;\n    struct Precalc {\n      \
    \  alignas(cache_size) T mask[branching][branching];\n        constexpr Precalc()\
    \ : mask{} {\n            for (int i = 0; i < branching; ++i)\n              \
    \  for (int j = 0; j < branching; ++j)\n                    mask[i][j] = (i <\
    \ j ? -1 : 0);\n        }\n    };\n    static constexpr Precalc precalc{};\n \
    \   static constexpr int calc_height(int n) {\n        return (n <= branching\
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
    \      j >>= branching_bits;\n        }\n        return s;\n    }\n};\n\n\n#line\
    \ 5 \"test/mo/hilbert_mo_static_range_inversions_query.test.cpp\"\n#include <bits/stdc++.h>\n\
    \nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int N, Q;\n    std::cin\
    \ >> N >> Q;\n    std::vector<int> A(N);\n    for (auto &x : A) {\n        std::cin\
    \ >> x;\n    }\n    auto c = A;\n    std::ranges::sort(c);\n    c.erase(std::unique(c.begin(),\
    \ c.end()), c.end());\n    for (auto &x : A) {\n        auto it = std::ranges::lower_bound(c,\
    \ x);\n        x = int(it - c.begin());\n    }\n    HilbertMo mo(N);\n    for\
    \ (auto i = 0; i < Q; ++i) {\n        int l, r;\n        std::cin >> l >> r;\n\
    \        mo.add(l, r);\n    }\n    auto val = 0LL;\n    auto k = int(c.size());\n\
    \    simd_segtree<int, 100000> seg;\n    std::vector<long long> ans(Q);\n    auto\
    \ add_left = [&](auto i) {\n        val += seg.sum(A[i]);\n        seg.add(A[i],\
    \ 1);\n    };\n    auto add_right = [&](auto i) {\n        val += seg.sum(A[i]\
    \ + 1, k);\n        seg.add(A[i], 1);\n    };\n    auto remove_left = [&](auto\
    \ i) {\n        val -= seg.sum(A[i]);\n        seg.add(A[i], -1);\n    };\n  \
    \  auto remove_right = [&](auto i) {\n        val -= seg.sum(A[i] + 1, k);\n \
    \       seg.add(A[i], -1);\n    };\n    auto eval = [&](auto i) { ans[i] = val;\
    \ };\n    mo.solve(add_left, add_right, remove_left, remove_right, eval);\n  \
    \  std::ranges::copy(ans, std::ostream_iterator<long long>(std::cout, \"\\n\"\
    ));\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_inversions_query\"\
    \n\n#include \"mo/hilbert_mo.hpp\"\n#include \"segment_tree/simd_segtree.hpp\"\
    \n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N, Q;\n    std::cin >> N >> Q;\n    std::vector<int> A(N);\n    for (auto\
    \ &x : A) {\n        std::cin >> x;\n    }\n    auto c = A;\n    std::ranges::sort(c);\n\
    \    c.erase(std::unique(c.begin(), c.end()), c.end());\n    for (auto &x : A)\
    \ {\n        auto it = std::ranges::lower_bound(c, x);\n        x = int(it - c.begin());\n\
    \    }\n    HilbertMo mo(N);\n    for (auto i = 0; i < Q; ++i) {\n        int\
    \ l, r;\n        std::cin >> l >> r;\n        mo.add(l, r);\n    }\n    auto val\
    \ = 0LL;\n    auto k = int(c.size());\n    simd_segtree<int, 100000> seg;\n  \
    \  std::vector<long long> ans(Q);\n    auto add_left = [&](auto i) {\n       \
    \ val += seg.sum(A[i]);\n        seg.add(A[i], 1);\n    };\n    auto add_right\
    \ = [&](auto i) {\n        val += seg.sum(A[i] + 1, k);\n        seg.add(A[i],\
    \ 1);\n    };\n    auto remove_left = [&](auto i) {\n        val -= seg.sum(A[i]);\n\
    \        seg.add(A[i], -1);\n    };\n    auto remove_right = [&](auto i) {\n \
    \       val -= seg.sum(A[i] + 1, k);\n        seg.add(A[i], -1);\n    };\n   \
    \ auto eval = [&](auto i) { ans[i] = val; };\n    mo.solve(add_left, add_right,\
    \ remove_left, remove_right, eval);\n    std::ranges::copy(ans, std::ostream_iterator<long\
    \ long>(std::cout, \"\\n\"));\n}\n"
  dependsOn:
  - mo/hilbert_mo.hpp
  - segment_tree/simd_segtree.hpp
  isVerificationFile: true
  path: test/mo/hilbert_mo_static_range_inversions_query.test.cpp
  requiredBy: []
  timestamp: '2026-02-27 15:20:30+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/mo/hilbert_mo_static_range_inversions_query.test.cpp
layout: document
redirect_from:
- /verify/test/mo/hilbert_mo_static_range_inversions_query.test.cpp
- /verify/test/mo/hilbert_mo_static_range_inversions_query.test.cpp.html
title: test/mo/hilbert_mo_static_range_inversions_query.test.cpp
---
