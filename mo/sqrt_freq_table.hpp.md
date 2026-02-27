---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
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
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"mo/sqrt_freq_table.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cmath>\n#include <vector>\n\nstruct SqrtFreqTable {\n \
    \   explicit SqrtFreqTable(int max_val)\n        : m_(std::max(1, max_val)), b_sz_(int(std::sqrt(m_))),\
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
    \ = 0;\n};\n\n\n"
  code: "#ifndef SQRT_FREQ_TABLE_HPP\n#define SQRT_FREQ_TABLE_HPP\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cmath>\n#include <vector>\n\nstruct SqrtFreqTable\
    \ {\n    explicit SqrtFreqTable(int max_val)\n        : m_(std::max(1, max_val)),\
    \ b_sz_(int(std::sqrt(m_))), freq_(m_ + 1),\n          bucket_(m_ / b_sz_ + 1)\
    \ {}\n    void insert(int x) { // O(1)\n        assert(0 <= x && x <= m_);\n \
    \       ++freq_[x];\n        ++bucket_[x / b_sz_];\n        ++total_;\n      \
    \  distinct_ += int(freq_[x] == 1);\n    }\n    void erase(int x) { // O(1)\n\
    \        assert(0 <= x && x <= m_);\n        assert(0 < freq_[x]);\n        --freq_[x];\n\
    \        --bucket_[x / b_sz_];\n        --total_;\n        distinct_ -= int(freq_[x]\
    \ == 0);\n    }\n    int count(int x) const { // O(1)\n        assert(0 <= x &&\
    \ x <= m_);\n        return freq_[x];\n    }\n    int size() const { return total_;\
    \ }\n    int count_distinct() const { return distinct_; }\n    int kth(int k)\
    \ const { // O(sqrt(M)), 0-indexed\n        auto cnt = 0;\n        for (auto i\
    \ = 0; i < m_ / b_sz_ + 1; ++i) {\n            if (cnt + bucket_[i] <= k) {\n\
    \                cnt += bucket_[i];\n                continue;\n            }\n\
    \            auto x = i * b_sz_;\n            while ((cnt += freq_[x]) <= k) {\n\
    \                ++x;\n            }\n            return x;\n        }\n     \
    \   return -1;\n    };\n    int rank(int x) const { // O(sqrt(M)), count y s.t.\
    \ y < x\n        if (x < 0) {\n            return 0;\n        }\n        if (m_\
    \ < x) {\n            return total_;\n        }\n        auto cnt = 0;\n     \
    \   for (auto i = 0; i < x / b_sz_; ++i) {\n            cnt += bucket_[i];\n \
    \       }\n        for (auto i = x / b_sz_ * b_sz_; i < x; ++i) {\n          \
    \  cnt += freq_[i];\n        }\n        return cnt;\n    }\n\nprivate:\n    const\
    \ int m_, b_sz_;\n    std::vector<int> freq_, bucket_;\n    int total_ = 0, distinct_\
    \ = 0;\n};\n\n#endif // SQRT_FREQ_TABLE_HPP"
  dependsOn: []
  isVerificationFile: false
  path: mo/sqrt_freq_table.hpp
  requiredBy: []
  timestamp: '2026-02-28 01:07:59+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/mo/hilbert_mo_range_kth_smallest.test.cpp
  - test/mo/hilbert_mo_static_range_count_distinct.test.cpp
  - test/mo/aoj0489.test.cpp
  - test/mo/hilbert_mo_static_range_frequency.test.cpp
  - test/mo/aoj2270.test.cpp
documentation_of: mo/sqrt_freq_table.hpp
layout: document
redirect_from:
- /library/mo/sqrt_freq_table.hpp
- /library/mo/sqrt_freq_table.hpp.html
title: mo/sqrt_freq_table.hpp
---
