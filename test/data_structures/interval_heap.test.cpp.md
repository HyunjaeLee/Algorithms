---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structures/interval_heap.hpp
    title: data_structures/interval_heap.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/double_ended_priority_queue
    links:
    - https://judge.yosupo.jp/problem/double_ended_priority_queue
  bundledCode: "#line 1 \"test/data_structures/interval_heap.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/double_ended_priority_queue\"\n\n#line 1 \"\
    data_structures/interval_heap.hpp\"\n\n\n\n#include <cassert>\n#include <utility>\n\
    #include <vector>\n\n// source: https://natsugiri.hatenablog.com/entry/2016/10/10/035445\n\
    template <typename T> struct interval_heap {\n    interval_heap() = default;\n\
    \    void push(const T &x) {\n        auto k = int(data_.size());\n        data_.push_back(x);\n\
    \        up(k);\n    }\n    void pop_min() {\n        assert(!data_.empty());\n\
    \        if (int(data_.size()) < 3) {\n            data_.pop_back();\n       \
    \ } else {\n            std::swap(data_[1], data_.back());\n            data_.pop_back();\n\
    \            auto k = down(1);\n            up(k);\n        }\n    }\n    void\
    \ pop_max() {\n        assert(!data_.empty());\n        if (int(data_.size())\
    \ < 2) {\n            data_.pop_back();\n        } else {\n            std::swap(data_[0],\
    \ data_.back());\n            data_.pop_back();\n            auto k = down(0);\n\
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
    \n\n#line 4 \"test/data_structures/interval_heap.test.cpp\"\n#include <bits/stdc++.h>\n\
    \nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int N, Q;\n    std::cin\
    \ >> N >> Q;\n    interval_heap<int> pq;\n    for (auto i = 0; i < N; ++i) {\n\
    \        int x;\n        std::cin >> x;\n        pq.push(x);\n    }\n    for (auto\
    \ i = 0; i < Q; ++i) {\n        int t;\n        std::cin >> t;\n        if (t\
    \ == 0) {\n            int x;\n            std::cin >> x;\n            pq.push(x);\n\
    \        } else if (t == 1) {\n            std::cout << pq.min() << \"\\n\";\n\
    \            pq.pop_min();\n        } else {\n            std::cout << pq.max()\
    \ << \"\\n\";\n            pq.pop_max();\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/double_ended_priority_queue\"\
    \n\n#include \"data_structures/interval_heap.hpp\"\n#include <bits/stdc++.h>\n\
    \nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int N, Q;\n    std::cin\
    \ >> N >> Q;\n    interval_heap<int> pq;\n    for (auto i = 0; i < N; ++i) {\n\
    \        int x;\n        std::cin >> x;\n        pq.push(x);\n    }\n    for (auto\
    \ i = 0; i < Q; ++i) {\n        int t;\n        std::cin >> t;\n        if (t\
    \ == 0) {\n            int x;\n            std::cin >> x;\n            pq.push(x);\n\
    \        } else if (t == 1) {\n            std::cout << pq.min() << \"\\n\";\n\
    \            pq.pop_min();\n        } else {\n            std::cout << pq.max()\
    \ << \"\\n\";\n            pq.pop_max();\n        }\n    }\n}\n"
  dependsOn:
  - data_structures/interval_heap.hpp
  isVerificationFile: true
  path: test/data_structures/interval_heap.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 08:38:39+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/data_structures/interval_heap.test.cpp
layout: document
redirect_from:
- /verify/test/data_structures/interval_heap.test.cpp
- /verify/test/data_structures/interval_heap.test.cpp.html
title: test/data_structures/interval_heap.test.cpp
---
