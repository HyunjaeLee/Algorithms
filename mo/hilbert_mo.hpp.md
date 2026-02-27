---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: mo/mo_tree.hpp
    title: mo/mo_tree.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/mo/aoj0489.test.cpp
    title: test/mo/aoj0489.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/mo/aoj2270.test.cpp
    title: test/mo/aoj2270.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/mo/hilbert_mo_range_kth_smallest.test.cpp
    title: test/mo/hilbert_mo_range_kth_smallest.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/mo/hilbert_mo_static_range_count_distinct.test.cpp
    title: test/mo/hilbert_mo_static_range_count_distinct.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/mo/hilbert_mo_static_range_frequency.test.cpp
    title: test/mo/hilbert_mo_static_range_frequency.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/mo/hilbert_mo_static_range_inversions_query.test.cpp
    title: test/mo/hilbert_mo_static_range_inversions_query.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"mo/hilbert_mo.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <array>\n#include <cassert>\n#include <vector>\n\nstruct HilbertMo {\n    HilbertMo(int\
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
    \    }\n    std::vector<query> queries_;\n    const int n_, log_;\n};\n\n\n"
  code: "#ifndef HILBERT_MO_HPP\n#define HILBERT_MO_HPP\n\n#include <algorithm>\n\
    #include <array>\n#include <cassert>\n#include <vector>\n\nstruct HilbertMo {\n\
    \    HilbertMo(int n) : n_(n), log_(std::bit_width(unsigned(n))) {}\n    void\
    \ add(int l, int r) {\n        assert(0 <= l && l <= r && r <= n_);\n        auto\
    \ index = int(queries_.size());\n        auto order = hilbert_order(l, r);\n \
    \       queries_.push_back({l, r, index, order});\n    }\n    void solve(auto\
    \ add, auto remove, auto eval) { solve(add, add, remove, remove, eval); }\n  \
    \  void solve(auto add_left, auto add_right, auto remove_left, auto remove_right,\
    \ auto eval) {\n        sort(queries_.begin(), queries_.end());\n        auto\
    \ l = 0, r = 0;\n        for (auto [left, right, index, order] : queries_) {\n\
    \            while (left < l) {\n                add_left(--l);\n            }\n\
    \            while (r < right) {\n                add_right(r++);\n          \
    \  }\n            while (l < left) {\n                remove_left(l++);\n    \
    \        }\n            while (right < r) {\n                remove_right(--r);\n\
    \            }\n            eval(index);\n        }\n    }\n\nprivate:\n    struct\
    \ query {\n        int left, right, index;\n        long long order;\n       \
    \ bool operator<(const query &other) const { return order < other.order; }\n \
    \   };\n    long long hilbert_order(int x, int y) const {\n        auto d = 0LL;\n\
    \        for (auto s = 1 << log_; s > 0; s >>= 1) {\n            bool rx = x &\
    \ s, ry = y & s;\n            d = (d << 2) | ((rx * 3) ^ ry);\n            if\
    \ (!ry) {\n                if (rx) {\n                    x = ~x;\n          \
    \          y = ~y;\n                }\n                std::swap(x, y);\n    \
    \        }\n        }\n        return d;\n    }\n    std::vector<query> queries_;\n\
    \    const int n_, log_;\n};\n\n#endif // HILBERT_MO_HPP"
  dependsOn: []
  isVerificationFile: false
  path: mo/hilbert_mo.hpp
  requiredBy:
  - mo/mo_tree.hpp
  timestamp: '2026-02-27 15:20:30+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/mo/hilbert_mo_range_kth_smallest.test.cpp
  - test/mo/hilbert_mo_static_range_count_distinct.test.cpp
  - test/mo/aoj0489.test.cpp
  - test/mo/hilbert_mo_static_range_frequency.test.cpp
  - test/mo/hilbert_mo_static_range_inversions_query.test.cpp
  - test/mo/aoj2270.test.cpp
documentation_of: mo/hilbert_mo.hpp
layout: document
redirect_from:
- /library/mo/hilbert_mo.hpp
- /library/mo/hilbert_mo.hpp.html
title: mo/hilbert_mo.hpp
---
