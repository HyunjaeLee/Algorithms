---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/hilbert_mo_static_range_inversions_query.test.cpp
    title: test/hilbert_mo_static_range_inversions_query.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"mo/hilbert_mo.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <array>\n#include <cassert>\n#include <vector>\n\nstruct hilbert_mo {\n    hilbert_mo(int\
    \ n) : n_(n), log_(std::__lg(std::max(1, n_ - 1)) + 1) {}\n    void add(int l,\
    \ int r) {\n        assert(0 <= l && l <= r && r <= n_);\n        auto index =\
    \ static_cast<int>(queries_.size());\n        auto order = hilbert_order(l, r,\
    \ log_, 0);\n        queries_.push_back({l, r, index, order});\n    }\n    template\
    \ <typename Add, typename Remove, typename Eval>\n    void run(Add add, Remove\
    \ remove, Eval eval) {\n        run(add, add, remove, remove, eval);\n    }\n\
    \    template <typename AddLeft, typename AddRight, typename RemoveLeft,\n   \
    \           typename RemoveRight, typename Eval>\n    void run(AddLeft add_left,\
    \ AddRight add_right, RemoveLeft remove_left,\n             RemoveRight remove_right,\
    \ Eval eval) {\n        sort(queries_.begin(), queries_.end());\n        auto\
    \ l = 0, r = 0;\n        for (auto [left, right, index, order] : queries_) {\n\
    \            while (left < l) {\n                add_left(--l);\n            }\n\
    \            while (r < right) {\n                add_right(r++);\n          \
    \  }\n            while (l < left) {\n                remove_left(l++);\n    \
    \        }\n            while (right < r) {\n                remove_right(--r);\n\
    \            }\n            eval(index);\n        }\n    }\n\nprivate:\n    struct\
    \ query {\n        int left, right, index;\n        long long order;\n       \
    \ bool operator<(const query &other) const { return order < other.order; }\n \
    \   };\n    long long hilbert_order(int x, int y, int pow, int rotate) const {\n\
    \        if (pow == 0) {\n            return 0;\n        }\n        auto hpow\
    \ = 1 << (pow - 1);\n        auto seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y\
    \ < hpow) ? 1 : 2);\n        seg = (seg + rotate) & 3;\n        const std::array<int,\
    \ 4> rotate_delta{3, 0, 0, 1};\n        auto nx = x & (x ^ hpow), ny = y & (y\
    \ ^ hpow);\n        auto nrot = (rotate + rotate_delta[seg]) & 3;\n        auto\
    \ subsquare_size = static_cast<long long>(1) << (2 * pow - 2);\n        auto ans\
    \ = seg * subsquare_size;\n        auto add = hilbert_order(nx, ny, pow - 1, nrot);\n\
    \        ans += (seg == 1 || seg == 2) ? add : (subsquare_size - add - 1);\n \
    \       return ans;\n    }\n    std::vector<query> queries_;\n    const int n_,\
    \ log_;\n};\n\n\n"
  code: "#ifndef HILBERT_MO_HPP\n#define HILBERT_MO_HPP\n\n#include <algorithm>\n\
    #include <array>\n#include <cassert>\n#include <vector>\n\nstruct hilbert_mo {\n\
    \    hilbert_mo(int n) : n_(n), log_(std::__lg(std::max(1, n_ - 1)) + 1) {}\n\
    \    void add(int l, int r) {\n        assert(0 <= l && l <= r && r <= n_);\n\
    \        auto index = static_cast<int>(queries_.size());\n        auto order =\
    \ hilbert_order(l, r, log_, 0);\n        queries_.push_back({l, r, index, order});\n\
    \    }\n    template <typename Add, typename Remove, typename Eval>\n    void\
    \ run(Add add, Remove remove, Eval eval) {\n        run(add, add, remove, remove,\
    \ eval);\n    }\n    template <typename AddLeft, typename AddRight, typename RemoveLeft,\n\
    \              typename RemoveRight, typename Eval>\n    void run(AddLeft add_left,\
    \ AddRight add_right, RemoveLeft remove_left,\n             RemoveRight remove_right,\
    \ Eval eval) {\n        sort(queries_.begin(), queries_.end());\n        auto\
    \ l = 0, r = 0;\n        for (auto [left, right, index, order] : queries_) {\n\
    \            while (left < l) {\n                add_left(--l);\n            }\n\
    \            while (r < right) {\n                add_right(r++);\n          \
    \  }\n            while (l < left) {\n                remove_left(l++);\n    \
    \        }\n            while (right < r) {\n                remove_right(--r);\n\
    \            }\n            eval(index);\n        }\n    }\n\nprivate:\n    struct\
    \ query {\n        int left, right, index;\n        long long order;\n       \
    \ bool operator<(const query &other) const { return order < other.order; }\n \
    \   };\n    long long hilbert_order(int x, int y, int pow, int rotate) const {\n\
    \        if (pow == 0) {\n            return 0;\n        }\n        auto hpow\
    \ = 1 << (pow - 1);\n        auto seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y\
    \ < hpow) ? 1 : 2);\n        seg = (seg + rotate) & 3;\n        const std::array<int,\
    \ 4> rotate_delta{3, 0, 0, 1};\n        auto nx = x & (x ^ hpow), ny = y & (y\
    \ ^ hpow);\n        auto nrot = (rotate + rotate_delta[seg]) & 3;\n        auto\
    \ subsquare_size = static_cast<long long>(1) << (2 * pow - 2);\n        auto ans\
    \ = seg * subsquare_size;\n        auto add = hilbert_order(nx, ny, pow - 1, nrot);\n\
    \        ans += (seg == 1 || seg == 2) ? add : (subsquare_size - add - 1);\n \
    \       return ans;\n    }\n    std::vector<query> queries_;\n    const int n_,\
    \ log_;\n};\n\n#endif // HILBERT_MO_HPP"
  dependsOn: []
  isVerificationFile: false
  path: mo/hilbert_mo.hpp
  requiredBy: []
  timestamp: '2022-09-30 12:44:03+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/hilbert_mo_static_range_inversions_query.test.cpp
documentation_of: mo/hilbert_mo.hpp
layout: document
redirect_from:
- /library/mo/hilbert_mo.hpp
- /library/mo/hilbert_mo.hpp.html
title: mo/hilbert_mo.hpp
---
