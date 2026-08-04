---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/segment_tree/aizu1625.test.cpp
    title: test/segment_tree/aizu1625.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/segment_tree/sparse_segtree_2d.test.cpp
    title: test/segment_tree/sparse_segtree_2d.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://github.com/Aeren1564/CP/blob/master/Library/Data_Structure/Segment_Tree/segment_tree_2d_sparse.sublime-snippet
    - https://github.com/maspypy/library/blob/main/ds/segtree/segtree_2d.hpp
  bundledCode: "#line 1 \"segment_tree/sparse_segtree_2d.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <numeric>\n#include <tuple>\n#include <vector>\n\n\
    // https://github.com/Aeren1564/CP/blob/master/Library/Data_Structure/Segment_Tree/segment_tree_2d_sparse.sublime-snippet\n\
    // https://github.com/maspypy/library/blob/main/ds/segtree/segtree_2d.hpp\ntemplate\
    \ <typename IndexType, class S, auto op, auto e, bool Compress = true>\nstruct\
    \ sparse_segtree_2d {\n    sparse_segtree_2d(const std::vector<IndexType> &x,\
    \ const std::vector<IndexType> &y)\n        : sparse_segtree_2d(int(x.size()),\
    \ [&](int i) { return std::tuple{x[i], y[i], e()}; }) {}\n    sparse_segtree_2d(const\
    \ std::vector<IndexType> &x, const std::vector<IndexType> &y,\n              \
    \        const std::vector<S> &data)\n        : sparse_segtree_2d(int(x.size()),\
    \ [&](int i) { return std::tuple{x[i], y[i], data[i]}; }) {\n    }\n    // f(i)\
    \ = (x, y, val)\n    sparse_segtree_2d(int n, auto f) : n_(n) {\n        std::vector<IndexType>\
    \ x(n), y(n);\n        std::vector<S> wt(n);\n        for (auto i = 0; i < n;\
    \ ++i) {\n            auto [a, b, c] = f(i);\n            x[i] = a, y[i] = b,\
    \ wt[i] = c;\n        }\n        if constexpr (Compress) {\n            key_x_\
    \ = x;\n            std::sort(key_x_.begin(), key_x_.end());\n            key_x_.erase(std::unique(key_x_.begin(),\
    \ key_x_.end()), key_x_.end());\n            nx_ = int(key_x_.size());\n     \
    \   } else {\n            min_x_ = (x.empty() ? 0 : *std::min_element(x.begin(),\
    \ x.end()));\n            nx_ = (x.empty() ? 1 : *std::max_element(x.begin(),\
    \ x.end()) - min_x_ + 1);\n        }\n        log_ = 0;\n        while ((1 <<\
    \ log_) < nx_) {\n            ++log_;\n        }\n        size_ = 1 << log_;\n\
    \        std::vector<int> ix(n);\n        for (auto i = 0; i < n; ++i) {\n   \
    \         ix[i] = xtoi(x[i]);\n        }\n        indptr_.assign(2 * size_, 0);\n\
    \        for (auto i : ix) {\n            for (i += size_; i; i >>= 1) {\n   \
    \             ++indptr_[i];\n            }\n        }\n        indptr_.insert(indptr_.begin(),\
    \ 0);\n        for (auto i = 1; i < int(indptr_.size()); ++i) {\n            indptr_[i]\
    \ += indptr_[i - 1];\n        }\n        data_.assign(2 * indptr_.back(), e());\n\
    \        to_left_.assign(indptr_[size_], 0);\n        std::vector<int> ptr = indptr_;\n\
    \        std::vector<int> I(y.size());\n        std::iota(I.begin(), I.end(),\
    \ 0);\n        std::sort(I.begin(), I.end(), [&](int i, int j) { return y[i] <\
    \ y[j]; });\n        pos_.resize(n);\n        for (auto i = 0; i < n; ++i) {\n\
    \            pos_[I[i]] = i;\n        }\n        for (auto raw_idx : I) {\n  \
    \          int i = ix[raw_idx] + size_;\n            int j = -1;\n           \
    \ for (; i; i >>= 1) {\n                int p = ptr[i];\n                ptr[i]++;\n\
    \                data_[indptr_[i + 1] + p] = wt[raw_idx];\n                if\
    \ (j != -1) {\n                    to_left_[p] = (j % 2 == 0);\n             \
    \   }\n                j = i;\n            }\n        }\n        to_left_.insert(to_left_.begin(),\
    \ 0);\n        for (auto i = 1; i < int(to_left_.size()); ++i) {\n           \
    \ to_left_[i] += to_left_[i - 1];\n        }\n        for (auto i = 0; i < 2 *\
    \ size_; ++i) {\n            int off = 2 * indptr_[i];\n            int m = indptr_[i\
    \ + 1] - indptr_[i];\n            for (auto j = m - 1; 0 < j; --j) {\n       \
    \         data_[off + j] = op(data_[off + 2 * j + 0], data_[off + 2 * j + 1]);\n\
    \            }\n        }\n        all_y_ = y;\n        std::sort(all_y_.begin(),\
    \ all_y_.end());\n    }\n    // raw_idx: index in the original point cloud\n \
    \   void multiply(int raw_idx, S val) {\n        assert(0 <= raw_idx && raw_idx\
    \ < n_);\n        int i = 1, p = pos_[raw_idx];\n        while (true) {\n    \
    \        multiply_i(i, p - indptr_[i], val);\n            if (size_ <= i) {\n\
    \                break;\n            }\n            int lc = to_left_[p] - to_left_[indptr_[i]];\n\
    \            int rc = (p - indptr_[i]) - lc;\n            if (to_left_[p + 1]\
    \ - to_left_[p]) {\n                p = indptr_[2 * i + 0] + lc;\n           \
    \     i = 2 * i + 0;\n            } else {\n                p = indptr_[2 * i\
    \ + 1] + rc;\n                i = 2 * i + 1;\n            }\n        }\n    }\n\
    \    // raw_idx: index in the original point cloud\n    void set(int raw_idx,\
    \ S val) {\n        assert(0 <= raw_idx && raw_idx < n_);\n        int i = 1,\
    \ p = pos_[raw_idx];\n        while (true) {\n            set_i(i, p - indptr_[i],\
    \ val);\n            if (size_ <= i) {\n                break;\n            }\n\
    \            int lc = to_left_[p] - to_left_[indptr_[i]];\n            int rc\
    \ = (p - indptr_[i]) - lc;\n            if (to_left_[p + 1] - to_left_[p]) {\n\
    \                p = indptr_[2 * i + 0] + lc;\n                i = 2 * i + 0;\n\
    \            } else {\n                p = indptr_[2 * i + 1] + rc;\n        \
    \        i = 2 * i + 1;\n            }\n        }\n    }\n    // [lx, rx) * [ly,\
    \ ry)\n    // O(log^2 n)\n    S prod(IndexType lx, IndexType rx, IndexType ly,\
    \ IndexType ry) const {\n        assert(lx <= rx && ly <= ry);\n        int L\
    \ = xtoi(lx);\n        int R = xtoi(rx);\n        S res = e();\n        auto dfs\
    \ = [&](auto self, int i, int l, int r, int a, int b) -> void {\n            if\
    \ (a == b || R <= l || r <= L) {\n                return;\n            }\n   \
    \         if (L <= l && r <= R) {\n                res = op(res, query_i(i, a,\
    \ b));\n                return;\n            }\n            int la = to_left_[indptr_[i]\
    \ + a] - to_left_[indptr_[i]];\n            int ra = a - la;\n            int\
    \ lb = to_left_[indptr_[i] + b] - to_left_[indptr_[i]];\n            int rb =\
    \ b - lb;\n            int m = (l + r) / 2;\n            self(self, 2 * i + 0,\
    \ l, m, la, lb);\n            self(self, 2 * i + 1, m, r, ra, rb);\n        };\n\
    \        dfs(dfs, 1, 0, size_,\n            int(std::lower_bound(all_y_.begin(),\
    \ all_y_.end(), ly) - all_y_.begin()),\n            int(std::lower_bound(all_y_.begin(),\
    \ all_y_.end(), ry) - all_y_.begin()));\n        return res;\n    }\n    // [lx,\
    \ rx) * [ly, ry)\n    // O(log n)\n    int count(IndexType lx, IndexType rx, IndexType\
    \ ly, IndexType ry) const {\n        assert(lx <= rx && ly <= ry);\n        int\
    \ L = xtoi(lx);\n        int R = xtoi(rx);\n        int res = 0;\n        auto\
    \ dfs = [&](auto self, int i, int l, int r, int a, int b) -> void {\n        \
    \    if (a == b || R <= l || r <= L) {\n                return;\n            }\n\
    \            if (L <= l && r <= R) {\n                res += b - a;\n        \
    \        return;\n            }\n            int la = to_left_[indptr_[i] + a]\
    \ - to_left_[indptr_[i]];\n            int ra = a - la;\n            int lb =\
    \ to_left_[indptr_[i] + b] - to_left_[indptr_[i]];\n            int rb = b - lb;\n\
    \            int m = (l + r) / 2;\n            self(self, 2 * i + 0, l, m, la,\
    \ lb);\n            self(self, 2 * i + 1, m, r, ra, rb);\n        };\n       \
    \ dfs(dfs, 1, 0, size_,\n            int(std::lower_bound(all_y_.begin(), all_y_.end(),\
    \ ly) - all_y_.begin()),\n            int(std::lower_bound(all_y_.begin(), all_y_.end(),\
    \ ry) - all_y_.begin()));\n        return res;\n    }\n\nprivate:\n    int xtoi(IndexType\
    \ x) const {\n        if constexpr (Compress) {\n            return int(std::lower_bound(key_x_.begin(),\
    \ key_x_.end(), x) - key_x_.begin());\n        }\n        return std::clamp<IndexType>(x\
    \ - min_x_, 0, nx_);\n    }\n    S query_i(int i, int a, int b) const {\n    \
    \    int lid = indptr_[i];\n        int n = indptr_[i + 1] - indptr_[i];\n   \
    \     int off = 2 * lid;\n        S val = e();\n        for (auto L = n + a, R\
    \ = n + b; L < R; L >>= 1, R >>= 1) {\n            if (L & 1) {\n            \
    \    val = op(val, data_[off + L++]);\n            }\n            if (R & 1) {\n\
    \                val = op(data_[off + --R], val);\n            }\n        }\n\
    \        return val;\n    }\n    void multiply_i(int i, int j, S val) {\n    \
    \    int lid = indptr_[i];\n        int n = indptr_[i + 1] - indptr_[i];\n   \
    \     int off = 2 * lid;\n        for (j += n; j; j >>= 1) {\n            data_[off\
    \ + j] = op(data_[off + j], val);\n        }\n    }\n    void set_i(int i, int\
    \ j, S val) {\n        int lid = indptr_[i];\n        int n = indptr_[i + 1] -\
    \ indptr_[i];\n        int off = 2 * lid;\n        j += n;\n        data_[off\
    \ + j] = val;\n        for (; 0 < (j >>= 1);) {\n            data_[off + j] =\
    \ op(data_[off + 2 * j + 0], data_[off + 2 * j + 1]);\n        }\n    }\n    int\
    \ n_, nx_, log_, size_;\n    IndexType min_x_;\n    std::vector<IndexType> key_x_,\
    \ all_y_;\n    std::vector<int> pos_, indptr_, to_left_;\n    std::vector<S> data_;\n\
    };\n\n\n"
  code: "#ifndef SPARSE_SEGTREE_2D_HPP\n#define SPARSE_SEGTREE_2D_HPP\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <numeric>\n#include <tuple>\n#include\
    \ <vector>\n\n// https://github.com/Aeren1564/CP/blob/master/Library/Data_Structure/Segment_Tree/segment_tree_2d_sparse.sublime-snippet\n\
    // https://github.com/maspypy/library/blob/main/ds/segtree/segtree_2d.hpp\ntemplate\
    \ <typename IndexType, class S, auto op, auto e, bool Compress = true>\nstruct\
    \ sparse_segtree_2d {\n    sparse_segtree_2d(const std::vector<IndexType> &x,\
    \ const std::vector<IndexType> &y)\n        : sparse_segtree_2d(int(x.size()),\
    \ [&](int i) { return std::tuple{x[i], y[i], e()}; }) {}\n    sparse_segtree_2d(const\
    \ std::vector<IndexType> &x, const std::vector<IndexType> &y,\n              \
    \        const std::vector<S> &data)\n        : sparse_segtree_2d(int(x.size()),\
    \ [&](int i) { return std::tuple{x[i], y[i], data[i]}; }) {\n    }\n    // f(i)\
    \ = (x, y, val)\n    sparse_segtree_2d(int n, auto f) : n_(n) {\n        std::vector<IndexType>\
    \ x(n), y(n);\n        std::vector<S> wt(n);\n        for (auto i = 0; i < n;\
    \ ++i) {\n            auto [a, b, c] = f(i);\n            x[i] = a, y[i] = b,\
    \ wt[i] = c;\n        }\n        if constexpr (Compress) {\n            key_x_\
    \ = x;\n            std::sort(key_x_.begin(), key_x_.end());\n            key_x_.erase(std::unique(key_x_.begin(),\
    \ key_x_.end()), key_x_.end());\n            nx_ = int(key_x_.size());\n     \
    \   } else {\n            min_x_ = (x.empty() ? 0 : *std::min_element(x.begin(),\
    \ x.end()));\n            nx_ = (x.empty() ? 1 : *std::max_element(x.begin(),\
    \ x.end()) - min_x_ + 1);\n        }\n        log_ = 0;\n        while ((1 <<\
    \ log_) < nx_) {\n            ++log_;\n        }\n        size_ = 1 << log_;\n\
    \        std::vector<int> ix(n);\n        for (auto i = 0; i < n; ++i) {\n   \
    \         ix[i] = xtoi(x[i]);\n        }\n        indptr_.assign(2 * size_, 0);\n\
    \        for (auto i : ix) {\n            for (i += size_; i; i >>= 1) {\n   \
    \             ++indptr_[i];\n            }\n        }\n        indptr_.insert(indptr_.begin(),\
    \ 0);\n        for (auto i = 1; i < int(indptr_.size()); ++i) {\n            indptr_[i]\
    \ += indptr_[i - 1];\n        }\n        data_.assign(2 * indptr_.back(), e());\n\
    \        to_left_.assign(indptr_[size_], 0);\n        std::vector<int> ptr = indptr_;\n\
    \        std::vector<int> I(y.size());\n        std::iota(I.begin(), I.end(),\
    \ 0);\n        std::sort(I.begin(), I.end(), [&](int i, int j) { return y[i] <\
    \ y[j]; });\n        pos_.resize(n);\n        for (auto i = 0; i < n; ++i) {\n\
    \            pos_[I[i]] = i;\n        }\n        for (auto raw_idx : I) {\n  \
    \          int i = ix[raw_idx] + size_;\n            int j = -1;\n           \
    \ for (; i; i >>= 1) {\n                int p = ptr[i];\n                ptr[i]++;\n\
    \                data_[indptr_[i + 1] + p] = wt[raw_idx];\n                if\
    \ (j != -1) {\n                    to_left_[p] = (j % 2 == 0);\n             \
    \   }\n                j = i;\n            }\n        }\n        to_left_.insert(to_left_.begin(),\
    \ 0);\n        for (auto i = 1; i < int(to_left_.size()); ++i) {\n           \
    \ to_left_[i] += to_left_[i - 1];\n        }\n        for (auto i = 0; i < 2 *\
    \ size_; ++i) {\n            int off = 2 * indptr_[i];\n            int m = indptr_[i\
    \ + 1] - indptr_[i];\n            for (auto j = m - 1; 0 < j; --j) {\n       \
    \         data_[off + j] = op(data_[off + 2 * j + 0], data_[off + 2 * j + 1]);\n\
    \            }\n        }\n        all_y_ = y;\n        std::sort(all_y_.begin(),\
    \ all_y_.end());\n    }\n    // raw_idx: index in the original point cloud\n \
    \   void multiply(int raw_idx, S val) {\n        assert(0 <= raw_idx && raw_idx\
    \ < n_);\n        int i = 1, p = pos_[raw_idx];\n        while (true) {\n    \
    \        multiply_i(i, p - indptr_[i], val);\n            if (size_ <= i) {\n\
    \                break;\n            }\n            int lc = to_left_[p] - to_left_[indptr_[i]];\n\
    \            int rc = (p - indptr_[i]) - lc;\n            if (to_left_[p + 1]\
    \ - to_left_[p]) {\n                p = indptr_[2 * i + 0] + lc;\n           \
    \     i = 2 * i + 0;\n            } else {\n                p = indptr_[2 * i\
    \ + 1] + rc;\n                i = 2 * i + 1;\n            }\n        }\n    }\n\
    \    // raw_idx: index in the original point cloud\n    void set(int raw_idx,\
    \ S val) {\n        assert(0 <= raw_idx && raw_idx < n_);\n        int i = 1,\
    \ p = pos_[raw_idx];\n        while (true) {\n            set_i(i, p - indptr_[i],\
    \ val);\n            if (size_ <= i) {\n                break;\n            }\n\
    \            int lc = to_left_[p] - to_left_[indptr_[i]];\n            int rc\
    \ = (p - indptr_[i]) - lc;\n            if (to_left_[p + 1] - to_left_[p]) {\n\
    \                p = indptr_[2 * i + 0] + lc;\n                i = 2 * i + 0;\n\
    \            } else {\n                p = indptr_[2 * i + 1] + rc;\n        \
    \        i = 2 * i + 1;\n            }\n        }\n    }\n    // [lx, rx) * [ly,\
    \ ry)\n    // O(log^2 n)\n    S prod(IndexType lx, IndexType rx, IndexType ly,\
    \ IndexType ry) const {\n        assert(lx <= rx && ly <= ry);\n        int L\
    \ = xtoi(lx);\n        int R = xtoi(rx);\n        S res = e();\n        auto dfs\
    \ = [&](auto self, int i, int l, int r, int a, int b) -> void {\n            if\
    \ (a == b || R <= l || r <= L) {\n                return;\n            }\n   \
    \         if (L <= l && r <= R) {\n                res = op(res, query_i(i, a,\
    \ b));\n                return;\n            }\n            int la = to_left_[indptr_[i]\
    \ + a] - to_left_[indptr_[i]];\n            int ra = a - la;\n            int\
    \ lb = to_left_[indptr_[i] + b] - to_left_[indptr_[i]];\n            int rb =\
    \ b - lb;\n            int m = (l + r) / 2;\n            self(self, 2 * i + 0,\
    \ l, m, la, lb);\n            self(self, 2 * i + 1, m, r, ra, rb);\n        };\n\
    \        dfs(dfs, 1, 0, size_,\n            int(std::lower_bound(all_y_.begin(),\
    \ all_y_.end(), ly) - all_y_.begin()),\n            int(std::lower_bound(all_y_.begin(),\
    \ all_y_.end(), ry) - all_y_.begin()));\n        return res;\n    }\n    // [lx,\
    \ rx) * [ly, ry)\n    // O(log n)\n    int count(IndexType lx, IndexType rx, IndexType\
    \ ly, IndexType ry) const {\n        assert(lx <= rx && ly <= ry);\n        int\
    \ L = xtoi(lx);\n        int R = xtoi(rx);\n        int res = 0;\n        auto\
    \ dfs = [&](auto self, int i, int l, int r, int a, int b) -> void {\n        \
    \    if (a == b || R <= l || r <= L) {\n                return;\n            }\n\
    \            if (L <= l && r <= R) {\n                res += b - a;\n        \
    \        return;\n            }\n            int la = to_left_[indptr_[i] + a]\
    \ - to_left_[indptr_[i]];\n            int ra = a - la;\n            int lb =\
    \ to_left_[indptr_[i] + b] - to_left_[indptr_[i]];\n            int rb = b - lb;\n\
    \            int m = (l + r) / 2;\n            self(self, 2 * i + 0, l, m, la,\
    \ lb);\n            self(self, 2 * i + 1, m, r, ra, rb);\n        };\n       \
    \ dfs(dfs, 1, 0, size_,\n            int(std::lower_bound(all_y_.begin(), all_y_.end(),\
    \ ly) - all_y_.begin()),\n            int(std::lower_bound(all_y_.begin(), all_y_.end(),\
    \ ry) - all_y_.begin()));\n        return res;\n    }\n\nprivate:\n    int xtoi(IndexType\
    \ x) const {\n        if constexpr (Compress) {\n            return int(std::lower_bound(key_x_.begin(),\
    \ key_x_.end(), x) - key_x_.begin());\n        }\n        return std::clamp<IndexType>(x\
    \ - min_x_, 0, nx_);\n    }\n    S query_i(int i, int a, int b) const {\n    \
    \    int lid = indptr_[i];\n        int n = indptr_[i + 1] - indptr_[i];\n   \
    \     int off = 2 * lid;\n        S val = e();\n        for (auto L = n + a, R\
    \ = n + b; L < R; L >>= 1, R >>= 1) {\n            if (L & 1) {\n            \
    \    val = op(val, data_[off + L++]);\n            }\n            if (R & 1) {\n\
    \                val = op(data_[off + --R], val);\n            }\n        }\n\
    \        return val;\n    }\n    void multiply_i(int i, int j, S val) {\n    \
    \    int lid = indptr_[i];\n        int n = indptr_[i + 1] - indptr_[i];\n   \
    \     int off = 2 * lid;\n        for (j += n; j; j >>= 1) {\n            data_[off\
    \ + j] = op(data_[off + j], val);\n        }\n    }\n    void set_i(int i, int\
    \ j, S val) {\n        int lid = indptr_[i];\n        int n = indptr_[i + 1] -\
    \ indptr_[i];\n        int off = 2 * lid;\n        j += n;\n        data_[off\
    \ + j] = val;\n        for (; 0 < (j >>= 1);) {\n            data_[off + j] =\
    \ op(data_[off + 2 * j + 0], data_[off + 2 * j + 1]);\n        }\n    }\n    int\
    \ n_, nx_, log_, size_;\n    IndexType min_x_;\n    std::vector<IndexType> key_x_,\
    \ all_y_;\n    std::vector<int> pos_, indptr_, to_left_;\n    std::vector<S> data_;\n\
    };\n\n#endif // SPARSE_SEGTREE_2D_HPP"
  dependsOn: []
  isVerificationFile: false
  path: segment_tree/sparse_segtree_2d.hpp
  requiredBy: []
  timestamp: '2026-08-04 08:03:55+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/segment_tree/sparse_segtree_2d.test.cpp
  - test/segment_tree/aizu1625.test.cpp
documentation_of: segment_tree/sparse_segtree_2d.hpp
layout: document
redirect_from:
- /library/segment_tree/sparse_segtree_2d.hpp
- /library/segment_tree/sparse_segtree_2d.hpp.html
title: segment_tree/sparse_segtree_2d.hpp
---
