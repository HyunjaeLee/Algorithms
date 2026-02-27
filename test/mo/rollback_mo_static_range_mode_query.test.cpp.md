---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: mo/rollback_mo.hpp
    title: Rollback Mo
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/static_range_mode_query
    links:
    - https://judge.yosupo.jp/problem/static_range_mode_query
  bundledCode: "#line 1 \"test/mo/rollback_mo_static_range_mode_query.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/static_range_mode_query\"\n\n\
    #line 1 \"mo/rollback_mo.hpp\"\n\n\n\n#include <algorithm>\n#include <cassert>\n\
    #include <cmath>\n#include <utility>\n#include <vector>\n\nstruct RollbackMo {\n\
    \    explicit RollbackMo(int n) : n_(n) {}\n    void add(int l, int r) { // [l,\
    \ r)\n        assert(0 <= l && l <= r && r <= n_);\n        queries_.emplace_back(l,\
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
    \ queries_;\n};\n\n\n#line 4 \"test/mo/rollback_mo_static_range_mode_query.test.cpp\"\
    \n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N, Q;\n    std::cin >> N >> Q;\n    std::vector<int> A(N);\n    std::copy_n(std::istream_iterator<int>(std::cin),\
    \ N, A.begin());\n    auto C = A;\n    std::ranges::sort(C);\n    C.erase(std::unique(C.begin(),\
    \ C.end()), C.end());\n    for (auto &a : A) {\n        a = int(std::ranges::lower_bound(C,\
    \ a) - C.begin());\n    }\n    RollbackMo mo(N);\n    for (auto i = 0; i < Q;\
    \ ++i) {\n        int l, r;\n        std::cin >> l >> r;\n        mo.add(l, r);\n\
    \    }\n    auto best = 0, val = 0;\n    std::vector<int> freq(C.size());\n  \
    \  std::vector<std::tuple<int, int, int>> history;\n    std::vector<std::pair<int,\
    \ int>> ans(Q);\n    auto add = [&](int i) {\n        auto a = A[i];\n       \
    \ history.emplace_back(best, val, a);\n        ++freq[a];\n        if (val < freq[a])\
    \ {\n            best = a;\n            val = freq[a];\n        }\n    };\n  \
    \  auto rollback = [&] {\n        auto [b, v, a] = history.back();\n        history.pop_back();\n\
    \        best = b;\n        val = v;\n        --freq[a];\n    };\n    auto eval\
    \ = [&](int i) { ans[i] = {C[best], val}; };\n    mo.solve(add, rollback, eval);\n\
    \    for (auto [mode, cnt] : ans) {\n        std::cout << mode << \" \" << cnt\
    \ << \"\\n\";\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_mode_query\"\
    \n\n#include \"mo/rollback_mo.hpp\"\n#include <bits/stdc++.h>\n\nint main() {\n\
    \    std::cin.tie(0)->sync_with_stdio(0);\n    int N, Q;\n    std::cin >> N >>\
    \ Q;\n    std::vector<int> A(N);\n    std::copy_n(std::istream_iterator<int>(std::cin),\
    \ N, A.begin());\n    auto C = A;\n    std::ranges::sort(C);\n    C.erase(std::unique(C.begin(),\
    \ C.end()), C.end());\n    for (auto &a : A) {\n        a = int(std::ranges::lower_bound(C,\
    \ a) - C.begin());\n    }\n    RollbackMo mo(N);\n    for (auto i = 0; i < Q;\
    \ ++i) {\n        int l, r;\n        std::cin >> l >> r;\n        mo.add(l, r);\n\
    \    }\n    auto best = 0, val = 0;\n    std::vector<int> freq(C.size());\n  \
    \  std::vector<std::tuple<int, int, int>> history;\n    std::vector<std::pair<int,\
    \ int>> ans(Q);\n    auto add = [&](int i) {\n        auto a = A[i];\n       \
    \ history.emplace_back(best, val, a);\n        ++freq[a];\n        if (val < freq[a])\
    \ {\n            best = a;\n            val = freq[a];\n        }\n    };\n  \
    \  auto rollback = [&] {\n        auto [b, v, a] = history.back();\n        history.pop_back();\n\
    \        best = b;\n        val = v;\n        --freq[a];\n    };\n    auto eval\
    \ = [&](int i) { ans[i] = {C[best], val}; };\n    mo.solve(add, rollback, eval);\n\
    \    for (auto [mode, cnt] : ans) {\n        std::cout << mode << \" \" << cnt\
    \ << \"\\n\";\n    }\n}\n"
  dependsOn:
  - mo/rollback_mo.hpp
  isVerificationFile: true
  path: test/mo/rollback_mo_static_range_mode_query.test.cpp
  requiredBy: []
  timestamp: '2026-02-28 01:07:59+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/mo/rollback_mo_static_range_mode_query.test.cpp
layout: document
redirect_from:
- /verify/test/mo/rollback_mo_static_range_mode_query.test.cpp
- /verify/test/mo/rollback_mo_static_range_mode_query.test.cpp.html
title: test/mo/rollback_mo_static_range_mode_query.test.cpp
---
