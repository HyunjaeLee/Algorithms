---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/mo/rollback_mo_static_range_mode_query.test.cpp
    title: test/mo/rollback_mo_static_range_mode_query.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"mo/rollback_mo.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cmath>\n#include <utility>\n#include <vector>\n\nstruct\
    \ RollbackMo {\n    explicit RollbackMo(int n) : n_(n) {}\n    void add(int l,\
    \ int r) { // [l, r)\n        assert(0 <= l && l <= r && r <= n_);\n        queries_.emplace_back(l,\
    \ r);\n    }\n    void solve(auto add, auto rollback, auto eval) { solve(add,\
    \ add, rollback, eval); }\n    void solve(auto add_left, auto add_right, auto\
    \ rollback, auto eval) {\n        const auto q = int(queries_.size());\n     \
    \   if (q == 0) {\n            return;\n        }\n        const auto b_num =\
    \ int(std::sqrt(q));\n        const auto b_sz = (n_ + b_num - 1) / b_num;\n  \
    \      std::vector<std::vector<int>> buckets((n_ - 1) / b_sz + 1);\n        auto\
    \ rollback_n = [&](int n) {\n            for (auto i = 0; i < n; ++i) {\n    \
    \            rollback();\n            }\n        };\n        auto naive = [&](int\
    \ qid) {\n            auto [l, r] = queries_[qid];\n            for (auto i =\
    \ l; i < r; ++i) {\n                add_right(i);\n            }\n           \
    \ eval(qid);\n            rollback_n(r - l);\n        };\n        for (auto qid\
    \ = 0; qid < q; ++qid) {\n            auto [l, r] = queries_[qid];\n         \
    \   auto il = l / b_sz, ir = r / b_sz;\n            if (il == ir) {\n        \
    \        naive(qid);\n            } else {\n                buckets[il].push_back(qid);\n\
    \            }\n        }\n        for (auto &bucket : buckets) {\n          \
    \  if (bucket.empty()) {\n                continue;\n            }\n         \
    \   std::ranges::sort(bucket, {}, [&](int i) { return queries_[i].second; });\n\
    \            auto lmax = 0;\n            for (auto qid : bucket) {\n         \
    \       auto [l, r] = queries_[qid];\n                lmax = std::max(lmax, l);\n\
    \            }\n            auto l = lmax, r = lmax;\n            for (auto qid\
    \ : bucket) {\n                auto [ql, qr] = queries_[qid];\n              \
    \  while (r < qr) {\n                    add_right(r++);\n                }\n\
    \                while (ql < l) {\n                    add_left(--l);\n      \
    \          }\n                eval(qid);\n                rollback_n(lmax - l);\n\
    \                l = lmax;\n            }\n            rollback_n(r - l);\n  \
    \      }\n    }\n\nprivate:\n    int n_;\n    std::vector<std::pair<int, int>>\
    \ queries_;\n};\n\n\n"
  code: "#ifndef ROLLBACK_MO_HPP\n#define ROLLBACK_MO_HPP\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cmath>\n#include <utility>\n#include <vector>\n\n\
    struct RollbackMo {\n    explicit RollbackMo(int n) : n_(n) {}\n    void add(int\
    \ l, int r) { // [l, r)\n        assert(0 <= l && l <= r && r <= n_);\n      \
    \  queries_.emplace_back(l, r);\n    }\n    void solve(auto add, auto rollback,\
    \ auto eval) { solve(add, add, rollback, eval); }\n    void solve(auto add_left,\
    \ auto add_right, auto rollback, auto eval) {\n        const auto q = int(queries_.size());\n\
    \        if (q == 0) {\n            return;\n        }\n        const auto b_num\
    \ = int(std::sqrt(q));\n        const auto b_sz = (n_ + b_num - 1) / b_num;\n\
    \        std::vector<std::vector<int>> buckets((n_ - 1) / b_sz + 1);\n       \
    \ auto rollback_n = [&](int n) {\n            for (auto i = 0; i < n; ++i) {\n\
    \                rollback();\n            }\n        };\n        auto naive =\
    \ [&](int qid) {\n            auto [l, r] = queries_[qid];\n            for (auto\
    \ i = l; i < r; ++i) {\n                add_right(i);\n            }\n       \
    \     eval(qid);\n            rollback_n(r - l);\n        };\n        for (auto\
    \ qid = 0; qid < q; ++qid) {\n            auto [l, r] = queries_[qid];\n     \
    \       auto il = l / b_sz, ir = r / b_sz;\n            if (il == ir) {\n    \
    \            naive(qid);\n            } else {\n                buckets[il].push_back(qid);\n\
    \            }\n        }\n        for (auto &bucket : buckets) {\n          \
    \  if (bucket.empty()) {\n                continue;\n            }\n         \
    \   std::ranges::sort(bucket, {}, [&](int i) { return queries_[i].second; });\n\
    \            auto lmax = 0;\n            for (auto qid : bucket) {\n         \
    \       auto [l, r] = queries_[qid];\n                lmax = std::max(lmax, l);\n\
    \            }\n            auto l = lmax, r = lmax;\n            for (auto qid\
    \ : bucket) {\n                auto [ql, qr] = queries_[qid];\n              \
    \  while (r < qr) {\n                    add_right(r++);\n                }\n\
    \                while (ql < l) {\n                    add_left(--l);\n      \
    \          }\n                eval(qid);\n                rollback_n(lmax - l);\n\
    \                l = lmax;\n            }\n            rollback_n(r - l);\n  \
    \      }\n    }\n\nprivate:\n    int n_;\n    std::vector<std::pair<int, int>>\
    \ queries_;\n};\n\n#endif // ROLLBACK_MO_HPP"
  dependsOn: []
  isVerificationFile: false
  path: mo/rollback_mo.hpp
  requiredBy: []
  timestamp: '2026-02-28 01:07:59+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/mo/rollback_mo_static_range_mode_query.test.cpp
documentation_of: mo/rollback_mo.hpp
layout: document
title: Rollback Mo
---

+ [https://maspypy.github.io/library/ds/offline_query/rollback_mo.hpp](https://maspypy.github.io/library/ds/offline_query/rollback_mo.hpp)
