---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: wavelet/wavelet_matrix.hpp
    title: wavelet/wavelet_matrix.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_kth_smallest
    links:
    - https://judge.yosupo.jp/problem/range_kth_smallest
  bundledCode: "#line 1 \"test/wavelet_matrix_range_kth_smallest.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n#line 1 \"\
    wavelet/wavelet_matrix.hpp\"\n\n\n\n#include <algorithm>\n#include <cassert>\n\
    #include <vector>\n\nstruct bit_vector {\n    explicit bit_vector(int n) : data_((n\
    \ + 63) >> 6), sum_(data_.size() + 1) {}\n    void set(int pos) { data_[pos >>\
    \ 6] |= 1ULL << (pos & 63); }\n    int rank(int l, int r, bool value) const {\n\
    \        auto count = rank(r) - rank(l);\n        return value ? count : r - l\
    \ - count;\n    }\n    bool operator[](int pos) const {\n        return static_cast<bool>(data_[pos\
    \ >> 6] >> (pos & 63) & 1);\n    }\n    void build() {\n        for (auto i =\
    \ 0; i < static_cast<int>(data_.size()); ++i) {\n            sum_[i + 1] = sum_[i]\
    \ + __builtin_popcountll(data_[i]);\n        }\n    }\n\nprivate:\n    // Returns\
    \ the number of bits that are set to true in [0, pos)\n    int rank(int pos) const\
    \ {\n        return sum_[pos >> 6] +\n               __builtin_popcountll(data_[pos\
    \ >> 6] &\n                                    ((1ULL << (pos & 63)) - 1ULL));\n\
    \    }\n    std::vector<unsigned long long> data_;\n    std::vector<int> sum_;\n\
    };\n\ntemplate <typename T> struct wavelet_matrix {\n    // data must not be empty\n\
    \    wavelet_matrix(std::vector<T> data)\n        : n_(static_cast<int>(data.size())),\n\
    \          log_(std::max(\n              1, 64 - __builtin_clzll(static_cast<unsigned\
    \ long long>(\n                          *std::max_element(data.begin(), data.end()))))),\n\
    \          data_(log_, bit_vector(n_)), mid_(log_) {\n        assert(std::all_of(data.begin(),\
    \ data.end(),\n                           [](auto x) { return x >= 0; }));\n \
    \       for (auto i = log_ - 1; i >= 0; --i) {\n            for (auto j = 0; j\
    \ < n_; ++j) {\n                if (data[j] >> i & 1) {\n                    data_[i].set(j);\n\
    \                }\n            }\n            data_[i].build();\n           \
    \ auto it =\n                std::stable_partition(data.begin(), data.end(),\n\
    \                                      [&](auto x) { return !(x >> i & 1); });\n\
    \            mid_[i] = static_cast<int>(it - data.begin());\n        }\n    }\n\
    \    T access(int pos) const {\n        assert(0 <= pos && pos < n_);\n      \
    \  T result = 0;\n        for (auto i = log_ - 1; i >= 0; --i) {\n           \
    \ if (data_[i][pos]) {\n                result |= static_cast<T>(1) << i;\n  \
    \              pos = mid_[i] + data_[i].rank(0, pos, true);\n            } else\
    \ {\n                pos = data_[i].rank(0, pos, false);\n            }\n    \
    \    }\n        return result;\n    }\n    int rank(int l, int r, T x) const {\n\
    \        assert(0 <= l && l <= r && r <= n_);\n        for (auto i = log_ - 1;\
    \ i >= 0; --i) {\n            if (x >> i & 1) {\n                l = mid_[i] +\
    \ data_[i].rank(0, l, true);\n                r = mid_[i] + data_[i].rank(0, r,\
    \ true);\n            } else {\n                l = data_[i].rank(0, l, false);\n\
    \                r = data_[i].rank(0, r, false);\n            }\n        }\n \
    \       return r - l;\n    }\n    T quantile(int l, int r, int k) const {\n  \
    \      assert(0 <= l && l <= r && r <= n_ && 0 <= k && k < r - l);\n        T\
    \ result = 0;\n        for (auto i = log_ - 1; i >= 0; --i) {\n            if\
    \ (auto count = data_[i].rank(l, r, false); count <= k) {\n                result\
    \ |= static_cast<T>(1) << i;\n                k -= count;\n                l =\
    \ mid_[i] + data_[i].rank(0, l, true);\n                r = mid_[i] + data_[i].rank(0,\
    \ r, true);\n            } else {\n                l = data_[i].rank(0, l, false);\n\
    \                r = data_[i].rank(0, r, false);\n            }\n        }\n \
    \       return result;\n    }\n\nprivate:\n    const int n_, log_;\n    std::vector<bit_vector>\
    \ data_;\n    std::vector<int> mid_;\n};\n\n\n#line 4 \"test/wavelet_matrix_range_kth_smallest.test.cpp\"\
    \n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N, Q;\n    std::cin >> N >> Q;\n    std::vector<int> v(N);\n    for (auto\
    \ &x : v) {\n        std::cin >> x;\n    }\n    wavelet_matrix<int> wm(std::move(v));\n\
    \    while (Q--) {\n        int l, r, k;\n        std::cin >> l >> r >> k;\n \
    \       std::cout << wm.quantile(l, r, k) << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n\
    #include \"../wavelet/wavelet_matrix.hpp\"\n#include <bits/stdc++.h>\n\nint main()\
    \ {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int N, Q;\n    std::cin >>\
    \ N >> Q;\n    std::vector<int> v(N);\n    for (auto &x : v) {\n        std::cin\
    \ >> x;\n    }\n    wavelet_matrix<int> wm(std::move(v));\n    while (Q--) {\n\
    \        int l, r, k;\n        std::cin >> l >> r >> k;\n        std::cout <<\
    \ wm.quantile(l, r, k) << '\\n';\n    }\n}\n"
  dependsOn:
  - wavelet/wavelet_matrix.hpp
  isVerificationFile: true
  path: test/wavelet_matrix_range_kth_smallest.test.cpp
  requiredBy: []
  timestamp: '2022-09-08 09:47:38+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/wavelet_matrix_range_kth_smallest.test.cpp
layout: document
redirect_from:
- /verify/test/wavelet_matrix_range_kth_smallest.test.cpp
- /verify/test/wavelet_matrix_range_kth_smallest.test.cpp.html
title: test/wavelet_matrix_range_kth_smallest.test.cpp
---
