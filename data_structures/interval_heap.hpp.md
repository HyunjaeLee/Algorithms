---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/data_structures/interval_heap.test.cpp
    title: test/data_structures/interval_heap.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://natsugiri.hatenablog.com/entry/2016/10/10/035445
  bundledCode: "#line 1 \"data_structures/interval_heap.hpp\"\n\n\n\n#include <cassert>\n\
    #include <utility>\n#include <vector>\n\n// source: https://natsugiri.hatenablog.com/entry/2016/10/10/035445\n\
    template <typename T> struct interval_heap {\n    interval_heap() = default;\n\
    \    void push(const T &x) {\n        auto k = int(data_.size());\n        data_.push_back(x);\n\
    \        up(k);\n    }\n    void pop_min() {\n        assert(!data_.empty());\n\
    \        if (int(data_.size()) < 3) {\n            data_.pop_back();\n       \
    \ } else {\n            std::swap(data_[1], data_.back());\n            data_.pop_back();\n\
    \            int k = down(1);\n            up(k);\n        }\n    }\n    void\
    \ pop_max() {\n        assert(!data_.empty());\n        if (int(data_.size())\
    \ < 2) {\n            data_.pop_back();\n        } else {\n            std::swap(data_[0],\
    \ data_.back());\n            data_.pop_back();\n            int k = down(0);\n\
    \            up(k);\n        }\n    }\n    const T &min() const {\n        assert(!data_.empty());\n\
    \        return int(data_.size()) < 2 ? data_[0] : data_[1];\n    }\n    const\
    \ T &max() const {\n        assert(!data_.empty());\n        return data_[0];\n\
    \    }\n    int size() const { return int(data_.size()); }\n    bool empty() const\
    \ { return data_.empty(); }\n\nprivate:\n    int parent(int k) const { return\
    \ (((k >> 1) - 1) & ~1); }\n    int down(int k) {\n        auto n = int(data_.size());\n\
    \        if (k & 1) { // min heap\n            while (2 * k + 1 < n) {\n     \
    \           auto c = 2 * k + 3;\n                if (n <= c || data_[c - 2] <\
    \ data_[c]) {\n                    c -= 2;\n                }\n              \
    \  if (c < n && data_[c] < data_[k]) {\n                    std::swap(data_[k],\
    \ data_[c]);\n                    k = c;\n                } else {\n         \
    \           break;\n                }\n            }\n        } else { // max\
    \ heap\n            while (2 * k + 2 < n) {\n                auto c = 2 * k +\
    \ 4;\n                if (n <= c || data_[c] < data_[c - 2]) {\n             \
    \       c -= 2;\n                }\n                if (c < n && data_[k] < data_[c])\
    \ {\n                    std::swap(data_[k], data_[c]);\n                    k\
    \ = c;\n                } else {\n                    break;\n               \
    \ }\n            }\n        }\n        return k;\n    }\n    int up(int k, int\
    \ root = 1) {\n        if ((k | 1) < int(data_.size()) && data_[k & ~1] < data_[k\
    \ | 1]) {\n            std::swap(data_[k & ~1], data_[k | 1]);\n            k\
    \ ^= 1;\n        }\n        int p;\n        while (root < k && data_[p = parent(k)]\
    \ < data_[k]) { // max heap\n            std::swap(data_[p], data_[k]);\n    \
    \        k = p;\n        }\n        while (root < k && data_[k] < data_[p = parent(k)\
    \ | 1]) { // min heap\n            std::swap(data_[p], data_[k]);\n          \
    \  k = p;\n        }\n        return k;\n    }\n    std::vector<T> data_;\n};\n\
    \n\n"
  code: "#ifndef INTERVAL_HEAP_HPP\n#define INTERVAL_HEAP_HPP\n\n#include <cassert>\n\
    #include <utility>\n#include <vector>\n\n// source: https://natsugiri.hatenablog.com/entry/2016/10/10/035445\n\
    template <typename T> struct interval_heap {\n    interval_heap() = default;\n\
    \    void push(const T &x) {\n        auto k = int(data_.size());\n        data_.push_back(x);\n\
    \        up(k);\n    }\n    void pop_min() {\n        assert(!data_.empty());\n\
    \        if (int(data_.size()) < 3) {\n            data_.pop_back();\n       \
    \ } else {\n            std::swap(data_[1], data_.back());\n            data_.pop_back();\n\
    \            int k = down(1);\n            up(k);\n        }\n    }\n    void\
    \ pop_max() {\n        assert(!data_.empty());\n        if (int(data_.size())\
    \ < 2) {\n            data_.pop_back();\n        } else {\n            std::swap(data_[0],\
    \ data_.back());\n            data_.pop_back();\n            int k = down(0);\n\
    \            up(k);\n        }\n    }\n    const T &min() const {\n        assert(!data_.empty());\n\
    \        return int(data_.size()) < 2 ? data_[0] : data_[1];\n    }\n    const\
    \ T &max() const {\n        assert(!data_.empty());\n        return data_[0];\n\
    \    }\n    int size() const { return int(data_.size()); }\n    bool empty() const\
    \ { return data_.empty(); }\n\nprivate:\n    int parent(int k) const { return\
    \ (((k >> 1) - 1) & ~1); }\n    int down(int k) {\n        auto n = int(data_.size());\n\
    \        if (k & 1) { // min heap\n            while (2 * k + 1 < n) {\n     \
    \           auto c = 2 * k + 3;\n                if (n <= c || data_[c - 2] <\
    \ data_[c]) {\n                    c -= 2;\n                }\n              \
    \  if (c < n && data_[c] < data_[k]) {\n                    std::swap(data_[k],\
    \ data_[c]);\n                    k = c;\n                } else {\n         \
    \           break;\n                }\n            }\n        } else { // max\
    \ heap\n            while (2 * k + 2 < n) {\n                auto c = 2 * k +\
    \ 4;\n                if (n <= c || data_[c] < data_[c - 2]) {\n             \
    \       c -= 2;\n                }\n                if (c < n && data_[k] < data_[c])\
    \ {\n                    std::swap(data_[k], data_[c]);\n                    k\
    \ = c;\n                } else {\n                    break;\n               \
    \ }\n            }\n        }\n        return k;\n    }\n    int up(int k, int\
    \ root = 1) {\n        if ((k | 1) < int(data_.size()) && data_[k & ~1] < data_[k\
    \ | 1]) {\n            std::swap(data_[k & ~1], data_[k | 1]);\n            k\
    \ ^= 1;\n        }\n        int p;\n        while (root < k && data_[p = parent(k)]\
    \ < data_[k]) { // max heap\n            std::swap(data_[p], data_[k]);\n    \
    \        k = p;\n        }\n        while (root < k && data_[k] < data_[p = parent(k)\
    \ | 1]) { // min heap\n            std::swap(data_[p], data_[k]);\n          \
    \  k = p;\n        }\n        return k;\n    }\n    std::vector<T> data_;\n};\n\
    \n#endif // INTERVAL_HEAP_HPP"
  dependsOn: []
  isVerificationFile: false
  path: data_structures/interval_heap.hpp
  requiredBy: []
  timestamp: '2026-07-15 08:33:55+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/data_structures/interval_heap.test.cpp
documentation_of: data_structures/interval_heap.hpp
layout: document
redirect_from:
- /library/data_structures/interval_heap.hpp
- /library/data_structures/interval_heap.hpp.html
title: data_structures/interval_heap.hpp
---
