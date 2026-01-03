---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/wavelet/wavelet_matrix_range_kth_smallest.test.cpp
    title: test/wavelet/wavelet_matrix_range_kth_smallest.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/wavelet/wavelet_matrix_static_range_frequency.test.cpp
    title: test/wavelet/wavelet_matrix_static_range_frequency.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"wavelet/wavelet_matrix.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <limits>\n#include <type_traits>\n#include <vector>\n\
    \nstruct bit_vector {\n    explicit bit_vector(int n) : data_((n + 63) >> 6),\
    \ sum_(data_.size() + 1) {}\n    void set(int pos) { data_[pos >> 6] |= 1ULL <<\
    \ (pos & 63); }\n    int rank(int l, int r, bool value) const {\n        auto\
    \ count = rank(r) - rank(l);\n        return value ? count : r - l - count;\n\
    \    }\n    bool operator[](int pos) const {\n        return static_cast<bool>(data_[pos\
    \ >> 6] >> (pos & 63) & 1);\n    }\n    void build() {\n        for (auto i =\
    \ 0; i < static_cast<int>(data_.size()); ++i) {\n            sum_[i + 1] = sum_[i]\
    \ + __builtin_popcountll(data_[i]);\n        }\n    }\n\nprivate:\n    // Returns\
    \ the number of bits that are set to true in [0, pos)\n    int rank(int pos) const\
    \ {\n        return sum_[pos >> 6] +\n               __builtin_popcountll(data_[pos\
    \ >> 6] &\n                                    ((1ULL << (pos & 63)) - 1ULL));\n\
    \    }\n    std::vector<unsigned long long> data_;\n    std::vector<int> sum_;\n\
    };\n\ntemplate <typename T> struct wavelet_matrix {\n    // data must not be empty\n\
    \    wavelet_matrix(std::vector<T> data)\n        : n_(static_cast<int>(data.size())),\n\
    \          log_(std::numeric_limits<T>::digits), data_(log_, bit_vector(n_)),\n\
    \          mid_(log_) {\n        assert(std::all_of(data.begin(), data.end(),\n\
    \                           [](auto x) { return x >= 0; }));\n        for (auto\
    \ i = log_ - 1; i >= 0; --i) {\n            for (auto j = 0; j < n_; ++j) {\n\
    \                if (data[j] >> i & 1) {\n                    data_[i].set(j);\n\
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
    \       return result;\n    }\n    int range(int l, int r, T x, T y) const {\n\
    \        return range(l, r, y) - range(l, r, x);\n    }\n\nprivate:\n    int range(int\
    \ l, int r, T x) const {\n        auto count = 0;\n        for (auto i = log_\
    \ - 1; i >= 0; --i) {\n            if (x >> i & 1) {\n                count +=\
    \ data_[i].rank(l, r, false);\n                l = mid_[i] + data_[i].rank(0,\
    \ l, true);\n                r = mid_[i] + data_[i].rank(0, r, true);\n      \
    \      } else {\n                l = data_[i].rank(0, l, false);\n           \
    \     r = data_[i].rank(0, r, false);\n            }\n        }\n        return\
    \ count;\n    }\n    const int n_, log_;\n    std::vector<bit_vector> data_;\n\
    \    std::vector<int> mid_;\n};\n\n\n"
  code: "#ifndef WAVELET_MATRIX_HPP\n#define WAVELET_MATRIX_HPP\n\n#include <algorithm>\n\
    #include <cassert>\n#include <limits>\n#include <type_traits>\n#include <vector>\n\
    \nstruct bit_vector {\n    explicit bit_vector(int n) : data_((n + 63) >> 6),\
    \ sum_(data_.size() + 1) {}\n    void set(int pos) { data_[pos >> 6] |= 1ULL <<\
    \ (pos & 63); }\n    int rank(int l, int r, bool value) const {\n        auto\
    \ count = rank(r) - rank(l);\n        return value ? count : r - l - count;\n\
    \    }\n    bool operator[](int pos) const {\n        return static_cast<bool>(data_[pos\
    \ >> 6] >> (pos & 63) & 1);\n    }\n    void build() {\n        for (auto i =\
    \ 0; i < static_cast<int>(data_.size()); ++i) {\n            sum_[i + 1] = sum_[i]\
    \ + __builtin_popcountll(data_[i]);\n        }\n    }\n\nprivate:\n    // Returns\
    \ the number of bits that are set to true in [0, pos)\n    int rank(int pos) const\
    \ {\n        return sum_[pos >> 6] +\n               __builtin_popcountll(data_[pos\
    \ >> 6] &\n                                    ((1ULL << (pos & 63)) - 1ULL));\n\
    \    }\n    std::vector<unsigned long long> data_;\n    std::vector<int> sum_;\n\
    };\n\ntemplate <typename T> struct wavelet_matrix {\n    // data must not be empty\n\
    \    wavelet_matrix(std::vector<T> data)\n        : n_(static_cast<int>(data.size())),\n\
    \          log_(std::numeric_limits<T>::digits), data_(log_, bit_vector(n_)),\n\
    \          mid_(log_) {\n        assert(std::all_of(data.begin(), data.end(),\n\
    \                           [](auto x) { return x >= 0; }));\n        for (auto\
    \ i = log_ - 1; i >= 0; --i) {\n            for (auto j = 0; j < n_; ++j) {\n\
    \                if (data[j] >> i & 1) {\n                    data_[i].set(j);\n\
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
    \       return result;\n    }\n    int range(int l, int r, T x, T y) const {\n\
    \        return range(l, r, y) - range(l, r, x);\n    }\n\nprivate:\n    int range(int\
    \ l, int r, T x) const {\n        auto count = 0;\n        for (auto i = log_\
    \ - 1; i >= 0; --i) {\n            if (x >> i & 1) {\n                count +=\
    \ data_[i].rank(l, r, false);\n                l = mid_[i] + data_[i].rank(0,\
    \ l, true);\n                r = mid_[i] + data_[i].rank(0, r, true);\n      \
    \      } else {\n                l = data_[i].rank(0, l, false);\n           \
    \     r = data_[i].rank(0, r, false);\n            }\n        }\n        return\
    \ count;\n    }\n    const int n_, log_;\n    std::vector<bit_vector> data_;\n\
    \    std::vector<int> mid_;\n};\n\n#endif // WAVELET_MATRIX_HPP"
  dependsOn: []
  isVerificationFile: false
  path: wavelet/wavelet_matrix.hpp
  requiredBy: []
  timestamp: '2022-09-08 12:22:22+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/wavelet/wavelet_matrix_static_range_frequency.test.cpp
  - test/wavelet/wavelet_matrix_range_kth_smallest.test.cpp
documentation_of: wavelet/wavelet_matrix.hpp
layout: document
redirect_from:
- /library/wavelet/wavelet_matrix.hpp
- /library/wavelet/wavelet_matrix.hpp.html
title: wavelet/wavelet_matrix.hpp
---
