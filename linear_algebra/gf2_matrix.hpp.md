---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/linear_algebra/matrix_det_mod_2.test.cpp
    title: test/linear_algebra/matrix_det_mod_2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/linear_algebra/matrix_rank_mod_2.test.cpp
    title: test/linear_algebra/matrix_rank_mod_2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/linear_algebra/system_of_linear_equations_mod_2.test.cpp
    title: test/linear_algebra/system_of_linear_equations_mod_2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"linear_algebra/gf2_matrix.hpp\"\n\n\n\n#include <bit>\n\
    #include <string_view>\n#include <vector>\n\n#ifdef __x86_64__\n#define USE_AVX2\n\
    #endif\n\n#ifdef USE_AVX2\n#include <immintrin.h>\n#endif\n\nstruct GF2Matrix\
    \ {\n    GF2Matrix(int r, int c) : rows_(r), cols_(c), stride_((c + 63) / 64)\
    \ {\n        data_ = new unsigned long long[rows_ * stride_]{};\n    }\n    ~GF2Matrix()\
    \ { delete[] data_; }\n    void set(int r, int c) { data_[r * stride_ + (c / 64)]\
    \ |= (1ULL << (c % 64)); }\n    void flip(int r, int c) { data_[r * stride_ +\
    \ (c / 64)] ^= (1ULL << (c % 64)); }\n    bool get(int r, int c) { return (data_[r\
    \ * stride_ + (c / 64)] >> (c % 64)) & 1; }\n#ifdef USE_AVX2\n    __attribute__((target(\"\
    avx2\"))) void xor_rows(unsigned long long *d,\n                             \
    \                     const unsigned long long *s, int start_idx) {\n        int\
    \ i = start_idx;\n        for (; i + 4 <= stride_; i += 4) {\n            auto\
    \ dst = reinterpret_cast<__m256i *>(&d[i]);\n            auto src = reinterpret_cast<const\
    \ __m256i *>(&s[i]);\n            auto sum = _mm256_xor_si256(_mm256_loadu_si256(dst),\
    \ _mm256_loadu_si256(src));\n            _mm256_storeu_si256(dst, sum);\n    \
    \    }\n        for (; i < stride_; ++i) {\n            d[i] ^= s[i];\n      \
    \  }\n    }\n#else\n    void xor_rows(unsigned long long *d, const unsigned long\
    \ long *s, int start_idx) {\n        for (int i = start_idx; i < stride_; ++i)\
    \ {\n            d[i] ^= s[i];\n        }\n    }\n#endif\n#ifdef USE_AVX2\n  \
    \  __attribute__((target(\"avx2\"))) void set_row(int row, std::string_view s)\
    \ {\n        auto n = (int)s.size();\n        auto one = _mm256_set1_epi8('1');\n\
    \        auto str = s.data();\n        auto dst = (unsigned int *)data_;\n   \
    \     auto i = 0;\n        for (; i + 32 <= n; i += 32) {\n            auto src\
    \ = reinterpret_cast<const __m256i *>(&str[i]);\n            dst[row * stride_\
    \ * 2 + i / 32] =\n                (unsigned int)_mm256_movemask_epi8(_mm256_cmpeq_epi8(_mm256_loadu_si256(src),\
    \ one));\n        }\n        for (; i < n; i++) {\n            if (s[i] == '1')\
    \ {\n                set(row, i);\n            }\n        }\n    }\n#else\n  \
    \  void set_row(int row, std::string_view s) {\n        auto n = (int)s.size();\n\
    \        for (auto i = 0; i < n; i++) {\n            if (s[i] == '1') {\n    \
    \            set(row, i);\n            }\n        }\n    }\n#endif\n    int gaussian_elimination()\
    \ { // O(min(N, M) * N * M / 64)\n        int pivot_row = 0;\n        for (int\
    \ col = 0; col < cols_ && pivot_row < rows_; ++col) {\n            int chunk_idx\
    \ = col / 64;\n            unsigned long long bit_mask = (1ULL << (col % 64));\n\
    \            int target = -1;\n            for (int i = pivot_row; i < rows_;\
    \ ++i) {\n                if (data_[i * stride_ + chunk_idx] & bit_mask) {\n \
    \                   target = i;\n                    break;\n                }\n\
    \            }\n            if (target == -1) {\n                continue;\n \
    \           }\n            if (pivot_row != target) {\n                xor_rows(data_\
    \ + pivot_row * stride_, data_ + target * stride_, chunk_idx);\n            }\n\
    \            for (int i = pivot_row + 1; i < rows_; ++i) {\n                if\
    \ (data_[i * stride_ + chunk_idx] & bit_mask) {\n                    xor_rows(data_\
    \ + i * stride_, data_ + pivot_row * stride_, chunk_idx);\n                }\n\
    \            }\n            ++pivot_row;\n        }\n        return pivot_row;\n\
    \    }\n    int gauss_jordan_elimination() {\n        int pivot_row = 0;\n   \
    \     for (int col = 0; col < cols_ && pivot_row < rows_; ++col) {\n         \
    \   int chunk_idx = col / 64;\n            unsigned long long bit_mask = (1ULL\
    \ << (col % 64));\n            int target = -1;\n            for (int i = pivot_row;\
    \ i < rows_; ++i) {\n                if (data_[i * stride_ + chunk_idx] & bit_mask)\
    \ {\n                    target = i;\n                    break;\n           \
    \     }\n            }\n            if (target == -1) {\n                continue;\n\
    \            }\n            if (pivot_row != target) {\n                xor_rows(data_\
    \ + pivot_row * stride_, data_ + target * stride_, chunk_idx);\n            }\n\
    \            for (int i = 0; i < rows_; ++i) {\n                if (i != pivot_row\
    \ && (data_[i * stride_ + chunk_idx] & bit_mask)) {\n                    xor_rows(data_\
    \ + i * stride_, data_ + pivot_row * stride_, chunk_idx);\n                }\n\
    \            }\n            ++pivot_row;\n        }\n        return pivot_row;\n\
    \    }\n    template <typename T = std::vector<bool>> std::vector<T> solve() {\n\
    \        auto rank = gauss_jordan_elimination();\n        std::vector<int> pivot(rank);\n\
    \        std::vector<char> is_pivot_col(cols_);\n        for (auto i = 0, j =\
    \ 0; i < rank;) {\n            if (data_[i * stride_ + j]) {\n               \
    \ pivot[i] = 64 * j + std::countr_zero(data_[i * stride_ + j]);\n            \
    \    is_pivot_col[pivot[i]] = true;\n                ++i;\n            } else\
    \ {\n                ++j;\n            }\n        }\n        if (is_pivot_col[cols_\
    \ - 1]) {\n            return {};\n        }\n        T ans(cols_ - 1);\n    \
    \    for (auto i = 0; i < rank; ++i) {\n            ans[pivot[i]] = get(i, cols_\
    \ - 1);\n        }\n        std::vector<T> ret = {ans};\n        ret.reserve(cols_\
    \ - rank);\n        for (auto j = 0; j < cols_ - 1; ++j) {\n            if (is_pivot_col[j])\
    \ {\n                continue;\n            }\n            T basis(cols_ - 1);\n\
    \            basis[j] = true;\n            for (auto i = 0; i < rank; ++i) {\n\
    \                basis[pivot[i]] = get(i, j);\n            }\n            ret.push_back(basis);\n\
    \        }\n        return ret;\n    }\n    const int rows_, cols_, stride_;\n\
    \    unsigned long long *data_;\n};\n\n\n"
  code: "#ifndef GF2_MATRIX_HPP\n#define GF2_MATRIX_HPP\n\n#include <bit>\n#include\
    \ <string_view>\n#include <vector>\n\n#ifdef __x86_64__\n#define USE_AVX2\n#endif\n\
    \n#ifdef USE_AVX2\n#include <immintrin.h>\n#endif\n\nstruct GF2Matrix {\n    GF2Matrix(int\
    \ r, int c) : rows_(r), cols_(c), stride_((c + 63) / 64) {\n        data_ = new\
    \ unsigned long long[rows_ * stride_]{};\n    }\n    ~GF2Matrix() { delete[] data_;\
    \ }\n    void set(int r, int c) { data_[r * stride_ + (c / 64)] |= (1ULL << (c\
    \ % 64)); }\n    void flip(int r, int c) { data_[r * stride_ + (c / 64)] ^= (1ULL\
    \ << (c % 64)); }\n    bool get(int r, int c) { return (data_[r * stride_ + (c\
    \ / 64)] >> (c % 64)) & 1; }\n#ifdef USE_AVX2\n    __attribute__((target(\"avx2\"\
    ))) void xor_rows(unsigned long long *d,\n                                   \
    \               const unsigned long long *s, int start_idx) {\n        int i =\
    \ start_idx;\n        for (; i + 4 <= stride_; i += 4) {\n            auto dst\
    \ = reinterpret_cast<__m256i *>(&d[i]);\n            auto src = reinterpret_cast<const\
    \ __m256i *>(&s[i]);\n            auto sum = _mm256_xor_si256(_mm256_loadu_si256(dst),\
    \ _mm256_loadu_si256(src));\n            _mm256_storeu_si256(dst, sum);\n    \
    \    }\n        for (; i < stride_; ++i) {\n            d[i] ^= s[i];\n      \
    \  }\n    }\n#else\n    void xor_rows(unsigned long long *d, const unsigned long\
    \ long *s, int start_idx) {\n        for (int i = start_idx; i < stride_; ++i)\
    \ {\n            d[i] ^= s[i];\n        }\n    }\n#endif\n#ifdef USE_AVX2\n  \
    \  __attribute__((target(\"avx2\"))) void set_row(int row, std::string_view s)\
    \ {\n        auto n = (int)s.size();\n        auto one = _mm256_set1_epi8('1');\n\
    \        auto str = s.data();\n        auto dst = (unsigned int *)data_;\n   \
    \     auto i = 0;\n        for (; i + 32 <= n; i += 32) {\n            auto src\
    \ = reinterpret_cast<const __m256i *>(&str[i]);\n            dst[row * stride_\
    \ * 2 + i / 32] =\n                (unsigned int)_mm256_movemask_epi8(_mm256_cmpeq_epi8(_mm256_loadu_si256(src),\
    \ one));\n        }\n        for (; i < n; i++) {\n            if (s[i] == '1')\
    \ {\n                set(row, i);\n            }\n        }\n    }\n#else\n  \
    \  void set_row(int row, std::string_view s) {\n        auto n = (int)s.size();\n\
    \        for (auto i = 0; i < n; i++) {\n            if (s[i] == '1') {\n    \
    \            set(row, i);\n            }\n        }\n    }\n#endif\n    int gaussian_elimination()\
    \ { // O(min(N, M) * N * M / 64)\n        int pivot_row = 0;\n        for (int\
    \ col = 0; col < cols_ && pivot_row < rows_; ++col) {\n            int chunk_idx\
    \ = col / 64;\n            unsigned long long bit_mask = (1ULL << (col % 64));\n\
    \            int target = -1;\n            for (int i = pivot_row; i < rows_;\
    \ ++i) {\n                if (data_[i * stride_ + chunk_idx] & bit_mask) {\n \
    \                   target = i;\n                    break;\n                }\n\
    \            }\n            if (target == -1) {\n                continue;\n \
    \           }\n            if (pivot_row != target) {\n                xor_rows(data_\
    \ + pivot_row * stride_, data_ + target * stride_, chunk_idx);\n            }\n\
    \            for (int i = pivot_row + 1; i < rows_; ++i) {\n                if\
    \ (data_[i * stride_ + chunk_idx] & bit_mask) {\n                    xor_rows(data_\
    \ + i * stride_, data_ + pivot_row * stride_, chunk_idx);\n                }\n\
    \            }\n            ++pivot_row;\n        }\n        return pivot_row;\n\
    \    }\n    int gauss_jordan_elimination() {\n        int pivot_row = 0;\n   \
    \     for (int col = 0; col < cols_ && pivot_row < rows_; ++col) {\n         \
    \   int chunk_idx = col / 64;\n            unsigned long long bit_mask = (1ULL\
    \ << (col % 64));\n            int target = -1;\n            for (int i = pivot_row;\
    \ i < rows_; ++i) {\n                if (data_[i * stride_ + chunk_idx] & bit_mask)\
    \ {\n                    target = i;\n                    break;\n           \
    \     }\n            }\n            if (target == -1) {\n                continue;\n\
    \            }\n            if (pivot_row != target) {\n                xor_rows(data_\
    \ + pivot_row * stride_, data_ + target * stride_, chunk_idx);\n            }\n\
    \            for (int i = 0; i < rows_; ++i) {\n                if (i != pivot_row\
    \ && (data_[i * stride_ + chunk_idx] & bit_mask)) {\n                    xor_rows(data_\
    \ + i * stride_, data_ + pivot_row * stride_, chunk_idx);\n                }\n\
    \            }\n            ++pivot_row;\n        }\n        return pivot_row;\n\
    \    }\n    template <typename T = std::vector<bool>> std::vector<T> solve() {\n\
    \        auto rank = gauss_jordan_elimination();\n        std::vector<int> pivot(rank);\n\
    \        std::vector<char> is_pivot_col(cols_);\n        for (auto i = 0, j =\
    \ 0; i < rank;) {\n            if (data_[i * stride_ + j]) {\n               \
    \ pivot[i] = 64 * j + std::countr_zero(data_[i * stride_ + j]);\n            \
    \    is_pivot_col[pivot[i]] = true;\n                ++i;\n            } else\
    \ {\n                ++j;\n            }\n        }\n        if (is_pivot_col[cols_\
    \ - 1]) {\n            return {};\n        }\n        T ans(cols_ - 1);\n    \
    \    for (auto i = 0; i < rank; ++i) {\n            ans[pivot[i]] = get(i, cols_\
    \ - 1);\n        }\n        std::vector<T> ret = {ans};\n        ret.reserve(cols_\
    \ - rank);\n        for (auto j = 0; j < cols_ - 1; ++j) {\n            if (is_pivot_col[j])\
    \ {\n                continue;\n            }\n            T basis(cols_ - 1);\n\
    \            basis[j] = true;\n            for (auto i = 0; i < rank; ++i) {\n\
    \                basis[pivot[i]] = get(i, j);\n            }\n            ret.push_back(basis);\n\
    \        }\n        return ret;\n    }\n    const int rows_, cols_, stride_;\n\
    \    unsigned long long *data_;\n};\n\n#endif // GF2_MATRIX_HPP"
  dependsOn: []
  isVerificationFile: false
  path: linear_algebra/gf2_matrix.hpp
  requiredBy: []
  timestamp: '2026-01-15 02:23:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/linear_algebra/system_of_linear_equations_mod_2.test.cpp
  - test/linear_algebra/matrix_rank_mod_2.test.cpp
  - test/linear_algebra/matrix_det_mod_2.test.cpp
documentation_of: linear_algebra/gf2_matrix.hpp
layout: document
title: GF(2) Matrix
---
### Related Problems
+ [Xor Maximization](https://www.acmicpc.net/problem/11191)
+ [Even Separation](https://www.acmicpc.net/problem/19212)
+ [Brazilian FootXOR](https://www.acmicpc.net/problem/34733)
