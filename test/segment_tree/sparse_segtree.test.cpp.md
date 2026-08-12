---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoids/affine_monoid.hpp
    title: monoids/affine_monoid.hpp
  - icon: ':heavy_check_mark:'
    path: segment_tree/sparse_segtree.hpp
    title: segment_tree/sparse_segtree.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_set_range_composite_large_array
    links:
    - https://judge.yosupo.jp/problem/point_set_range_composite_large_array
  bundledCode: "#line 1 \"test/segment_tree/sparse_segtree.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/point_set_range_composite_large_array\"\n\n\
    #line 1 \"segment_tree/sparse_segtree.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <cstdint>\n#include <vector>\n\n// https://suisen-cp.github.io/cp-library-cpp/library/datastructure/segment_tree/sparse_segment_tree.hpp\n\
    template <typename IndexType, // type of index\n          typename S,        \
    \ // type of element\n          auto op,            // S op(S a, S b)\n      \
    \    auto e,             // S e()\n          auto init = [](IndexType, IndexType)\
    \ { return e(); }\n          // (l, r) -> init[l] * init[l+1] * ... * init[r-1]\n\
    \          >\nstruct sparse_segtree {\n    using index_type = IndexType;\n   \
    \ using value_type = S;\n\nprivate:\n    using pool_index_type = uint32_t;\n\n\
    \    struct Node {\n        pool_index_type ch[2]{0, 0};\n        value_type dat;\n\
    \        Node(const value_type &dat_) : dat(dat_) {}\n    };\n\n    static inline\
    \ std::vector<Node> pool{Node{e()}};\n\n    static pool_index_type new_node(const\
    \ value_type &dat) {\n        const pool_index_type res = static_cast<pool_index_type>(pool.size());\n\
    \        return pool.emplace_back(dat), res;\n    }\n\npublic:\n    sparse_segtree()\
    \ : sparse_segtree(0) {}\n    explicit sparse_segtree(IndexType n_) : n(n_), root(new_node(init(0,\
    \ n))) {}\n\n    static void reserve(int siz) { pool.reserve(siz); }\n\n    value_type\
    \ get(index_type i) const {\n        assert(0 <= i and i < n);\n        pool_index_type\
    \ cur = root;\n        for (index_type l = 0, r = n; cur and r - l > 1;) {\n \
    \           index_type m = l + (r - l) / 2;\n            if (i < m)\n        \
    \        cur = pool[cur].ch[0], r = m;\n            else\n                cur\
    \ = pool[cur].ch[1], l = m;\n        }\n        return get(cur, i, i + 1);\n \
    \   }\n    template <typename Fun> void apply_fun(index_type i, Fun &&fun) {\n\
    \        assert(0 <= i and i < n);\n        auto rec = [&](auto self, pool_index_type\
    \ cur, index_type l, index_type r) -> void {\n            if (r - l == 1) {\n\
    \                pool[cur].dat = fun(get(cur, l, r));\n                return;\n\
    \            }\n            const index_type m = l + (r - l) / 2;\n          \
    \  if (i < m)\n                self(self, get_or_create_child(cur, 0, l, m), l,\
    \ m);\n            else\n                self(self, get_or_create_child(cur, 1,\
    \ m, r), m, r);\n            pool[cur].dat = op(get(pool[cur].ch[0], l, m), get(pool[cur].ch[1],\
    \ m, r));\n        };\n        rec(rec, root, 0, n);\n    }\n    void set(index_type\
    \ i, const value_type &val) {\n        apply_fun(i, [&val](const value_type &)\
    \ { return val; });\n    }\n\n    value_type operator()(index_type l, index_type\
    \ r) const {\n        assert(0 <= l and l <= r and r <= n);\n        return query(root,\
    \ l, r, 0, n);\n    }\n    value_type prod(index_type l, index_type r) const {\
    \ return (*this)(l, r); }\n    value_type all_prod() const { return pool[root].dat;\
    \ }\n\nprivate:\n    index_type n;\n    pool_index_type root;\n\n    value_type\
    \ get(pool_index_type node, index_type tl, index_type tr) const {\n        return\
    \ node ? pool[node].dat : init(tl, tr);\n    }\n\n    pool_index_type get_or_create_child(pool_index_type\
    \ node, int index, index_type tl,\n                                        index_type\
    \ tr) {\n        if (pool[node].ch[index])\n            return pool[node].ch[index];\n\
    \        const pool_index_type ch = new_node(init(tl, tr));\n        return pool[node].ch[index]\
    \ = ch;\n    }\n\n    value_type query(pool_index_type node, index_type ql, index_type\
    \ qr, index_type tl,\n                     index_type tr) const {\n        if\
    \ (tr <= ql or qr <= tl)\n            return e();\n        if (not node)\n   \
    \         return init(std::max(ql, tl), std::min(qr, tr));\n        if (ql <=\
    \ tl and tr <= qr)\n            return pool[node].dat;\n        const index_type\
    \ tm = tl + (tr - tl) / 2;\n        return op(query(pool[node].ch[0], ql, qr,\
    \ tl, tm), query(pool[node].ch[1], ql, qr, tm, tr));\n    }\n};\n\n\n#line 1 \"\
    monoids/affine_monoid.hpp\"\n\n\n\ntemplate <typename Z> struct AffineMonoid {\n\
    \    static AffineMonoid op(AffineMonoid f, AffineMonoid g) {\n        auto [a,\
    \ b] = f;\n        auto [c, d] = g;\n        return {c * a, c * b + d};\n    }\n\
    \    static AffineMonoid e() { return {1, 0}; }\n    Z a, b;\n};\n\n\n#line 5\
    \ \"test/segment_tree/sparse_segtree.test.cpp\"\n#include <atcoder/modint>\n#include\
    \ <bits/stdc++.h>\nusing Z = atcoder::modint998244353;\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N, Q;\n    std::cin >> N >> Q;\n    using S = AffineMonoid<Z>;\n    sparse_segtree<int,\
    \ S, S::op, S::e> seg(N);\n    while (Q--) {\n        int t;\n        std::cin\
    \ >> t;\n        if (t == 0) {\n            int p, c, d;\n            std::cin\
    \ >> p >> c >> d;\n            seg.set(p, {c, d});\n        } else {\n       \
    \     int l, r, x;\n            std::cin >> l >> r >> x;\n            auto [a,\
    \ b] = seg.prod(l, r);\n            auto ans = a * x + b;\n            std::cout\
    \ << ans.val() << \"\\n\";\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_composite_large_array\"\
    \n\n#include \"segment_tree/sparse_segtree.hpp\"\n#include \"monoids/affine_monoid.hpp\"\
    \n#include <atcoder/modint>\n#include <bits/stdc++.h>\nusing Z = atcoder::modint998244353;\n\
    \nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int N, Q;\n    std::cin\
    \ >> N >> Q;\n    using S = AffineMonoid<Z>;\n    sparse_segtree<int, S, S::op,\
    \ S::e> seg(N);\n    while (Q--) {\n        int t;\n        std::cin >> t;\n \
    \       if (t == 0) {\n            int p, c, d;\n            std::cin >> p >>\
    \ c >> d;\n            seg.set(p, {c, d});\n        } else {\n            int\
    \ l, r, x;\n            std::cin >> l >> r >> x;\n            auto [a, b] = seg.prod(l,\
    \ r);\n            auto ans = a * x + b;\n            std::cout << ans.val() <<\
    \ \"\\n\";\n        }\n    }\n}\n"
  dependsOn:
  - segment_tree/sparse_segtree.hpp
  - monoids/affine_monoid.hpp
  isVerificationFile: true
  path: test/segment_tree/sparse_segtree.test.cpp
  requiredBy: []
  timestamp: '2026-08-12 17:52:00+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/segment_tree/sparse_segtree.test.cpp
layout: document
redirect_from:
- /verify/test/segment_tree/sparse_segtree.test.cpp
- /verify/test/segment_tree/sparse_segtree.test.cpp.html
title: test/segment_tree/sparse_segtree.test.cpp
---
