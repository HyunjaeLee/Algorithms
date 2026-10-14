---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: data_structures/static_range_frequency.hpp
    title: data_structures/static_range_frequency.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/data_structures/static_range_frequency.test.cpp
    title: test/data_structures/static_range_frequency.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structures/csr.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <ranges>\n#include <utility>\n#include <vector>\n\ntemplate <typename T> struct\
    \ csr {\n    explicit csr(int n) : n_(n) {}\n    void add(int i, T x) {\n    \
    \    assert(!built_);\n        assert(0 <= i && i < n_);\n        buf_.emplace_back(i,\
    \ x);\n    }\n    void build() {\n        assert(!built_);\n        ptr_.assign(n_\
    \ + 2, 0);\n        csr_.resize(buf_.size());\n        for (auto [i, x] : buf_)\
    \ {\n            ++ptr_[i + 2];\n        }\n        for (int i = 0; i < n_; ++i)\
    \ {\n            ptr_[i + 1] += ptr_[i];\n        }\n        for (auto [i, x]\
    \ : buf_) {\n            csr_[ptr_[i + 1]++] = x;\n        }\n        built_ =\
    \ true;\n    }\n    auto operator[](int i) {\n        assert(built_);\n      \
    \  assert(0 <= i && i < n_);\n        return std::ranges::subrange(csr_.begin()\
    \ + ptr_[i], csr_.begin() + ptr_[i + 1]);\n    }\n    auto operator[](int i) const\
    \ {\n        assert(built_);\n        assert(0 <= i && i < n_);\n        return\
    \ std::ranges::subrange(csr_.begin() + ptr_[i], csr_.begin() + ptr_[i + 1]);\n\
    \    }\n    int size() const { return n_; }\n\nprivate:\n    int n_;\n    bool\
    \ built_ = false;\n    std::vector<std::pair<int, T>> buf_;\n    std::vector<T>\
    \ csr_;\n    std::vector<int> ptr_;\n};\n\n\n"
  code: "#ifndef CSR_HPP\n#define CSR_HPP\n\n#include <cassert>\n#include <ranges>\n\
    #include <utility>\n#include <vector>\n\ntemplate <typename T> struct csr {\n\
    \    explicit csr(int n) : n_(n) {}\n    void add(int i, T x) {\n        assert(!built_);\n\
    \        assert(0 <= i && i < n_);\n        buf_.emplace_back(i, x);\n    }\n\
    \    void build() {\n        assert(!built_);\n        ptr_.assign(n_ + 2, 0);\n\
    \        csr_.resize(buf_.size());\n        for (auto [i, x] : buf_) {\n     \
    \       ++ptr_[i + 2];\n        }\n        for (int i = 0; i < n_; ++i) {\n  \
    \          ptr_[i + 1] += ptr_[i];\n        }\n        for (auto [i, x] : buf_)\
    \ {\n            csr_[ptr_[i + 1]++] = x;\n        }\n        built_ = true;\n\
    \    }\n    auto operator[](int i) {\n        assert(built_);\n        assert(0\
    \ <= i && i < n_);\n        return std::ranges::subrange(csr_.begin() + ptr_[i],\
    \ csr_.begin() + ptr_[i + 1]);\n    }\n    auto operator[](int i) const {\n  \
    \      assert(built_);\n        assert(0 <= i && i < n_);\n        return std::ranges::subrange(csr_.begin()\
    \ + ptr_[i], csr_.begin() + ptr_[i + 1]);\n    }\n    int size() const { return\
    \ n_; }\n\nprivate:\n    int n_;\n    bool built_ = false;\n    std::vector<std::pair<int,\
    \ T>> buf_;\n    std::vector<T> csr_;\n    std::vector<int> ptr_;\n};\n\n#endif\
    \ // CSR_HPP"
  dependsOn: []
  isVerificationFile: false
  path: data_structures/csr.hpp
  requiredBy:
  - data_structures/static_range_frequency.hpp
  timestamp: '2026-10-14 13:04:34+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/data_structures/static_range_frequency.test.cpp
documentation_of: data_structures/csr.hpp
layout: document
redirect_from:
- /library/data_structures/csr.hpp
- /library/data_structures/csr.hpp.html
title: data_structures/csr.hpp
---
