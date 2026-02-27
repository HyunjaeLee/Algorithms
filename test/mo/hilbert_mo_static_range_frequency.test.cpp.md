---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: mo/hilbert_mo.hpp
    title: mo/hilbert_mo.hpp
  - icon: ':heavy_check_mark:'
    path: mo/sqrt_freq_table.hpp
    title: mo/sqrt_freq_table.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/static_range_frequency
    links:
    - https://judge.yosupo.jp/problem/static_range_frequency
  bundledCode: "#line 1 \"test/mo/hilbert_mo_static_range_frequency.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/static_range_frequency\"\n\n#line\
    \ 1 \"mo/hilbert_mo.hpp\"\n\n\n\n#include <algorithm>\n#include <array>\n#include\
    \ <cassert>\n#include <vector>\n\nstruct HilbertMo {\n    HilbertMo(int n) : n_(n),\
    \ log_(std::bit_width(unsigned(n))) {}\n    void add(int l, int r) {\n       \
    \ assert(0 <= l && l <= r && r <= n_);\n        auto index = int(queries_.size());\n\
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
    \ 1 \"mo/sqrt_freq_table.hpp\"\n\n\n\n#line 6 \"mo/sqrt_freq_table.hpp\"\n#include\
    \ <cmath>\n#line 8 \"mo/sqrt_freq_table.hpp\"\n\nstruct SqrtFreqTable {\n    explicit\
    \ SqrtFreqTable(int max_val)\n        : m_(std::max(1, max_val)), b_sz_(int(std::sqrt(m_))),\
    \ freq_(m_ + 1),\n          bucket_(m_ / b_sz_ + 1) {}\n    void insert(int x)\
    \ { // O(1)\n        assert(0 <= x && x <= m_);\n        ++freq_[x];\n       \
    \ ++bucket_[x / b_sz_];\n        ++total_;\n        distinct_ += int(freq_[x]\
    \ == 1);\n    }\n    void erase(int x) { // O(1)\n        assert(0 <= x && x <=\
    \ m_);\n        assert(0 < freq_[x]);\n        --freq_[x];\n        --bucket_[x\
    \ / b_sz_];\n        --total_;\n        distinct_ -= int(freq_[x] == 0);\n   \
    \ }\n    int count(int x) const { // O(1)\n        assert(0 <= x && x <= m_);\n\
    \        return freq_[x];\n    }\n    int size() const { return total_; }\n  \
    \  int count_distinct() const { return distinct_; }\n    int kth(int k) const\
    \ { // O(sqrt(M)), 0-indexed\n        auto cnt = 0;\n        for (auto i = 0;\
    \ i < m_ / b_sz_ + 1; ++i) {\n            if (cnt + bucket_[i] <= k) {\n     \
    \           cnt += bucket_[i];\n                continue;\n            }\n   \
    \         auto x = i * b_sz_;\n            while ((cnt += freq_[x]) <= k) {\n\
    \                ++x;\n            }\n            return x;\n        }\n     \
    \   return -1;\n    };\n    int rank(int x) const { // O(sqrt(M)), count y s.t.\
    \ y < x\n        if (x < 0) {\n            return 0;\n        }\n        if (m_\
    \ < x) {\n            return total_;\n        }\n        auto cnt = 0;\n     \
    \   for (auto i = 0; i < x / b_sz_; ++i) {\n            cnt += bucket_[i];\n \
    \       }\n        for (auto i = x / b_sz_ * b_sz_; i < x; ++i) {\n          \
    \  cnt += freq_[i];\n        }\n        return cnt;\n    }\n\nprivate:\n    const\
    \ int m_, b_sz_;\n    std::vector<int> freq_, bucket_;\n    int total_ = 0, distinct_\
    \ = 0;\n};\n\n\n#line 5 \"test/mo/hilbert_mo_static_range_frequency.test.cpp\"\
    \n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N, Q;\n    std::cin >> N >> Q;\n    std::vector<int> A(N);\n    for (auto\
    \ &a : A) {\n        std::cin >> a;\n    }\n    auto C = A;\n    std::ranges::sort(C);\n\
    \    C.erase(unique(C.begin(), C.end()), C.end());\n    for (auto &a : A) {\n\
    \        auto it = std::ranges::lower_bound(C, a);\n        a = int(it - C.begin());\n\
    \    }\n    std::vector<int> X(Q);\n    HilbertMo mo(N);\n    for (auto &x : X)\
    \ {\n        int l, r;\n        std::cin >> l >> r >> x;\n        auto it = std::ranges::lower_bound(C,\
    \ x);\n        x = (it != C.end() && *it == x) ? int(it - C.begin()) : -1;\n \
    \       mo.add(l, r);\n    }\n    SqrtFreqTable table(int(C.size()) - 1);\n  \
    \  std::vector<int> ans(Q);\n    auto add = [&](int i) { table.insert(A[i]); };\n\
    \    auto remove = [&](int i) { table.erase(A[i]); };\n    auto eval = [&](int\
    \ i) { ans[i] = (X[i] == -1) ? 0 : table.count(X[i]); };\n    mo.solve(add, remove,\
    \ eval);\n    std::ranges::copy(ans, std::ostream_iterator<int>(std::cout, \"\\\
    n\"));\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_frequency\"\
    \n\n#include \"mo/hilbert_mo.hpp\"\n#include \"mo/sqrt_freq_table.hpp\"\n#include\
    \ <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N, Q;\n    std::cin >> N >> Q;\n    std::vector<int> A(N);\n    for (auto\
    \ &a : A) {\n        std::cin >> a;\n    }\n    auto C = A;\n    std::ranges::sort(C);\n\
    \    C.erase(unique(C.begin(), C.end()), C.end());\n    for (auto &a : A) {\n\
    \        auto it = std::ranges::lower_bound(C, a);\n        a = int(it - C.begin());\n\
    \    }\n    std::vector<int> X(Q);\n    HilbertMo mo(N);\n    for (auto &x : X)\
    \ {\n        int l, r;\n        std::cin >> l >> r >> x;\n        auto it = std::ranges::lower_bound(C,\
    \ x);\n        x = (it != C.end() && *it == x) ? int(it - C.begin()) : -1;\n \
    \       mo.add(l, r);\n    }\n    SqrtFreqTable table(int(C.size()) - 1);\n  \
    \  std::vector<int> ans(Q);\n    auto add = [&](int i) { table.insert(A[i]); };\n\
    \    auto remove = [&](int i) { table.erase(A[i]); };\n    auto eval = [&](int\
    \ i) { ans[i] = (X[i] == -1) ? 0 : table.count(X[i]); };\n    mo.solve(add, remove,\
    \ eval);\n    std::ranges::copy(ans, std::ostream_iterator<int>(std::cout, \"\\\
    n\"));\n}\n"
  dependsOn:
  - mo/hilbert_mo.hpp
  - mo/sqrt_freq_table.hpp
  isVerificationFile: true
  path: test/mo/hilbert_mo_static_range_frequency.test.cpp
  requiredBy: []
  timestamp: '2026-02-28 01:07:59+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/mo/hilbert_mo_static_range_frequency.test.cpp
layout: document
redirect_from:
- /verify/test/mo/hilbert_mo_static_range_frequency.test.cpp
- /verify/test/mo/hilbert_mo_static_range_frequency.test.cpp.html
title: test/mo/hilbert_mo_static_range_frequency.test.cpp
---
