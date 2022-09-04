---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/segtree_beats.test.cpp
    title: test/segtree_beats.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"segment_tree/segtree_beats.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\ntemplate <typename S, typename Op, typename\
    \ E, typename F, typename Mapping,\n          typename Composition, typename Id>\n\
    struct segtree_beats {\n    segtree_beats(const std::vector<S> &data, Op op, E\
    \ e, Mapping mapping,\n                      Composition composition, Id id)\n\
    \        : op_(op), e_(e), mapping_(mapping), composition_(composition), id_(id),\n\
    \          n_(static_cast<int>(data.size())),\n          log_(std::__lg(std::max(n_\
    \ - 1, 1)) + 1), size_(1 << log_),\n          data_(2 * size_, e_()), lazy_(size_,\
    \ id_()) {\n        for (auto i = 0; i < n_; ++i) {\n            data_[size_ +\
    \ i] = data[i];\n        }\n        for (auto i = size_ - 1; i >= 1; --i) {\n\
    \            update(i);\n        }\n    }\n    void set(int pos, S x) {\n    \
    \    assert(0 <= pos && pos < n_);\n        pos += size_;\n        for (auto i\
    \ = log_; i >= 1; --i) {\n            push(pos >> i);\n        }\n        data_[pos]\
    \ = x;\n        for (auto i = 1; i <= log_; ++i) {\n            update(pos >>\
    \ i);\n        }\n    }\n    S get(int pos) {\n        assert(0 <= pos && pos\
    \ < n_);\n        pos += size_;\n        for (auto i = log_; i >= 1; --i) {\n\
    \            push(pos >> i);\n        }\n        return data_[pos];\n    }\n \
    \   S prod(int l, int r) {\n        assert(0 <= l && l <= r && r <= n_);\n   \
    \     if (l == r)\n            return e_();\n        l += size_;\n        r +=\
    \ size_;\n        for (auto i = log_; i >= 1; --i) {\n            if (((l >> i)\
    \ << i) != l) {\n                push(l >> i);\n            }\n            if\
    \ (((r >> i) << i) != r) {\n                push((r - 1) >> i);\n            }\n\
    \        }\n        S sml = e_(), smr = e_();\n        while (l < r) {\n     \
    \       if (l & 1) {\n                sml = op_(sml, data_[l++]);\n          \
    \  }\n            if (r & 1) {\n                smr = op_(data_[--r], smr);\n\
    \            }\n            l >>= 1;\n            r >>= 1;\n        }\n      \
    \  return op_(sml, smr);\n    }\n    S all_prod() { return data_[1]; }\n    void\
    \ apply(int pos, F f) {\n        assert(0 <= pos && pos < n_);\n        pos +=\
    \ size_;\n        for (auto i = log_; i >= 1; --i) {\n            push(pos >>\
    \ i);\n        }\n        data_[pos] = mapping(f, data_[pos]);\n        for (auto\
    \ i = 1; i <= log_; ++i) {\n            update(pos >> i);\n        }\n    }\n\
    \    void apply(int l, int r, F f) {\n        assert(0 <= l && l <= r && r <=\
    \ n_);\n        if (l == r) {\n            return;\n        }\n        l += size_;\n\
    \        r += size_;\n        for (auto i = log_; i >= 1; --i) {\n           \
    \ if (((l >> i) << i) != l) {\n                push(l >> i);\n            }\n\
    \            if (((r >> i) << i) != r) {\n                push((r - 1) >> i);\n\
    \            }\n        }\n        int l2 = l, r2 = r;\n        while (l < r)\
    \ {\n            if (l & 1) {\n                all_apply(l++, f);\n          \
    \  }\n            if (r & 1) {\n                all_apply(--r, f);\n         \
    \   }\n            l >>= 1;\n            r >>= 1;\n        }\n        l = l2;\n\
    \        r = r2;\n        for (auto i = 1; i <= log_; ++i) {\n            if (((l\
    \ >> i) << i) != l) {\n                update(l >> i);\n            }\n      \
    \      if (((r >> i) << i) != r) {\n                update((r - 1) >> i);\n  \
    \          }\n        }\n    }\n\nprivate:\n    void update(int node) {\n    \
    \    data_[node] = op_(data_[2 * node], data_[2 * node + 1]);\n    }\n    void\
    \ all_apply(int node, F f) {\n        data_[node] = mapping_(f, data_[node]);\n\
    \        if (node < size_) {\n            lazy_[node] = composition_(f, lazy_[node]);\n\
    \            if (data_[node].fail) {\n                push(node);\n          \
    \      update(node);\n            }\n        }\n    }\n    void push(int node)\
    \ {\n        all_apply(2 * node, lazy_[node]);\n        all_apply(2 * node + 1,\
    \ lazy_[node]);\n        lazy_[node] = id_();\n    }\n    Op op_;\n    E e_;\n\
    \    Mapping mapping_;\n    Composition composition_;\n    Id id_;\n    const\
    \ int n_, log_, size_;\n    std::vector<S> data_;\n    std::vector<F> lazy_;\n\
    };\n\ntemplate <typename S, typename Op, typename E, typename Mapping,\n     \
    \     typename Composition, typename Id>\nsegtree_beats(const std::vector<S> &data,\
    \ Op op, E e, Mapping mapping,\n                  Composition composition, Id\
    \ id)\n    -> segtree_beats<S, Op, E, std::invoke_result_t<Id>, Mapping,\n   \
    \                      Composition, Id>;\n\n\n"
  code: "#ifndef SEGTREE_BEATS_HPP\n#define SEGTREE_BEATS_HPP\n\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\ntemplate <typename S, typename Op, typename\
    \ E, typename F, typename Mapping,\n          typename Composition, typename Id>\n\
    struct segtree_beats {\n    segtree_beats(const std::vector<S> &data, Op op, E\
    \ e, Mapping mapping,\n                      Composition composition, Id id)\n\
    \        : op_(op), e_(e), mapping_(mapping), composition_(composition), id_(id),\n\
    \          n_(static_cast<int>(data.size())),\n          log_(std::__lg(std::max(n_\
    \ - 1, 1)) + 1), size_(1 << log_),\n          data_(2 * size_, e_()), lazy_(size_,\
    \ id_()) {\n        for (auto i = 0; i < n_; ++i) {\n            data_[size_ +\
    \ i] = data[i];\n        }\n        for (auto i = size_ - 1; i >= 1; --i) {\n\
    \            update(i);\n        }\n    }\n    void set(int pos, S x) {\n    \
    \    assert(0 <= pos && pos < n_);\n        pos += size_;\n        for (auto i\
    \ = log_; i >= 1; --i) {\n            push(pos >> i);\n        }\n        data_[pos]\
    \ = x;\n        for (auto i = 1; i <= log_; ++i) {\n            update(pos >>\
    \ i);\n        }\n    }\n    S get(int pos) {\n        assert(0 <= pos && pos\
    \ < n_);\n        pos += size_;\n        for (auto i = log_; i >= 1; --i) {\n\
    \            push(pos >> i);\n        }\n        return data_[pos];\n    }\n \
    \   S prod(int l, int r) {\n        assert(0 <= l && l <= r && r <= n_);\n   \
    \     if (l == r)\n            return e_();\n        l += size_;\n        r +=\
    \ size_;\n        for (auto i = log_; i >= 1; --i) {\n            if (((l >> i)\
    \ << i) != l) {\n                push(l >> i);\n            }\n            if\
    \ (((r >> i) << i) != r) {\n                push((r - 1) >> i);\n            }\n\
    \        }\n        S sml = e_(), smr = e_();\n        while (l < r) {\n     \
    \       if (l & 1) {\n                sml = op_(sml, data_[l++]);\n          \
    \  }\n            if (r & 1) {\n                smr = op_(data_[--r], smr);\n\
    \            }\n            l >>= 1;\n            r >>= 1;\n        }\n      \
    \  return op_(sml, smr);\n    }\n    S all_prod() { return data_[1]; }\n    void\
    \ apply(int pos, F f) {\n        assert(0 <= pos && pos < n_);\n        pos +=\
    \ size_;\n        for (auto i = log_; i >= 1; --i) {\n            push(pos >>\
    \ i);\n        }\n        data_[pos] = mapping(f, data_[pos]);\n        for (auto\
    \ i = 1; i <= log_; ++i) {\n            update(pos >> i);\n        }\n    }\n\
    \    void apply(int l, int r, F f) {\n        assert(0 <= l && l <= r && r <=\
    \ n_);\n        if (l == r) {\n            return;\n        }\n        l += size_;\n\
    \        r += size_;\n        for (auto i = log_; i >= 1; --i) {\n           \
    \ if (((l >> i) << i) != l) {\n                push(l >> i);\n            }\n\
    \            if (((r >> i) << i) != r) {\n                push((r - 1) >> i);\n\
    \            }\n        }\n        int l2 = l, r2 = r;\n        while (l < r)\
    \ {\n            if (l & 1) {\n                all_apply(l++, f);\n          \
    \  }\n            if (r & 1) {\n                all_apply(--r, f);\n         \
    \   }\n            l >>= 1;\n            r >>= 1;\n        }\n        l = l2;\n\
    \        r = r2;\n        for (auto i = 1; i <= log_; ++i) {\n            if (((l\
    \ >> i) << i) != l) {\n                update(l >> i);\n            }\n      \
    \      if (((r >> i) << i) != r) {\n                update((r - 1) >> i);\n  \
    \          }\n        }\n    }\n\nprivate:\n    void update(int node) {\n    \
    \    data_[node] = op_(data_[2 * node], data_[2 * node + 1]);\n    }\n    void\
    \ all_apply(int node, F f) {\n        data_[node] = mapping_(f, data_[node]);\n\
    \        if (node < size_) {\n            lazy_[node] = composition_(f, lazy_[node]);\n\
    \            if (data_[node].fail) {\n                push(node);\n          \
    \      update(node);\n            }\n        }\n    }\n    void push(int node)\
    \ {\n        all_apply(2 * node, lazy_[node]);\n        all_apply(2 * node + 1,\
    \ lazy_[node]);\n        lazy_[node] = id_();\n    }\n    Op op_;\n    E e_;\n\
    \    Mapping mapping_;\n    Composition composition_;\n    Id id_;\n    const\
    \ int n_, log_, size_;\n    std::vector<S> data_;\n    std::vector<F> lazy_;\n\
    };\n\ntemplate <typename S, typename Op, typename E, typename Mapping,\n     \
    \     typename Composition, typename Id>\nsegtree_beats(const std::vector<S> &data,\
    \ Op op, E e, Mapping mapping,\n                  Composition composition, Id\
    \ id)\n    -> segtree_beats<S, Op, E, std::invoke_result_t<Id>, Mapping,\n   \
    \                      Composition, Id>;\n\n#endif // SEGTREE_BEATS_HPP"
  dependsOn: []
  isVerificationFile: false
  path: segment_tree/segtree_beats.hpp
  requiredBy: []
  timestamp: '2022-09-03 15:38:48+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/segtree_beats.test.cpp
documentation_of: segment_tree/segtree_beats.hpp
layout: document
title: Segtree Beats
---

Source: [AC Library](https://github.com/atcoder/ac-library/blob/master/atcoder/lazysegtree.hpp)
