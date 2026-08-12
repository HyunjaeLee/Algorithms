---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/segment_tree/sparse_lazy_segtree.test.cpp
    title: test/segment_tree/sparse_lazy_segtree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://suisen-cp.github.io/cp-library-cpp/library/datastructure/segment_tree/sparse_lazy_segment_tree.hpp
  bundledCode: "#line 1 \"segment_tree/sparse_lazy_segtree.hpp\"\n\n\n\n#include <array>\n\
    #include <cassert>\n#include <cstdint>\n#include <vector>\n\n// https://suisen-cp.github.io/cp-library-cpp/library/datastructure/segment_tree/sparse_lazy_segment_tree.hpp\n\
    template <typename IndexType, // type of index\n          typename S,        \
    \ // type of element\n          auto op,            // S op(S a, S b)\n      \
    \    auto e,             // S e()\n          typename F,         // type of operator\
    \ which acts on S\n          auto mapping,       // S mapping(F f, S x, IndexType\
    \ l, IndexType r)\n          auto composition,   // F composition(F f, F g)\n\
    \          auto id,            // F id()\n          auto init = [](IndexType,\n\
    \                         IndexType) { return e(); } // initializes product of\
    \ segment [l, r)\n          >\nstruct sparse_lazy_segtree {\n    using index_type\
    \ = IndexType;\n    using value_type = S;\n    using operator_type = F;\n\nprivate:\n\
    \    using pool_index_type = uint32_t;\n\n    struct Node {\n        pool_index_type\
    \ ch[2]{0, 0};\n        value_type dat;\n        operator_type laz;\n        Node(const\
    \ value_type &dat_) : dat(dat_), laz(id()) {}\n    };\n\n    static inline std::vector<Node>\
    \ pool{Node{e()}};\n\n    static pool_index_type new_node(const value_type &dat)\
    \ {\n        const pool_index_type res = static_cast<pool_index_type>(pool.size());\n\
    \        return pool.emplace_back(dat), res;\n    }\n\npublic:\n    sparse_lazy_segtree()\
    \ : sparse_lazy_segtree(0) {}\n    explicit sparse_lazy_segtree(IndexType n_)\
    \ : n(n_), root(new_node(init(0, n))) {}\n\n    static void reserve(int siz) {\
    \ pool.reserve(siz); }\n\n    value_type get(index_type i) const {\n        assert(0\
    \ <= i and i < n);\n        operator_type f = id();\n        pool_index_type cur\
    \ = root;\n        for (std::array<index_type, 2> lr{0, n}; cur and lr[1] - lr[0]\
    \ > 1;) {\n            index_type m = lr[0] + (lr[1] - lr[0]) / 2;\n         \
    \   bool b = i >= m;\n            f = composition(f, pool[cur].laz);\n       \
    \     cur = pool[cur].ch[b], lr[not b] = m;\n        }\n        return mapping(f,\
    \ cur ? pool[cur].dat : init(i, i + 1), i, i + 1);\n    }\n    template <typename\
    \ Fun> void apply_fun(index_type i, Fun &&fun) {\n        assert(0 <= i and i\
    \ < n);\n        static std::vector<pool_index_type> path;\n        pool_index_type\
    \ cur = root;\n        for (std::array<index_type, 2> lr{0, n}; lr[1] - lr[0]\
    \ > 1;) {\n            path.push_back(cur);\n            index_type m = lr[0]\
    \ + (lr[1] - lr[0]) / 2;\n            bool b = i >= m;\n            push(cur,\
    \ lr[0], lr[1]);\n            cur = pool[cur].ch[b], lr[not b] = m;\n        }\n\
    \        pool[cur].dat = fun(pool[cur].dat);\n        while (path.size())\n  \
    \          update(path.back()), path.pop_back();\n    }\n    void set(index_type\
    \ i, const value_type &val) {\n        apply_fun(i, [&val](const value_type &)\
    \ { return val; });\n    }\n    void apply(index_type i, const operator_type &f)\
    \ {\n        apply_fun(i, [&f, i](const value_type &val) { return mapping(f, val,\
    \ i, i + 1); });\n    }\n\n    value_type operator()(index_type l, index_type\
    \ r) {\n        assert(0 <= l and l <= r and r <= n);\n        if (l == r)\n \
    \           return e();\n        return query(root, l, r, 0, n);\n    }\n    value_type\
    \ prod(index_type l, index_type r) { return (*this)(l, r); }\n    value_type all_prod()\
    \ { return pool[root].dat; }\n\n    void apply(index_type l, index_type r, const\
    \ operator_type &f) {\n        assert(0 <= l and l <= r and r <= n);\n       \
    \ if (l == r)\n            return;\n        apply(root, f, l, r, 0, n);\n    }\n\
    \    void apply_all(const operator_type &f) { apply_all(root, f, 0, n); }\n\n\
    private:\n    index_type n;\n    pool_index_type root;\n\n    pool_index_type\
    \ get_or_create_child(pool_index_type node, int index, index_type tl,\n      \
    \                                  index_type tr) {\n        if (pool[node].ch[index])\n\
    \            return pool[node].ch[index];\n        const pool_index_type ch =\
    \ new_node(init(tl, tr));\n        return pool[node].ch[index] = ch;\n    }\n\n\
    \    void apply_all(pool_index_type node, const operator_type &f, index_type tl,\
    \ index_type tr) {\n        pool[node].dat = mapping(f, pool[node].dat, tl, tr);\n\
    \        pool[node].laz = composition(f, pool[node].laz);\n    }\n    void push(pool_index_type\
    \ node, index_type tl, index_type tr) {\n        const index_type tm = tl + (tr\
    \ - tl) / 2;\n        const operator_type laz = pool[node].laz;\n        apply_all(get_or_create_child(node,\
    \ 0, tl, tm), laz, tl, tm);\n        apply_all(get_or_create_child(node, 1, tm,\
    \ tr), laz, tm, tr);\n        pool[node].laz = id();\n    }\n\n    void update(pool_index_type\
    \ node) {\n        pool_index_type lch = pool[node].ch[0], rch = pool[node].ch[1];\n\
    \        pool[node].dat = op(pool[lch].dat, pool[rch].dat);\n    }\n\n    value_type\
    \ query(pool_index_type node, index_type ql, index_type qr, index_type tl,\n \
    \                    index_type tr) {\n        if (tr <= ql or qr <= tl)\n   \
    \         return e();\n        if (ql <= tl and tr <= qr)\n            return\
    \ pool[node].dat;\n        push(node, tl, tr);\n        const index_type tm =\
    \ tl + (tr - tl) / 2;\n        return op(query(pool[node].ch[0], ql, qr, tl, tm),\
    \ query(pool[node].ch[1], ql, qr, tm, tr));\n    }\n\n    void apply(pool_index_type\
    \ node, const operator_type &f, index_type ql, index_type qr,\n              \
    \ index_type tl, index_type tr) {\n        if (tr <= ql or qr <= tl)\n       \
    \     return;\n        if (ql <= tl and tr <= qr)\n            return apply_all(node,\
    \ f, tl, tr);\n        const index_type tm = tl + (tr - tl) / 2;\n        push(node,\
    \ tl, tr);\n        apply(pool[node].ch[0], f, ql, qr, tl, tm), apply(pool[node].ch[1],\
    \ f, ql, qr, tm, tr);\n        update(node);\n    }\n};\n\n\n"
  code: "#ifndef SPARSE_LAZY_SEGTREE_HPP\n#define SPARSE_LAZY_SEGTREE_HPP\n\n#include\
    \ <array>\n#include <cassert>\n#include <cstdint>\n#include <vector>\n\n// https://suisen-cp.github.io/cp-library-cpp/library/datastructure/segment_tree/sparse_lazy_segment_tree.hpp\n\
    template <typename IndexType, // type of index\n          typename S,        \
    \ // type of element\n          auto op,            // S op(S a, S b)\n      \
    \    auto e,             // S e()\n          typename F,         // type of operator\
    \ which acts on S\n          auto mapping,       // S mapping(F f, S x, IndexType\
    \ l, IndexType r)\n          auto composition,   // F composition(F f, F g)\n\
    \          auto id,            // F id()\n          auto init = [](IndexType,\n\
    \                         IndexType) { return e(); } // initializes product of\
    \ segment [l, r)\n          >\nstruct sparse_lazy_segtree {\n    using index_type\
    \ = IndexType;\n    using value_type = S;\n    using operator_type = F;\n\nprivate:\n\
    \    using pool_index_type = uint32_t;\n\n    struct Node {\n        pool_index_type\
    \ ch[2]{0, 0};\n        value_type dat;\n        operator_type laz;\n        Node(const\
    \ value_type &dat_) : dat(dat_), laz(id()) {}\n    };\n\n    static inline std::vector<Node>\
    \ pool{Node{e()}};\n\n    static pool_index_type new_node(const value_type &dat)\
    \ {\n        const pool_index_type res = static_cast<pool_index_type>(pool.size());\n\
    \        return pool.emplace_back(dat), res;\n    }\n\npublic:\n    sparse_lazy_segtree()\
    \ : sparse_lazy_segtree(0) {}\n    explicit sparse_lazy_segtree(IndexType n_)\
    \ : n(n_), root(new_node(init(0, n))) {}\n\n    static void reserve(int siz) {\
    \ pool.reserve(siz); }\n\n    value_type get(index_type i) const {\n        assert(0\
    \ <= i and i < n);\n        operator_type f = id();\n        pool_index_type cur\
    \ = root;\n        for (std::array<index_type, 2> lr{0, n}; cur and lr[1] - lr[0]\
    \ > 1;) {\n            index_type m = lr[0] + (lr[1] - lr[0]) / 2;\n         \
    \   bool b = i >= m;\n            f = composition(f, pool[cur].laz);\n       \
    \     cur = pool[cur].ch[b], lr[not b] = m;\n        }\n        return mapping(f,\
    \ cur ? pool[cur].dat : init(i, i + 1), i, i + 1);\n    }\n    template <typename\
    \ Fun> void apply_fun(index_type i, Fun &&fun) {\n        assert(0 <= i and i\
    \ < n);\n        static std::vector<pool_index_type> path;\n        pool_index_type\
    \ cur = root;\n        for (std::array<index_type, 2> lr{0, n}; lr[1] - lr[0]\
    \ > 1;) {\n            path.push_back(cur);\n            index_type m = lr[0]\
    \ + (lr[1] - lr[0]) / 2;\n            bool b = i >= m;\n            push(cur,\
    \ lr[0], lr[1]);\n            cur = pool[cur].ch[b], lr[not b] = m;\n        }\n\
    \        pool[cur].dat = fun(pool[cur].dat);\n        while (path.size())\n  \
    \          update(path.back()), path.pop_back();\n    }\n    void set(index_type\
    \ i, const value_type &val) {\n        apply_fun(i, [&val](const value_type &)\
    \ { return val; });\n    }\n    void apply(index_type i, const operator_type &f)\
    \ {\n        apply_fun(i, [&f, i](const value_type &val) { return mapping(f, val,\
    \ i, i + 1); });\n    }\n\n    value_type operator()(index_type l, index_type\
    \ r) {\n        assert(0 <= l and l <= r and r <= n);\n        if (l == r)\n \
    \           return e();\n        return query(root, l, r, 0, n);\n    }\n    value_type\
    \ prod(index_type l, index_type r) { return (*this)(l, r); }\n    value_type all_prod()\
    \ { return pool[root].dat; }\n\n    void apply(index_type l, index_type r, const\
    \ operator_type &f) {\n        assert(0 <= l and l <= r and r <= n);\n       \
    \ if (l == r)\n            return;\n        apply(root, f, l, r, 0, n);\n    }\n\
    \    void apply_all(const operator_type &f) { apply_all(root, f, 0, n); }\n\n\
    private:\n    index_type n;\n    pool_index_type root;\n\n    pool_index_type\
    \ get_or_create_child(pool_index_type node, int index, index_type tl,\n      \
    \                                  index_type tr) {\n        if (pool[node].ch[index])\n\
    \            return pool[node].ch[index];\n        const pool_index_type ch =\
    \ new_node(init(tl, tr));\n        return pool[node].ch[index] = ch;\n    }\n\n\
    \    void apply_all(pool_index_type node, const operator_type &f, index_type tl,\
    \ index_type tr) {\n        pool[node].dat = mapping(f, pool[node].dat, tl, tr);\n\
    \        pool[node].laz = composition(f, pool[node].laz);\n    }\n    void push(pool_index_type\
    \ node, index_type tl, index_type tr) {\n        const index_type tm = tl + (tr\
    \ - tl) / 2;\n        const operator_type laz = pool[node].laz;\n        apply_all(get_or_create_child(node,\
    \ 0, tl, tm), laz, tl, tm);\n        apply_all(get_or_create_child(node, 1, tm,\
    \ tr), laz, tm, tr);\n        pool[node].laz = id();\n    }\n\n    void update(pool_index_type\
    \ node) {\n        pool_index_type lch = pool[node].ch[0], rch = pool[node].ch[1];\n\
    \        pool[node].dat = op(pool[lch].dat, pool[rch].dat);\n    }\n\n    value_type\
    \ query(pool_index_type node, index_type ql, index_type qr, index_type tl,\n \
    \                    index_type tr) {\n        if (tr <= ql or qr <= tl)\n   \
    \         return e();\n        if (ql <= tl and tr <= qr)\n            return\
    \ pool[node].dat;\n        push(node, tl, tr);\n        const index_type tm =\
    \ tl + (tr - tl) / 2;\n        return op(query(pool[node].ch[0], ql, qr, tl, tm),\
    \ query(pool[node].ch[1], ql, qr, tm, tr));\n    }\n\n    void apply(pool_index_type\
    \ node, const operator_type &f, index_type ql, index_type qr,\n              \
    \ index_type tl, index_type tr) {\n        if (tr <= ql or qr <= tl)\n       \
    \     return;\n        if (ql <= tl and tr <= qr)\n            return apply_all(node,\
    \ f, tl, tr);\n        const index_type tm = tl + (tr - tl) / 2;\n        push(node,\
    \ tl, tr);\n        apply(pool[node].ch[0], f, ql, qr, tl, tm), apply(pool[node].ch[1],\
    \ f, ql, qr, tm, tr);\n        update(node);\n    }\n};\n\n#endif // SPARSE_LAZY_SEGTREE_HPP"
  dependsOn: []
  isVerificationFile: false
  path: segment_tree/sparse_lazy_segtree.hpp
  requiredBy: []
  timestamp: '2026-08-12 17:21:46+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/segment_tree/sparse_lazy_segtree.test.cpp
documentation_of: segment_tree/sparse_lazy_segtree.hpp
layout: document
redirect_from:
- /library/segment_tree/sparse_lazy_segtree.hpp
- /library/segment_tree/sparse_lazy_segtree.hpp.html
title: segment_tree/sparse_lazy_segtree.hpp
---
